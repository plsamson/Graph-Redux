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
	for (int i = 0, j = 0; i < arr && j < 2 * arr; i++, j += 2)
		graphe.inserer(arcs[j], arcs[j + 1], emprunts[i]);

	if (graphe.sommets() != som)
	{
		std::cerr << RED << "ECHEC - I" << RESET << std::endl;
		erreur++;
	}
	if (graphe.arcs() != arr)
	{
		std::cerr << RED << "ECHEC - II" << RESET << std::endl;
		erreur++;
	}
	graphe.reduire("BNP");
	if (graphe.sommets() != som)
	{
		std::cerr << RED << "ECHEC - III" << RESET << std::endl;
		erreur++;
	}
	if (graphe.arcs() != arr - 7)
	{
		std::cerr << RED << "ECHEC - IV" << RESET << std::endl;
		erreur++;
	}
	if (graphe.arc("BNP", "BMO") ||
		graphe.arc("BNP", "BEA") ||
		graphe.arc("NBG", "AXA") ||
		graphe.arc("BEA", "AXA") ||
		graphe.arc("ATB", "BIC") ||
		graphe.arc("BEA", "ATB") ||
		graphe.arc("BMO", "AXA"))
	{
		std::cerr << RED << "ECHEC - V" << RESET << std::endl;
		erreur++;
	}
	if (graphe.dette("BNP") != 2460 + 1360 + 2650)
	{
		std::cerr << RED << "ECHEC - VI" << RESET << std::endl;
		erreur++;
	}
	if (graphe.pret("BNP") != 0)
	{
		std::cerr << RED << "ECHEC - VII" << RESET << std::endl;
		erreur++;
	}
	Digraph<std::string> bigraph;
	bigraph.inserer("A");
	bigraph.inserer("B");
	bigraph.reduire("A");
	if (bigraph.sommets() != 2 || bigraph.arcs() != 0)
	{
		std::cerr << RED << "ECHEC - VIII" << RESET << std::endl;
		erreur++;
	}
	bigraph.reduire("B");
	if (bigraph.sommets() != 2 || bigraph.arcs() != 0)
	{
		std::cerr << RED << "ECHEC - IX" << RESET << std::endl;
		erreur++;
	}
	bigraph.inserer("A", "B", 3105);
	bigraph.reduire("A");
	if (bigraph.sommets() != 2 || bigraph.arcs() != 1)
	{
		std::cerr << RED << "ECHEC - X" << RESET << std::endl;
		erreur++;
	}
	bigraph.inserer("B", "A", 3105);
	bigraph.reduire("B");
	if (bigraph.sommets() != 2 || bigraph.arcs() != 0)
	{
		std::cerr << RED << "ECHEC - XI" << RESET << std::endl;
		erreur++;
	}
	Digraph<int> grogu;
	for (int i = 0; i < 10000; i++)
		grogu.inserer(i, i + 1, (i + 1) * (i + 1));
	int old_erreur = erreur;
	for (int i = 0; i < 10000; i += 1000)
	{
		grogu.reduire(i);
		if (grogu.arcs() != 10000)
			erreur++;
	}
	if (old_erreur != erreur)
	{
		std::cerr << RED << "ECHEC - XII" << RESET << std::endl;
		erreur++;
	}
	grogu.inserer(10000, 0, 0.5);
	Digraph<int> clone(grogu), cloone(grogu), clooone(grogu), cloooone(grogu);
	clone.reduire(0);
	cloone.reduire(100);
	clooone.reduire(1000);
	cloooone.reduire(10000);
	if (clone.arcs() != 10000 ||
		cloone.arcs() != 10000 ||
		clooone.arcs() != 10000 ||
		cloooone.arcs() != 10000 ||
		clone.arc(10000, 0) ||
		cloone.arc(10000, 0) ||
		clooone.arc(10000, 0) ||
		cloooone.arc(10000, 0))
	{
		std::cerr << RED << "ECHEC - XIII" << RESET << std::endl;
		erreur++;
	}
	Digraph<int> yoda;
	for (int j = 0; j < 10; j++)
	{
		yoda.inserer(0, j * 100 + 1, 3105);
		for (int i = 1; i < 100; i++)
			yoda.inserer((j * 100) + i, (j * 100) + i + 1, 3105);
		yoda.inserer(j * 100 + 100, 0, 3105);
	}
	if (yoda.sommets() != 1001 || yoda.arcs() != 1010)
	{
		std::cerr << RED << "ECHEC - XIV" << RESET << std::endl;
		erreur++;
	}
	old_erreur = erreur;
	for (int i = 1; i < 1000; i++)
		if (yoda.dette(i) != 3105 || yoda.pret(i) != 3105)
			erreur++;
	if (old_erreur != erreur)
	{
		std::cerr << RED << "ECHEC - XV" << RESET << std::endl;
		erreur++;
	}
	Digraph<int> luke(yoda), leia(yoda), obi(yoda);
	luke.reduire(7);
	leia.reduire(107);
	obi.reduire(207);
	if (luke.sommets() != 1001 || luke.arcs() != 909 ||
		leia.sommets() != 1001 || leia.arcs() != 909 ||
		obi.sommets() != 1001 || obi.arcs() != 909)
	{
		std::cerr << RED << "ECHEC - XV" << RESET << std::endl;
		erreur++;
	}
	luke.reduire(8);
	luke.reduire(18);
	luke.reduire(28);
	leia.reduire(108);
	leia.reduire(118);
	leia.reduire(128);
	obi.reduire(208);
	obi.reduire(218);
	obi.reduire(228);
	if (luke.sommets() != 1001 || luke.arcs() != 909 ||
		leia.sommets() != 1001 || leia.arcs() != 909 ||
		obi.sommets() != 1001 || obi.arcs() != 909 ||
		luke.dette(0) != 3105 * 9 || luke.pret(0) != 3105 * 9 ||
		leia.dette(0) != 3105 * 9 || leia.pret(0) != 3105 * 9 ||
		obi.dette(0) != 3105 * 9 || obi.pret(0) != 3105 * 9)
	{
		std::cerr << RED << "ECHEC - XVII" << RESET << std::endl;
		erreur++;
	}
	yoda.reduire(0);
	luke.reduire(0);
	leia.reduire(0);
	obi.reduire(0);
	if (yoda.sommets() != 1001 || yoda.arcs() != 0 ||
		luke.sommets() != 1001 || luke.arcs() != 0 ||
		leia.sommets() != 1001 || leia.arcs() != 0 ||
		obi.sommets() != 1001 || obi.arcs() != 0)
	{
		std::cerr << RED << "ECHEC - XVIII" << RESET << std::endl;
		erreur++;
	}
	if (erreur == 0)
		std::cout << GREEN << "\t==> OK" << RESET << std::endl;
	return erreur;
}
