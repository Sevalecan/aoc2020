#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>

int main(int argc, char *argv[])
{
	using namespace std;
	vector<string> args;

	cout << "Argc: " << argc << endl;

	for (int x = 0; x < argc; x++)
		args.push_back(argv[x]);

	vector<string> rows;
	string inputfile = "input3.txt";
	if (argc > 1)
		inputfile = "input3t.txt";
	fstream data(inputfile, fstream::in);

	while (data.good())
	{
		string line;
		getline(data, line);
		rows.push_back(line);
	}
	
	auto treecheck = [&](int xs, int ys) -> int
	{
		int c = 0;
		int treecount = 0;
		int rowlen = rows[0].size();

		for (int r = 0; r < rows.size(); r += ys, c+= xs)
		{
			if (rows[r][c % rowlen] == '#') treecount++;
		}

		return treecount;
	};

	vector<int> slopes = { 1, 1, 3, 1, 5, 1, 7, 1, 1, 2 };
	uint64_t total_trees = 0;

	for (int x = 0; x < slopes.size(); x+=2)
	{
		int res = treecheck(slopes[x], slopes[x+1]);
		cout << "Trees " << x/2 << ", " << res << endl;

		if (total_trees == 0)
			total_trees = res;
		else
			total_trees *= uint64_t(res);
	}

	cout << "Trees hit: " << total_trees;

	return 0;
}
