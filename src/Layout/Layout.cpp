#include "Layout.h"
#include "console.h"
#include <iostream>
using namespace std;

Layout::Layout(ComponentList* comp_list, int side) {
    this->comp_list = comp_list;
    this->setComponent(side);
    this->setContour();
}

Layout::~Layout() {
    delete this->comp_list;
    delete this->tree;
    delete this->contour;
}

<<<<<<< HEAD
float Layout::getFitness() {
    return this->fitness;
}

void Layout::setComponent(string side) {
=======
void Layout::setComponent(int side) {
>>>>>>> f52d2a3388d715e43ca5329c86d0f7be7a975b05
    this->tree = new BinaryTree(this->comp_list);
    if (side == 1) { this->tree->setSingleSide(); }
    if (side == 2) { this->tree->setDoubleSide(); }
}

void Layout::setContour() {

}

void Layout::printComponent() {
    this->tree->printBinaryTree();
}