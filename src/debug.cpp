#include "Layout.h"
#include <iostream>
using namespace std;

void debug() {
    ComponentList* component_list = new ComponentList();
    // component_list->printAllData();
    
    cout << "construct tree" << endl;
    BinaryTree* tree = new BinaryTree(component_list);
    tree->setDoubleSide();
    tree->printBinaryTree();

    cout << "construct copy tree" << endl;
    BinaryTree* new_tree = tree->copy();
    
    // random select node
    // map<int, TreeNode*> TreeNode_map = new_tree->getTreeNodeMap();
    // TreeNode* node;
    // for (int i = 0; i < 2; i++) {
    //     do {
    //         node = TreeNode_map[rand() % component_list->getSize()];
    //     } while (node->getID() < 3);
    //     cout << "random select node " << node->getID() << endl;

    //     // delete node
    //     new_tree->delete_node(node);
    // }

    tree->swap(5, 7);
    map<int, TreeNode*> TreeNode_map = tree->getTreeNodeMap();
    TreeNode_map[5]->setID(100);
    tree->printBinaryTree();

    // new_tree->swap(5, 7);
    // map<int, TreeNode*> TreeNode_map = new_tree->getTreeNodeMap();
    // TreeNode_map[5]->setID(100);
    // new_tree->printBinaryTree();
}