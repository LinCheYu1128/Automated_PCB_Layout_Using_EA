#include "ComponentList.h"
// #include ".\Crossover\Crossover.cpp"
#include "GA.h"
#include "console.h"
#include <iostream>
#include <algorithm>
using namespace std;

GA::GA() {
    this->setParameter(new GA_Parameter());
    this->setPopulation();
}

GA::~GA() {
    delete this->parameter;

    for (unsigned int i = 0; i < this->population.size(); i++) {
        delete this->population[i];
    }
    this->population.clear();

    for (unsigned int i = 0; i < this->parent.size(); i++) {
        delete this->parent[i];
    }
    this->parent.clear();
    
    for (unsigned int i = 0; i < this->offspring.size(); i++) {
        delete this->offspring[i];
    }
    this->offspring.clear();
}

vector<Layout*> GA::selectParent() {
    int popSize = this->parameter->getPopSize();
    int k = this->parameter->getTournamentNum();
    bool check = true;

    vector<Layout*> selected_parent;
    selected_parent.reserve(2);
    vector<int> index_arr;
    index_arr.reserve(k);

    Console::log("Pop size = " + to_string(popSize));
    Console::log("k = " + to_string(k));
    
    while (selected_parent.size() < 2) {
        index_arr.clear();
        for (int i = 0; i < k; i++)
            index_arr.push_back(rand() % popSize);
        
        sort(index_arr.begin(), index_arr.end());

        for(int i = 0; i < k; i++)
            cout << index_arr.at(i) << " ";
        cout << endl;
        // Ignore repeating check. (YF)
        selected_parent.push_back(this->population.at(index_arr.front()));

        if (selected_parent.size() == 2) {
            if (selected_parent.front() == selected_parent.back()) {
                selected_parent.pop_back();
            }
        }
    }
    return selected_parent;
}

void GA::crossover() {
    // TODO
    cout << "Conduct Crossover" << endl;
    vector<Layout*> Parents = this->selectParent();
    this->leftSubtreeCrossover(Parents);
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
    ComponentList* component_list = new ComponentList();

    for (int i = 0; i < this->parameter->getPopSize(); i++) {
        Layout* layout = new Layout(component_list, 2);
        // layout->printComponent();
        this->population.push_back(layout);
    }
}

vector<Layout*> GA::leftSubtreeCrossover(vector<Layout*>Parents){
    cout << "start crossover"<<endl;
    return Parents;
}