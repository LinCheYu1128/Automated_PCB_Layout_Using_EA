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
    // component_list->printAllData();
    cout << "construct tree" << endl;
    BinaryTree* tree = new BinaryTree(component_list);
    tree->setDoubleSide();
    
    cout << "construct copy tree" << endl;
    BinaryTree* new_tree = tree->copy();

    // random select node
    map<int, TreeNode*> TreeNode_map = tree->getTreeNodeMap();
    TreeNode* node = TreeNode_map[rand() % component_list->getSize()];
    cout << node->getComponentProp()->getName() << endl;

    // delete node
    tree->delete_node(node);
    
    tree->printBinaryTree();
    new_tree->printBinaryTree();

    return 0;
}