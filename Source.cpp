#include <iostream>
#include <fstream>
#include "AFN.h"

std::ifstream f("afn.txt");

int main()
{
	AFN afn;
	f >> afn;
	std::cout << afn;
	afn.verificare();
	std::cout << '\n';

	std::string word;
	std::cout << '\n';
	std::cout << "Introduceti cuvantul: ";
	bool flag = true;
	std::cout << "Daca doriti sa va opriti scrieti: stop\n";
	do
	{
		std::cin >> word;
		if (word == "stop")
		{
			break;
		}
		std::cout << afn.word_accepted(word) << '\n';
	} while (word != "stop");
	return 0;
}