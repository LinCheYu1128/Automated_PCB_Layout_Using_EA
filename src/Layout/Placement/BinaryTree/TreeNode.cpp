#include "TreeNode.h"
#include "Component.h"
#include <iostream>
#include <string>
#include <vector>
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
    new_node->setComponentState(this->getComponentState()->copy());
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
    } else {
        cout << "no branch defined" << endl;
        exit(0);
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

void TreeNode::disconnect(string branch) {
    if (branch == "parent" || branch == "all") {
        string mybranch = this->branch;
        if(mybranch == "left"){
            if(this->parent) this->parent->leftchild = nullptr;
        }else if((mybranch == "right")){
            if(this->parent) this->parent->rightchild = nullptr;
        }
        this->parent = nullptr;
    }

    if (branch == "left" || branch == "all") {
        if(this->leftchild) this->leftchild->parent = nullptr;
        this->leftchild = nullptr;
    }
    if (branch == "right" || branch == "all") {
        if(this->rightchild) this->rightchild->parent = nullptr;
        this->rightchild = nullptr;
    }
}

void TreeNode::setID(int id) {
    this->id = id;
}

void TreeNode::setBranch(string branch) {
    this->branch = branch;
}

void TreeNode::setChild(TreeNode* node, string branch) {
    if (branch == "left") {
        this->setLeftChild(node);
    } else if (branch == "right") {
        this->setRightChild(node);
    }
}

void TreeNode::setLeftChild(TreeNode* node) {
    this->leftchild = node;
    this->leftchild->setBranch("left");
    node->parent = this;
}

void TreeNode::setRightChild(TreeNode* node) {
    this->rightchild = node;
    this->rightchild->setBranch("right");
    node->parent = this;
}

void TreeNode::setParent(TreeNode* parent, string branch) {
    this->parent = parent;
    if(parent) parent->setChild(this, branch);
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

bool TreeNode::search(int ID) {
    // cout << "start search " << ID << endl;
    TreeNode* temp = this;
    
    if (temp->getID() == ID) {
        // cout << "node ID " << ID << " has been searched at node " << this->getID() << endl;
        return true;
    }
    if (temp->getLeftchild() && temp->getLeftchild()->search(ID)) {
        return true;
    }
    if (temp->getRightchild() && temp->getRightchild()->search(ID)) {
        return true;
    }

    // cout << "node ID " << ID << " can't be searched at node " << this->getID() << endl;
    return false;
}


void TreeNode::updateNode() {
    if (this->comp_state->getAngle() == 0 || this->comp_state->getAngle() == 180) {
        this->comp_state->setLength(this->comp_prop->getLength() + 2*this->comp_state->getMargin());
        this->comp_state->setWidth(this->comp_prop->getWidth() + 2*this->comp_state->getMargin());
    } else {
        this->comp_state->setLength(this->comp_prop->getWidth() + 2*this->comp_state->getMargin());
        this->comp_state->setWidth(this->comp_prop->getLength() + 2*this->comp_state->getMargin());
    }
}

void TreeNode::shiftUp(vector<Point> contour) {
    double x;
    double max_y = 0;
    ComponentState* comp = this->getComponentState();
    if (this->getBranch() == "root") x = 0;
    else {
        ComponentState* parent = this->getParent()->getComponentState();
        if (this->getBranch() == "left") x = parent->getPosition().x + parent->getLength();
        else if (this->getBranch() == "right") x = parent->getPosition().x;
        else {cout << "Branch invalid" << endl; exit(0);}
    }
    for (unsigned int i = 0; i < contour.size(); i++){
        if (contour.at(i).x >= x && contour.at(i).x < x + comp->getLength()) {
            max_y = max(contour.at(i).y, max_y);
        }
    }
    comp->setPosition(x, max_y);
}

