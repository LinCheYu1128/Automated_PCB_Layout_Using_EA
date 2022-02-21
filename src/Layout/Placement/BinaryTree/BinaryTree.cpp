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

BinaryTree* BinaryTree::copy() {
    BinaryTree* new_tree = new BinaryTree(this->comp_list);
    new_tree->setSide(this->side);
    TreeNode* new_root = new_tree->getRoot();
    new_root->setTreeNode(this->root);
    this->copyNode(new_root);
    return new_tree;
}

void BinaryTree::copyNode(TreeNode* parent) {
    if (parent->getLeftchild() != nullptr) {
        TreeNode* left_child = parent->getLeftchild()->copy();
        parent->setLeftchild(left_child);
        this->copyNode(parent->getLeftchild());
    }
    if (parent->getRightchild() != nullptr) {
        TreeNode* right_child = parent->getRightchild()->copy();
        parent->setRightchild(right_child);
        this->copyNode(parent->getRightchild());
    }
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
            this->root = new TreeNode(new_comp);
            child_node = this->root;
        } else {
            // left & right branch
            parent_pos = rand() % existed_nodes_num;
            parent_node = TreeNode_map[parent_pos];
            child_node = random_select_node(parent_node, new_comp);
        }

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
            this->root = new TreeNode(new_comp);
            child_node = this->root;
        } else if (i == 1) {
            // front_root
            this->root->setLeftchild(new TreeNode(new_comp));
            child_node = this->root->getLeftchild();
            child_node->setParent(this->root);
        } else if (i == 2) {
            // back_root
            this->root->setRightchild(new TreeNode(new_comp));
            child_node = this->root->getRightchild();
            child_node->setParent(this->root);
        } else {
            // left & right branch
            parent_pos = rand() % existed_nodes_num;
            parent_node = TreeNode_map[parent_pos];
            child_node = random_select_node(parent_node, new_comp);
        }

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

TreeNode* random_select_node(TreeNode* parent_node, ComponentProperty* new_comp) {
    int branch_dir;
    TreeNode* child_node;
    vector<TreeNode*> successors;
    successors.push_back(parent_node->getLeftchild());
    successors.push_back(parent_node->getRightchild());

    while (true) {
        branch_dir = rand() % 2;
        if (successors[branch_dir] == nullptr) {
            if (branch_dir == 0) {
                parent_node->setLeftchild(new TreeNode(new_comp));
                parent_node->getLeftchild()->setParent(parent_node);
                child_node = parent_node->getLeftchild();
                break;
            } else {
                parent_node->setRightchild(new TreeNode(new_comp));
                parent_node->getRightchild()->setParent(parent_node);
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