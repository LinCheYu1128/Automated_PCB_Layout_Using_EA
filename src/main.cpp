#include "BinaryTree.h"
#include "ComponentList.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

const Component_Path comp_info = {
    "component.csv",                    // component_csvfile
    "..\\resources\\",                   // component_relativePath
    "..\\resources\\pin position\\"      // pinPosition_relativePath
};

int main () {
    srand((unsigned)time(0));
    
    ComponentList* component_list = new ComponentList(comp_info);
    component_list->printData("T501");
    
    BinaryTree* tree = new BinaryTree(component_list);
    tree->printBinaryTree();
    
    return 0;
}