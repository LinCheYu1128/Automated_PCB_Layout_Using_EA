#include "Layout.h"
#include "GA.h"
#include "console.h"
#include <iostream>
#include <ctime>
using namespace std;

int main (int argc, char **argv) {
    srand((unsigned)time(0));
    
    Console::set(argc, argv);
    Console::run();

    return 0;
}