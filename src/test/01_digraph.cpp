#include "../digraph.h"
#include <iostream>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"

int main()
{
	int erreur = 0, som = 15, arr = 34;
	Digraph<std::string> graphe;
	std::string vertices[] = {"BIC", "BMO", "BNP", "ATB", "BEA", "AXA", "NBG",
							  "BOC", "RBC", "BOA", "LCL", "BNS", "CIC", "BNC", "ING"};
	std::string arcs[] = {"NBG", "LCL", "NBG", "AXA", "LCL", "RBC", "LCL", "BOA",
						  "LCL", "BNS", "BNS", "BOA", "BNS", "BIC", "BNS", "CIC", "CIC", "LCL",
						  "CIC", "ING", "ATB", "CIC", "ATB", "BIC", "ATB", "BNP", "ING", "ATB",
						  "ING", "BNC", "BNC", "NBG", "BNC", "BEA", "BOC", "NBG", "BOC", "AXA",
						  "BNP", "BMO", "BNP", "BEA", "BIC", "BMO", "BIC", "BNP", "BMO", "BOA",
						  "BMO", "NBG", "BMO", "AXA", "BOA", "RBC", "BOA", "NBG", "RBC", "NBG",
						  "BEA", "AXA", "BEA", "BOC", "BEA", "ING", "BEA", "ATB", "AXA", "BNP"};
	double emprunts[] = {5320, 1500, 4420, 3900, 8010, 6370, 5320, 2313, 5500, 4200,
						 7622, 1700, 3050, 1700, 1302, 4710, 4500, 1740, 2200, 4000, 5000, 3012, 3220,
						 2410, 3240, 3440, 5100, 7400, 3800, 1100, 3900, 9390, 2100, 9200};
	for (int i = 0; i < som; i++)
		graphe.inserer(vertices[i]);
	if (graphe.sommets() != som)
	{
		std::cerr << RED << RED << "ECHEC - I" << RESET << std::endl;
		erreur++;
	}
	if (graphe.arcs() != 0)
	{
		std::cerr << RED << "ECHEC - II" << RESET << std::endl;
		erreur++;
	}
	for (int i = 0, j = 0; i < arr && j < 2 * arr; i++, j += 2)
		graphe.inserer(arcs[j], arcs[j + 1], emprunts[i]);
	if (graphe.sommets() != som)
	{
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
		erreur++;
	}
	if (graphe.arcs() != arr)
	{
		std::cerr << RED << "ECHEC - IV" << RESET << std::endl;
		erreur++;
	}
	int old_erreur = erreur;
	for (int i = 0; i < som; i++)
		if (!graphe.sommet(vertices[i]))
			erreur++;
	if (old_erreur != erreur)
	{
		std::cerr << RED << "ECHEC - V" << RESET << std::endl;
		erreur++;
	}
	old_erreur = erreur;
	for (int i = 0; i < 2 * arr; i += 2)
		if (!graphe.arc(arcs[i], arcs[i + 1]) || graphe.arc(arcs[i + 1], arcs[i]))
			erreur++;
	if (old_erreur != erreur)
	{
		std::cerr << RED << "ECHEC - VI" << RESET << std::endl;
		erreur++;
	}
	std::string pas_arcs[] = {"BOC", "BNC", "AXA", "BNC", "RBC", "BMO", "BOA", "BNP", "BOA", "BIC", "NBG", "BNP", "BNP", "CIC"};
	old_erreur = erreur;
	for (int i = 0; i < 14; i += 2)
		if (graphe.arc(pas_arcs[i], pas_arcs[i + 1]))
			erreur++;
	if (old_erreur != erreur)
	{
		std::cerr << RED << "ECHEC - VII" << RESET << std::endl;
		erreur++;
	}
	Digraph<int> digraph;
	for (int i = 0; i < 1024; i++)
		digraph.inserer(i);
	if (digraph.sommets() != 1024)
	{
		std::cerr << RED << "ECHEC - VIII" << RESET << std::endl;
		erreur++;
	}
	if (digraph.arcs() != 0)
	{
		std::cerr << RED << "ECHEC - IX" << RESET << std::endl;
		erreur++;
	}
	for (int i = 10; i < 1000; i += 10)
		for (int j = 1; j < 10; j++)
		{
			digraph.inserer(i, i + j, 3105.3173);
			digraph.inserer(i, i - j, 3173.3105);
		}
	if (digraph.sommets() != 1024)
	{
		std::cerr << RED << "ECHEC - X" << RESET << std::endl;
		erreur++;
	}
	if (digraph.arcs() != 1782)
	{
		std::cerr << RED << "ECHEC - XI" << RESET << std::endl;
		erreur++;
	}
	for (int i = 0; i < 1024; i++)
		digraph.inserer(i);

	for (int i = 10; i < 1000; i += 10)
		for (int j = 1; j < 10; j++)
		{
			digraph.inserer(i, i + j, 3105.3173);
			digraph.inserer(i, i - j, 3173.3105);
		}
	if (digraph.sommets() != 1024 || digraph.arcs() != 1782)
	{
		std::cerr << RED << "ECHEC - XII" << RESET << std::endl;
		erreur++;
	}
	if (erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
