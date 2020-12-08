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

bool is_number(const std::string& s)
{
	    return !s.empty() && std::find_if(s.begin(), 
			            s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main(int argc, char *argv[])
{
	vector<string> args;

	cout << "Argc: " << argc << endl;

	for (int x = 0; x < argc; x++)
		args.push_back(argv[x]);

	vector<string> rows;
	string inputfile = "input7.txt";
	if (argc > 1)
	{
#ifdef DAY1
		inputfile = "input7t.txt";
#endif
#ifdef DAY2
		inputfile = "input7t2.txt";
#endif
	}
	fstream data(inputfile, fstream::in);

	while (data.good())
	{
		string line;
		getline(data, line);
		rows.push_back(line);
	}
	const string bcontain(" bags contain ");
	const string bcomma(" bag, ");
	const string bscomma(" bag, ");
	const string bend(" bags.");
	const string bsend(" bag.");

	unordered_map<string, unordered_map<string, int>> bagtree;
	set<string> bdelim{ "bag,", "bags,", "bag.", "bags." };

	for (auto x : rows)
	{
		string topbag;
		unordered_map<string, int> subbags;
		string cbag;
		auto words = split(x, " ");
		bool first = true;
		bool checking = true;
		int bnum = 0;
		for (auto y : words)
		{
			if (y == "bags" and first)
				first = false;
			else if (y == "contain")
			{
			}
			else if (y == "no")
			{
				checking = false;
			}
			else if (!checking)
			{
				// Skip it then.
			}
			else if (first)
			{
				if (topbag.size() == 0)
				{
					topbag = y;
				}
				else
				{
					topbag.append(" ");
					topbag.append(y);
				}
			}
			else if (bdelim.contains(y))
			{
				subbags[cbag] = bnum;
				cbag.clear();
			}
			else if (is_number(y))
			{
				bnum = stoi(y);
			}
			else
			{
				if (cbag.size() == 0)
					cbag = y;
				else
				{
					cbag.append(" ");
					cbag.append(y);
				}
			}
		}
		bagtree[topbag] = subbags;
		cout << "Added " << topbag << " with " << subbags.size() << " subbags." << endl;
		for (const auto & [x,y] : subbags)
			cout << "\t" << x << ", " << y << endl;
	}

	int count = 0;

#ifdef DAY1
	set<string> nextcheck;
	set<string> checked;

	for (const auto & [top, subbags] : bagtree)
	{
		if (subbags.contains("shiny gold"))
		{
			containables.insert(top);
		}
	}

	cout << "num containables " << containables.size() << endl;

	while (!containables.empty())
	{
		set<string> newcont;
		std::set_union(checked.begin(), checked.end(), containables.begin(), containables.end(), inserter(checked, checked.begin()));

		for (const auto & [top, subbags] : bagtree)
		{
			for (const auto &x: containables)
			{
				if (subbags.contains(x))
				{
					if (!checked.contains(top))
						newcont.insert(top);
				}
			}
		}
		containables.swap(newcont);
	}

	cout << "Possible bag containments: " << checked.size() << endl;
#endif
#ifdef DAY2
	uint64_t ccount = 0;

	unordered_map<string, uint64_t> tocheck{{"shiny gold", 1}};

	while (!tocheck.empty())
	{
		unordered_map<string, uint64_t> nextcheck;
		for (const auto& [key, mult] : tocheck)
		{
			ccount += mult;
			for (auto& [newkey, newmult] : bagtree[key])
			{
				if (nextcheck.contains(newkey))
					nextcheck[newkey] += newmult*mult;
				else
					nextcheck[newkey] = newmult*mult;
			}
		}
		nextcheck.swap(tocheck);
	}
	ccount -= 1;

	cout << "total bags contained in shiny gold bag: " << ccount << endl;

//	transform(bagtree.begin(), bagtree.end(), inserter(containables, containables.end()), [](auto pair) { return pair.first; });
#endif

	return 0;
}
