#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>
#include <regex>
#include <set>
#include <chrono>

using namespace std;
vector<string> split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find (delimiter, pos_start)) != string::npos) {
		token = s.substr (pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back (token);
	}

	res.push_back (s.substr (pos_start));
	return res;
}

bool is_number(const std::string& s)
{
	    return !s.empty() && std::find_if(s.begin(), 
			            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main(int argc, char *argv[])
{
	chrono::steady_clock::time_point begin, end;
	begin = chrono::steady_clock::now();
	vector<string> args;

	cout << "Argc: " << argc << endl;

	for (int x = 0; x < argc; x++)
		args.push_back(argv[x]);

	vector<string> rows;
	string inputfile = "input10.txt";
	if (argc > 1)
	{
		inputfile = "input10t.txt";
	}
	fstream data(inputfile, fstream::in);

	while (data.good())
	{
		string line;
		getline(data, line);
		if (line.size())
		{
			rows.push_back(line);
		}
	}

	vector<int64_t> nums;

	transform(rows.begin(), rows.end(), std::back_inserter(nums), [](string x) -> int64_t { return stoll(x); });


	sort(nums.begin(), nums.end());

	int last = 0;
	int d3 = 0;
	int d1 = 0;
	for (int x = 0; x < nums.size(); x++)
	{
		if (nums[x]-last == 3)
			d3++;
		else if (nums[x]-last == 1)
			d1++;
		last = nums[x];
	}

	d3++;

	cout << "D3 differences: " << d3 << ", D1 differences: " << d1 << endl;

	cout << "Mult: " << (d3*d1) << endl;

	int64_t maxnum = *(nums.end()-1);

	function<int64_t(int64_t)> ccurs;
	unordered_map<int64_t, int64_t> branches;
	int afcalls = 0;
	int cachecalls = 0;

	ccurs = [&](int64_t line) -> int64_t {
		int64_t num;
		if (line == -1)
			num = 0;
		else num = nums[line];
		int64_t poss = 0;
		if (branches.contains(num))
		{
			cachecalls++;
			return branches[num];
		}
		afcalls++;
		if (num == maxnum) return 1;
		for (int64_t x = line+1; x < nums.size() && (nums[x] - num) <= 3; x++)
		{
			int64_t br = ccurs(x);
			poss += br;
			branches[nums[x]] = br;
		}
		return poss;
	};

	cout << "Total possibilities: " << ccurs(-1) << endl;

	end = chrono::steady_clock::now();

	cout << "Runtime for day 10 parts 1 and 2: " << chrono::duration_cast<chrono::microseconds>(end-begin).count() << "[μs]" << endl;

	cout << "Actual recursive calls: " << afcalls << endl;
	cout << "Cache calls: " << cachecalls << endl;
	cout << "Total adapters: " << nums.size() << endl;
	return 0;
}
