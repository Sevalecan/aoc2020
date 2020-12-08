#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>

int main()
{
	using namespace std;
	std::vector<string> pwds;
	int valid = 0;


	fstream data("input2.txt", std::fstream::in | std::fstream::out);

	std::string line;
	int count = data.gcount();
	while (data.good())
	{
		getline(data, line);
		if (line.size() > 0)
		{
			pwds.push_back(line);
		}
	}

	string delimiter = ": ";
	for (auto pwd : pwds)
	{
		string cond = pwd.substr(0, pwd.find(delimiter));
		string after = pwd.substr(pwd.find(delimiter)+delimiter.length(), string::npos);

		int temp = cond.find(" ");
		char ltr = cond[temp+1];
		string range = cond.substr(0, temp);
		temp = range.find("-");
		
		cout << range << endl;
		int min = stoi(range.substr(0, temp));
		int max = stoi(range.substr(temp+1, string::npos));

		int count = 0;
		for (char const &c: after)
		{
			if (c == ltr) count++;
		}

		/* Part1
		if (count >= min and count <= max)
			valid++;
			*/

		bool hf = (after[min-1] == ltr);
		bool hs = (after[max-1] == ltr);

		if (!hf != !hs)
			valid++;

	}


	cout << "Valid pwds: " << valid << endl;

	return 0;
}

