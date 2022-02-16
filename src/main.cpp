#include "Layout.h"
#include "GA/GA.h"
#include <iostream>
#include <ctime>
using namespace std;

int main () {
    srand((unsigned)time(0));
    
    GA* GA_optimizer = new GA();

    cout << "complete GA_optimizer" << endl;

    cout << "Hello we are testing git pull upstream" << endl;
    
    delete GA_optimizer;

    return 0;
}