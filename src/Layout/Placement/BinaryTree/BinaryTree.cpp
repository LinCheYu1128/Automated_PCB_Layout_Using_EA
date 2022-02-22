#include "BinaryTree.h"
#include "PlotBinaryTree.h"
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
using namespace std;

BinaryTree::BinaryTree(ComponentList* comp_list) {
    this->comp_list = comp_list;
    this->side = 0;  // default value
}

BinaryTree::~BinaryTree() {
    delete this->comp_list;
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

BinaryTree* BinaryTree::copy() {
    BinaryTree* new_tree = new BinaryTree(this->comp_list);
    new_tree->setSide(this->side);
    new_tree->setRoot(this->root->copy());
    this->copyByTraverseTree(this->root, new_tree->getRoot());
    return new_tree;
}

void BinaryTree::copyByTraverseTree(TreeNode* old_root, TreeNode* new_root) {
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
    // if (this->root && this->root->getLeftchild()) {
    //     node->setLeftChild(this->root->getLeftchild());
    // }
    // if (this->root && this->root->getRightchild()) {
    //     node->setRightChild(this->root->getRightchild());
    // }
    this->root = node;
    this->root->setBranch("root");
    this->root->disconnect("parent");
}

void BinaryTree::setSide(int side) {
    this->side = side;
}

void BinaryTree::setSingleSide() {
    this->side = 0;
    vector<int> comp_list_index(this->comp_list->getSize()-3);

    for (int i = 0; i < comp_list_index.size(); i++) {
        comp_list_index[i] = i+3;
    }

    random_shuffle(comp_list_index.begin(), comp_list_index.end());

    int parent_pos = 0;
    int existed_nodes_num = 0;
    ComponentProperty* new_comp;
    TreeNode* parent_node;
    TreeNode* child_node;

    for (int i = 0; i < comp_list_index.size(); i++) {
        new_comp = comp_list->getDataByIndex(comp_list_index[i]);

        if (i == 0) {
            // root
            this->setRoot(new TreeNode(new_comp));
            // this->root = new TreeNode(new_comp);
            // this->root->setBranch("root");
            child_node = this->root;
        } else {
            // left & right branch
            parent_pos = rand() % existed_nodes_num;
            parent_node = TreeNode_map[parent_pos];
            child_node = random_construct_tree(parent_node, new_comp);
        }

        child_node->setID(i);
        TreeNode_map[i] = child_node;
        existed_nodes_num += 1;
    }

    cout << "construct single side tree successfully" << endl;
}

void BinaryTree::setDoubleSide() {
    this->side = 1;
    vector<int> comp_list_index(this->comp_list->getSize());

    for (int i = 0; i < comp_list_index.size(); i++) {
        comp_list_index[i] = i;
    }

    random_shuffle(comp_list_index.begin()+3, comp_list_index.end());

    int parent_pos = 0;
    int existed_nodes_num = 0;
    ComponentProperty* new_comp;
    TreeNode* parent_node;
    TreeNode* child_node;
    // vector<TreeNode*> existed_nodes;

    for (int i = 0; i < comp_list_index.size(); i++) {
        new_comp = comp_list->getDataByIndex(comp_list_index[i]);

        if (i == 0) {
            // origin
            // this->root = new TreeNode(new_comp);
            // this->root->setBranch("root");
            this->setRoot(new TreeNode(new_comp));
            child_node = this->root;
        } else if (i == 1) {
            // front_root
            this->root->setLeftChild(new TreeNode(new_comp));
            // this->root->getLeftchild()->setBranch("left");
            child_node = this->root->getLeftchild();
            // child_node->setParent(this->root);
        } else if (i == 2) {
            // back_root
            this->root->setRightChild(new TreeNode(new_comp));
            // this->root->getRightchild()->setBranch("right");
            child_node = this->root->getRightchild();
            // child_node->setParent(this->root);
        } else {
            // left & right branch
            parent_pos = rand() % existed_nodes_num;
            parent_node = TreeNode_map[parent_pos];
            child_node = random_construct_tree(parent_node, new_comp);
        }

        child_node->setID(i);
        TreeNode_map[i] = child_node;
        existed_nodes_num += 1;
    }
    cout << "construct double side tree successfully" << endl;
}

void BinaryTree::printBinaryTree() {
    cout << "start print binary tree" << endl;
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
                // parent_node->getLeftchild()->setParent(parent_node);
                child_node = parent_node->getLeftchild();
                // child_node->setBranch("left");
                break;
            } else {
                parent_node->setRightChild(new TreeNode(new_comp));
                // parent_node->getRightchild()->setParent(parent_node);
                child_node = parent_node->getRightchild();
                // child_node->setBranch("right");
                break;
            }
        }
        parent_node = successors[branch_dir];
        successors[0] = parent_node->getLeftchild();
        successors[1] = parent_node->getRightchild();
    }
    
    return child_node;
}

void BinaryTree::delete_node(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    /* Steps:
       - Find the node we want to delete.
       - Four cases:
        * node with left & right child.
        * node with left/right child only.
        * leaf node.
    */

    this->delete_leaf_node(node);
    this->delete_hasOneChild_node(node);
    // this->delete_hasBothChild_node(node);

    return;
}

void BinaryTree::delete_leaf_node(TreeNode* node) {
    if (node->getLeftchild() == nullptr && node->getRightchild() == nullptr) {
        cout << "delete leaf node " << node->getComponentProp()->getName() << endl;
    } else {
        return;
    }
    
    if (node->getBranch() == "root") {
        cout << "delete node is root" << endl;
        this->root = nullptr;
    } else {
        cout << "delete node is " << node->getBranch() << endl;
        node->getParent()->disconnect(node->getBranch());
    }
    node->disconnect();
}

void BinaryTree::delete_hasOneChild_node(TreeNode* node) {
    TreeNode* successor;
    if (node->getLeftchild() != nullptr && node->getRightchild() == nullptr) {
        successor = node->getLeftchild();
        cout << "delete hasLeftChild node " << node->getComponentProp()->getName() << endl;
    } else if (node->getLeftchild() == nullptr && node->getRightchild() != nullptr) {
        successor = node->getRightchild();
        cout << "delete hasRightChild node " << node->getComponentProp()->getName() << endl;
    } else {
        return;
    }

    if (node->getBranch() == "root") {
        cout << "delete node is root" << endl;
        this->setRoot(successor);
    } else {
        cout << "delete node is " << node->getBranch() << endl;
        node->getParent()->setChild(node->getBranch(), successor);
    }
    node->disconnect();
}

void BinaryTree::delete_hasBothChild_node(TreeNode* node) {
    TreeNode* successor;
    if (node->getLeftchild() != nullptr && node->getRightchild() == nullptr) {
        successor = node->getLeftchild();
        cout << "delete hasLeftChild node " << node->getComponentProp()->getName() << endl;
    } else if (node->getLeftchild() == nullptr && node->getRightchild() != nullptr) {
        successor = node->getRightchild();
        cout << "delete hasRightChild node " << node->getComponentProp()->getName() << endl;
    } else {
        return;
    }

    if (node->getBranch() == "root") {
        cout << "delete node is root" << endl;
        this->setRoot(successor);
        return;
    } else {
        cout << node->getBranch() << endl;
        node->getParent()->setChild(node->getBranch(), successor);
        // successor->setParent(node->getParent());
        // node->setParent(nullptr);
        node->setLeftChild(nullptr);
        node->setRightChild(nullptr);
    }

    return;
}