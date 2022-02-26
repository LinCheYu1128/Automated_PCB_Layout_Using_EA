#include "Layout.h"
#include "console.h"
#include <iostream>
using namespace std;

Layout::Layout(BinaryTree* tree, ComponentList* comp_list, int side){
    this->comp_list = comp_list;
    this->tree = tree;
    this->setContour();
    this->tree->updateTree();

    if (side == 1) this->setState(this->tree->getRoot(), this->front_contour);
    else if (side == 2) {
        this->setState(this->tree->getRoot()->getLeftchild(), this->front_contour);
        this->setState(this->tree->getRoot()->getRightchild(), this->back_contour);
    }
    else {cout << "unknown side" << endl; exit(0);} 
    this->component_num = comp_list->getSize();

    this->front_contour->printContour();
    this->back_contour->printContour();
}

Layout::Layout(ComponentList* comp_list, int side) {
    this->comp_list = comp_list;
    this->setBinaryTree(side);
    this->setContour();

    this->tree->updateTree();

    if (side == 1) this->setState(this->tree->getRoot(), this->front_contour);
    else if (side == 2) {
        this->setState(this->tree->getRoot()->getLeftchild(), this->front_contour);
        this->setState(this->tree->getRoot()->getRightchild(), this->back_contour);
    }
    else {cout << "unknown side" << endl; exit(0);} 
    this->component_num = comp_list->getSize();

    this->front_contour->printContour();
    this->back_contour->printContour();
}

Layout::~Layout() {
    delete this->comp_list;
    delete this->tree;
    delete this->front_contour;
    delete this->back_contour;
}

void Layout::setBinaryTree(int side) {
    this->tree = new BinaryTree(this->comp_list);
    if (side == 1) { this->tree->setSingleSide(); }
    if (side == 2) { this->tree->setDoubleSide(); }
}

void Layout::setContour() {
    this->front_contour = new Contour();
    this->back_contour = new Contour();
}


void Layout::setState(TreeNode* root, Contour* contour) {
    root->shiftUp(contour->getContour());
    contour->addBlock(root->getComponentState());

    if (root->getLeftchild()) {
        setState(root->getLeftchild(), contour);
    }
    if (root->getRightchild()) {
        setState(root->getRightchild(), contour);
    }
}

void Layout::printComponent() {
    this->tree->printBinaryTree();
}