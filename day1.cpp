#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	using std::fstream;
	std::vector<int> listl;
	std::vector<int> listh;

	listl.reserve(1e3);
	listh.reserve(1e3);
	fstream data("input1.txt", std::fstream::in | std::fstream::out);

	std::string line;
	int count = data.gcount();
	while (data.good())
	{
		data >> line;
		if (line.size() > 0)
		{
			int num = std::stoi(line);
			if (num > 1010) listh.push_back(num);
			else listl.push_back(num);
		}
	}

	for (auto i : listl)
	{
		for (auto j : listh)
		{
			if (i+j == 2020)
			{
				std::cout << "i: " << i <<  ", j: " << j << ", mult: " << i*j << std::endl;
				goto next;
			}
		}
	}

next:

	listl.insert(listl.end(), listh.begin(), listh.end());

	for (int i = 0; i < listl.size(); ++i)
	{
		for (int j = i+1; j < listl.size(); ++j)
		{
			for (int k = j + 1; k < listl.size(); k++)
			{
				int a = listl[i], b = listl[j], c = listl[k];
				if (a+b+c == 2020)
				{
					std::cout << "a: " << a << ", b: " << b << ", c: " << c << ", mult: " << (a*b*c) << std::endl;
				}
			}
		}
	}

	return 0;
}

