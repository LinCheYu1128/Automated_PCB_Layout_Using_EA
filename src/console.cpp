#include "Layout.h"
#include "GA.h"
#include "MOEAD.h"
#include "console.h"
#include <iostream>
using namespace std;

Console* Console::instance;
int Console::mode;

void Console::run() {
    
    for(int exp = 0; exp < 1; exp++){
        GA_Optimization(exp);
    }
    
    // MOEAD_Optimization();

    // Test();
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}

void GA_Optimization(int exp){
    cout << "==========GA==========" << endl;
    
    GA* GA_optimizer = new GA();

    
    string filenamePin = "Pin" + to_string(exp) + ".csv";
    string filenameCsv = "Placement" + to_string(exp) + ".csv";

    int generation = GA_optimizer->getParameter()->getGeneration();

    for(int i = 0; i < generation; i++){
        
        cout << "generation: " << i << endl;

        GA_optimizer->crossover();
        // cout << "test 1" << endl;
        GA_optimizer->mutation(i);
        // cout << "test 2" << endl;
        GA_optimizer->evaluate("offspring");
        // cout << "test 3" << endl;
        GA_optimizer->mergePopulationOffspring();
        // cout << "test 4" << endl;
        GA_optimizer->survivorSelect();
        // cout << "test 5" << endl;
        GA_optimizer->updateBestOffspring();
        // cout << "test 6" << endl;
        GA_optimizer->pushBehavior();
        // cout << "test 7" << endl;
        cout << "area: " << GA_optimizer->getBestOffspring()->getArea() << endl;
        cout << "pns: " << GA_optimizer->getBestOffspring()->getPns() << endl;
        cout << "fitness: " << GA_optimizer->getBestOffspring()->getFitness() << endl;
        cout << "aspect ratio:" << GA_optimizer->getBestOffspring()->getAspectRatio() << endl;
        writeCsv(GA_optimizer->getBestOffspring());
        writePin(GA_optimizer->getBestOffspring());

        GA_optimizer->getOutputFile();
    }
    
    cout << "area " << GA_optimizer->getBestOffspring()->getArea() << endl;
    cout << "WL " << GA_optimizer->getBestOffspring()->getWireLength() << endl;
    cout << "pns " << GA_optimizer->getBestOffspring()->getPns() << endl;
    // writeCsv(GA_optimizer->getBestOffspring());
    // cout << "test 2" << endl;
    delete GA_optimizer;
    
}

void MOEAD_Optimization(){
    cout << "==========MOEAD==========" << endl;
    
    MOEAD* MOEAD_optimizer = new MOEAD();
    int generation = MOEAD_optimizer->getParameter()->getGeneration();
    int popsize = MOEAD_optimizer->getParameter()->getPopSize();

    for(int i = 0; i < generation; i++){
        cout << "generation: " << i << endl;
        for(int pop_no = 0; pop_no < popsize; pop_no++){
            // cout << "pop no.: " << pop_no << endl;

            // for(unsigned i = 0; i < MOEAD_optimizer->getPopulation().size(); i++){
            //     cout << "population " << i << ": " << MOEAD_optimizer->getPopulation()[i]->getArea() << endl;
            // }

            MOEAD_optimizer->findNeighbor(pop_no);
            MOEAD_optimizer->parentSelect();
            MOEAD_optimizer->crossover();
            MOEAD_optimizer->mutation();
            MOEAD_optimizer->updateNeighbors();

            // cout << "offspring: " << MOEAD_optimizer->getOffspring()->getArea() << endl;
            // for(unsigned i = 0; i < MOEAD_optimizer->getPopulation().size(); i++){
            //     cout << "population " << i << ": " << MOEAD_optimizer->getPopulation()[i]->getArea() << endl;
            //     MOEAD_optimizer->getPopulation()[i]
            // }

            MOEAD_optimizer->updateExternalPopulation();
        }
        // MOEAD_optimizer->printExternalPopulation();
    }

    MOEAD_optimizer->writeCsvandPin();

    MOEAD_optimizer->getOutputFile();

    delete MOEAD_optimizer;
}

void Test(){
    // ComponentList* component_list = new ComponentList();
    while(1){
        cout << "test" << endl;
        GA* GA_optimizer = new GA();
        // Layout* layout = new Layout(component_list, 2);
        // layout->getBinaryTree()->ExtractTree(0);
        // swapSubtreeMutation(layout);
        // vector<TreeNode*> node_permu;
        // node_permu = layout->getBinaryTree()->ExtractTree(0);
        delete GA_optimizer;
        cout << "end" << endl;
    }
}