#include "../digraph.h"
#include <iostream>
#include <chrono>
#include <vector>
#include <random>

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
	int erreur = 0, n = 10000, som = 0;
	Digraph<int> star;
	std::vector<int> poids;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.0, 100.0);
	for (int i = 0; i < n; i++)
	{
		int var = int(dist(mt) * 1000);
		star.inserer(0, i + 1, var);
		poids.push_back(var);
		som += var;
	}
	Chrono timer;
	timer.debut();
	if (star.sommets() != n + 1 || star.arcs() != n)
		erreur++;
	if (star.pret(0) != som || star.dette(0) != 0)
		erreur++;
	for (int i = 0; i < n; i++)
		if (star.dette(i + 1) != poids[i] || star.pret(i + 1) != 0)
			erreur++;
	for (int i = 0; i < n; i++)
		star.reduire(i + 1);
	star.reduire(0);
	if (star.sommets() != n + 1 || star.arcs() != n)
		erreur++;
	if (star.pret(0) != som || star.dette(0) != 0)
		erreur++;
	timer.fin();
	if (erreur != 0 || timer.duree > 10000000)
	{
		std::cerr << RED << "ECHEC - PERFORMANCES" << RESET << std::endl;
		return erreur;
	}
	std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return 0;
}
