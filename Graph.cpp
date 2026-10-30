
#include "Graph.h"
#include <sstream>
#include <stdexcept>

// Add a node to the graph.
void Graph::AddNode(nodekey_t key) {
    // A node key must be unique.
    if (IsPresent(key)) {
        throw invalid_argument("Node already exists");
    }

    // Store the node in insertion order.
    nodes.push_back(key);
}


// Add a directed edge between two existing nodes.
const GraphEdge* Graph::AddEdge(
    nodekey_t fromNodeKey,
    nodekey_t toNodeKey,
    unsigned int weight
) {
    // Both nodes must already exist.
    if (!IsPresent(fromNodeKey) || !IsPresent(toNodeKey)) {
        throw invalid_argument("Node does not exist");
    }

    // Do not allow duplicate directed edges.
    for (const GraphEdge* edge : edges) {
        if (edge->from == fromNodeKey &&
            edge->to == toNodeKey) {
            throw invalid_argument("Edge already exists");
        }
    }

    // Create the edge on the heap so its address remains stable.
    GraphEdge* edge = new GraphEdge;

    edge->from = fromNodeKey;
    edge->to = toNodeKey;
    edge->weight = weight;

    edges.push_back(edge);

    return edge;
}


// Check whether a node exists in the graph.
bool Graph::IsPresent(nodekey_t key) const {
    for (nodekey_t node : nodes) {
        if (node == key) {
            return true;
        }
    }

    return false;
}


// Return all nodes in insertion order as a string.
string Graph::NodesToString() const {
    string result = "[";

    for (size_t i = 0; i < nodes.size(); i++) {
        if (i > 0) {
            result += ", ";
        }

        result += "(" + to_string(nodes[i]) + ")";
    }

    result += "]";

    return result;
}


// Return all edges in insertion order as a string.
string Graph::EdgesToString() const {
    string result = "[";

    for (size_t i = 0; i < edges.size(); i++) {
        if (i > 0) {
            result += ", ";
        }

        const GraphEdge* edge = edges[i];

        result += "((" + to_string(edge->from) +
                  ")->(" + to_string(edge->to) +
                  ") w:" + to_string(edge->weight) + ")";
    }

    result += "]";

    return result;
}


// Return all edges that leave the specified node.
set<const GraphEdge*> Graph::GetOutwardEdgesFrom(
    nodekey_t nodeKey
) const {
    set<const GraphEdge*> result;

    for (const GraphEdge* edge : edges) {
        if (edge->from == nodeKey) {
            result.insert(edge);
        }
    }

    return result;
}


// Return all node keys as a set.
set<nodekey_t> Graph::GetNodes() const {
    set<nodekey_t> result;

    for (nodekey_t node : nodes) {
        result.insert(node);
    }

    return result;
}


// Return the number of edges.
size_t Graph::Size() const {
    return edges.size();
}


// Return the number of nodes.
size_t Graph::Order() const {
    return nodes.size();
}


// Free the memory allocated for every edge.
Graph::~Graph() {
    for (GraphEdge* edge : edges) {
        delete edge;
    }

    edges.clear();
}
