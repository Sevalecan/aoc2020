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
	string inputfile = "input9.txt";
	if (argc > 1)
	{
		inputfile = "input9t.txt";
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

	int plen = 25;

	auto psums = [](decltype(nums)::iterator start, decltype(nums)::iterator stop) -> set<int64_t> {
		set<int64_t> sums;
		for (auto x = start; x != stop; x++)
		{
			for (auto y = x+1; y != stop; y++)
			{
				sums.insert((*x)+(*y));
			}
		}
		return sums;
	};

	int64_t ncnum = 0;
	int64_t ncrow = 0;

	for (int x = plen; x < nums.size(); x++)
	{
		set<int64_t> sums = psums(nums.begin() + x - plen, nums.begin() + x);
		if (!sums.contains(nums[x]))
		{
			cout << "First non conforming number is " << nums[x] << " at row " << x << endl;
			ncnum = nums[x];
			goto part2;
		}
	}

part2:

	int64_t summer = 0;
	for (int x = 0; x < nums.size(); x++)
	{
		summer = 0;
		for (int y = x; y < nums.size(); y++)
		{
			summer += nums[y];
			if (summer == ncnum && nums[y] != ncnum)
			{
				cout << "Range from " << x << " to " << y << endl;
				int64_t min;
				int64_t max;

				auto z = minmax_element(nums.begin() + x, nums.begin() + y + 1);
				min = *(z.first);
				max = *(z.second);
				cout << "min: " << min << ", max: " << max << ", summed:" << (min+max) << endl;
				goto end;
			}
		}
	}
end:

	return 0;
}
