#include "Layout.h"
#include "GA.h"
#include "console.h"
#include <iostream>
#include <ctime>
using namespace std;

int main (int argc, char **argv) {
    unsigned int seed = (unsigned)time(0);
    srand(seed);
    cout << seed << endl;
    // seed = 1653323067;
    

    Console::set(argc, argv);
    Console::run();

    return 0;
}