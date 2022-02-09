#include "../includes/BinaryTree.h"
#include "../includes/PlotBinaryTree.h"
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
using namespace std;

BinaryTree::BinaryTree(ComponentList* comp_list) {
    this->comp_list = comp_list;
    // this->root = setBinaryTree(comp_list);
    this->contour = new Contour();
    this->side = 0;  // default value
}

BinaryTree::~BinaryTree() {
    delete this->root;
    delete this->contour;
}

TreeNode* BinaryTree::getRoot() {
    return this->root;
}

TreeNode* BinaryTree::setBinaryTree(ComponentList* comp_list) {
    TreeNode* root = new TreeNode(comp_list->getData("T501"));
    root->setLeftchild(comp_list->getData("M503"));
    root->setRightchild(comp_list->getData("D508"));
    root->getLeftchild()->setLeftchild(comp_list->getData("R532"));
    root->getLeftchild()->setRightchild(comp_list->getData("Q504"));
    root->getLeftchild()->getLeftchild()->setRightchild(comp_list->getData("ZD501"));
    root->getLeftchild()->getRightchild()->setRightchild(comp_list->getData("R517"));
    root->getRightchild()->setRightchild(comp_list->getData("L501"));

    cout << "construct tree successfully" << endl;
    return root;
}

void BinaryTree::setSingleSide() {
    this->side = 0;

    vector<int> comp_list_index(this->comp_list->getSize());
    for (int i = 0; i < comp_list_index.size(); i++) {
        comp_list_index[i] = i;
    }
    random_shuffle(comp_list_index.begin(), comp_list_index.end());

    for (int i = 0; i < comp_list_index.size(); i++) {
        cout << comp_list_index[i] << endl;
    }
}

void BinaryTree::setDoubleSide() {
    this->side = 1;
}

void BinaryTree::printBinaryTree() {
    cout << "start print binary tree" << endl;
    PlotBinaryTree* plot_tree = new PlotBinaryTree(this);
    plot_tree->plotBinaryTree();
}