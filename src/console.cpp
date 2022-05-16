#include "Layout.h"
#include "GA.h"
// #include "MOEAD.h"
#include "console.h"
#include <iostream>
using namespace std;

Console* Console::instance;
int Console::mode;

void Console::run() {
    GA_Optimization();

    // MOEAD_Optimization();

    // Test();
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}

void GA_Optimization(){
    GA* GA_optimizer = new GA();
    // GA_optimizer->evaluate("population");
    
    // int count = 0;
    // while(1){
    //     cout << count << endl;
    //     cout << "origin fitness: " << GA_optimizer->getPopulation()[0]->getFitness() << endl;
    //     Layout* temp = GA_optimizer->getPopulation()[0]->copy();
    //     cout << "copy fitness: " << temp->getFitness() << endl;
    //     if(GA_optimizer->getPopulation()[0]->getFitness() != temp->getFitness()) break;
    //     count++;
    // }

    int generation = GA_optimizer->getParameter()->getGeneration();
    

    for(int i = 0; i < generation; i++){
        // if(i % 10 == 9){
        //     cout << "generation: " << i << endl;
        // }
        cout << "generation: " << i << endl;

        GA_optimizer->crossover();
        GA_optimizer->evaluate("offspring");
        // for(unsigned i = 0; i < GA_optimizer->getOffspring().size(); i++){
        //     cout << "offspring " << i << ": " << GA_optimizer->getOffspring()[i]->getFitness() << endl;
        // }
        GA_optimizer->mutation(i);
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
        // for(unsigned i = 0; i < GA_optimizer->getPopulation().size(); i++){
        //     cout << "population " << i << ": " << GA_optimizer->getPopulation()[i]->getFitness() << endl;
        // }  
        // cout << "test 5" << endl;
        GA_optimizer->updateBestOffspring();
        // cout << "test 6" << endl;
        GA_optimizer->pushBehavior();

        // cout << "best offspring" << endl;
        cout << "area " << GA_optimizer->getBestOffspring()->getArea() << endl;
        // cout << "pns " << GA_optimizer->getBestOffspring()->getPns() << endl;

        // cout << "best fitness: " << GA_optimizer->getPopulation()[0]->getFitness() << endl;
        // cout << "area: " << GA_optimizer->getPopulation()[0]->getArea() << ", Pns: " << GA_optimizer->getPopulation()[0]->getPns() << endl;

        // cout << endl << endl;

        writeCsv(GA_optimizer->getBestOffspring());
        writePin(GA_optimizer->getBestOffspring());

        GA_optimizer->getOutputFile();
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
    
    cout << "area " << GA_optimizer->getBestOffspring()->getArea() << endl;
    cout << "WL " << GA_optimizer->getBestOffspring()->getWireLength() << endl;
    cout << "pns " << GA_optimizer->getBestOffspring()->getPns() << endl;
    // writeCsv(GA_optimizer->getBestOffspring());
    // cout << "test 2" << endl;
    delete GA_optimizer;
}

// void MOEAD_Optimization(){
//     MOEAD* MOEAD_optimizer = new MOEAD();
//     int generation = MOEAD_optimizer->getParameter()->getGeneration();
//     int popsize = MOEAD_optimizer->getParameter()->getPopSize();

//     for(int i = 0; i < generation; i++){
//         cout << "generation: " << i << endl;
//         for(int pop_no = 0; pop_no < popsize; pop_no++){
//             // cout << "pop no.: " << pop_no << endl;

//             // for(unsigned i = 0; i < MOEAD_optimizer->getPopulation().size(); i++){
//             //     cout << "population " << i << ": " << MOEAD_optimizer->getPopulation()[i]->getArea() << endl;
//             // }

//             MOEAD_optimizer->findNeighbor(pop_no);
//             MOEAD_optimizer->parentSelect();
//             MOEAD_optimizer->crossover();
//             MOEAD_optimizer->mutation();
//             MOEAD_optimizer->updateNeighbors();

//             // cout << "offspring: " << MOEAD_optimizer->getOffspring()->getArea() << endl;
//             // for(unsigned i = 0; i < MOEAD_optimizer->getPopulation().size(); i++){
//             //     cout << "population " << i << ": " << MOEAD_optimizer->getPopulation()[i]->getArea() << endl;
//             //     MOEAD_optimizer->getPopulation()[i]
//             // }

//             MOEAD_optimizer->updateExternalPopulation();
//         }
//         // MOEAD_optimizer->printExternalPopulation();
//     }

//     MOEAD_optimizer->getOutputFile();

//     delete MOEAD_optimizer;
// }

void Test(){
    ComponentList* component_list = new ComponentList();
    while(1){
        cout << "test" << endl;
        Layout* layout = new Layout(component_list, 2);
        // layout->getBinaryTree()->ExtractTree(0);
        swapSubtreeMutation(layout);
        // vector<TreeNode*> node_permu;
        // node_permu = layout->getBinaryTree()->ExtractTree(0);
        delete layout;
        cout << "end" << endl;
    }
}