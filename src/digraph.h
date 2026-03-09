#ifndef __DIGRAPH_H__
#define __DIGRAPH_H__

#include <set>
#include <map>
#include <tuple>
#include <assert.h>
#include <vector>

template <class T>
class Digraph
{
public:
	// Constructeurs / Destructeur / Affectation
	Digraph();
	Digraph(const Digraph &autre);
	~Digraph();
	Digraph<T> &operator=(const Digraph<T> &autre);

	/************* Fonctions pour les caractéristiques de graphe *************/
	// Retourne le nombre de sommets du graphe courant.
	int sommets() const;
	// Retourne le nombre d'arcs du graphe courant.
	int arcs() const;
	// Retourne "true" si "u" est un sommet du graphe courant. "false" si non.
	bool sommet(T u) const;
	// Retourne "true" si "(u,v)" est un arc du graphe courant. "false" si non.
	bool arc(T u, T v) const;

	/***************************** Modificateurs *****************************/
	// Insère le sommet "u" si le graphe ne le contient pas. Ne fait rien
	// si le graphe contient déjà le sommet "u".
	void inserer(T u);

	// Créé un arc entre les sommets "u" et "v" avec le poids "emprunt",
	// si le graphe ne contient pas l'arc "(u, v)". Ne fait rien si le
	// graphe contient déjà un arc "(u,v)".
	// Conditions :
	//  - "u" doit être différent de "v",
	//  - "emprunt" doit être strictement positif,
	//    - assert si ces conditions ne sont pas satisfaites,
	//  - si l'arc "(u,v)" existe déjà, rien ne sera fait,
	//  - si l'un ou les deux sommets n'existent pas, ils sont créés.
	void inserer(T u, T v, double emprunt);

	// Supprime le sommet "u" et tous les arcs qui lui sont incidents.
	void supprimer(T u);

	// Supprime l'arc "(u, v)" si présent.
	void supprimer(T u, T v);

	/*********************** Fonctions financières ***********************/
	// Retourne le montant total que doit rembourser le sommet "u".
	double dette(T u) const;

	// Retourne le montant total des remboursements que doit recevoir
	// le sommet "u".
	double pret(T u) const;

	// Réduit les dettes circulaires du sommet "s". Voir énoncé pour détails.
	void reduire(T s);

	/******************************** Bonus *******************************/
	// Créé un sous-graphe induit par les sommets de S. Assert si un u∈S
	// n'est pas dans le graphe courant.
	Digraph<T> cooperative(std::set<T> &S) const;

	// Montant total des dettes externes vers SG (u∉SG → v∈SG)
	double dette(const Digraph<T> &SG) const;

	// Montant total des prêts internes SG vers externes (u∈SG → v∉SG)
	double pret(const Digraph<T> &SG) const;

	// Réduit les dettes circulaires internes à SG.
	void reduire(const Digraph<T> &SG);

private:
	// Représentation : map sommet -> set{(voisin, poids)}
	std::map<T, std::set<std::tuple<T, double>>> graphe;

	// Helpers de performance, détermine si noeud ne fais pas partie d'un cycle
	bool noCyclePossible(const T &start) const;
	bool noCyclePossible(const T &start, const std::set<T> &nodes) const;

	// Helpers pour détection et réduction de cycles simples
	bool findCycle(const T &start,
				   std::vector<T> &path,
				   std::vector<double> &weights);
	bool dfsCycle(const T &current,
				  const T &start,
				  std::set<T> &visited,
				  std::vector<T> &path,
				  std::vector<double> &weights);
	bool reduireUnCycle(const T &start);

	// Helpers pour cycles restreints à un sous-graphe SG
	bool findCycleRestricted(const T &start,
							 const std::set<T> &nodes,
							 std::vector<T> &path,
							 std::vector<double> &weights);
	bool dfsCycleRestricted(const T &current,
							const T &start,
							const std::set<T> &nodes,
							std::set<T> &visited,
							std::vector<T> &path,
							std::vector<double> &weights);
	bool reduireUnCycleRestricted(const T &start,
								  const std::set<T> &nodes);
};

// --- Implémentation ---

template <class T>
/**
 * Constructeur par défaut
 * Initialise un graphe vide.
 */
Digraph<T>::Digraph() : graphe()
{
}

template <class T>
/**
 * Constructeur de copie
 * Copie le contenu de "autre"
 */
Digraph<T>::Digraph(const Digraph &autre) : graphe(autre.graphe)
{
}

template <class T>
/**
 * Destructeur
 * Aucune action spécifique (std::map gère sa propre destruction)
 */
Digraph<T>::~Digraph()
{
}

template <class T>
/**
 * Opérateur d'affectation
 * Copie les donnees de "autre" si différent de soi-même.
 */
Digraph<T> &Digraph<T>::operator=(const Digraph &autre)
{
	if (this != &autre)
		graphe = autre.graphe;
	return *this;
}

template <class T>
/**
 * Retourne le nombre de sommets présents dans le graphe.
 */
int Digraph<T>::sommets() const
{
	return graphe.size();
}

template <class T>
/**
 * Retourne le nombre total d'arcs dans le graphe.
 */
int Digraph<T>::arcs() const
{
	int count = 0;
	// Parcours de chaque liste d'adjacence
	for (auto const &p : graphe)
		count += p.second.size();
	return count;
}

template <class T>
/**
 * Indique si "u" est un sommet du graphe.
 * recherche par clé = O(log V)
 */
bool Digraph<T>::sommet(T u) const
{
	return graphe.find(u) != graphe.end();
}

template <class T>
/**
 * Indique si l'arc (u->v) existe dans le graphe.
 */
bool Digraph<T>::arc(T u, T v) const
{
	auto it = graphe.find(u);
	if (it == graphe.end())
		return false;
	// Recherche linenaire dans set d'arc
	for (auto const &tpl : it->second)
		if (std::get<0>(tpl) == v)
			return true;
	return false;
}

template <class T>
/**
 * Insère le sommet "u" s'il existe pas déjà.
 */
void Digraph<T>::inserer(T u)
{
	if (!sommet(u))
		graphe[u] = {};
}

template <class T>
/**
 * Insère un arc (u->v) de poids "emprunt".
 * Conditions : u != v, emprunt > 0, pas de doublon.
 */
void Digraph<T>::inserer(T u, T v, double emprunt)
{
	assert(u != v);
	assert(emprunt > 0);
	// garantir existence des 2 sommets
	if (!sommet(u))
		graphe[u] = {};
	if (!sommet(v))
		graphe[v] = {};
	auto &edges = graphe[u];
	// Éviter doublon d'arc
	for (auto const &tpl : edges)
		if (std::get<0>(tpl) == v)
			return;
	edges.insert(std::make_tuple(v, emprunt));
}

template <class T>
/**
 * Supprime le sommet "u" et tous les arcs entrants vers "u".
 */
void Digraph<T>::supprimer(T u)
{
	if (!sommet(u))
		return;
	// supprime sommet
	graphe.erase(u);
	// supprime arcs entrants
	for (auto &p : graphe)
	{
		auto &edges = p.second;
		for (auto it = edges.begin(); it != edges.end();)
			if (std::get<0>(*it) == u)
				it = edges.erase(it);
			else
				++it;
	}
}

template <class T>
/**
 * Supprime l'arc (u→v) s'il existe.
 */
void Digraph<T>::supprimer(T u, T v)
{
	auto it = graphe.find(u);
	if (it == graphe.end())
		return;
	auto &edges = it->second;
	for (auto iter = edges.begin(); iter != edges.end(); ++iter)
	{
		if (std::get<0>(*iter) == v)
		{
			edges.erase(iter);
			return;
		}
	}
}

template <class T>
/**
 * Calcule la dette de "u": somme des poids des arcs entrants vers "u".
 */
double Digraph<T>::dette(T u) const
{
	assert(sommet(u));
	double sum = 0;
	for (auto const &p : graphe)
		for (auto const &tpl : p.second)
			if (std::get<0>(tpl) == u)
				sum += std::get<1>(tpl);
	return sum;
}

template <class T>
/**
 * Calcule le prêt de "u": somme des poids des arcs sortants de "u".
 */
double Digraph<T>::pret(T u) const
{
	assert(sommet(u));
	double sum = 0;
	auto it = graphe.find(u);
	if (it != graphe.end())
		for (auto const &tpl : it->second)
			sum += std::get<1>(tpl);
	return sum;
}

template <class T>
/**
 * Recherche un cycle simple partant de "start"
 * Remplit "path" et "weights" si un cycle est trouvé.
 */
bool Digraph<T>::findCycle(const T &start,
						   std::vector<T> &path,
						   std::vector<double> &weights)
{
	path.clear();
	weights.clear();
	std::set<T> visited;
	visited.insert(start);
	path.push_back(start);
	// initie recherche en profondeur
	return dfsCycle(start, start, visited, path, weights);
}

template <class T>
/**
 * DFS pour détecter un cycle revenant à "start"
 */
bool Digraph<T>::dfsCycle(const T &current,
						  const T &start,
						  std::set<T> &visited,
						  std::vector<T> &path,
						  std::vector<double> &weights)
{
	auto it = graphe.find(current);
	if (it == graphe.end())
		return false;
	// pour chaque arc current->v
	for (auto const &tpl : it->second)
	{
		T v = std::get<0>(tpl);
		double w = std::get<1>(tpl);
		// condition d’arret si on revient a start
		if (v == start)
		{
			path.push_back(start);
			weights.push_back(w);
			return true;
		}
		// si v non visité, on plonge plus profond
		if (visited.insert(v).second)
		{
			path.push_back(v);
			weights.push_back(w);
			if (dfsCycle(v, start, visited, path, weights))
				return true;
			// backtrack si ca aboutit pas
			path.pop_back();
			weights.pop_back();
		}
	}
	return false;
}

template <class T>
/**
 * Réduit un seul cycle simple partant de "start"
 * Soustrait la plus petite dette et supprime les arcs à poids nul.
 */
bool Digraph<T>::reduireUnCycle(const T &start)
{
	// Call helper de performance
	if (noCyclePossible(start))
		return false;
	std::vector<T> path;
	std::vector<double> weights;
	path.reserve(graphe.size()); // pour éviter des réallocations couteuses lors du DFS
	weights.reserve(graphe.size());
	if (!findCycle(start, path, weights))
		return false;
	// recherche du minimum m dans les poids du cycle
	double m = weights.front();
	for (double w : weights)
		if (w < m)
			m = w;
	// Soustrait m à chaque arc, supprime si null
	for (std::size_t i = 0; i + 1 < path.size(); ++i)
	{
		T u = path[i];
		T v = path[i + 1];
		auto &edges = graphe[u];
		for (auto it = edges.begin(); it != edges.end(); ++it)
		{
			if (std::get<0>(*it) == v)
			{
				double neww = std::get<1>(*it) - m;
				if (neww > 0)
					edges.insert(std::make_tuple(v, neww));
				edges.erase(it);
				break;
			}
		}
	}
	return true;
}

template <class T>
/**
 * Réduit tous les cycles simples partant de "s" jusqu'a épuisement.
 */
void Digraph<T>::reduire(T s)
{
	assert(sommet(s));
	// répète jusqu’a impossibilité de réduire
	// (tant que l'appel reduireUnCycle est true)
	while (reduireUnCycle(s))
	{
	}
}

template <class T>
/**
 * Recherche un cycle restreint à l'ensemble "nodes"
 */
bool Digraph<T>::findCycleRestricted(const T &start,
									 const std::set<T> &nodes,
									 std::vector<T> &path,
									 std::vector<double> &weights)
{
	path.clear();
	weights.clear();
	std::set<T> visited;
	visited.insert(start);
	path.push_back(start);
	// initie DFS en restreignant les etapes à "nodes"
	return dfsCycleRestricted(start, start, nodes, visited, path, weights);
}

template <class T>
/**
 * DFS pour cycle restreint aux sommets de "nodes"
 */
bool Digraph<T>::dfsCycleRestricted(const T &current,
									const T &start,
									const std::set<T> &nodes,
									std::set<T> &visited,
									std::vector<T> &path,
									std::vector<double> &weights)
{
	auto it = graphe.find(current);
	if (it == graphe.end())
		return false;
	for (auto const &tpl : it->second)
	{
		T v = std::get<0>(tpl);
		double w = std::get<1>(tpl);
		if (nodes.find(v) == nodes.end())
			continue; // skip si hors SG
		if (v == start)
		{
			path.push_back(start);
			weights.push_back(w);
			return true;
		}
		if (visited.insert(v).second)
		{
			path.push_back(v);
			weights.push_back(w);
			if (dfsCycleRestricted(v, start, nodes, visited, path, weights))
				return true;
			path.pop_back();
			weights.pop_back();
		}
	}
	return false;
}

template <class T>
/**
 * Réduit un cycle simple restreint à "nodes"
 */
bool Digraph<T>::reduireUnCycleRestricted(const T &start,
										  const std::set<T> &nodes)
{
	// Call helper de performance
	if (noCyclePossible(start, nodes))
		return false;
	std::vector<T> path;
	std::vector<double> weights;
	path.reserve(graphe.size()); // pour éviter des réallocations couteuses lors du DFS
	weights.reserve(graphe.size());
	if (!findCycleRestricted(start, nodes, path, weights))
		return false;
	// Détermination de la plus petite dette du cycle restreint
	double m = weights.front();
	for (double w : weights)
		if (w < m)
			m = w;
	// soustraction de m à chaque arc du cycle, suppression si null
	for (std::size_t i = 0; i + 1 < path.size(); ++i)
	{
		T u = path[i];
		T v = path[i + 1];
		auto &edges = graphe[u];
		for (auto it = edges.begin(); it != edges.end(); ++it)
		{
			if (std::get<0>(*it) == v)
			{
				double neww = std::get<1>(*it) - m;
				if (neww > 0)
					edges.insert(std::make_tuple(v, neww));
				edges.erase(it);
				break;
			}
		}
	}
	return true;
}

template <class T>
/**
 * Réduit tous les cycles internes au sous-graphe "SG".
 */
void Digraph<T>::reduire(const Digraph<T> &SG)
{
	std::set<T> nodes;
	for (auto const &p : SG.graphe)
		nodes.insert(p.first);
	// applique réduction restreinte sur chaque sommet
	for (auto const &s : nodes)
		// tant que l'appel de reduireUnCycleRestricted renvoie true
		while (reduireUnCycleRestricted(s, nodes))
		{
		}
}

template <class T>
/**
 * Construit le sous-graphe induit par l'ensemble "S"
 */
Digraph<T> Digraph<T>::cooperative(std::set<T> &S) const
{
	for (auto const &u : S)
		assert(sommet(u));
	Digraph<T> res;
	for (auto const &u : S)
		res.inserer(u);
	// seulement les arcs u->v avec u,v ∈ S
	for (auto const &u : S)
	{
		auto it = graphe.find(u);
		if (it == graphe.end())
			continue;
		for (auto const &tpl : it->second)
		{
			T v = std::get<0>(tpl);
			double w = std::get<1>(tpl);
			if (S.find(v) != S.end())
				res.inserer(u, v, w);
		}
	}
	return res;
}

template <class T>
/**
 * Calcule la dette du sous-graphe "SG" envers les sommets externes
 */
double Digraph<T>::dette(const Digraph<T> &SG) const
{
	double sum = 0;
	// additionne arcs externes entrant dans SG
	for (auto const &p : graphe)
	{
		if (SG.sommet(p.first))
			continue;
		for (auto const &tpl : p.second)
		{
			T v = std::get<0>(tpl);
			double w = std::get<1>(tpl);
			if (SG.sommet(v))
				sum += w;
		}
	}
	return sum;
}

template <class T>
/**
 * Calcule le pret du sous-graphe "SG" envers les sommets externes
 */
double Digraph<T>::pret(const Digraph<T> &SG) const
{
	double sum = 0;
	// additionne arcs sortants de SG vers l’extérieur
	for (auto const &p : SG.graphe)
	{
		auto it = graphe.find(p.first);
		if (it == graphe.end())
			continue;
		for (auto const &tpl : it->second)
		{
			T v = std::get<0>(tpl);
			double w = std::get<1>(tpl);
			if (!SG.sommet(v))
				sum += w;
		}
	}
	return sum;
}

template <class T>
/**
 * Helper pour améliorer performance et éviter allocation des DFS inutiles
 * Retourne true si aucun cycle n'est possible
 */
bool Digraph<T>::noCyclePossible(const T &start) const
{
	auto it = graphe.find(start);
	// pas de successeurs
	if (it == graphe.end() || it->second.empty())
		return true;
	// pas de prédécesseurs
	for (auto const &p : graphe)
	{
		for (auto const &tpl : p.second)
		{
			if (std::get<0>(tpl) == start)
				return false; // on a au moins un predecesseur
		}
	}
	return true;
}

template <class T>
/**
 * Helper pour améliorer performance sur les cycles restreints
 * Retourne true si aucun cycle n'est possible dans "nodes"
 */
bool Digraph<T>::noCyclePossible(const T &start, const std::set<T> &nodes) const
{
	auto it = graphe.find(start);
	// pas de successeurs dans "nodes"
	if (it == graphe.end() || it->second.empty())
		return true;
	// pas de prédécesseurs dans "nodes"
	for (auto const &u : nodes)
	{
		auto &E = graphe.at(u);
		for (auto const &tpl : E)
		{
			if (std::get<0>(tpl) == start)
				return false; // on a un predecesseur dans SG
		}
	}
	return true;
}

#endif // __DIGRAPH_H__