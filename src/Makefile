# Environnement de compilation
CXX=g++
C11=--std=c++11

# Emplacement des sources
SRCS = $(notdir $(wildcard test/*_digraph.cpp))

# Noms des exécutables
EXEC_DIG = $(SRCS:.cpp=)

# Par défaut : construire tous les exécutables
all: $(EXEC_DIG)

# Règle de compilation : associer le nom de la cible au fichier source dans test/
%: test/%.cpp
	$(CXX) $(C11) -o $@ $<

# Exécuter les tests
digraph: $(EXEC_DIG)
	@for exec in $(EXEC_DIG); do \
		if [ $$exec = "07_digraph" ]; then \
			./$$exec data/complete data/complete_reduction; \
		elif [ $$exec = "08_digraph" ]; then \
			./$$exec data/tutte_graph data/tutte_dettes-prets_sommet; \
		elif [ $$exec = "09_digraph" ]; then \
			./$$exec data/regular_graph data/regular_dettes-prets_sommet; \
		elif [ $$exec = "10_digraph" ]; then \
			./$$exec data/dorogovtsev_graph data/dorogovtsev_dettes-prets_sommet; \
		else \
			./$$exec; \
		fi; \
	done

# Exécuter les tests avec chronométrage
test: $(EXEC_DIG)
	@for exec in $(EXEC_DIG); do \
		printf "\n=== Test $$exec ===\n"; \
		if [ $$exec = "07_digraph" ]; then \
			time -p ./$$exec data/complete data/complete_reduction; \
		elif [ $$exec = "08_digraph" ]; then \
			time -p ./$$exec data/tutte_graph data/tutte_dettes-prets_sommet; \
		elif [ $$exec = "09_digraph" ]; then \
			time -p ./$$exec data/regular_graph data/regular_dettes-prets_sommet; \
		elif [ $$exec = "10_digraph" ]; then \
			time -p ./$$exec data/dorogovtsev_graph data/dorogovtsev_dettes-prets_sommet; \
		else \
			time -p ./$$exec; \
		fi; \
	done

# Supprimer les exécutables
clean:
	rm -f $(EXEC_DIG)
