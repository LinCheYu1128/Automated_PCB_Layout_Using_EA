#include "../includes/BinaryTree.h"

BinaryTree::BinaryTree(ComponentProperty* comp_prop) {
    root = new TreeNode(new Data(comp_prop));
    contour = new Contour();
    cout << "construct tree successfully" << endl;
}

void BinaryTree::printBinaryTree() {
    root->printTreeNode();
}