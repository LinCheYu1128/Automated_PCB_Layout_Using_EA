#include "Layout.h"
#include "console.h"
#include <iostream>
using namespace std;

Layout::Layout(ComponentList* comp_list, int side) {
    this->comp_list = comp_list;
    this->setBinaryTree(side);
    this->setContour();
  
    this->setState(this->tree->getRoot());
    
    //----*
    this->printComponent();
    this->contour->printContour();
=======
    this->component_num = comp_list->getSize();
}

Layout::~Layout() {
    delete this->comp_list;
    delete this->tree;
    delete this->contour;
}

void Layout::setBinaryTree(int side) {
    this->tree = new BinaryTree(this->comp_list);
    if (side == 1) { this->tree->setSingleSide(); }
    if (side == 2) { this->tree->setDoubleSide(); }
}

void Layout::setContour() {
    this->contour = new Contour();
}

void Layout::setState(TreeNode* root) {
    root->updateState(this->contour->getContour());
    //-----
    Point check = root->getComponentState()->getPosition();
    cout << "Position after update: (" << check.x << ", " << check.y << ")" << endl;
    //-----
    this->contour->addBlock(root->getComponentState());
    if (root->getLeftchild()) {
        setState(root->getLeftchild());
    }
    if (root->getRightchild()) {
        setState(root->getRightchild());
    }
}

void Layout::printComponent() {
    this->tree->printBinaryTree();
}