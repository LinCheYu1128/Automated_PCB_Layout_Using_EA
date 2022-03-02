#include "ComponentList.h"
#include "GA.h"
#include "console.h"
#include "Layout.h"
#include <iostream>
#include <fstream>
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

vector<Layout*> GA::parentSelect() {
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

        // for(int i = 0; i < k; i++)
        //     cout << index_arr.at(i) << " ";
        // cout << endl;
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
    vector<Layout*> Parents = this->parentSelect();
    this->leftSubtreeCrossover(Parents);

    
    // Parents.at(0)->printComponent();
    // Parents.at(1)->printComponent();
    // Layout *offspring = leftSubtreeCrossover(Parents);
    // offspring->getBinaryTree()->printBinaryTree();
    
    Layout *offspring = kPointCrossover(Parents);
    offspring->getBinaryTree()->printBinaryTree();

}

void GA::mutation() {

    // // TODO
    // int popSize = this->parameter->getPopSize();
    // int MutationRate = this->parameter->getMutationRate();

    // cout << "Conduct Nutation" << endl;
    // for (int i = 0; i < popSize; i++){
    //     // swapBranchMutation();
    // }

    cout << "conduct mutation" << endl;

    Layout* test_layout = this->getPopulation().at(1);

    cout << "before mutation" << endl;
    test_layout->getTree()->printBinaryTree();

    bitwiseMutation(test_layout, 0.5);

    cout << "after mutation" << endl;
    test_layout->getTree()->printBinaryTree();
    
=======
    // TODO
}

void GA::survivorSelect() {
    sort(this->population.begin(), this->population.end(), SortPop);
    this->population.erase(this->population.begin() + this->parameter->getPopSize(), this->population.end());

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

void GA::getOutputFile() {
    ofstream ExpResult("FILENAME_AnytimeBehavior.csv");
    ExpResult << "Total Generation" << "," << this->parameter->getGeneration() << "\n";
    ExpResult << "Population Size" << "," << this->parameter->getPopSize() << "\n";
    ExpResult << "Crossover Rate" << "," << this->parameter->getCrossoverRate() << "\n";
    ExpResult << "Mutation Rate" << "," << this->parameter->getMutationRate() << "\n";
    ExpResult << "Angle Mutation Rate" << "," << this->parameter->getAngleChangeRate() << "\n";
    ExpResult << "Angle Bit Flip Rate" << "," << this->parameter->getSideChangeRate() << "\n";
    ExpResult << "k Tournament Selection" << "," << this->parameter->getTournamentNum() << "\n";

    // Wait expand
    for(unsigned int i = 0; i < this->anytimeBehavior.size(); i++) {
        ExpResult << this->anytimeBehavior.at(i) << "\n";
    }
}

void GA::setParameter(GA_Parameter* parameter) {
    this->parameter = parameter;
}

void GA::setPopulation() {
    ComponentList* component_list = new ComponentList();

    for (int i = 0; i < this->parameter->getPopSize(); i++) {
        Layout* layout = new Layout(component_list, 1);
        // layout->printComponent();
        this->population.push_back(layout);
    }
}

void GA::pushBehavior() {
    this->anytimeBehavior.push_back(this->bestOffspring->getFitness());
}

bool SortPop(Layout *layout_1, Layout *layout_2) {
    return layout_1->getFitness() < layout_2->getFitness();
}

vector<Layout*> GA::leftSubtreeCrossover(vector<Layout*>Parents){
    cout << "start crossover"<<endl;
    return Parents;
}

