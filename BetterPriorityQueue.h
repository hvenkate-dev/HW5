
#ifndef BETTER_PRIORITY_QUEUE_H
#define BETTER_PRIORITY_QUEUE_H

#include "Graph.h"
#include <queue>
#include <vector>
#include <functional>
#include <string>
#include <climits>

using namespace std;

// Represents one graph node stored in the priority queue.
struct BPQNode {
    int pri = INT_MAX;
    bool visited = false;
    nodekey_t gnode = INVALID_NODE_KEY;

    bool operator<(const BPQNode& other) const {
        return pri < other.pri;
    }

    bool operator>(const BPQNode& other) const {
        return pri > other.pri;
    }

    bool operator==(const BPQNode& other) const {
        return gnode == other.gnode;
    }
};

// A priority queue with support for checking and updating nodes.
class BetterPriorityQueue
    : public priority_queue<BPQNode, vector<BPQNode>, greater<BPQNode>> {
public:
    bool Contains(BPQNode node) const;
    bool Update(BPQNode node);

    string ToString() const;
    static string BPQNodeToString(BPQNode node);
};

#endif
