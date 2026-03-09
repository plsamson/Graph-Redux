#include "../digraph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <vector>
#include <set>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

class Chrono
{
public:
	Chrono() {}
	~Chrono() {}
	void debut()
	{
		start = std::chrono::steady_clock::now();
	}
	void fin()
	{
		end = std::chrono::steady_clock::now();
		duree = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	}
	float duree;

private:
	std::chrono::steady_clock::time_point start, end;
};

int main(int argc, char *argv[])
{
	int erreur = 0;
	Digraph<int> tutte;
	std::string line;
	std::ifstream input_graph(argv[1]);
	while (std::getline(input_graph, line) && !line.empty())
	{
		std::stringstream ss(line);
		int u, v;
		double emprunt;
		ss >> u >> v >> emprunt;
		tutte.inserer(u, v, emprunt);
	}
	std::vector<int> dettes, prets;
	std::ifstream input_dp(argv[2]);
	while (std::getline(input_dp, line) && !line.empty())
	{
		std::stringstream ss(line);
		int d, p;
		ss >> d >> p;
		dettes.push_back(d);
		prets.push_back(p);
	}
	Chrono timer;
	timer.debut();
	if (tutte.sommets() != 46 || tutte.arcs() != 69)
		erreur++;
	for (int i = 0; i < 46; i++)
	{
		if (tutte.dette(i) != dettes[i])
			erreur++;
	}
	for (int i = 0; i < 46; i++)
		if (tutte.pret(i) != prets[i])
			erreur++;
	for (int i = 0; i < 46; i++)
	{
		tutte.reduire(i);
		if (tutte.dette(i) - tutte.pret(i) != dettes[i] - prets[i])
			erreur++;
	}
	timer.fin();
	if (erreur != 0 || timer.duree > 10000)
	{
		std::cerr << RED << "ECHEC - PERFORMANCES" << RESET << std::endl;
		return erreur;
	}
	std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return 0;
}
