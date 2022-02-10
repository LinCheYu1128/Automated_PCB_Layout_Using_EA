#include "Layout.h"
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
    Layout* layout = new Layout(component_list, "double");
    layout->printComponent();

    return 0;
}