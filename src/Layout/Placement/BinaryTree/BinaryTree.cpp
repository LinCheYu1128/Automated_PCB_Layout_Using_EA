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
    vector<TreeNode*> existed_nodes;

    for (int i = 0; i < comp_list_index.size(); i++) {
        new_comp = comp_list->getDataByIndex(comp_list_index[i]);
        // root
        if (i == 0) {
            this->root = new TreeNode(new_comp);
            existed_nodes.push_back(this->root);
            existed_nodes_num += 1;
            continue;
        }
        // left & right branch
        parent_pos = rand() % existed_nodes_num;
        parent_node = existed_nodes[parent_pos];
        child_node = random_select_node(parent_node, new_comp);
        existed_nodes_num += 1;
        existed_nodes.push_back(child_node);
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
    vector<TreeNode*> existed_nodes;

    for (int i = 0; i < comp_list_index.size(); i++) {
        new_comp = comp_list->getDataByIndex(comp_list_index[i]);
        // origin, front_root, back_root
        if (i == 0) {
            this->root = new TreeNode(new_comp);
            existed_nodes.push_back(this->root);
            existed_nodes_num += 1;
            continue;
        }
        if (i == 1) {
            this->root->setLeftchild(new_comp);
            this->root->getLeftchild()->setParent(this->root);
            existed_nodes.push_back(this->root->getLeftchild());
            existed_nodes_num += 1;
            continue;
        }
        if (i == 2) {
            this->root->setRightchild(new_comp);
            this->root->getRightchild()->setParent(this->root);
            existed_nodes.push_back(this->root->getRightchild());
            existed_nodes_num += 1;
            continue;
        }
        // left & right branch
        parent_pos = rand() % existed_nodes_num;
        parent_node = existed_nodes[parent_pos];
        cout << "parent_node: " << parent_node->getComponentProp()->getName() << endl;
        child_node = random_select_node(parent_node, new_comp);
        cout << "child_node: " << child_node->getComponentProp()->getName() << endl;
        existed_nodes_num += 1;
        existed_nodes.push_back(child_node);
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
                parent_node->setLeftchild(new_comp);
                parent_node->getLeftchild()->setParent(parent_node);
                child_node = parent_node->getLeftchild();
                break;
            } else {
                parent_node->setRightchild(new_comp);
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