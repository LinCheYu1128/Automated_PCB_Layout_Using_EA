#include "Layout.h"
#include "GA.h"
#include "console.h"
#include <iostream>
using namespace std;

Console* Console::instance;
int Console::mode;

void Console::run() {

    GA* GA_optimizer = new GA();
    
    int generation = GA_optimizer->getParameter()->getGeneration();
    for(int i = 0; i < generation; i++){
        GA_optimizer->crossover();
        GA_optimizer->mutation();
        GA_optimizer->evaluate("offspring");
        GA_optimizer->getPopulation().insert(GA_optimizer->getPopulation().end(),GA_optimizer->getOffspring().begin(), GA_optimizer->getOffspring().end());
        sort(GA_optimizer->getPopulation().begin(), GA_optimizer->getPopulation().end(), SortPop);
        GA_optimizer->survivorSelect();
        GA_optimizer->updateBestOffspring();
        GA_optimizer->pushBehavior();
    }
    
    delete GA_optimizer;
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}