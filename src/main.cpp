#include "Layout.h"
#include "GA/GA.h"
#include <iostream>
#include <ctime>
using namespace std;

int main () {
    srand((unsigned)time(0));
    
    GA* GA_optimizer = new GA();
    GA_optimizer->setPopulation();

    cout << "complete GA_optimizer" << endl;

    delete GA_optimizer;

    return 0;
}