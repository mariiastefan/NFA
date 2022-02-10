#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <sstream>
#include <queue>

class AFN {
private:
	std::vector<std::string> stari;
	std::string sigma;
	std::vector<std::string> finale;
	std::string StareInit;
	std::unordered_map<std::string,std::vector<std::pair<char, std::string>>> delta;
	int nr_tranzitii;
	friend std::istream& operator >> (std::istream& in, AFN& afn);
	friend std::ostream& operator <<(std::ostream& out, AFN afn);
public:
	AFN();
	AFN(std::vector<std::string> stari1, std::string sigma1, std::vector<std::string> finale1, std::string StareInit1, int nr_tranzitii1, std::unordered_map<std::string, std::vector<std::pair<char, std::string>>> delta1);
	void verificare();
	bool regula1();
	bool regula2();
	bool regula3();
	std::string word_accepted(std::string cuvant);
};
