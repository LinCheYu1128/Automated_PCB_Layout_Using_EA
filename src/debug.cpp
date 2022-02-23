#include "Layout.h"
#include "DebugMode.h"
#include <iostream>
using namespace std;

Console::Console(int argc, char **argv) {
    // this->set(argc, argv);
}

void Console::set(int argc, char **argv) {
    cout << "We have " << argc << " arguments" << endl;
    for (int i = 0; i < argc; i++) {
        if (argv[1] == "--debug" || argv[1][1] == 'd') {
            cout << "Debug Mode On" << endl;
            this->mode = 0;
        } else {
            this->mode = 1;
            cout << "Debug Mode Off" << endl;
        }
    }
}

void Console::run() {
    ComponentList* component_list = new ComponentList();
    // component_list->printAllData();
    
    cout << "construct tree" << endl;
    BinaryTree* tree = new BinaryTree(component_list);
    tree->setDoubleSide();
    tree->printBinaryTree();

    cout << "construct copy tree" << endl;
    BinaryTree* new_tree = tree->copy();
    
    // random select node to delete
    cout << "start random select node to delete" << endl;
    map<int, TreeNode*> TreeNode_map = new_tree->getTreeNodeMap();
    // delete node
    for (int i = 0; i < 38; i++) {
        new_tree->delete_node(i);
        new_tree->printBinaryTree();
    }

    // new_tree->printBinaryTree();

    // for (int i = 0; i < 2; i++) {
    //     do {
    //         node = TreeNode_map[rand() % component_list->getSize()];
    //     } while (node->getID() < 3);
    //     cout << "random select node " << node->getID() << endl;

    //     // delete node
    //     new_tree->delete_node(node);
    // }

    
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

void Console::log(ostream& stream) {
    if (mode == DEBUG_MODE) {
        stream << "In debug mode";
    }
    return;
}