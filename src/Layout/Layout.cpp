#include "Layout.h"
#include "debug.h"
#include <iostream>
using namespace std;

Console console = Console::getInstance();

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

void Layout::setComponent(int side) {
    this->tree = new BinaryTree(this->comp_list);
    if (side == 1) { this->tree->setSingleSide(); }
    if (side == 2) { this->tree->setDoubleSide(); }
}

void Layout::setContour() {

}

void Layout::printComponent() {
    this->tree->printBinaryTree();
}