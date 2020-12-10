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

struct CPU
{
	int accumulator;
	int ip;
	vector<tuple<string, int>> program;
	vector<int> lrc;

	unordered_map<string, function<void()>> instructions;

	void nop()
	{
		ip++;
	}
	void acc()
	{
		accumulator += get<1>(program[ip]);
		ip++;
	}
	void jmp()
	{
		ip += get<1>(program[ip]);
	}

	void reset()
	{
		ip = 0;
		accumulator = 0;
		lrc.clear();
		lrc.insert(lrc.begin(), program.size(), 0);
	}

	void loadProgram(std::vector<string> &lines)
	{
		program.clear();
		lrc.clear();

		program.reserve(lines.size());
		lrc.reserve(lines.size());

		lrc.insert(lrc.begin(), lines.size(), 0);

		for (int i = 0; i < lines.size(); i++)
		{
			if (lines[i].size() == 0)
				lrc.pop_back();
			else
			{
				auto sl = split(lines[i], " ");
				program.push_back({sl[0], stoi(sl[1])});
			}
		}
		ip = 0;
		accumulator = 0;
	}

	void writeProgram(string file)
	{
		fstream outf(file, fstream::out | fstream::trunc);
		for(auto &x : program)
		{

			outf <<  << endl;
		}
	}

	CPU()
	{
		using ft = function<void()>;
		instructions = decltype(instructions){
			{"nop", ft(bind(&nop, this))},
			{"acc", ft(bind(&acc, this))},
			{"jmp", ft(bind(&jmp, this))}
		};
	}

	int run()
	{
		int mrun = true;
		while (mrun)
		{
			if (ip >= program.size())
				return 0;
			if (++lrc[ip] > 1)
			{
			//	cout << "Instruction repeated on line: " << ip << endl;
			//	cout << "Value of accumulator: " << accumulator << endl;
				return -1;
			}

			string instr = get<0>(program[ip]);

			instructions[instr]();
		}
		return 0;
	}
};

int main(int argc, char *argv[])
{
	chrono::steady_clock::time_point begin, end;
	begin = chrono::steady_clock::now();
	vector<string> args;

	cout << "Argc: " << argc << endl;

	for (int x = 0; x < argc; x++)
		args.push_back(argv[x]);

	vector<string> rows;
	string inputfile = "input8.txt";
	if (argc > 1)
	{
		inputfile = "input8t.txt";
	}
	fstream data(inputfile, fstream::in);

	while (data.good())
	{
		string line;
		getline(data, line);
		rows.push_back(line);
	}

	CPU cpu;

	cpu.loadProgram(rows);

	bool run = true;
	int swapcount = 0;
	
	for (int i = 0; i < cpu.program.size() && run; i++)
	{
		auto fun = [&](string to) -> void {
			cpu.reset();
			auto lastop = cpu.program[i];
			cpu.program[i] = {to, get<1>(cpu.program[i])};

			int res = cpu.run();
			if (res == 0)
			{
				run = false;
				cout << "Final accumulator after fix: " << cpu.accumulator << endl;

			}
			cpu.program[i] = lastop;
			swapcount++;
		};

		if (get<0>(cpu.program[i]) == "nop")
		{
			fun("jmp");
		}

		else if (get<0>(cpu.program[i]) == "jmp")
		{
			fun("nop");
		}
	}

	end = chrono::steady_clock::now();

	cout << "Runtime for day 8 parts 1 and 2: " << chrono::duration_cast<chrono::microseconds>(end-begin).count() << "[μs]" << endl;
	cout << "Total swap & runs completed: " << swapcount << endl;

	return 0;
}
