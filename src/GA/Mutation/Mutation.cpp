#include "GA.h"
#include "console.h"
#include "Layout.h"
#include <iostream>
#include <algorithm>
using namespace std;

int MyRandom (int i) { return std::rand()%i;}

void swapBranchMutation(Layout *input){
    // cout << "conduct swapBranchMutation" << endl;

    int componentsize = input->getComponentNum();

    BinaryTree* inputtree = input->getBinaryTree();
    map<int, TreeNode*> tempmap = inputtree->getTreeNodeMap();

    int targetId = rand() % componentsize;
    TreeNode* targetnode = tempmap[targetId];

    while(targetnode->getLeftchild() == nullptr || targetnode->getRightchild() == nullptr){
        targetId = rand() % componentsize;
        inputtree = input->getBinaryTree();
        tempmap = inputtree->getTreeNodeMap();
        targetnode = tempmap[targetId];
    }

    int leftchild = targetnode->getLeftchild()->getID();
    int rightchild = targetnode->getRightchild()->getID();

    Console::log("parent = " + to_string(targetId));
    Console::log("left child = " + to_string(leftchild));
    Console::log("right child = " + to_string(rightchild));

    inputtree->swap(leftchild, rightchild);

}

void swapSubtreeMutation(Layout *input){
    // cout << "conduct swapSubtreeMutation" << endl;

    int componentsize = input->getComponentNum();

    BinaryTree* inputtree = input->getBinaryTree();
    map<int, TreeNode*> inputmap = inputtree->getTreeNodeMap();

    int s1 = rand() % componentsize;
    int s2 = rand() % componentsize;

    while(s1 == s2 || inputmap[s1]->search(s2) || inputmap[s2]->search(s1)){
        s1 = rand() % componentsize;
        s2 = rand() % componentsize;
    }
    // cout << inputmap[s1]->getComponentProp()->getName() << endl;
    // cout << inputmap[s2]->getComponentProp()->getName() << endl;
    inputtree->swap(s1, s2);

}

void bitwiseMutation(Layout *input,  double prob){
    // cout << "conduct bitwiseMutation" << endl;

    int componentsize = input->getComponentNum();

    BinaryTree* inputtree = input->getBinaryTree();
    map<int, TreeNode*> inputmap = inputtree->getTreeNodeMap();

    // for(int i=0; i < componentsize; i++){
    //     cout << inputmap[i]->getComponentState()->getAngle() << " ";
    // }
    // cout << endl;

    for(int i = 0; i < componentsize; i++){
        double x = (double) rand() / (RAND_MAX + 1.0);
        if(x <= prob){
            int angle = rand() % 4;
            while(inputmap[i]->getComponentState()->getAngle() / 90 == angle){
                angle = rand() % 4;
            }
            inputmap[i]->getComponentState()->setAngle(90*angle);
        }
    }

    // for(int i=0; i < componentsize; i++){
    //     cout << inputmap[i]->getComponentState()->getAngle() << " ";
    // }
    // cout << endl;
}

void shiftSubtreeMutation(Layout *input){
    // cout << "conduct shiftSubtreeMutation" << endl;

    int componentsize = input->getComponentNum();

    // cout << "test 1" << endl;

    BinaryTree* inputtree = input->getBinaryTree();
    map<int, TreeNode*> inputmap = inputtree->getTreeNodeMap();

    // cout << "test 2" << endl;

    int targetId = rand() % componentsize;
    TreeNode* targetnode = inputmap[targetId];
    while(targetnode->getBranch() == "root"){
        targetId = rand() % componentsize;
        targetnode = inputmap[targetId];
    }
    // cout << "targetnode ID: " << targetId << endl;
    int targetparentID = targetnode->getParent()->getID();

    // cout << "targetparent ID: " << targetparentID << endl;

    targetnode->disconnect("parent");

    // cout << "test 3" << endl;

    TreeNode* leaf = inputtree->findLeafNode(inputtree->getRoot());

    // cout << "test 4" << endl;
    while(leaf->getID() == targetparentID && inputmap[targetparentID]->getBranch() != "root"){
        leaf = inputtree->findLeafNode(inputtree->getRoot());
    }

    // cout << "leaf: " << leaf->getID() << endl;

    int branch_dir = rand() % 2;
    if(branch_dir == 0){
        // cout << "add leftchild" << endl;
        leaf->setLeftChild(targetnode);
    }else{
        // cout << "add rightchild" << endl;
        leaf->setRightChild(targetnode);
    }

}

void insertMutation(Layout *input){
    // cout << "conduct insertMutation" << endl;

    BinaryTree* inputtree = input->getBinaryTree();
    map<int, TreeNode*> inputmap = inputtree->getTreeNodeMap();

    if(inputtree->getSide() == 1){
        vector<TreeNode*> node_permu;
        node_permu = inputtree->ExtractTree(0);
        // node_permu = ExtractTree(dup_tree->root);

        int amount = node_permu.size();
        int mutate_p1 = 0, mutate_p2 = 0;
        while (mutate_p1 == mutate_p2 || mutate_p1 == mutate_p2 +1 || mutate_p2 == mutate_p1 +1 || mutate_p1 == 0 || mutate_p2 == 0 ) {
            mutate_p1 = rand() % amount;
            mutate_p2 = rand() % amount;
        }

        int pivot = mutate_p2;
        TreeNode *key_node = node_permu.at(mutate_p2);

        // cout << "Insertion point: " << node_permu.at(mutate_p1)->getID() << " and " << node_permu.at(mutate_p2)->getID() << endl;

        // for(unsigned i=0; i < node_permu.size(); i++){
        //     cout << node_permu[i]->getID() << " ";
        // }
        // cout << endl;

        if (mutate_p1 < mutate_p2){
            while (pivot > mutate_p1) {
                node_permu.at(pivot) = node_permu.at(pivot-1);
                pivot--;
            }
            node_permu.at(mutate_p1+1) = key_node;
        }
        else {
            while (pivot < mutate_p1) {
                node_permu.at(pivot) = node_permu.at(pivot+1);
                pivot++;
            }
            node_permu.at(mutate_p1-1) = key_node;
        }

        // for(unsigned i=0; i < node_permu.size(); i++){
        //     cout << node_permu[i]->getID() << " ";
        // }
        // cout << endl;

        inputtree->ModifyTree(node_permu);
    }else if(inputtree->getSide() == 2){
        vector<TreeNode*> node_permu_front;
        vector<TreeNode*> node_permu_back;
        node_permu_front = inputtree->ExtractTree(-2);
        node_permu_back = inputtree->ExtractTree(-3);

        node_permu_front.erase(node_permu_front.begin());
        node_permu_back.erase(node_permu_back.begin());

        int front_size = node_permu_front.size();
        int back_size = node_permu_back.size();
        node_permu_front.insert(node_permu_front.end(), node_permu_back.begin(), node_permu_back.end());
        node_permu_back.clear();
        int amount = node_permu_front.size();

        // for(unsigned i=0; i < node_permu_front.size(); i++){
        //     cout << node_permu_front[i]->getID() << " ";
        // }
        // cout << endl;


        int mutate_p1 = 0, mutate_p2 = 0;
        while (mutate_p1 == mutate_p2 || mutate_p1 == mutate_p2 +1 || mutate_p2 == mutate_p1 +1) {
            mutate_p1 = rand() % amount;
            mutate_p2 = rand() % amount;
        }

        int pivot = mutate_p2;
        TreeNode *key_node = node_permu_front.at(mutate_p2);

        // cout << "Insertion point: " << node_permu_front.at(mutate_p1)->getID() << " and " << node_permu_front.at(mutate_p2)->getID() << endl;

        if (mutate_p1 < mutate_p2){
            while (pivot > mutate_p1) {
                node_permu_front.at(pivot) = node_permu_front.at(pivot-1);
                pivot--;
            }
            node_permu_front.at(mutate_p1+1) = key_node;
        }
        else {
            while (pivot < mutate_p1) {
                node_permu_front.at(pivot) = node_permu_front.at(pivot+1);
                pivot++;
            }
            node_permu_front.at(mutate_p1-1) = key_node;
        }

        // for(unsigned i=0; i < node_permu_front.size(); i++){
        //     cout << node_permu_front[i]->getID() << " ";
        // }
        // cout << endl;

        int n = 0;
        while (node_permu_back.size() != back_size) {
            node_permu_back.push_back(node_permu_front.at(front_size + n));
            n++;
        }

        node_permu_front.insert(node_permu_front.begin(), inputtree->getRoot()->getLeftchild());
        node_permu_back.insert(node_permu_back.begin(), inputtree->getRoot()->getRightchild());

        inputtree->ModifyDoubleSidedTree(node_permu_front, node_permu_back);
    }

}

void scrambleMutation(Layout *input){
    // cout << "conduct scrambleMutation" << endl;

    BinaryTree* inputtree = input->getBinaryTree();
    map<int, TreeNode*> inputmap = inputtree->getTreeNodeMap();

    if(inputtree->getSide() == 1){
        vector<TreeNode*> node_permu;
        node_permu = inputtree->ExtractTree(0);
        int amount = node_permu.size();
        vector<TreeNode*> scramble_list;

        // for(unsigned i=0; i < node_permu.size(); i++){
        //     cout << node_permu[i]->getID() << " ";
        // }
        // cout << endl;

        int mutate_p1 = 0, mutate_p2 = 0;
        while (mutate_p1 == mutate_p2 || mutate_p1 == 0 || mutate_p2 == 0){
            mutate_p1 = rand() % amount;
            mutate_p2 = rand() % amount;
        }
        if (mutate_p2 < mutate_p1){
            swap(mutate_p1, mutate_p2);
        }

        // cout << "m1: " << node_permu.at(mutate_p1)->getID() << "  m2: " << node_permu.at(mutate_p2)->getID() << endl;

        int pivot = mutate_p1;
        while (pivot <= mutate_p2){
            scramble_list.push_back(node_permu.at(pivot));
            pivot++;
        }

        random_shuffle(scramble_list.begin(), scramble_list.end(), MyRandom);

        pivot = mutate_p1;
        while (pivot <= mutate_p2){
            node_permu.at(pivot) = scramble_list.at(pivot-mutate_p1);
            pivot++;
        }

        // for(unsigned i=0; i < node_permu.size(); i++){
        //     cout << node_permu[i]->getID() << " ";
        // }
        // cout << endl;

        inputtree->ModifyTree(node_permu);
    }else if(inputtree->getSide() == 2){
        vector<TreeNode*> node_permu_front;
        vector<TreeNode*> node_permu_back;
        node_permu_front = inputtree->ExtractTree(-2);
        node_permu_back = inputtree->ExtractTree(-3);

        node_permu_front.erase(node_permu_front.begin());
        node_permu_back.erase(node_permu_back.begin());

        int front_size = node_permu_front.size();
        int back_size = node_permu_back.size();
        node_permu_front.insert(node_permu_front.end(), node_permu_back.begin(), node_permu_back.end());
        node_permu_back.clear();
        int amount = node_permu_front.size();

        // for(unsigned i=0; i < node_permu_front.size(); i++){
        //     cout << node_permu_front[i]->getID() << " ";
        // }
        // cout << endl;

        vector<TreeNode*> scramble_list;
        int mutate_p1 = 0, mutate_p2 = 0;
        while (mutate_p1 == mutate_p2 || mutate_p1 == 0 || mutate_p2 == 0){
            mutate_p1 = rand() % amount;
            mutate_p2 = rand() % amount;
        }
        if (mutate_p2 < mutate_p1){
            swap(mutate_p1, mutate_p2);
        }

        // cout << "m1: " << node_permu_front.at(mutate_p1)->getID() << "  m2: " << node_permu_front.at(mutate_p2)->getID() << endl;

        int pivot = mutate_p1;
        while (pivot <= mutate_p2){
            scramble_list.push_back(node_permu_front.at(pivot));
            pivot++;
        }

        random_shuffle(scramble_list.begin(), scramble_list.end(), MyRandom);

        pivot = mutate_p1;
        while (pivot <= mutate_p2){
            node_permu_front.at(pivot) = scramble_list.at(pivot-mutate_p1);
            pivot++;
        }

        // for(unsigned i=0; i < node_permu_front.size(); i++){
        //     cout << node_permu_front[i]->getID() << " ";
        // }
        // cout << endl;

        int n = 0;
        while (node_permu_back.size() != back_size) {
            node_permu_back.push_back(node_permu_front.at(front_size + n));
            n++;
        }

        node_permu_front.insert(node_permu_front.begin(), inputtree->getRoot()->getLeftchild());
        node_permu_back.insert(node_permu_back.begin(), inputtree->getRoot()->getRightchild());

        inputtree->ModifyDoubleSidedTree(node_permu_front, node_permu_back);
    }

}

void swapNodeMutation(Layout *input){
    // cout << "conduct swapNodeMutation" << endl;

    BinaryTree* inputtree = input->getBinaryTree();
    map<int, TreeNode*> inputmap = inputtree->getTreeNodeMap();

    if(inputtree->getSide() == 1){
        vector<TreeNode*> node_permu;
        node_permu = inputtree->ExtractTree(0);
        int amount = node_permu.size();

        int mutate_p1 = 0, mutate_p2 = 0;
        while (mutate_p1 == mutate_p2 || mutate_p1 == 0 || mutate_p2 == 0){
            mutate_p1 = rand() % amount;
            mutate_p2 = rand() % amount;
        }

        // cout << node_permu.at(mutate_p1)->getID() << " swap with " << node_permu.at(mutate_p2)->getID() << endl;

        swap(node_permu.at(mutate_p1), node_permu.at(mutate_p2));
        inputtree->ModifyTree(node_permu);

    }else if(inputtree->getSide() == 2){

        vector<TreeNode*> node_permu_front;
        vector<TreeNode*> node_permu_back;
        node_permu_front = inputtree->ExtractTree(-2);
        node_permu_back = inputtree->ExtractTree(-3);

        int front_size = node_permu_front.size();
        int back_size = node_permu_back.size();
        node_permu_front.insert(node_permu_front.end(), node_permu_back.begin(), node_permu_back.end());
        node_permu_back.clear();
        int amount = node_permu_front.size();

        // for(unsigned i=0; i < node_permu_front.size(); i++){
        //     cout << node_permu_front[i]->getID() << " ";
        // }
        // cout << endl;

        int mutate_p1 = 0, mutate_p2 = 0;
        while (mutate_p1 == mutate_p2 || mutate_p1 == 0 || mutate_p2 == 0 || mutate_p1 == front_size || mutate_p2 == front_size){
            mutate_p1 = rand() % amount;
            mutate_p2 = rand() % amount;
        }

        // cout << node_permu_front.at(mutate_p1)->getID() << " swap with " << node_permu_front.at(mutate_p2)->getID() << endl;

        swap(node_permu_front.at(mutate_p1), node_permu_front.at(mutate_p2));

        // for(unsigned i=0; i < node_permu_front.size(); i++){
        //     cout << node_permu_front[i]->getID() << " ";
        // }
        // cout << endl;

        int n = 0;
        while (node_permu_back.size() != back_size) {
            node_permu_back.push_back(node_permu_front.at(front_size + n));
            n++;
        }
        inputtree->ModifyDoubleSidedTree(node_permu_front, node_permu_back);
    }
}