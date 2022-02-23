#include "Layout.h"
#include "GA/GA.h"
#include "debug.h"
#include <iostream>
#include <ctime>
using namespace std;

int main (int argc, char **argv) {
    srand((unsigned)time(0));
    
    // GA* GA_optimizer = new GA();
    // cout << "complete GA_optimizer" << endl;
    // delete GA_optimizer;
    
    Console console = Console::set(argc, argv);
    
    console.run();

    return 0;
}