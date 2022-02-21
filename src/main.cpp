#include "Layout.h"
#include "GA/GA.h"
#include <iostream>
#include <ctime>
using namespace std;

int main () {
    srand((unsigned)time(0));
    
    // GA* GA_optimizer = new GA();
    // cout << "complete GA_optimizer" << endl;
    // delete GA_optimizer;
    ComponentList* component_list = new ComponentList();
    component_list->printAllData();
    // BinaryTree* tree = new BinaryTree(component_list);
    // tree->setDoubleSide();
    // tree->printBinaryTree();
    // BinaryTree* new_tree = tree->copy();
    // new_tree->printBinaryTree();
    return 0;
}