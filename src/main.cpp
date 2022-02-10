#include "BinaryTree.h"
#include "ComponentList.h"
#include <iostream>
#include <ctime>
using namespace std;

const Component_Path comp_info = {
    "component.csv",                     // component_csvfile
    "..\\resources\\",                   // component_relativePath
    "..\\resources\\pin position\\"      // pinPosition_relativePath
};

int main () {
    srand((unsigned)time(0));
    
    ComponentList* component_list = new ComponentList(comp_info);
    // component_list->printData("T501");   // test log component data
    
    BinaryTree* tree = new BinaryTree(component_list);
    tree->setSingleSide();  // single side
    // tree->setDoubleSide();  // double side
    
    tree->printBinaryTree();

    return 0;
}