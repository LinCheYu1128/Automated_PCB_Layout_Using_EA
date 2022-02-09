#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

// Class
#include "BinaryTree.h"
// #include "Contour.h"
// #include "TreeNode.h"
// #include "Component.h"
#include "ComponentList.h"

// Function

const Component_Path comp_info = {
    "component.csv",                    // component_csvfile
    "..\\resources\\",                   // component_relativePath
    "..\\resources\\pin position\\"      // pinPosition_relativePath
};

int main () {
    srand((unsigned)time(0));
    
    ComponentList* component_list = new ComponentList(comp_info);
    component_list->printData("T501");

    // map<string, Point> pin_position = {{"A", {1, 0}}, {"B", {2, 2}}, {"C", {3, 3}}, {"D", {4, 4}}, {"E", {4, 4}}};
    // ComponentProperty* comp_prop = new ComponentProperty();
    // comp_prop->setAllPinPosition(pin_position);
    
    BinaryTree* tree = new BinaryTree(component_list);
    tree->printBinaryTree();
    return 0;
}