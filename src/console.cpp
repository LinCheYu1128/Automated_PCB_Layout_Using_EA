#include "Layout.h"
#include "GA.h"
#include "console.h"
#include <iostream>
using namespace std;

Console* Console::instance;
int Console::mode;

void Console::run() {

    GA* GA_optimizer = new GA();
    // cout << "test 1" << endl;
    GA_optimizer->getPopulation().at(0)->setWireLength();
    // cout << "test 2" << endl;
    cout << "wire length: " << GA_optimizer->getPopulation().at(0)->getWireLength() << endl;
    // cout << "test 3" << endl;
    delete GA_optimizer;
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}

// GA* GA_optimizer = new GA();
// log("complete GA_optimizer");
// delete GA_optimizer;

// // random select node to swap
// cout << "start random select node to swap" << endl;
// map<int, TreeNode*> TreeNode_map = tree->getTreeNodeMap();
// int a = rand() % component_list->getSize();
// int b = rand() % component_list->getSize();
// cout << "initial random select node " << a << ", " << b << endl;
// while (b == a || TreeNode_map.at(a)->search(b) || TreeNode_map.at(b)->search(a)) {
//     b = rand() % component_list->getSize();
//     cout << "random select node " << a << ", " << b << endl;
// }
// // swap node
// tree->swap(a, b);
// tree->printBinaryTree();