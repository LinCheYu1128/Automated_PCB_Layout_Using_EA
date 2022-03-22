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
        // if(i % 10 == 9){
        //     cout << "generation: " << i << endl;
        // }
        cout << "generation: " << i << endl;

        GA_optimizer->crossover();
        // GA_optimizer->evaluate("offspring");
        // for(unsigned i = 0; i < GA_optimizer->getOffspring().size(); i++){
        //     cout << "offspring " << i << ": " << GA_optimizer->getOffspring()[i]->getFitness() << endl;
        // }
        GA_optimizer->mutation();
        // cout << "test 1" << endl;
        GA_optimizer->evaluate("offspring");
        // for(unsigned i = 0; i < GA_optimizer->getOffspring().size(); i++){
        //     cout << "offspring " << i << ": " << GA_optimizer->getOffspring()[i]->getFitness() << endl;
        // }
        // cout << "test 2" << endl;
        GA_optimizer->mergePopulationOffspring();
        // for (unsigned i = 0; i < GA_optimizer->getPopulation().size(); i++){
        //     cout << GA_optimizer->getPopulation()[i]->getFitness() << endl;
        // }
        // cout << "test 4" << endl;
        GA_optimizer->survivorSelect();
        for(unsigned i = 0; i < GA_optimizer->getPopulation().size(); i++){
            cout << "population " << i << ": " << GA_optimizer->getPopulation()[i]->getFitness() << endl;
        }  
        // cout << "test 5" << endl;
        GA_optimizer->updateBestOffspring();
        // cout << "test 6" << endl;
        GA_optimizer->pushBehavior();
        cout << GA_optimizer->getBestOffspring() << endl;
        cout << "fitness: " << GA_optimizer->getBestOffspring()->getFitness() << endl;
    }
    
    // GA_optimizer->getOutputFile();

    // cout << "test 1" << endl;
    // cout << GA_optimizer->getOffspring()[3] << endl;
    // vector<TreeNode*> temp = GA_optimizer->getOffspring()[1]->getBinaryTree()->ExtractTree(GA_optimizer->getOffspring()[1]->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp.size(); i++){
    //     cout << temp[i]->getComponentProp()->getName() << " ";
    // }
    // cout << endl;
    // writeCsv(GA_optimizer->getOffspring()[1]);
    // writeCsv(GA_optimizer->getPopulation()[0]);
    writeCsv(GA_optimizer->getBestOffspring());
    writePin(GA_optimizer->getBestOffspring());
    cout << "area " << GA_optimizer->getBestOffspring()->getArea() << endl;
    cout << "WL " << GA_optimizer->getBestOffspring()->getWireLength() << endl;
    cout << "pns " << GA_optimizer->getBestOffspring()->getPns() << endl;
    // writeCsv(GA_optimizer->getBestOffspring());
    // cout << "test 2" << endl;
    delete GA_optimizer;
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}