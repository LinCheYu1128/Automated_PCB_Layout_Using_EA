#include "../includes/BinaryTree.h"
#include "../includes/PlotBinaryTree.h"
#include <iostream>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
using namespace std;

BinaryTree::BinaryTree(ComponentList* comp_list) {
    this->comp_list = comp_list;
    // this->root = setBinaryTree(comp_list);
    this->contour = new Contour();
    this->side = 0;  // default value
}

BinaryTree::~BinaryTree() {
    delete this->root;
    delete this->contour;
}

TreeNode* BinaryTree::getRoot() {
    return this->root;
}

void BinaryTree::setBinaryTree() {
    this->root = new TreeNode(this->comp_list->getDataByName("T501"));
    this->root->setLeftchild(this->comp_list->getDataByName("M503"));
    this->root->setRightchild(this->comp_list->getDataByName("D508"));
    this->root->getLeftchild()->setLeftchild(this->comp_list->getDataByName("R532"));
    this->root->getLeftchild()->setRightchild(this->comp_list->getDataByName("Q504"));
    this->root->getLeftchild()->getLeftchild()->setRightchild(this->comp_list->getDataByName("ZD501"));
    this->root->getLeftchild()->getRightchild()->setRightchild(this->comp_list->getDataByName("R517"));
    this->root->getRightchild()->setRightchild(this->comp_list->getDataByName("L501"));

    cout << "construct tree successfully" << endl;
    // return root;
}

void BinaryTree::setSingleSide() {
    this->side = 0;
    vector<int> comp_list_index(this->comp_list->getSize()-3);

    for (int i = 0; i < comp_list_index.size(); i++) {
        comp_list_index[i] = i+3;
    }

    random_shuffle(comp_list_index.begin(), comp_list_index.end());

    int branch_dir = 0;
    int selected_pos = 0;
    int existed_nodes_num = 0;
    ComponentProperty* new_comp;
    TreeNode* selected_node;
    TreeNode* new_node;
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
        branch_dir = rand() % 2;
        selected_pos = rand() % existed_nodes_num;
        selected_node = existed_nodes[selected_pos];
        if (branch_dir == 0) {
            while (selected_node->getLeftchild() != nullptr) {
                int rand_branch = rand() % 2;
                if (rand_branch == 0) {
                    selected_node = selected_node->getLeftchild();
                } else {
                    if (selected_node->getRightchild() != nullptr) {
                        selected_node = selected_node->getRightchild();
                    } else {
                        selected_node = selected_node->getLeftchild();
                    }
                }
            }
            selected_node->setLeftchild(new_comp);
            selected_node->getLeftchild()->setParent(selected_node);
            new_node = selected_node->getLeftchild();
        } else {
            while (selected_node->getRightchild() != nullptr) {
                int rand_branch = rand() % 2;
                if (rand_branch == 0) {
                    if (selected_node->getLeftchild() != nullptr) {
                        selected_node = selected_node->getLeftchild();
                    } else {
                        selected_node = selected_node->getRightchild();
                    }
                } else {
                    selected_node = selected_node->getRightchild();
                }
            }
            selected_node->setRightchild(new_comp);
            selected_node->getRightchild()->setParent(selected_node);
            new_node = selected_node->getRightchild();
        }
        existed_nodes_num += 1;
        existed_nodes.push_back(new_node);
    }
    cout << "construct single side tree successfully" << endl;
}

void BinaryTree::setDoubleSide() {
    this->side = 1;
}

void BinaryTree::printBinaryTree() {
    cout << "start print binary tree" << endl;
    PlotBinaryTree* plot_tree = new PlotBinaryTree(this);
    plot_tree->plotBinaryTree();
}