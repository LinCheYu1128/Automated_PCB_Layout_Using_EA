#include "../includes/PlotBinaryTree.h"
#include <iostream>
#include <string>
using namespace std;

PlotBinaryTree::PlotBinaryTree(BinaryTree* tree) {
    this->tree = tree;
}

void PlotBinaryTree::plotBinaryTree() {
    this->plotBinaryTree(this->tree->getRoot());
}

void PlotBinaryTree::plotBinaryTree(TreeNode* node) {
    this->plotBinaryTree("", node, false);
}

void PlotBinaryTree::plotBinaryTree(string prefix, TreeNode* node, bool isLeft) {
    if( node != nullptr ) {
        cout << prefix;
        cout << (isLeft ? "|-- " : "\\-- ");

        // print the value of the node
        cout << node->getComponentProp()->getName() << endl;

        // enter the next tree level - left and right branch
        this->plotBinaryTree(prefix + (isLeft ? "|   " : "    "), node->getLeftchild(), true);
        this->plotBinaryTree(prefix + (isLeft ? "|   " : "    "), node->getRightchild(), false);
    }
}