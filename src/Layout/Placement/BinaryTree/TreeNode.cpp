#include "TreeNode.h"
#include "Component.h"
#include <iostream>
#include <string>
using namespace std;

TreeNode::TreeNode(ComponentProperty* comp_prop) {
    this->branch = "";
    this->parent = nullptr;
    this->leftchild = nullptr;
    this->rightchild = nullptr;

    this->comp_prop = new ComponentProperty();
    this->comp_state = new ComponentState();
    this->setComponentProp(comp_prop);
}

TreeNode::~TreeNode() {
    delete this->leftchild;
    delete this->rightchild;
    delete this->comp_prop;
    delete this->comp_state;
}

TreeNode* TreeNode::copy() {
    TreeNode* new_node = new TreeNode(this->comp_prop);
    new_node->setLeftchild(this->getLeftchild());
    new_node->setRightchild(this->getRightchild());
    new_node->setParent(this->getParent());
    return new_node;
}

string TreeNode::getBranch() {
    return this->branch;
}

TreeNode* TreeNode::getLeftchild() {
    return this->leftchild;
}

// void TreeNode::setLeftchild(ComponentProperty* comp_prop) {
//     this->leftchild = new TreeNode(comp_prop);
//     this->leftchild->setParent(this);
// }

void TreeNode::setLeftchild(TreeNode* node) {
    this->leftchild = new TreeNode(node->getComponentProp());
    this->leftchild->setComponentState(node->getComponentState());
    this->leftchild->setParent(this);
}

TreeNode* TreeNode::getRightchild() {
    return this->rightchild;
}

// void TreeNode::setRightchild(ComponentProperty* comp_prop) {
//     this->rightchild = new TreeNode(comp_prop);
//     this->rightchild->setParent(this);
// }
void TreeNode::setRightchild(TreeNode* node) {
    this->rightchild = new TreeNode(node->getComponentProp());
    this->rightchild->setComponentState(node->getComponentState());
    this->rightchild->setParent(this);
}


TreeNode* TreeNode::getParent() {
    return this->parent;
}
void TreeNode::setParent(TreeNode* parent) {
    this->parent = parent;
}

void TreeNode::setComponentProp(ComponentProperty* comp_prop) {
    this->comp_prop->setAllInfo(comp_prop);
}

void TreeNode::setComponentState(ComponentState* comp_state) {
    this->comp_state = comp_state;
}

ComponentProperty* TreeNode::getComponentProp() {
    return this->comp_prop;
}

ComponentState* TreeNode::getComponentState() {
    return this->comp_state;
}

void TreeNode::setTreeNode(TreeNode* node) {
    this->setComponentProp(node->getComponentProp());
    this->setComponentState(node->getComponentState());
}

void TreeNode::printTreeNode() {
    cout << "Component name: " << this->comp_prop->getName() << endl;
    cout << "Component color: " << this->comp_prop->getColor() << endl;
    cout << "Component length: " << this->comp_prop->getLength() << endl;
    cout << "Component width: " << this->comp_prop->getWidth() << endl;
    cout << "Component height: " << this->comp_prop->getHeight() << endl;
    cout << "Component voltage: " << this->comp_prop->getVoltage() << endl;
    cout << "Component default pin position: " << endl;
    comp_prop->printDefaultPinPosition();
    cout << "Component side: " << this->comp_state->getSide() << endl;
    cout << "Component angle: " << this->comp_state->getAngle() << endl;
    cout << "Component coor_X: " << this->comp_state->getPosition().x << ", coor_Y: " << this->comp_state->getPosition().y << endl;
    cout << "Component margin: " << this->comp_state->getMargin() << endl;
}