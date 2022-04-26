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
    // NetList* netlist = new NetList();
    // for(auto &item: netlist->getNetList()){
    //     cout << item.first << endl;
    //     for(auto &item2: item.second){
    //         cout << item2 << " ";
    //     }
    //     cout << endl;
    // netlist->outputTwoPinNetList();
    
    GA* GA_optimizer = new GA();
    
    int generation = GA_optimizer->getParameter()->getGeneration();
    
    GA_optimizer->crossover();

    // for(int i = 0; i < generation; i++){
    //     // if(i % 10 == 9){
    //     //     cout << "generation: " << i << endl;
    //     // }
    //     cout << "generation: " << i << endl;

    //     GA_optimizer->crossover();
    //     // GA_optimizer->evaluate("offspring");
    //     // for(unsigned i = 0; i < GA_optimizer->getOffspring().size(); i++){
    //     //     cout << "offspring " << i << ": " << GA_optimizer->getOffspring()[i]->getFitness() << endl;
    //     // }
    //     GA_optimizer->mutation(i);
    //     // cout << "test 1" << endl;
    //     GA_optimizer->evaluate("offspring");
    //     // for(unsigned i = 0; i < GA_optimizer->getOffspring().size(); i++){
    //     //     cout << "offspring " << i << ": " << GA_optimizer->getOffspring()[i]->getFitness() << endl;
    //     // }
    //     // cout << "test 2" << endl;
    //     GA_optimizer->mergePopulationOffspring();
    //     // for (unsigned i = 0; i < GA_optimizer->getPopulation().size(); i++){
    //     //     cout << GA_optimizer->getPopulation()[i]->getFitness() << endl;
    //     // }
    //     // cout << "test 4" << endl;
    //     GA_optimizer->survivorSelect();
    //     // for(unsigned i = 0; i < GA_optimizer->getPopulation().size(); i++){
    //     //     cout << "population " << i << ": " << GA_optimizer->getPopulation()[i]->getFitness() << endl;
    //     // }  
    //     // cout << "test 5" << endl;
    //     GA_optimizer->updateBestOffspring();
    //     // cout << "test 6" << endl;
    //     GA_optimizer->pushBehavior();

    //     // cout << endl << "best offspring" << endl;
    //     // cout << "area " << GA_optimizer->getBestOffspring()->getArea() << endl;
    //     // cout << "pns " << GA_optimizer->getBestOffspring()->getPns() << endl;

    //     cout << "best fitness: " << GA_optimizer->getPopulation()[0]->getFitness() << endl;
    //     cout << "area: " << GA_optimizer->getPopulation()[0]->getArea() << ", Pns: " << GA_optimizer->getPopulation()[0]->getPns() << endl;

    //     // cout << endl << endl;

    //     writeCsv(GA_optimizer->getBestOffspring());
    //     writePin(GA_optimizer->getBestOffspring());
    // }
    
    
}

void Console::log(string message) {
    if (mode == DEBUG_MODE) {
        cout << message << endl;
    }
    return;
}