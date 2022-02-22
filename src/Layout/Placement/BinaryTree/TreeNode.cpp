#include "TreeNode.h"
#include "Component.h"
#include <iostream>
#include <string>
using namespace std;

TreeNode::TreeNode(ComponentProperty* comp_prop) {
    this->id = 0;
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
    // copy information without connection
    TreeNode* new_node = new TreeNode(this->comp_prop);
    new_node->setID(this->id);
    new_node->setBranch(this->branch);
    new_node->setComponentState(this->getComponentState());
    return new_node;
}

int TreeNode::getID() {
    return this->id;
}

string TreeNode::getBranch() {
    return this->branch;
}

TreeNode* TreeNode::getChild(string branch) {
    if (branch == "left") {
        return this->leftchild;
    } else if (branch == "right") {
        return this->rightchild;
    }
}

TreeNode* TreeNode::getLeftchild() {
    return this->leftchild;
}

TreeNode* TreeNode::getRightchild() {
    return this->rightchild;
}

TreeNode* TreeNode::getParent() {
    return this->parent;
}

ComponentProperty* TreeNode::getComponentProp() {
    return this->comp_prop;
}

ComponentState* TreeNode::getComponentState() {
    return this->comp_state;
}

void TreeNode::replaceBy(TreeNode* node) {
    this->setComponentProp(node->getComponentProp());
    this->setComponentState(node->getComponentState());
    this->setID(node->getID());
}

void TreeNode::disconnect(string branch) {
    if (branch == "parent" || branch == "all") {
        this->parent = nullptr;
    }
    if (branch == "left" || branch == "all") {
        cout << "disconnect left" << endl;
        this->leftchild = nullptr;
    }
    if (branch == "right" || branch == "all") {
        cout << "disconnect right" << endl;
        this->rightchild = nullptr;
    }
}

void TreeNode::setID(int id) {
    this->id = id;
}

void TreeNode::setBranch(string branch) {
    this->branch = branch;
}

void TreeNode::setChild(string branch, TreeNode* node) {
    if (branch == "left") {
        this->setLeftChild(node);
    } else if (branch == "right") {
        this->setRightChild(node);
    }
}

void TreeNode::setLeftChild(TreeNode* node) {
    this->leftchild = node;
    this->leftchild->setParent(this, "left");
}

void TreeNode::setRightChild(TreeNode* node) {
    this->rightchild = node;
    this->rightchild->setParent(this, "right");
}

void TreeNode::setParent(TreeNode* parent, string branch) {
    this->parent = parent;
    this->branch = branch;
}

void TreeNode::setComponentProp(ComponentProperty* comp_prop) {
    // ToCheck setAllInfo
    this->comp_prop->setAllInfo(comp_prop);
}

void TreeNode::setComponentState(ComponentState* comp_state) {
    this->comp_state = comp_state;
}

// void TreeNode::changeParent(TreeNode* parent, string branch) {
//     if (this->parent->getLeftchild()->getComponentProp()->getName() == this->getComponentProp()->getName()) {
//         this->parent->setLeftchild(nullptr);
//     } else {
//         this->parent->setRightchild(nullptr);
//     }
//     this->setParent(parent);
//     if (branch == "left") {
//         parent->setLeftchild(this);
//     } else if (branch == "right") {
//         parent->setRightchild(this);
//     }
// }

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