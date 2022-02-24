#include "GA.h"
#include "console.h"
#include "BinaryTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

Layout*leftSubtreeCrossover(vector<Layout*>Parents){
    // cout << "start crossover"<<endl;
    ComponentList* component_list = new ComponentList();

    BinaryTree *BTreeA = Parents.at(0)->getBinaryTree()->copy();
    BTreeA->printBinaryTree();
    while (BTreeA->getRoot()->getRightchild()){
        BTreeA->delete_node(BTreeA->getRoot()->getRightchild()->getID());
    }
    BTreeA->printBinaryTree();
    vector<int> ArraytoDelete;
    vector<TreeNode*> stack;
    stack.push_back(BTreeA->getRoot());
    TreeNode* node;
    while(!stack.empty()) {
        node = stack.back();
        stack.pop_back();
        ArraytoDelete.push_back(node->getID());
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
    }
    cout << "remaining nod number = " << ArraytoDelete.size() << endl;
    
    BinaryTree *BTreeB = Parents.at(1)->getBinaryTree()->copy();
    BTreeB->printBinaryTree();
    for(int item = 1; item<ArraytoDelete.size(); item++){
        BTreeB->delete_node(item);
        cout << "delete node "<<item<<endl;
        // BTreeB->printBinaryTree();
    }
    BTreeB->printBinaryTree();
    TreeNode* newroot = BTreeB->findRightestNode(BTreeB->getRoot());
    cout << BTreeB->getRoot()->getID() << endl;
    if(newroot->getID()==0){
        return new Layout(BTreeA, component_list, 1);
    }
    else{
        BTreeB->changetoroot(newroot);
        // cout << "delete node "<<0<<endl;
        BTreeB->printBinaryTree();
    }
    // cout << BTreeA->getTreeNodeMap().size() << endl;
    // Layout* offspring = new Layout(component_list, 1);
    // offspring->getBinaryTree()->printBinaryTree();
    // vector<int> left
    // 
    // parentB->printBinaryTree();
    cout << "end crossover"<<endl;
    return new Layout(BTreeA, component_list, 1);
}