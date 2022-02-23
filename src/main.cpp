#include "Layout.h"
#include "GA/GA.h"
#include "DebugMode.h"
#include <iostream>
#include <ctime>

using namespace std;

int main (int argc, char **argv) {
    srand((unsigned)time(0));
    
    // GA* GA_optimizer = new GA();
    // cout << "complete GA_optimizer" << endl;
    // delete GA_optimizer;

    Console* console = new Console(argc, argv);
    // console->log(cout << "Hello");
    console->run();

    return 0;
}