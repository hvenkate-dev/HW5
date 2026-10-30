#include "Dijkstra.h"
#include "Graph.h"
#include "BetterPriorityQueue.h"

#include <climits>
#include <map>
#include <set>

// Time complexity: O((V + E) log V) with a heap-based priority queue
// supporting efficient priority updates, where V is the number of nodes
// and E is the number of edges. This implementation scans the queue's
// underlying vector for Contains/Update, so those operations take O(V).
// Consequently, with this BetterPriorityQueue implementation, the
// conservative overall bound is O((V + E)V).

int dijkstra(nodekey_t start, nodekey_t goal, const Graph* graph) {
    // Reject a null graph or nodes that are not in the graph.
    if (graph == nullptr ||
        !graph->IsPresent(start) ||
        !graph->IsPresent(goal)) {
        return INT_MAX;
    }

    // Store the best distance found so far for each node.
    map<nodekey_t, int> distance;
    set<nodekey_t> visited;
    BetterPriorityQueue queue;

    // Initially, every node is unreachable.
    for (nodekey_t key : graph->GetNodes()) {
        distance[key] = INT_MAX;

        BPQNode node;
        node.gnode = key;
        node.pri = INT_MAX;
        queue.push(node);
    }

    // The starting node has distance zero.
    distance[start] = 0;

    BPQNode startNode;
    startNode.gnode = start;
    startNode.pri = 0;
    queue.Update(startNode);

    // Always process the unvisited node with the smallest distance.
    while (!queue.empty()) {
        BPQNode current = queue.top();
        queue.pop();

        // If the smallest remaining distance is infinite, no path exists.
        if (current.pri == INT_MAX) {
            return INT_MAX;
        }

        // The goal's shortest distance has now been determined.
        if (current.gnode == goal) {
            return current.pri;
        }

        visited.insert(current.gnode);

        // Examine every directed edge leaving the current node.
        set<const GraphEdge*> edges =
            graph->GetOutwardEdgesFrom(current.gnode);

        for (const GraphEdge* edge : edges) {
            nodekey_t neighbor = edge->to;

            if (visited.count(neighbor) > 0) {
                continue;
            }

            // Use a wider type for the addition to avoid integer overflow.
            long long candidate =
                static_cast<long long>(current.pri) + edge->weight;

            if (candidate < distance[neighbor] &&
                candidate < INT_MAX) {

                distance[neighbor] = static_cast<int>(candidate);

                BPQNode updated;
                updated.gnode = neighbor;
                updated.pri = static_cast<int>(candidate);

                queue.Update(updated);
            }
        }
    }

    // The queue ran out before the goal was reached.
    return INT_MAX;
}
