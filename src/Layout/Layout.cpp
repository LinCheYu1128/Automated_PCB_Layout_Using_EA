#include "Layout.h"
#include <iostream>
using namespace std;

Layout::Layout(ComponentList* comp_list, string side) {
    this->comp_list = comp_list;
    this->setComponent(side);
    this->setContour();
}

Layout::~Layout() {
    delete this->comp_list;
    delete this->tree;
    delete this->contour;
}

void Layout::setComponent(string side) {
    this->tree = new BinaryTree(this->comp_list);
    if (side == "single") {
        this->tree->setSingleSide();
    } else if (side == "double") {
        this->tree->setDoubleSide();
    }
}

void Layout::setContour() {

}

void Layout::printComponent() {
    this->tree->printBinaryTree();
}