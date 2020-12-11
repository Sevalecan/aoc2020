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
	vector<string> rows2;
	string inputfile = "input11.txt";
	if (argc > 1)
	{
		inputfile = "input11t.txt";
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

	auto calcp = [&](int lx, int ly) -> int {
		int adj = 0;
		for (int mx = lx-1; mx <= lx+1; mx++)
			for (int my = ly-1; my <= ly+1; my++)
			{
				if (mx >= 0 and mx < rows[0].size() and my >= 0 and my < rows.size() and !(lx == mx and ly == my))
					if (rows[my][mx] == '#')
						adj++;
			}
		return adj;

	};

	int xs = rows[0].size();
	int ys = rows.size();

	array<tuple<int, int>, 8> dirs;
	{
		int idx = 0;
		for (int x = -1; x < 2; x++) for (int y = -1; y < 2; y++) if (x != 0 or y != 0)
				dirs[idx++] = {x, y};

		for (auto &[dx, dy]: as_const(dirs))
			cout << "Dir " << dx << "," << dy << endl;
	}

	auto calcp2 = [&](int lx, int ly) -> int {
		int adj = 0;

		for (auto [dx, dy]: dirs)
		{
			int rdx = lx+dx;
			int rdy = ly+dy;
			while (rdx >= 0 && rdx < xs && rdy >= 0 && rdy < ys)
			{
				if (rows[rdy][rdx] == '#')
				{
					adj++;
					goto calcp2n;
				}
				else if (rows[rdy][rdx] == 'L')
					goto calcp2n;
				rdx += dx;
				rdy += dy;
			}
calcp2n:;
		}

		return adj;

	};

	rows2 = rows;
	int ccount = 0;

	using sclock=chrono::steady_clock;
	sclock::time_point last = sclock::now();

	while (true)
	{
		int changed = 0;
		for (int y = 0; y < rows.size(); y++)
		{
			for (int x = 0; x < rows[y].size(); x++)
			{
				char loc = rows[y][x];
				if (loc == '#' or loc == 'L')
				{
					int adj = calcp2(x, y);
					if (adj >= 5 and loc == '#')
						(changed++, rows2[y][x] = 'L');
					else if (adj == 0 and loc == 'L')
						(changed++, rows2[y][x] = '#');
				}

			}
		}

	/*	
		for (int x = 0; x < rows.size(); x++)
			cout << rows2[x] << endl;
		cout << endl;
		*/
		

		if (changed == 0)
		{
			int occupied = 0;
			for (auto &x : rows) for (auto &y : x)
			{
				if (y == '#')
					occupied++;
			}
			cout << "Occupied seats: " << occupied << endl;
			goto part2;
		}

		rows = rows2;
	}

	part2:


	end = chrono::steady_clock::now();

	cout << "Runtime for day 11 parts 1 and 2: " << chrono::duration_cast<chrono::microseconds>(end-begin).count() << "[μs]" << endl;

	return 0;
}
