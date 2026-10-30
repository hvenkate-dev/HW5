
#include "BetterPriorityQueue.h"
#include <algorithm>
#include <sstream>

// Return true if a node with the same graph key is in the queue.
bool BetterPriorityQueue::Contains(BPQNode node) const {
    for (const BPQNode& item : this->c) {
        if (item == node) {
            return true;
        }
    }

    return false;
}

// Update a node if it exists and its priority does not get worse.
bool BetterPriorityQueue::Update(BPQNode node) {
    for (size_t i = 0; i < this->c.size(); i++) {
        if (this->c[i] == node) {

            // Do not accept a larger, worse priority.
            if (node.pri > this->c[i].pri) {
                return false;
            }

            // Replace the existing node.
            this->c[i] = node;

            // Restore the heap after the priority decreases.
            // The changed node can move upward through this prefix.
            push_heap(
                this->c.begin(),
                this->c.begin() + i + 1,
                greater<BPQNode>()
            );

            return true;
        }
    }

    // The node does not exist in the queue.
    return false;
}

// Convert one node into a readable string.
string BetterPriorityQueue::BPQNodeToString(BPQNode node) {
    return "(" + to_string(node.gnode) +
           ", pri: " + to_string(node.pri) + ")";
}

// Convert the underlying heap vector into a readable string.
string BetterPriorityQueue::ToString() const {
    string result = "[";

    for (size_t i = 0; i < this->c.size(); i++) {
        if (i > 0) {
            result += ", ";
        }

        result += BPQNodeToString(this->c[i]);
    }

    result += "]";
    return result;
}
