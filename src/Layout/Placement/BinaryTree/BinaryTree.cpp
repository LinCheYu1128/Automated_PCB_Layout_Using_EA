#include "BinaryTree.h"
#include "PlotBinaryTree.h"
#include "console.h"
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <stack>
using namespace std;

BinaryTree::BinaryTree(ComponentList* comp_list) {
    this->comp_list = comp_list;
    this->root = nullptr;
}

BinaryTree::~BinaryTree() {
    delete this->root;
}

TreeNode* BinaryTree::getRoot() {
    return this->root;
}

int BinaryTree::getSide() {
    return this->side;
}

map<int, TreeNode*> BinaryTree::getTreeNodeMap() {
    return this->TreeNode_map;
}

ComponentList* BinaryTree::getComponentList(){
    return this->comp_list;
}

BinaryTree* BinaryTree::copy() {
    BinaryTree* new_tree = new BinaryTree(this->comp_list);
    new_tree->setSide(this->side);
    new_tree->setRoot(this->root->copy());
    new_tree->copyByTraverseTree(this->root, new_tree->getRoot());
    return new_tree;
}

void BinaryTree::copyByTraverseTree(TreeNode* old_root, TreeNode* new_root) {
    // cout << "new Tree Node Map: " << this->TreeNode_map.size() << endl;
    this->TreeNode_map[new_root->getID()] = new_root;
    if (old_root->getLeftchild() != nullptr) {
        new_root->setLeftChild(old_root->getLeftchild()->copy());
        this->copyByTraverseTree(old_root->getLeftchild(), new_root->getLeftchild());
    }
    if (old_root->getRightchild() != nullptr) {
        new_root->setRightChild(old_root->getRightchild()->copy());
        this->copyByTraverseTree(old_root->getRightchild(), new_root->getRightchild());
    }
    return;
}

void BinaryTree::setRoot(TreeNode* node) {
    this->root = node;
    // this->root->setBranch("root");
    // this->root->disconnect("parent");
}

void BinaryTree::setSide(int side) {
    this->side = side;
}

void BinaryTree::setSingleSide() {
    delete this->root;
    this->side = 1;
    vector<int> comp_list_index(this->comp_list->getSize());

    for (unsigned int i = 0; i < comp_list_index.size(); i++) {
        comp_list_index[i] = i;
    }

    random_shuffle(comp_list_index.begin(), comp_list_index.end());

    int parent_pos = 0;
    int existed_nodes_num = 0;
    ComponentProperty* new_comp;
    TreeNode* parent_node;
    TreeNode* child_node;

    for (unsigned int i = 0; i < comp_list_index.size(); i++) {
        new_comp = comp_list->getDataByIndex(comp_list_index[i]);

        if (i == 0) {
            // root
            this->setRoot(new TreeNode(new_comp));
            child_node = this->root;
        } else {
            // left & right branch
            parent_pos = rand() % existed_nodes_num;
            parent_node = this->TreeNode_map[parent_pos];
            child_node = random_construct_tree(parent_node, new_comp);
        }

        child_node->setID(i);
        this->TreeNode_map[i] = child_node;
        existed_nodes_num += 1;
    }

    // Console::log("construct single side tree successfully");
}

void BinaryTree::setDoubleSide() {
    delete this->root;
    this->side = 2;
    vector<int> comp_list_index(this->comp_list->getSize());

    for (unsigned int i = 0; i < comp_list_index.size(); i++) {
        comp_list_index[i] = i;
    }
    
    random_shuffle(comp_list_index.begin(), comp_list_index.end());

    int parent_pos = 0;
    int existed_nodes_num = 0;
    ComponentProperty* new_comp;
    TreeNode* parent_node;
    TreeNode* child_node;

    // origin
    this->setRoot(new TreeNode(new ComponentProperty("Origin", "0", 0, 0, 0.1, 0)));
    this->root->setID(-1);
    this->TreeNode_map[-1] = this->root;
    // front_root
    this->root->setLeftChild(new TreeNode(new ComponentProperty("F_RootHole", "0", 2, 9, 0.1, 0)));
    this->root->getLeftchild()->setID(-2);
    this->TreeNode_map[-2] = this->root->getLeftchild();
    // back_root
    this->root->setRightChild(new TreeNode(new ComponentProperty("B_RootHole", "0", 2, 9, 0.1, 0)));
    this->root->getRightchild()->setID(-3);
    this->TreeNode_map[-3] = this->root->getRightchild();
    
    for (unsigned int i = 0; i < comp_list_index.size(); i++) {
        new_comp = comp_list->getDataByIndex(comp_list_index[i]);
        // left & right branch
        parent_pos = rand() % (existed_nodes_num+3)-3;
        parent_node = this->TreeNode_map[parent_pos];
        child_node = random_construct_tree(parent_node, new_comp);

        child_node->setID(comp_list_index[i]);
        this->TreeNode_map[i] = child_node;
        existed_nodes_num += 1;
    }
    // Console::log("construct double side tree successfully");
}

void BinaryTree::printBinaryTree() {
    Console::log("start print binary tree");
    PlotBinaryTree* plot_tree = new PlotBinaryTree(this);
    plot_tree->plotBinaryTree();
}

TreeNode* BinaryTree::random_construct_tree(TreeNode* parent_node, ComponentProperty* new_comp) {
    int branch_dir;
    TreeNode* child_node;
    vector<TreeNode*> successors;
    successors.push_back(parent_node->getLeftchild());
    successors.push_back(parent_node->getRightchild());

    while (true) {
        branch_dir = rand() % 2;
        if (successors[branch_dir] == nullptr) {
            if (branch_dir == 0) {
                parent_node->setLeftChild(new TreeNode(new_comp));
                child_node = parent_node->getLeftchild();
                break;
            } else {
                parent_node->setRightChild(new TreeNode(new_comp));
                child_node = parent_node->getRightchild();
                break;
            }
        }
        parent_node = successors[branch_dir];
        successors[0] = parent_node->getLeftchild();
        successors[1] = parent_node->getRightchild();
    }
    
    return child_node;
}

void BinaryTree::swap(int id_1, int id_2) {
    // should make sure do search() before swap
    TreeNode* A = this->TreeNode_map.at(id_1);
    TreeNode* B = this->TreeNode_map.at(id_2);
    if (this->TreeNode_map[id_1] && this->TreeNode_map[id_2]) {
        TreeNode* A_parent = A->getParent();
        TreeNode* B_parent = B->getParent();
        string A_branch = A->getBranch();
        string B_branch = B->getBranch();
        A->setParent(B_parent, B_branch);
        B->setParent(A_parent, A_branch);
    } else {
        Console::log("Can't swap! Some node not inside this tree.");
        exit(0);
    }
}

void BinaryTree::changetoroot(TreeNode* node){
    // if(node->getRightchild()==nullptr && node->getLeftchild()==nullptr){
    //     cout << node->getBranch() << endl;
    //     node->getParent()->disconnect(node->getBranch());
    //     cout << "debug disconnect" << endl;
    //     if(this->getRoot()->getLeftchild()){
    //         node->setLeftChild(this->getRoot()->getLeftchild());
    //     }
    //     if(this->getRoot()->getRightchild()){
    //         node->setRightChild(this->getRoot()->getRightchild());
    //     }
    //     cout << "debug setChild" << endl;
    //     this->setRoot(node);
    // }
}

void BinaryTree::delete_node(int ID) {
    if (this->TreeNode_map.find(ID) == this->TreeNode_map.end()) {
        Console::log("this node does not exist in this tree");
        return;
    }

    TreeNode* delete_node = this->TreeNode_map.at(ID);

    if (delete_node == nullptr) {
        Console::log("this node has been removed");
        return;
    }

    if(this->getRoot() == delete_node){
        TreeNode*new_root = delete_node->delete_root_f();
        this->setRoot(new_root);
    }
    else{
        delete_node->delete_node_f();
    }
    delete delete_node;
    /* Steps:
       - Find the node we want to delete.
       - Four cases:
        * node with left & right child.
        * node with left/right child only.
        * leaf node.
    */

    // this->delete_leaf_node(node);
    // this->delete_hasOneChild_node(node);
    // this->delete_hasBothChild_node(node);
    // this->TreeNode_map[node->getID()] = nullptr;
    // // cout << "debug" << endl;
    
    return;
}

void BinaryTree::delete_leaf_node(TreeNode* node) {
    // if (node->getLeftchild() == nullptr && node->getRightchild() == nullptr) {
    //     Console::log("delete leaf node " + to_string(node->getID()));
    // } else {
    //     return;
    // }
    
    // if (node->getBranch() == "root") {
    //     Console::log("delete node is root");
    //     this->root = nullptr;
    // } else {
    //     Console::log("delete node is " + node->getBranch());
    //     if(node->getParent()) node->getParent()->disconnect(node->getBranch());
    // }
}

void BinaryTree::delete_hasOneChild_node(TreeNode* node) {
    TreeNode* successor;
    if (node->getLeftchild() != nullptr && node->getRightchild() == nullptr) {
        successor = node->getLeftchild();
        Console::log("delete has LeftChild node " + to_string(node->getID()));
    } else if (node->getLeftchild() == nullptr && node->getRightchild() != nullptr) {
        successor = node->getRightchild();
        Console::log("delete has RightChild node " + to_string(node->getID()));
    } else {
        return;
    }

    if (node->getBranch() == "root") {
        Console::log("delete node is root");
        this->setRoot(successor);
    } else {
        if(node->getParent()) node->getParent()->setChild(successor, node->getBranch());
    }
}

void BinaryTree::delete_hasBothChild_node(TreeNode* node) {
    // TreeNode* successor;
    // if (node->getLeftchild() != nullptr && node->getRightchild() != nullptr) {
    //     // since node has both children, findRightestNode(node) != nullptr
    //     successor = findRightestNode(node);
    //     Console::log("delete has BothChild node " + to_string(node->getID()));
    //     Console::log("found successor node "  + to_string(successor->getID()));
    //     // Console::log("successor old parent is "  + to_string(successor->getParent()->getID()));
    //     if(successor->getParent()) successor->getParent()->disconnect(successor->getBranch());
    // } else {
    //     return;
    // }

    // if (node->getBranch() == "root") {
    //     Console::log("delete node is root");
    //     this->setRoot(successor);
    // } else {
    //     // cout << "debug" << endl;
    //     successor->setParent(node->getParent(), node->getBranch());
    //     // cout << "debugA" << endl;
    //     // Console::log("successor new parent is " + to_string(successor->getParent()->getID()));
    //     // node must has left child, but right child may be successor        
    //     if (node->getLeftchild()) {
    //         // Console::log("node leftchild is " + to_string(node->getLeftchild()->getID()));
    //         successor->setLeftChild(node->getLeftchild());
    //     }
    //     if (node->getRightchild()) {
    //         successor->setRightChild(node->getRightchild());
    //         // Console::log("node rightchild is " + to_string(node->getRightchild()->getID()));
    //     }
    // }
}

TreeNode* BinaryTree::findRightestNode(TreeNode* node) {
    if (node->getLeftchild() == nullptr && node->getRightchild() == nullptr) {
        return node;
    }
    if (node->getRightchild()) {
        node = findRightestNode(node->getRightchild());
    }
    if (node->getLeftchild()) {
        node = findRightestNode(node->getLeftchild());
    }

    return node;
}

TreeNode* BinaryTree::findLeafNode(TreeNode* node) {
    if (node->getLeftchild() == nullptr && node->getRightchild() == nullptr) {
        return node;
    }
    if(node->getRightchild() && node->getLeftchild()){
        int lr = rand() % 2;
        if(lr == 0){
            node = findLeafNode(node->getLeftchild());
        }else{
            node = findLeafNode(node->getRightchild());
        }
    }else if(node->getLeftchild()){
        node = findLeafNode(node->getLeftchild());
    }else if(node->getRightchild()){
        node = findLeafNode(node->getRightchild());
    }

    return node;
}

vector<TreeNode*> BinaryTree::ExtractTree(int extractID){
    vector<TreeNode*> node_permu;
    stack<TreeNode*> node_stack;
    
    // BinaryTree* dup_tree = this->copy();
    
    node_stack.push(this->TreeNode_map[extractID]);
    
    // Pre-order iterate
    while (node_stack.empty() == false)
    {
        TreeNode* temp = node_stack.top();
        // cout << temp->component_.name << ' ';
        node_permu.push_back(node_stack.top());
        node_stack.pop();

        if (temp->getRightchild())
            node_stack.push(temp->getRightchild());
        if (temp->getLeftchild())
            node_stack.push(temp->getLeftchild());
    }
    // cout <<endl;

    return node_permu;
}

void BinaryTree::ModifyTree(vector<TreeNode*> node_permu){
    stack<TreeNode*> node_stack;
    node_stack.push(this->root);
    int ptr = 0;
    while (node_stack.empty() == false)
    {
        TreeNode* temp = node_stack.top();
        if (temp->getID() != node_permu.at(ptr)->getID() || temp->getComponentState()->getAngle() != node_permu.at(ptr)->getComponentState()->getAngle()) {
            temp->setID(node_permu.at(ptr)->getID());
            temp->setBranch(node_permu.at(ptr)->getBranch());
            temp->setComponentProp(node_permu.at(ptr)->getComponentProp()->copy());
            temp->setComponentState(node_permu.at(ptr)->getComponentState()->copy());
        }
        node_stack.pop();
        if (temp->getRightchild())
            node_stack.push(temp->getRightchild());
        if (temp->getLeftchild())
            node_stack.push(temp->getLeftchild());
        ptr++;
    }
}

void BinaryTree::ModifyDoubleSidedTree(vector<TreeNode*> node_permu_front, vector<TreeNode*> node_permu_back) {
    // BStarTree* new_tree = CopyTree(tree);
    stack<TreeNode*> node_stack;

    // Modify front tree
    node_stack.push(this->root->getLeftchild());
    int ptr = 0;
    while (node_stack.empty() == false)
    {
        TreeNode* temp = node_stack.top();
        // cout << "origin: " << temp->getID() << " modify: " << node_permu_front.at(ptr)->getID() << endl;
        // for(unsigned i=0; i < node_permu_front.size(); i++){
        //     cout << node_permu_front[i]->getID() << " ";
        // }
        // cout << endl;
        if (temp->getID() != node_permu_front.at(ptr)->getID()) {
            temp->setID(node_permu_front[ptr]->getID());
            temp->setBranch(node_permu_front[ptr]->getBranch());
            temp->setComponentProp(node_permu_front[ptr]->getComponentProp()->copy());
            temp->setComponentState(node_permu_front[ptr]->getComponentState()->copy());
        }
        node_stack.pop();
        if (temp->getRightchild())
            node_stack.push(temp->getRightchild());
        if (temp->getLeftchild())
            node_stack.push(temp->getLeftchild());
        ptr++;
    }

    // Modify back tree
    node_stack.push(this->root->getRightchild());
    ptr = 0;
    while (node_stack.empty() == false)
    {
        TreeNode* temp = node_stack.top();
        // cout << "origin: " << temp->getID() << " modify: " << node_permu_back.at(ptr)->getID() << endl;
        if (temp->getID() != node_permu_back.at(ptr)->getID() || temp->getComponentState()->getAngle() != node_permu_back.at(ptr)->getComponentState()->getAngle()) {
            temp->setID(node_permu_back.at(ptr)->getID());
            temp->setBranch(node_permu_back.at(ptr)->getBranch());
            temp->setComponentProp(node_permu_back.at(ptr)->getComponentProp()->copy());
            temp->setComponentState(node_permu_back.at(ptr)->getComponentState()->copy());
        }
        node_stack.pop();
        if (temp->getRightchild())
            node_stack.push(temp->getRightchild());
        if (temp->getLeftchild())
            node_stack.push(temp->getLeftchild());
        ptr++;
    }
}

void BinaryTree::varifyTree(){
    if(this->side != 1 || this->side != 2){
        cout << "side is not correct" << endl;
        exit(0);
    }
    if(this->root == nullptr){
        cout << "root does not exit" << endl;
        exit(0);
    }

    stack<TreeNode*> node_stack;
    node_stack.push(root);
    int ptr = 0;
    while (node_stack.empty() == false)
    {
        TreeNode* temp = node_stack.top();
        if(temp->getID() < -3 || temp->getID() > 35){
            cout << "node ID is not correct" << endl;
            exit(0);
        }else{

        }
        node_stack.pop();
        if (temp->getRightchild())
            node_stack.push(temp->getRightchild());
        if (temp->getLeftchild())
            node_stack.push(temp->getLeftchild());
        ptr++;
    }
}

void BinaryTree::updateTree() {
    if (root == nullptr) {
        return;
    }

    vector<TreeNode*> stack;
    stack.push_back(this->root);
    TreeNode* node;
    while(!stack.empty()) {
        node = stack.back();
        node->updateNode();
        stack.pop_back();
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
    }
}

void BinaryTree::updateTreeNodeMap(){
    this->TreeNode_map.clear();
    vector<TreeNode*> stack;
    stack.push_back(this->root);
    TreeNode* node;
    while(!stack.empty()) {
        node = stack.back();
        stack.pop_back();
        this->TreeNode_map.insert(std::pair<int, TreeNode*>(node->getID(), node));
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
    }
}
