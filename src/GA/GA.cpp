#include "ComponentList.h"
#include "GA/GA.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
using namespace std;

const Component_Path comp_info = {
    "component.csv",                     // component_csvfile
    "..\\resources\\",                   // component_relativePath
    "..\\resources\\pin position\\"      // pinPosition_relativePath
};

GA::GA() {
    this->setParameter(new GA_Parameter());
    this->setPopulation();
}

GA::~GA() {
    delete this->parameter;

    for (int i = 0; i < this->population.size(); i++) {
        delete this->population[i];
    }
    this->population.clear();

    for (int i = 0; i < this->parent.size(); i++) {
        delete this->parent[i];
    }
    this->parent.clear();
    
    for (int i = 0; i < this->offspring.size(); i++) {
        delete this->offspring[i];
    }
    this->offspring.clear();
}

vector<Layout*> GA::selectParent() {
    // TODO
    int popSize = this->parameter->getPopSize();
    int k = this->parameter->getTournamentNum();
    bool check = true;

    vector<Layout*> selected_parent;
    selected_parent.reserve(2);
    vector<int> index_arr;
    index_arr.reserve(k);
    
    while (selected_parent.size() < 2) {
        
        index_arr.clear();
        for (int i = 0; i < k; i++)
            index_arr.push_back(rand() % popSize);
        
        sort(index_arr.begin(), index_arr.end());
        // Ignore repeating check. (YF)
        selected_parent.push_back(this->population.at(index_arr.front()));
        
        if ()
    }
    

    

    return selected_parent;
}

void GA::crossover() {
    // TODO
    cout << "Conduct Crossover" << endl;


}

void GA::mutation() {
    // TODO
}

GA_Parameter* GA::getParameter() {
    return this->parameter;
}

vector<Layout*> GA::getPopulation() {
    return this->population;
}

vector<Layout*> GA::getParent() {
    return this->parent;
}

vector<Layout*> GA::getOffspring() {
    return this->offspring;
}

Layout* GA::getBest(string attr) {
    // area / wirelength / PnS / all
    return this->bestOffspring;
}

void GA::setParameter(GA_Parameter* parameter) {
    this->parameter = parameter;
}

void GA::setPopulation() {
    ComponentList* component_list = new ComponentList(comp_info);

    for (int i = 0; i < this->parameter->getPopSize(); i++) {
        Layout* layout = new Layout(component_list, "double");
        layout->printComponent();
        this->population.push_back(layout);
    }
}