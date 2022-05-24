#include "ComponentList.h"
#include "MOEAD.h"
#include "console.h"
#include "Layout.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>
using namespace std;

MOEAD::MOEAD() {
    this->setParameter(new MOEAD_Parameter());
    this->setPopulation();
    this->setParent();
    this->setOffspring();
    this->setWeightVector("./../resources/200-1.csv");
    this->evaluate("population",0);
    // this->setExternalPopulation();
}

MOEAD::~MOEAD() {
    delete this->parameter;
    
    for (unsigned int i = 0; i < this->population.size(); i++) {
        delete this->population[i];
    }
    this->population.clear();

    for (unsigned int i = 0; i < this->parent.size(); i++) {
        delete this->parent[i];
    }
    this->parent.clear();
    
    delete this->offspring;
}

void MOEAD::parentSelect() {

    this->parent.clear();
    int p1 = 0;
    int p2 = 0;
    while(p1 == p2){
        p1 = rand() % this->weight_vector_neighbors.size();
        p2 = rand() % this->weight_vector_neighbors.size();
    }
    parent.push_back(this->population.at(weight_vector_neighbors[p1]));
    parent.push_back(this->population.at(weight_vector_neighbors[p2]));
}

void MOEAD::findNeighbor(int individual){
    
    int neighboer_num = this->getParameter()->getNeighborNumber();
    this->weight_vector_neighbors.reserve(neighboer_num);
    this->weight_vector_neighbors.clear();
    map<double, int> distance;   

    for (unsigned i = 0; i < weight_vector.size(); i++) {
        if (i == individual) {
            distance[9999] = i;
        }
        else {
            double x_2 = pow(get<0>(weight_vector.at(individual)) - get<0>(weight_vector.at(i)), 2.0);
            double y_2 = pow(get<1>(weight_vector.at(individual)) - get<1>(weight_vector.at(i)), 2.0);
            double z_2 = pow(get<2>(weight_vector.at(individual)) - get<2>(weight_vector.at(i)), 2.0);
            distance[sqrt(x_2 + y_2 + z_2)] = i;
        }
    }
    
    for (map<double, int>::iterator iter = distance.begin(); iter != distance.end(); iter++) {
        while (weight_vector_neighbors.size() < (unsigned)neighboer_num) {
            // cout << "dist: " << iter->first << " index: " << iter->second << endl;
            weight_vector_neighbors.push_back(iter->second);
            break;
        }
    }

    // for (unsigned i = 0; i < weight_vector_neighbors.size(); i++){
    //     cout << weight_vector_neighbors[i] << endl;
    // }
    // cout << "----------------" << endl;
}

void MOEAD::crossover() {
    // cout << "Conduct Crossover" << endl;
    delete offspring;
    // cout << "test 1" << endl;

    int mode = rand()%2;

        switch (mode)
        {
        case 0:
            offspring = randomSubtreeCrossover(this->parent);
            break;
        case 1:
            offspring = kPointCrossover(this->parent, 2);
            break;
        case 2:
            offspring = nothingCrossover(this->parent);
            break;
        default:
            break;
        }

    // offspring = kPointCrossover(this->parent, 2);//memory leak
    // offspring = nothingCrossover(this->parent);
    // cout << "test 2" << endl;
    offspring->updateLayout();

    // cout << "End Crossover" << endl;
}

void MOEAD::mutation() {
    int mode = rand() % 7;
    // int mode = 3;

    switch (mode)
    {
    case 0:
        swapNodeMutation(this->offspring);
        break;
    case 1:
        insertMutation(this->offspring);
        break;
    case 2:
        bitwiseMutation(this->offspring, 0.2); //something wrong
        break;
    case 3:
        shiftSubtreeMutation(this->offspring); //something wrong
        break;
    case 4:
        swapBranchMutation(this->offspring);
        break;
    case 5:
        scrambleMutation(this->offspring);
        break;
    case 6:
        swapSubtreeMutation(this->offspring);
        break;
    case 7:
        
        break;
    default:
        cout << "something wrong" << endl;
        break;
    }
    offspring->updateLayout();
}

void MOEAD::updateNeighbors() {
    // cout << "test 1" << endl;
    for(unsigned i = 0; i < weight_vector_neighbors.size(); i++){
        // cout << weight_vector_neighbors.at(i) << endl;
        // cout << "population fitness: " << population[weight_vector_neighbors.at(i)]->getFitness() << endl;
        this->evaluate("offspring", i);
        // cout << "offspring fitness: " << offspring->getFitness() << endl;
        // if(i == 0){
        //     cout << "offspring area: " << offspring->getArea() << endl;
        //     cout << "offspring wirelength: " << offspring->getWireLength() << endl;
        //     cout << "offspring Pns: " << offspring->getPns() << endl;
        // }
        if(offspring->getFitness() < population[weight_vector_neighbors.at(i)]->getFitness()){
            // cout << weight_vector_neighbors.at(i) << endl;
            delete population[weight_vector_neighbors.at(i)];
            // cout << "test 2" << endl;
            population[weight_vector_neighbors.at(i)] = offspring->copy();
        }
        // cout << "test 4" << endl;
    }
    // cout << "-----------" << endl;
}

void MOEAD::evaluate(string target, int wv_index = 0){
    if(target == "population"){
        int populationsize = this->getPopulation().size();
        for(int i = 0; i < populationsize; i++){
            this->population[i]->setFitness(weight_vector[i]);
            // cout << "population " << i << ": " << this->population[i]->getFitness() << endl;
        }
    }else if(target == "offspring"){
        offspring->setFitness(weight_vector[wv_index]);
    }
}

int MOEAD::dominateRelationship(Layout *layout_1, Layout *layout_2){
    if(layout_1->getArea() <= layout_2->getArea() && 
       layout_1->getPns() <= layout_2->getPns() && 
       layout_1->getWireLength() <= layout_2->getWireLength() && 
       layout_1->getFitness() != layout_2->getFitness()){
        return 1;
    }else if(layout_1->getArea() >= layout_2->getArea() && 
             layout_1->getPns() >= layout_2->getPns() && 
             layout_1->getWireLength() >= layout_2->getWireLength() && 
             layout_1->getFitness() != layout_2->getFitness()){
        return -1;
    }else {
        return 0;
    }
}

void MOEAD::printExternalPopulation(){
    for(unsigned i = 0; i < external_population.size(); i++){
        cout << "offspring area: " << external_population[i]->getArea() << endl;
        cout << "offspring wirelength: " << external_population[i]->getWireLength() << endl;
        cout << "offspring Pns: " << external_population[i]->getPns() << endl;
    }
}

void MOEAD::updateExternalPopulation(){
    bool dominated = false;

    // cout << "---------External Population: " << external_population.size() << "--------------" << endl;
    // cout << "offspring area: " << offspring->getArea() << endl;
    // cout << "offspring wirelength: " << offspring->getWireLength() << endl;
    // cout << "offspring Pns: " << offspring->getPns() << endl;
    for(unsigned i = 0; i < external_population.size(); i++){
        
        // cout << "offspring area: " << offspring->getArea() << endl;
        // cout << "offspring wirelength: " << offspring->getWireLength() << endl;
        // cout << "offspring Pns: " << offspring->getPns() << endl;
        // cout << "------------------" << endl;
        // cout << "external_population area: " << external_population[i]->getArea() << endl;
        // cout << "external_population wirelength: " << external_population[i]->getWireLength() << endl;
        // cout << "external_population Pns: " << external_population[i]->getPns() << endl;
        // cout << "------------------" << endl;
        // cout << "Result: " << dominateRelationship(offspring, external_population[i]) << endl;
        int result = this->dominateRelationship(offspring, external_population[i]);
        if(result == 1){
            // cout << "get out" << endl;
            delete  external_population[i];
            external_population.erase(external_population.begin() + i);
        }else if(result == -1){
            // cout << "be dominated" << endl;
            dominated = true;
        }
    }

    if(!dominated){
        // cout << "pushed!" << endl;
        external_population.push_back(offspring->copy());
    }
}

MOEAD_Parameter* MOEAD::getParameter() {
    return this->parameter;
}

vector<Layout*> MOEAD::getPopulation() {
    return this->population;
}

vector<Layout*> MOEAD::getParent() {
    return this->parent;
}

Layout* MOEAD::getOffspring() {
    return this->offspring;
}

// Layout* MOEAD::getBest(string attr) {
//     // area / wirelength / PnS / all
//     return this->bestOffspring;
// }

vector<Layout*> MOEAD::getExternalPopulation() {
    return this->external_population;
}

void MOEAD::getOutputFile() {
    ofstream ExpResult("MOEAD_Experiment.csv");
    ExpResult << "Area,Wirelength,Pns" << "\n";
    // Wait expand
    for(unsigned int i = 0; i < this->external_population.size(); i++) {
        ExpResult << external_population.at(i)->getArea() << "," << external_population.at(i)->getWireLength() << "," << external_population.at(i)->getPns() << "\n";
    }
}

void MOEAD::setParameter(MOEAD_Parameter* parameter) {
    this->parameter = parameter;
}

void MOEAD::setPopulation() {
    ComponentList* component_list = new ComponentList();

    for (int i = 0; i < this->parameter->getPopSize(); i++) {
        Layout* layout = new Layout(component_list, 2);
        // layout->printComponent();
        this->population.push_back(layout);
    }
}

void MOEAD::setParent(){
    ComponentList* component_list = new ComponentList();

    for (int i = 0; i < 2; i++) {
        Layout* layout = new Layout(component_list, 2);
        this->parent.push_back(layout);
    }
}

void MOEAD::setWeightVector(string filename){
    ifstream inFile(filename);
    string temp;
    double area_weight, wirelength_weight, PS_weight;

    getline(inFile, temp, '\n');

    while (!inFile.eof()) {
        getline(inFile, temp, ',');
        area_weight = stod(temp);
        getline(inFile, temp, ',');
        wirelength_weight = stod(temp);
        getline(inFile, temp, '\n');
        PS_weight = stod(temp);
        
        tuple<double, double, double> wv = make_tuple(area_weight, wirelength_weight, PS_weight);
        weight_vector.push_back(wv);
    }
}

void MOEAD::setOffspring(){
    ComponentList* component_list = new ComponentList();
    this->offspring = new Layout(component_list, 2);
}

void MOEAD::writeCsvandPin(){
    for(unsigned i = 0; i < this->external_population.size(); i++){
        string filenamePin = "Pin" + to_string(i) + ".csv";
        string filenameCsv = "Placement" + to_string(i) + ".csv";
        writePin(this->external_population[i], filenamePin);
        writeCsv(this->external_population[i], filenameCsv);
    }
}

