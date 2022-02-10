#include "AFN.h"

std::istream& operator>>(std::istream& in, AFN& afn)
{
	std::string buffer, stare, sig, buff;
	std::getline(in, buffer);
	std::istringstream iss(buffer);
	while (iss >> stare)
	{
		afn.stari.push_back(stare);
	}
	buffer.clear();
	sig.clear();
	stare.clear();
	std::getline(in, buffer);
	std::istringstream is(buffer);
	while (is >> sig)
	{
		afn.sigma += sig;
	}
	buffer.clear();
	sig.clear();
	std::getline(in, buffer);
	std::istringstream isss(buffer);
	while (isss >> sig)
	{
		afn.finale.push_back(sig);
	}
	buffer.clear();
	sig.clear();
	char lit;
	in >> afn.StareInit;
	in >> afn.nr_tranzitii;

	for (int index = 0; index < afn.nr_tranzitii; index++)
	{
		in >> buffer >> lit >> stare;
		std::pair<char, std::string> pairs;
		pairs = std::make_pair(lit, stare);
		afn.delta[buffer].push_back(pairs);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, AFN afn)
{
	out << "Acestea sunt starile: ";
	for (int index = 0; index < afn.stari.size(); index++)
	{
		out << afn.stari[index] << " ";
	}
	out << '\n';
	out << "Alfabetul de intrare este urmatorul: ";
	for (int index = 0; index < afn.sigma.size(); index++)
	{
		out << afn.sigma[index] << " ";
	}
	out << '\n';
	out << "Starea initiala este: " << afn.StareInit;
	out << '\n';
	out << "Multimea starilor finale este urmatoarea: ";
	for (int index = 0; index < afn.finale.size(); index++)
	{
		out << afn.finale[index] << " ";
	}
	out << '\n';
	out << "AFN-ul are urmatoarele tranzitii: ";
	out << '\n';
	for (auto ind : afn.delta)
	{
		for (auto& ind1 : ind.second)
			std::cout <<"(" << ind.first << "," << ind1.first << ")-> " << ind1.second << '\n';

	}

	return out;
}

AFN::AFN()
{
	sigma = "";
	StareInit = "";
	nr_tranzitii = 0;
}
AFN::AFN(std::vector<std::string> stari1, std::string sigma1, std::vector<std::string> finale1, std::string StareInit1, int nr_tranzitii1, std::unordered_map<std::string, std::vector<std::pair<char, std::string>>> delta1) :stari{ stari1 }, sigma{ sigma1 }, finale{ finale1 }, StareInit{ StareInit1 }, nr_tranzitii{ nr_tranzitii1 }, delta{ delta1 }
{
}

bool AFN::regula1()
{
	if (std::find(stari.begin(), stari.end(), StareInit) == stari.end())
		return false;
	return true;
}

bool AFN::regula2()
{
	for (auto ind : finale)
	{
		if (std::find(stari.begin(), stari.end(), ind) == stari.end())
			return false;
	}
	return true;
}


bool AFN::regula3()
{
	for (auto ind : delta)
	{
		if (find(stari.begin(), stari.end(), ind.first) == stari.end())
			return false;
		for (auto& ind1 : ind.second)
		{
			if (find(stari.begin(), stari.end(), ind1.second) == stari.end() || sigma.find(ind1.first) == std::string::npos)
				return false;
		}
	}
	return true;

}

std::string AFN::word_accepted(std::string word)
{
	std::queue<std::string> queue;
	int nrStariRezultate = 0, aux;
	for (auto& ind : delta)
	{
		if (ind.first == StareInit)
		{
			for (auto& ind1 : ind.second)
			{
				if (ind1.first == word[0])
				{
					queue.push(ind1.second);
					nrStariRezultate++;
				}
			}
		}
	}
	word.erase(0, 1);
	while (!queue.empty())
	{
		aux = 0;
		for (int index1 = 0; index1 < nrStariRezultate; index1++)
		{
			for (auto index2 : delta)
			{
				if (queue.front() == index2.first)
				{
					for (auto ind3 : index2.second)
						if (word[0] == ind3.first)
						{
							aux++;
							queue.push(ind3.second);
						}
				}
			}
			if (word.size() == 0)
				if (std::find(finale.begin(), finale.end(), queue.front()) != finale.end())
					return "acceptat";
			queue.pop();
		}
		nrStariRezultate = aux;
		word.erase(0, 1);
	}
	return "neacceptat";
}



void AFN::verificare()
{
	if (regula1() == false)
	{
		std::cout << "Starea initiala nu se gaseste in automat\n";
	}
	if (regula2() == false)
	{
		std::cout << "Starile finale nu se gasesc in automat\n";
	}
	if (regula3() == false)
	{
		std::cout << "Tranzitiile nu contin doar elemente ale automatului\n";
	}
	if (regula1() == true && regula2() == true && regula3() == true)
	{
		std::cout << "Automatul este ok";
	}
}

