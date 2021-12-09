#include "../includes/TreeNode.h"

// TreeNode::TreeNode(Data* data) {
TreeNode::TreeNode(ComponentProperty* comp_prop) {
    this->branch = "";
    this->parent = nullptr;
    this->leftchild = nullptr;
    this->rightchild = nullptr;

    this->comp_prop = new ComponentProperty();
    this->comp_state = new ComponentState();
    this->setTreeNode(comp_prop);
}

TreeNode::~TreeNode() {
    delete leftchild;
    delete rightchild;
    delete comp_prop;
    delete comp_state;
}

string TreeNode::getBranch() {
    return branch;
}

TreeNode* TreeNode::getLeftchild() {
    return leftchild;
}
void TreeNode::setLeftchild(ComponentProperty* comp_prop) {
    leftchild = new TreeNode(comp_prop);
    leftchild->setParent(this);
}

TreeNode* TreeNode::getRightchild() {
    return rightchild;
}
void TreeNode::setRightchild(ComponentProperty* comp_prop) {
    rightchild = new TreeNode(comp_prop);
    rightchild->setParent(this);
}

TreeNode* TreeNode::getParent() {
    return parent;
}
void TreeNode::setParent(TreeNode* parent) {
    this->parent = parent;
}

ComponentProperty* TreeNode::getComponentProp() {
    return comp_prop;
}

void TreeNode::setTreeNode(ComponentProperty* comp_prop) {
    this->comp_prop->setAllInfo(comp_prop);
}

void TreeNode::printTreeNode() {
    cout << "Component name: " << comp_prop->getName() << endl;
    cout << "Component color: " << comp_prop->getColor() << endl;
    cout << "Component length: " << comp_prop->getLength() << endl;
    cout << "Component width: " << comp_prop->getWidth() << endl;
    cout << "Component height: " << comp_prop->getHeight() << endl;
    cout << "Component voltage: " << comp_prop->getVoltage() << endl;
    cout << "Component default pin position: " << endl;
    comp_prop->printDefaultPinPosition();
    cout << "Component side: " << comp_state->getSide() << endl;
    cout << "Component angle: " << comp_state->getAngle() << endl;
    cout << "Component coor_X: " << comp_state->getPosition().x << ", coor_Y: " << comp_state->getPosition().y << endl;
    cout << "Component margin: " << comp_state->getMargin() << endl;
}