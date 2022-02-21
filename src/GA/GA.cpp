#include "ComponentList.h"
#include "GA/GA.h"
#include <iostream>
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
    vector<Layout*> selected_parent;
    // TODO
    return selected_parent;
}

void GA::crossover() {
    // TODO
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
        Layout* layout = new Layout(component_list, "single");
        layout->printComponent();
        this->population.push_back(layout);
    }
}