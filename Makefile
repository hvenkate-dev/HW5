all: graph-tests bpq-tests dijkstra

graph-tests: Graph.cpp GraphTests.cpp Graph.h
	g++ -Wall -g Graph.cpp GraphTests.cpp -o graph-tests

bpq-tests: Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp Graph.h BetterPriorityQueue.h
	g++ -Wall -g Graph.cpp BetterPriorityQueue.cpp BPQTests.cpp -o bpq-tests

dijkstra: Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp Graph.h BetterPriorityQueue.h Dijkstra.h
	g++ -Wall -g Graph.cpp BetterPriorityQueue.cpp Dijkstra.cpp DijkstraTests.cpp -o dijkstra

clean:
	rm -f graph-tests bpq-tests dijkstra
