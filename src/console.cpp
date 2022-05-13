#include "Layout.h"
#include "GA.h"
#include "console.h"
#include "Route.hpp"
#include <iostream>
using namespace std;

Console* Console::instance;
int Console::mode;

void Console::run() {

    
    CellList* Cells = new CellList();
    for(auto item: Cells->getCellList()){
        cout << item->getCellName()<< endl;
    }
    

}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}