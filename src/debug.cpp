#include "Layout.h"
#include "debug.h"
#include <iostream>
using namespace std;

Console Console::instance;
int Console::mode;

void Console::run() {
    ComponentList* component_list = new ComponentList();
    // component_list->printAllData();
    
    log("construct tree");
    BinaryTree* tree = new BinaryTree(component_list);
    tree->setDoubleSide();
    tree->printBinaryTree();

    log("construct copy tree");
    BinaryTree* new_tree = tree->copy();
    
    log("start delete node");
    map<int, TreeNode*> TreeNode_map = new_tree->getTreeNodeMap();
    for (int i = 0; i < 38; i++) {
        new_tree->delete_node(i);
        new_tree->printBinaryTree();
    }
    
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

}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}