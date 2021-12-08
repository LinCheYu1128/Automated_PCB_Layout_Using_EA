#include "../includes/TreeNode.h"

TreeNode::TreeNode(Data* data) {
    this->parent = nullptr;
    this->leftchild = nullptr;
    this->rightchild = nullptr;
    this->data = data;
}

void TreeNode::printTreeNode() {
    data->printData();
}