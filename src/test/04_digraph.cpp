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
	int erreur = 0, n = 5000;
	Digraph<int> path;
	std::vector<int> poids;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.0, 100.0);
	for (int i = 0; i < n; i++)
	{
		int var = int(dist(mt) * 1000);
		path.inserer(i, i + 1, var);
		poids.push_back(var);
	}
	Chrono timer;
	timer.debut();
	if (path.sommets() != n + 1 || path.arcs() != n)
		erreur++;
	for (int i = 1; i < n; i++)
		if (path.pret(i) != poids[i] || path.dette(i + 1) != poids[i])
			erreur++;
	for (int i = 1; i < n; i += 50)
		path.reduire(i);
	if (path.sommets() != n + 1 || path.arcs() != n)
		erreur++;
	for (int i = 1; i < n; i++)
		if (path.pret(i) != poids[i] || path.dette(i + 1) != poids[i])
			erreur++;
	timer.fin();
	if (erreur != 0 || timer.duree > 7000000)
	{
		std::cerr << RED << "ECHEC - PERFORMANCES" << RESET << std::endl;
		return erreur;
	}
	std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return 0;
}
