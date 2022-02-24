#include "GA.h"
#include "console.h"
// #include "BinaryTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

vector<Layout*> leftSubtreeCrossover(vector<Layout*>Parents){
    // cout << "start crossover"<<endl;
    BinaryTree *parentA = Parents.at(0)->getBinaryTree();

    parentA->printBinaryTree();
    cout << "end crossover"<<endl;
    return Parents;
}