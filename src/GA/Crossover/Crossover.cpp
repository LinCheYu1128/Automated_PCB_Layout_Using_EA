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
    cout << "left subtree : "<<endl;
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
    cout << "number of remaining nodes = " << ArraytoDelete.size() << endl;
    
    BinaryTree *BTreeB = Parents.at(1)->getBinaryTree()->copy();
    cout << "origin BTreeB : "<<endl;
    BTreeB->printBinaryTree();
    for(unsigned int item = 1; item<ArraytoDelete.size(); item++){
        BTreeB->delete_node(item);
        cout << "delete node "<<ArraytoDelete.at(item)<<endl;
        // BTreeB->printBinaryTree();
    }
    cout << "after delete BTreeB : "<<endl;
    BTreeB->printBinaryTree();
    TreeNode* newroot = BTreeB->findRightestNode(BTreeB->getRoot());
    cout << "new root id : " << newroot->getID() << endl;
    if(newroot->getID()==0){
        return new Layout(BTreeA, component_list, 1);
    }
    else{
        BTreeB->changetoroot(newroot);
        cout << "right subtree : "<<endl;
        BTreeB->printBinaryTree();
    }
    cout << "BTreeA tree map size = "<<BTreeA->getTreeNodeMap().size() << endl;
    BTreeA->getRoot()->setRightChild(BTreeB->getRoot());
    BTreeA->printBinaryTree();
    cout << "end crossover"<<endl;
    return new Layout(BTreeA, component_list, 1);
}

Layout*kPointCrossover(vector<Layout*>Parents){
    // cout << "start crossover"<<endl;
    ComponentList* component_list = new ComponentList();

    BinaryTree *BTreeA = Parents.at(0)->getBinaryTree()->copy(); 
    cout << "order subtree : "<<endl;
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
    cout << "number of remaining nodes = " << ArraytoDelete.size() << endl;
    
    // BinaryTree *BTreeB = Parents.at(1)->getBinaryTree()->copy();
    // cout << "origin BTreeB : "<<endl;
    // BTreeB->printBinaryTree();
    // for(unsigned int item = 1; item<ArraytoDelete.size(); item++){
    //     BTreeB->delete_node(item);
    //     cout << "delete node "<<ArraytoDelete.at(item)<<endl;
    //     // BTreeB->printBinaryTree();
    // }
    // cout << "after delete BTreeB : "<<endl;
    // BTreeB->printBinaryTree();
    // TreeNode* newroot = BTreeB->findRightestNode(BTreeB->getRoot());
    // cout << "new root id : " << newroot->getID() << endl;
    // if(newroot->getID()==0){
    //     return new Layout(BTreeA, component_list, 1);
    // }
    // else{
    //     BTreeB->changetoroot(newroot);
    //     cout << "right subtree : "<<endl;
    //     BTreeB->printBinaryTree();
    // }
    // cout << "BTreeA tree map size = "<<BTreeA->getTreeNodeMap().size() << endl;
    // BTreeA->getRoot()->setRightChild(BTreeB->getRoot());
    // BTreeA->printBinaryTree();
    // cout << "end crossover"<<endl;
    return new Layout(BTreeA, component_list, 1);
}