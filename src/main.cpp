#include "Layout.h"
#include "GA.h"
#include "console.h"
#include <iostream>
#include <ctime>
using namespace std;

int main (int argc, char **argv) {
    srand((unsigned)time(0));
    cout << (unsigned)time(0) << endl;
    // srand(1652689932);
    // srand(1652770053);
    

    Console::set(argc, argv);
    Console::run();

    return 0;
}