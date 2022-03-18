#include "Layout.h"
#include "GA.h"
#include "console.h"
#include "NetList.h"
#include <iostream>
using namespace std;

Console* Console::instance;
int Console::mode;

void Console::run() {
    // ComponentList* component_list = new ComponentList();
    NetList* netlist = new NetList();
    for(auto &item: netlist->getNetList()){
        cout << item.first << endl;
        for(auto &item2: item.second){
            cout << item2 << " ";
        }
        cout << endl;
    }
    

    // GA* GA_optimizer = new GA();
    // int generation = GA_optimizer->getParameter()->getGeneration();
    // for(int i = 0; i < generation; i++){
    //     cout << "generation: " << i << endl;
        
    //     vector<Layout*> population = GA_optimizer->getPopulation();
    //     vector<Layout*> offspring = GA_optimizer->getOffspring();

    //     GA_optimizer->crossover();
    //     GA_optimizer->mutation();
    //     // cout << "test 1" << endl;
    //     GA_optimizer->evaluate("offspring");
    //     // cout << "test 2" << endl;
    //     population.insert(population.end(), offspring.begin(), offspring.end());
    //     // cout << "test 3" << endl;
    //     sort(population.begin(), population.end(), SortPop);
    //     // cout << "test 4" << endl;
    //     GA_optimizer->survivorSelect();
    //     // cout << "test 5" << endl;
    //     GA_optimizer->updateBestOffspring();
    //     // cout << "test 6" << endl;
    //     GA_optimizer->pushBehavior();
    //     // cout << "test 7" << endl;
    // }
    
    // GA_optimizer->getOutputFile();

    // delete GA_optimizer;
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}