
#include "Graph.h"
#include "BetterPriorityQueue.h"
#include "Dijkstra.h"

#include <iostream>
#include <cassert>

using namespace std;


int DijkstraTest(){
	cout << "Testing Dijkstra Algorithm..." << endl;
	
	// Test 1: graph from assignment
	Graph *g = new Graph();
	
	g->AddNode(1);
	g->AddNode(2);
	g->AddNode(3);
	
	g->AddEdge(1, 2, 7);
	g->AddEdge(2, 1, 7);
	g->AddEdge(1, 3, 9);
	g->AddEdge(3, 1, 9);

	
	cout <<  "---Graph---" << endl;
	cout << "\tnodes: " << g->NodesToString() << endl;
	cout << "\tedges: " << g->EdgesToString() << endl;
	cout << "---Graph---" << endl << endl;

	nodekey_t start = 1;
	nodekey_t end = 3;

	cout << "start: " << to_string(start) << "  goal: " << to_string(end) << endl;
	
	int ans = dijkstra(start, end, g);
	cout << "Output from Dijkstra(" << to_string(start) << ", " << to_string(end) << ") => " << ans << endl;
	assert(ans == 9);

	delete g;
	
	cout << "DONE with basic testing of Dijkstra algorithm" << endl;
	
	return ans;
}



int main(){
	
	DijkstraTest(); // this one by itself tests the graph on the assignment
	cout << endl;
	cout << "ALL TESTS PASSED!" << endl;

	return 0;
}
