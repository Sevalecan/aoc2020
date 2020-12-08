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
	string inputfile = "input6.txt";
	if (argc > 1)
		inputfile = "input6t.txt";
	fstream data(inputfile, fstream::in);

	while (data.good())
	{
		string line;
		getline(data, line);
		rows.push_back(line);
	}

	map<char, int> answers;
	int count = 0;
	int groupsize = 0;

	set<char> all;
	set<char> group;

	for (char a = 'a'; a <= 'z'; a++)
		all.insert(a);

	for (auto x : as_const(rows))
	{
		if (x.size() == 0)
		{
			for (const auto& [key, ans]: answers)
			{
				if (ans == groupsize)
					count++;
			}
			answers.clear();
			groupsize = 0;
		}
		else
		{
			groupsize++;
			for (auto y : as_const(x))
			{
				if (answers.contains(y))
				{
					answers[y]++;
				}
				else
					answers[y] = 1;
			}
		}
	}

	cout << count << endl;
	for (auto x : all)
	{
		cout << " " << x;
	}
	cout << endl;

	return 0;
}
