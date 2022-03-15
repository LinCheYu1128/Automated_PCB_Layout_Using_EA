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
        cout << "generation: " << i << endl;
        
        vector<Layout*> population = GA_optimizer->getPopulation();
        vector<Layout*> offspring = GA_optimizer->getOffspring();

        GA_optimizer->crossover();

        // for (unsigned i = 0; i < offspring.size(); i++){
        //     cout << "offspring " << i << ": " << offspring[i]->getFitness() << endl;
        // }

        GA_optimizer->mutation();
        // cout << "test 1" << endl;
        GA_optimizer->evaluate("offspring");

        // for (unsigned i = 0; i < offspring.size(); i++){
        //     cout << "offspring " << i << ": " << offspring[i]->getFitness() << endl;
        // }

        // cout << "test 2" << endl;
        population.insert(population.end(), offspring.begin(), offspring.end());
        // cout << "test 3" << endl;
        sort(population.begin(), population.end(), SortPop);

        // for (unsigned i = 0; i < population.size(); i++){
        //     cout << "population " << i << ": " << population[i]->getFitness() << endl;
        // }

        // cout << "test 4" << endl;
        GA_optimizer->survivorSelect();
        // cout << "test 5" << endl;
        GA_optimizer->updateBestOffspring();
        // cout << "test 6" << endl;
        GA_optimizer->pushBehavior();
        // cout << "test 7" << endl;
    }
    
    GA_optimizer->getOutputFile();

    delete GA_optimizer;
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}