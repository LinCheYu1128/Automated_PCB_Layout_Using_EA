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
    TreeNode* new_node = new TreeNode(this->comp_prop);
    new_node->setID(this->id);
    new_node->setBranch(this->branch);
    new_node->setComponentState(this->getComponentState());
    new_node->setLeftchild(this->getLeftchild());
    new_node->setRightchild(this->getRightchild());
    new_node->setParent(this->getParent());
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

void TreeNode::copyTreeNode(TreeNode* node) {
    cout << node->getComponentProp()->getName() << endl;
    this->setComponentProp(node->getComponentProp());
    this->setComponentState(node->getComponentState());
}

void TreeNode::setID(int id) {
    this->id = id;
}

void TreeNode::setBranch(string branch) {
    this->branch = branch;
}

void TreeNode::setChild(string branch, TreeNode* node) {
    if (branch == "left") {
        this->setLeftchild(node);
    } else if (branch == "right") {
        this->setRightchild(node);
    }
}

// void TreeNode::setLeftchild(ComponentProperty* comp_prop) {
//     this->leftchild = new TreeNode(comp_prop);
//     this->leftchild->setParent(this);
// }
void TreeNode::setLeftchild(TreeNode* node) {
    if (node == nullptr) {
        this->leftchild = nullptr;
        return;
    }
    if (this->leftchild == nullptr) {
        this->leftchild = node->copy();
        this->leftchild->setParent(this);
    } else {
        this->leftchild->setComponentProp(node->getComponentProp());
        this->leftchild->setComponentState(node->getComponentState());
    }
    this->leftchild->setID(node->getID());
    this->leftchild->setBranch("left");
}

// void TreeNode::setRightchild(ComponentProperty* comp_prop) {
//     this->rightchild = new TreeNode(comp_prop);
//     this->rightchild->setParent(this);
// }
void TreeNode::setRightchild(TreeNode* node) {
    if (node == nullptr) {
        this->rightchild = nullptr;
        return;
    }
    if (this->rightchild == nullptr) {
        this->rightchild = node->copy();
        this->rightchild->setParent(this);
    } else {
        this->rightchild->setComponentProp(node->getComponentProp());
        this->rightchild->setComponentState(node->getComponentState());
    }
    this->rightchild->setID(node->getID());
    this->rightchild->setBranch("right");
}

void TreeNode::setParent(TreeNode* parent) {
    this->parent = parent;
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