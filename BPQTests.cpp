
#include "BetterPriorityQueue.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

void ContainsTest() {
    cout << "Testing Contains..." << endl;

    BetterPriorityQueue q;

    BPQNode node1;
    node1.gnode = 1;
    node1.pri = 0;
    q.push(node1);

    BPQNode node2;
    node2.gnode = 2;
    node2.pri = 1;
    q.push(node2);

    assert(q.Contains(node1) == true);

    BPQNode missing;
    missing.gnode = 99;
    assert(q.Contains(missing) == false);

    cout << "Contains PASSED!" << endl;
}

void UpdateTest() {
    cout << "Testing Update..." << endl;

    BetterPriorityQueue q;

    // Add nodes with priorities 0 through 5.
    for (int i = 1; i <= 6; i++) {
        BPQNode node;
        node.gnode = i;
        node.pri = i - 1;
        q.push(node);
    }

    // Lower node 6's priority from 5 to 0.
    BPQNode improved;
    improved.gnode = 6;
    improved.pri = 0;

    assert(q.Update(improved) == true);

    // Confirm the improved node is at the top.
    assert(q.top().gnode == 1 || q.top().gnode == 6);
    assert(q.top().pri == 0);

    // Updating a missing node must fail.
    BPQNode missing;
    assert(q.Update(missing) == false);

    // Raising node 5's priority must be rejected.
    BPQNode worse;
    worse.gnode = 5;
    worse.pri = 80;

    assert(q.Update(worse) == false);

    cout << "Queue after updates: " << q.ToString() << endl;
    cout << "Update PASSED!" << endl;
}

void StringTest() {
    cout << "Testing string methods..." << endl;

    BPQNode node;
    node.gnode = 7;
    node.pri = 3;

    assert(BetterPriorityQueue::BPQNodeToString(node)
           == "(7, pri: 3)");

    BetterPriorityQueue q;
    q.push(node);

    assert(q.ToString() == "[(7, pri: 3)]");

    cout << "String methods PASSED!" << endl;
}

int main() {
    ContainsTest();
    UpdateTest();
    StringTest();

    cout << "\nALL TESTS PASSED!" << endl;
    return 0;
}
