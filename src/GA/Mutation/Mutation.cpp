#include "GA.h"
#include "console.h"
#include "BinaryTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

void swapBranchMutation(Layout *input){
    cout << "conduct swapBranchMutation" << endl;

    int componentsize = input->getComponentNum();

    int targetId = rand() % componentsize;
    BinaryTree* inputtree = input->getTree();
    map<int, TreeNode*> tempmap = inputtree->getTreeNodeMap();
    TreeNode* targetnode = tempmap[targetId];

    while(targetnode->getLeftchild() == nullptr || targetnode->getRightchild() == nullptr){
        targetId = rand() % componentsize;
        inputtree = input->getTree();
        tempmap = inputtree->getTreeNodeMap();
        targetnode = tempmap[targetId];
    }

    int leftchild = targetnode->getLeftchild()->getID();
    int rightchild = targetnode->getRightchild()->getID();

    inputtree->swap(leftchild, rightchild);

}
void swapSubtreeMutation(Layout *input){
    // cout << "conduct swapSubtreeMutation" << endl;

    // int componentsize = input->getComponentNum();

    // int s1 = rand() % componentsize;
    // int s2 = rand() % componentsize;

    // BinaryTree* inputtree = input->getTree();
    // map<int, TreeNode*> inputmap = inputtree->getTreeNodeMap();

    // while(s1 == s2 || inputmap[s1]->search(s2)){

    // }

}
void bitwiseMutation(Layout *input){
    cout << "conduct bitwiseMutation" << endl;
}
void shiftSubtreeMutation(Layout *input){
    cout << "conduct shiftSubtreeMutation" << endl;
}
void insertMutation(Layout *input){
    cout << "conduct insertMutation" << endl;
}
void scrambleMutation(Layout *input){
    cout << "conduct scrambleMutation" << endl;
}
void swapNodeMutation(Layout *input){
    cout << "conduct swapNodeMutation" << endl;
}