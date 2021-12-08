#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;

// Class
#include "BinaryTree.cpp"
#include "Contour.cpp"
#include "TreeNode.cpp"
#include "Data.cpp"
#include "Component.cpp"

// Function
#include "utility.cpp"

int main () {
    srand((unsigned)time(0));

    Component_Info comp_info = {
        "component.csv",
        ".\\resources\\",
        ".\\resources\\pin position\\"
    };
    
    ComponentList_Reader* component_list = new ComponentList_Reader(comp_info);
    component_list->printData();

    map<string, Point> pin_position = {{"A", {1, 0}}, {"B", {2, 2}}, {"C", {3, 3}}, {"D", {4, 4}}, {"E", {4, 4}}};
    ComponentProperty* comp_prop = new ComponentProperty();
    comp_prop->setAllPinPosition(pin_position);
    
    BinaryTree* tree = new BinaryTree(comp_prop);
    tree->printBinaryTree();

    return 0;
}