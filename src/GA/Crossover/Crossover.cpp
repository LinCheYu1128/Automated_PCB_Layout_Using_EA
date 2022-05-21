#include "GA.h"
#include "console.h"
#include "BinaryTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<TreeNode*> ExtractTreeWithTreeNode(BinaryTree* Tree){
    vector<TreeNode*> nodelist;
    vector<TreeNode*> stack;
    stack.push_back(Tree->getRoot());
    TreeNode* node;
    while(!stack.empty()) {
        node = stack.back();
        stack.pop_back();
        if(node->getID()!=-2 && node->getID()!= -3) nodelist.push_back(node);
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
    }
    nodelist.erase(nodelist.begin(),nodelist.begin()+1);

    return nodelist;
}

vector<TreeNode*> ExtractLeftTreeWithTreeNode(BinaryTree* Tree){
    vector<TreeNode*> nodelist;
    vector<TreeNode*> stack;
    stack.push_back(Tree->getRoot()->getLeftchild());
    TreeNode* node;
    while(!stack.empty()) {
        node = stack.back();
        stack.pop_back();
        if(node->getID()!=-2 && node->getID()!= -3) nodelist.push_back(node);
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
    }
    nodelist.erase(nodelist.begin(),nodelist.begin()+1);

    return nodelist;
}

Layout*leftSubtreeCrossover(vector<Layout*>Parents){
    // cout << "start crossover"<<endl;
    // ComponentList* component_list = new ComponentList();
    ComponentList* component_list = Parents.at(0)->getBinaryTree()->getComponentList();

    BinaryTree *BTree_temp = Parents.at(0)->getBinaryTree()->copy();
    BinaryTree *BTreeA = Parents.at(0)->getBinaryTree()->copy();
    // vector <TreeNode*> nodelistA_O = ExtractTreeWithTreeNode(BTreeA);
    // vector <TreeNode*> nodelistA = ExtractLeftTreeWithTreeNode(BTreeA);
    
    cout << "Tree A : "<<endl;
    BTreeA->printBinaryTree();
    while (BTreeA->getRoot()->getRightchild()){
        BTreeA->delete_node(BTreeA->getRoot()->getRightchild()->getID());
    }
    cout << "left subtree : "<<endl;
    BTreeA->printBinaryTree();
    vector<int> ArraytoDelete;
    vector<TreeNode*> stack;
    // stack.push_back(BTreeA->getRoot());
    // TreeNode* node;
    // while(!stack.empty()) {
    //     node = stack.back();
    //     stack.pop_back();
    //     ArraytoDelete.push_back(node->getID());
    //     if (node->getRightchild() != nullptr) {
    //         stack.push_back(node->getRightchild());
    //     }
    //     if (node->getLeftchild() != nullptr) {
    //         stack.push_back(node->getLeftchild());
    //     }
    // }
    // // cout << "number of remaining nodes = " << ArraytoDelete.size() << endl;
    
    // BinaryTree *BTreeB = Parents.at(1)->getBinaryTree()->copy();
    // // cout << "origin BTreeB : "<<endl;
    // // BTreeB->printBinaryTree();
    // for(unsigned int item = 1; item<ArraytoDelete.size(); item++){
    //     BTreeB->delete_node(ArraytoDelete.at(item));
    //     // cout << "delete node "<<ArraytoDelete.at(item)<<endl;
    //     // BTreeB->printBinaryTree();
    // }
    // // cout << "after delete BTreeB : "<<endl;
    // // BTreeB->printBinaryTree();
    // TreeNode* newroot = BTreeB->findRightestNode(BTreeB->getRoot());
    // // cout << "new root id : " << newroot->getID() << endl;
    // if(newroot->getID()==0){
    //     return new Layout(BTreeA, component_list, 1);
    // }
    // else{
    //     BTreeB->changetoroot(newroot);
    //     // cout << "right subtree : "<<endl;
    //     // BTreeB->printBinaryTree();
    // }
    // // cout << "BTreeA tree map size = "<<BTreeA->getTreeNodeMap().size() << endl;
    // BTreeA->getRoot()->setRightChild(BTreeB->getRoot());
    // // BTreeA->printBinaryTree();
    // // cout << "end crossover"<<endl;
    BTreeA->updateTreeNodeMap();
    return new Layout(BTree_temp, component_list, BTreeA->getSide());
}

Layout*randomSubtreeCrossover(vector<Layout*>Parents){
    ComponentList* component_list = Parents.at(0)->getBinaryTree()->getComponentList();

    BinaryTree *BTreeA = Parents.at(0)->getBinaryTree()->copy();
    // BTreeA->printBinaryTree();
    
    vector<TreeNode*> nodelist = ExtractTreeWithTreeNode(BTreeA);
    int amount = nodelist.size();
    TreeNode* picked_node = nodelist.at(rand() % (amount-1));
    while(picked_node->getID() <= 0){
       picked_node = nodelist.at(rand() % (amount-1)); 
    }
    // cout << "picked_node: " << picked_node->getComponentProp()->getName() << endl;

    picked_node->disconnect("parent");
    // BTreeA->printBinaryTree();
    vector<TreeNode*> picked_node_list; // get the subtree of pick node
    vector<TreeNode*> stack;
    stack.push_back(picked_node);
    TreeNode* node;
    while(!stack.empty()) {
        node = stack.back();
        stack.pop_back();
        picked_node_list.push_back(node);
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
    }

    BinaryTree *BTreeB = Parents.at(1)->getBinaryTree()->copy(); // get the insert position from tree b
    
    amount = picked_node_list.size() ;
    for(int i=0; i<amount; i++){
        // cout << item->getID() << endl;
        BTreeB->delete_node(picked_node_list.at(i)->getID());
    }
    
    // BTreeB->printBinaryTree();
    vector<TreeNode*> target_list;
    // vector<TreeNode*> stack;
    stack.push_back(BTreeB->getRoot());
    while(!stack.empty()) {
        node = stack.back();
        stack.pop_back();
        if(!node->getLeftchild() || !node->getRightchild()){
            target_list.push_back(node);
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
    }
    // for(auto item: target_list) cout << item->getComponentProp()->getName() << " ";
    TreeNode* target_node = target_list.at(rand() % (target_list.size()));
    // cout << "target node = "<< target_node->getComponentProp()->getName()<< endl;

    if(!target_node->getLeftchild()){
        target_node->setLeftChild(picked_node);
    }
    else if(!target_node->getRightchild()){
        target_node->setRightChild(picked_node);
    }
    else{
        cout << "something wrong" << endl;
    } 
    // BTreeB->printBinaryTree();
    // cout << "BTreeA tree map size = "<<BTreeA->getTreeNodeMap().size() << endl;
    // BTreeA->getRoot()->setRightChild(BTreeB->getRoot());
    // 
    // cout << "end crossover"<<endl;
    
    BTreeB->updateTreeNodeMap();
    delete BTreeA;
    // delete BTreeB;
    // cout << "crossover done" << endl;
    return new Layout(BTreeB, component_list, BTreeB->getSide());
}

vector<int> ExtractTreeWithID(BinaryTree* Tree){
    vector<int> nodelist;
    vector<TreeNode*> stack;
    stack.push_back(Tree->getRoot());
    TreeNode* node;
    while(!stack.empty()) {
        node = stack.back();
        stack.pop_back();
        nodelist.push_back(node->getID());
        if (node->getRightchild() != nullptr) {
            stack.push_back(node->getRightchild());
        }
        if (node->getLeftchild() != nullptr) {
            stack.push_back(node->getLeftchild());
        }
    }
    nodelist.erase(nodelist.begin(),nodelist.begin()+1);
    return nodelist;
}

bool checknodeexist(vector<TreeNode*> list, int index){
    for(auto item: list){
        if(item->getID()==index) return true;
    }
    return false;
}

Layout*kPointCrossover(vector<Layout*>Parents, int k){
    // cout << "start crossover"<<endl;
    // ComponentList* component_list = new ComponentList();

    // cout << "=========Parents=========" << endl;
    // for(unsigned i = 0; i < Parents.size(); i++){
    //     Parents[i]->getBinaryTree()->printBinaryTreeInPreorder();
    // }

    ComponentList* component_list = Parents.at(0)->getBinaryTree()->getComponentList();
    BinaryTree *BTreeA = Parents.at(0)->getBinaryTree()->copy();
    // BTreeA->printBinaryTree();
    BinaryTree *BTreeB = Parents.at(1)->getBinaryTree();

    int amount = BTreeA->getTreeNodeMap().size();

    vector<TreeNode*> nodelistA = ExtractTreeWithTreeNode(BTreeA);
    vector<TreeNode*> nodelistB = ExtractTreeWithTreeNode(BTreeB);
    // cout << "nodelist A = ";
    // for(auto point: nodelistA){
    //     cout << point->getID() << " ";
    // }
    // cout << endl;
    // cout << "nodelist B = ";
    // for(auto point: nodelistA){
    //     cout << point->getID() << " ";
    // }
    // cout << endl;
    
    vector<unsigned int> cutpoint;
    for (int i = 0; i < amount; i++){
        cutpoint.push_back(i);
    }
    random_shuffle(cutpoint.begin(), cutpoint.end());
    cutpoint.erase(cutpoint.begin()+k, cutpoint.end());
    sort(cutpoint.begin(),cutpoint.end());
    for (unsigned int i = 0; i < nodelistA.size(); i++){
        for (int t = 0; t < k-1; t++) {
            if(t%2 == 0 && (i < cutpoint.at(t) || i > cutpoint.at(t+1))){
                nodelistA.at(i)->setID(-4);
            }
        } 
    }

    unsigned int j = 0;
    ComponentProperty *CompProp;
    ComponentState *CompSt;
    // if(checknodeexist(nodelistA, 0)) cout<<"yes"<<endl;
    // else cout << "no" << endl;
    // TreeNode* node;
    for(auto point: nodelistA){
        if(point->getID()!=-4) continue;
        while(checknodeexist(nodelistA, nodelistB.at(j)->getID())){
            j++;
        }
        // for(auto point: nodelistA){
        //     cout << point->getID() << " ";
        // }
        // cout << endl;
        CompProp = nodelistB.at(j)->getComponentProp();
        CompSt = nodelistB.at(j)->getComponentState();
        point->setComponentProp(CompProp);
        point->setComponentState(CompSt);
        point->setID(nodelistB.at(j)->getID());
    }
    // cout << "nodelist child = ";
    // for(auto point: nodelistA){
    //     cout << point->getID() << " ";
    // }
    // cout << endl;
    
    // BTreeA->printBinaryTree();
    // cout << "end crossover"<<endl;
    BTreeA->updateTreeNodeMap();
    return new Layout(BTreeA, component_list, BTreeA->getSide());
}

Layout* nothingCrossover(vector<Layout*>Parents){

    // ComponentList* component_list = Parents.at(0)->getBinaryTree()->getComponentList();

    // BinaryTree *BTreeA = Parents.at(0)->getBinaryTree()->copy();
    Layout* new_layout = Parents.at(0)->copy();
    // Layout* new_layout = new Layout(component_list, 2);

    return new_layout;
}

void delete_test (vector<Layout*>Parents){
    BinaryTree *BTreeA = Parents.at(0)->getBinaryTree()->copy();
    BTreeA->printBinaryTree();
    while (BTreeA->getRoot()->getRightchild()){
        BTreeA->delete_node(BTreeA->getRoot()->getRightchild()->getID());
    }
    cout << "left subtree : "<<endl;
    BTreeA->printBinaryTree();
}