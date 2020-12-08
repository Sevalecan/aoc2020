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
	string inputfile = "input4.txt";
	if (argc > 1)
		inputfile = "input4t.txt";
	fstream data(inputfile, fstream::in);

	while (data.good())
	{
		string line;
		getline(data, line);
		rows.push_back(line);
	}

	int passstat = 0;
	int passcount = 0;
	int passtotal = 0;

	unordered_map<string, int> fields{
		make_pair("byr", 1),
		make_pair("iyr", 2),
		make_pair("eyr", 4),
		make_pair("hgt", 8),
		make_pair("hcl", 16),
		make_pair("ecl", 32),
		make_pair("pid", 64),
		make_pair("cid", 128)
	};
	auto range_check = [](string a, int low, int high) -> bool { int num = stoi(a); return num >= low && num <= high; };
	auto height_check = [](string a) -> bool {
		if (a.find("cm") != string::npos)
		{
			string cm(a.begin(), a.end()-2);
			int height = stoi(cm);
			return height >= 150 && height <= 193;
		}
		else if (a.find("in") != string::npos)
		{
			string in(a.begin(), a.end()-2);
			int height = stoi(in);
			return height >= 59 && height <= 76;
		}
		return false;
	};

	regex hair_colors("#[0-9a-f]{6}");
	cmatch m;

	auto hcl_check = [&hair_colors, &m](string a) -> bool {
		return regex_match(a, hair_colors);
	};

	set<string> eye_colors{"amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

	auto ec_check = [&eye_colors](string a) -> bool {
		return eye_colors.contains(a);
	};

	regex pid_regex("[0-9]{9}");

	std::function<bool(string)> pid_check([&pid_regex, &m] (string a) -> bool {
				return regex_match(a, pid_regex); 
			});


	unordered_map<string, function<bool(string)>> field_check = {
		{"byr", bind(range_check, placeholders::_1, 1920, 2002)},
		{"iyr", bind(range_check, placeholders::_1, 2010, 2020)},
		{"eyr", bind(range_check, placeholders::_1, 2020, 2030)},
		{"hgt", function<bool(string)>(height_check)},
		{"hcl", function<bool(string)>(hcl_check)}, // Hydrochloric acid
		{"ecl", function<bool(string)>(ec_check)},
		{"pid", pid_check}
	};


	for (int x = 0; x < rows.size(); x++)
	{
		if (rows[x].size() == 0 || x == rows.size()-1)
		{
			if ((passstat & 0x7F) == 0x7F)
				passcount++;
			passstat = 0;
		}
		else
		{
			vector<string> res = split(rows[x], " ");
			for (int y = 0; y < res.size(); y++)
			{
				vector<string> field = split(res[y], ":");
				string fname = field[0];
				string fvalue = field[1];
				if (field_check.contains(fname))
				{
					if (field_check[fname](fvalue))
					{
						passstat |= fields[field[0]];
					}
				}
			}
		}
	}

	cout << "Passing passports: " << passcount << endl;
	

	return 0;
}
