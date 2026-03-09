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
	int erreur = 0, n = 5000, arc = 0;
	Digraph<int> cycle;
	std::vector<int> poids;
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(1.0, 100.0);
	for (int i = 0; i <= n; i++)
	{
		int var = int(dist(mt) * 10000);
		if (var % 5 == 0)
		{
			var = 3105;
			arc++;
		}
		cycle.inserer(i % (n + 1), (i + 1) % (n + 1), var);
		poids.push_back(var);
	}
	Chrono timer;
	timer.debut();
	if (cycle.sommets() != n + 1 || cycle.arcs() != n + 1)
		erreur++;
	Digraph<int> ctrl_c = cycle;
	Digraph<int> ctrl_v = cycle;
	ctrl_c.reduire(1000);
	ctrl_v.reduire(2000);
	if (ctrl_c.arcs() != ctrl_c.arcs() || ctrl_c.arcs() != n + 1 - arc)
		erreur++;
	for (int i = 0; i <= n; i++)
		if (ctrl_c.arc(i % (n + 1), (i + 1) % (n + 1)) != ctrl_v.arc(i % (n + 1), (i + 1) % (n + 1)))
			erreur++;
	timer.fin();
	if (erreur != 0 || timer.duree > 70000)
	{
		std::cerr << RED << "ECHEC - PERFORMANCES" << RESET << std::endl;
		return erreur;
	}
	std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return 0;
}
