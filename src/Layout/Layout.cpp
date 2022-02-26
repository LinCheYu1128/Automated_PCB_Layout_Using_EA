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

BinaryTree* Layout::getBinaryTree(){
    return this->tree;
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

void writeCsv(Layout layout){
    BinaryTree* layout_tree = layout.getBinaryTree();
    std::ofstream layout_data;
    layout_data.open ("output.csv");
    stack<TreeNode*> nodes;
    nodes.push(layout_tree->getRoot());
    while (nodes.size() > 0) {
        TreeNode *current = nodes.top();
        nodes.pop();
        ComponentProperty* prop = current->getComponentProp();
        ComponentState* state = current->getComponentState();
        layout_data << prop->getName() << "," 
                    << prop->getColor() << ","
                    << prop->getLength() << ","
                    << prop->getWidth() << ","
                    << prop->getHeight() << ","
                    << prop->getVoltage() << ","
                    << state->getPosition().x << ","
                    << state->getPosition().y << ","
                    << state->getAngle() << ","
                    << state->getSide() << ",";
        if (current->getLeftchild()) layout_data << current->getLeftchild()->getComponentProp()->getName() << ",";
        else layout_data << "null" << ",";
        if (current->getRightchild()) layout_data << current->getRightchild()->getComponentProp()->getName() << ",";
        else layout_data << "null" << ",";
        layout_data << "\n";

        if (current->getLeftchild()) nodes.push(current->getLeftchild());
        if (current->getRightchild()) nodes.push(current->getRightchild()); 
    }
    layout_data.close();
}