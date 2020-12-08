#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <functional>
#include <regex>
#include <set>

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

int main(int argc, char *argv[])
{
	vector<string> args;

	cout << "Argc: " << argc << endl;

	for (int x = 0; x < argc; x++)
		args.push_back(argv[x]);

	vector<string> rows;
	string inputfile = "input5.txt";
	if (argc > 1)
		inputfile = "input5t.txt";
	fstream data(inputfile, fstream::in);

	while (data.good())
	{
		string line;
		getline(data, line);
		rows.push_back(line);
	}

	map<char, int> nums{
		{'L', 0},
		{'F', 0},
		{'B', 1},
		{'R', 1}
	};

	int max = 0;
	int min = 0xFFFFFF;
	set<int> seats;

	for (auto x: rows)
	{
		int num = 0;
		for (auto y = 0; y < x.size(); y++)
		{
			num = (num << 1) + nums[x[y]];
		}
//		cout << "Seat ID: " << num << endl;
		seats.insert(num);
		if (num > max)
			max = num;
		if (num < min)
			min = num;
	}

	cout << "Max Seat ID: " << max << endl;

	for (auto x: seats)
	{
		cout << x << endl;
	}

	for (int x = min+1; x < max; x++)
	{
		if (!seats.contains(x))
		{
			cout << "Missing seat " << x << endl;
		}
	}

	return 0;
}
