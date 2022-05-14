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
    this->evaluate("population");
    this->setBestOffspring();
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

    // cout << "Conduct Crossover" << endl;

    this->offspring.clear();
    for(unsigned i = 0; i < this->population.size(); i++) {//
        // cout << "test 1" << endl;
        vector<Layout*> Parents = this->parentSelect();
        // cout << "test 2" << endl;
        Layout *child = randomSubtreeCrossover(Parents);
        // Layout *child = kPointCrossover(Parents, 2);
        // Layout *child = Parents[0]->copy();
        // cout << "test 3" << endl;
        child->updateLayout();
        offspring.push_back(child);
        // cout << "test 4" << endl;
    }

    // cout << "End Crossover" << endl;
}

void GA::mutation(int gen) {

    // cout << "Conduct mutation" << endl;

    for(unsigned i = 0; i < this->offspring.size(); i++) {
        // offspring[i]->getBinaryTree()->printBinaryTree();
        // int mode = 3;
        int mode ;
        mode = 0;
        // offspring[i]->getBinaryTree()->printBinaryTree();
        switch (mode)
        {
        case 0:
            swapNodeMutation(this->offspring[i]);//nono
            break;
        case 1:
            insertMutation(this->offspring[i]);//nono
            break;
        case 2:
            bitwiseMutation(this->offspring[i],0.2);//save
            break;
        case 3:
            shiftSubtreeMutation(this->offspring[i]);//nono
            break;
        case 4:
            swapBranchMutation(this->offspring[i]);//save
            break;
        case 5:
            scrambleMutation(this->offspring[i]);//nono
            break;
        case 6:
            swapSubtreeMutation(this->offspring[i]);//nono
            break;
        case 7:
            
            break;
        default:
            cout << "something wrong" << endl;
            break;
        }
        this->offspring[i]->updateLayout();
        // offspring[i]->getBinaryTree()->printBinaryTree();
        // // cout << offspring[i] << endl;
        // vector<TreeNode*> temp = offspring[i]->getBinaryTree()->ExtractTree(offspring[i]->getBinaryTree()->getRoot()->getID());
        // for(unsigned i = 0; i < temp.size(); i++){
        //     cout << temp[i]->getComponentProp()->getName() << " ";
        // }
        // cout << endl;
    }
    // cout << offspring[3] << endl;
    // vector<TreeNode*> temp = offspring[1]->getBinaryTree()->ExtractTree(offspring[1]->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp.size(); i++){
    //     cout << temp[i]->getComponentProp()->getName() << " ";
    // }
    // cout << endl;
    // cout << "End mutation" << endl;
}

void GA::survivorSelect() {
    sort(this->population.begin(), this->population.end(), SortPop);
    for (unsigned int i = 0; i < this->offspring.size(); i++) {
        delete this->population[this->parameter->getPopSize() + i];
    }
    this->population.erase(this->population.begin() + this->parameter->getPopSize(), this->population.end());
}

void GA::evaluate(string target){
    if(target == "population"){
        int populationsize = this->getPopulation().size();
        for(int i = 0; i < populationsize; i++){
            this->population[i]->setFitness();
        }
    }else if(target == "offspring"){
        int offspringsize = this->getOffspring().size();
        for(int i = 0; i < offspringsize; i++){
            this->offspring[i]->setFitness();
        }
    }
}

void GA::updateBestOffspring(){
    // should use copy function
    Layout* new_best = this->population[0]->copy();
    // cout << "current fitness: " << this->population[0]->getFitness() << endl;
    // cout << "copy fitness: " << new_best->getFitness() << endl;

    // this->population[0]->getContour("front")->printContour();
    // cout << "-----------------" << endl;
    // new_best->getContour("front")->printContour();

    // vector<TreeNode*> temp = this->population[0]->getBinaryTree()->ExtractTree(this->population[0]->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp.size(); i++){
    //     cout << temp[i]->getComponentProp()->getHeight() << " ";
    // }
    // cout << endl;

    // vector<TreeNode*> temp1 = new_best->getBinaryTree()->ExtractTree(new_best->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp1.size(); i++){
    //     cout << temp1[i]->getComponentProp()->getHeight() << " ";
    // }
    // cout << endl;

    // vector<TreeNode*> temp2 = this->population[0]->getBinaryTree()->ExtractTree(this->population[0]->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp2.size(); i++){
    //     cout << temp2[i]->getComponentState()->getWidth() << " ";
    // }
    // cout << endl;

    // vector<TreeNode*> temp3 = new_best->getBinaryTree()->ExtractTree(new_best->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp3.size(); i++){
    //     cout << temp3[i]->getComponentState()->getWidth() << " ";
    // }
    // cout << endl;

    // vector<TreeNode*> temp4 = this->population[0]->getBinaryTree()->ExtractTree(this->population[0]->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp4.size(); i++){
    //     cout << temp4[i]->getComponentState()->getPosition().y << " ";
    // }
    // cout << endl;

    // vector<TreeNode*> temp5 = new_best->getBinaryTree()->ExtractTree(new_best->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp5.size(); i++){
    //     cout << temp5[i]->getComponentState()->getPosition().y << " ";
    // }
    // cout << endl;

    // vector<TreeNode*> temp6 = this->population[0]->getBinaryTree()->ExtractTree(this->population[0]->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp6.size(); i++){
    //     cout << temp6[i]->getComponentState()->getPosition().x << " ";
    // }
    // cout << endl;

    // vector<TreeNode*> temp7 = new_best->getBinaryTree()->ExtractTree(new_best->getBinaryTree()->getRoot()->getID());
    // for(unsigned i = 0; i < temp7.size(); i++){
    //     cout << temp7[i]->getComponentState()->getPosition().x << " ";
    // }
    // cout << endl;

    // cout << "best fitness: " << this->bestOffspring->getFitness() << endl;
    if(new_best->getFitness() < this->bestOffspring->getFitness()){
        // Layout* temp = this->bestOffspring;
        // delete temp;
        this->bestOffspring = new_best;
    }
    if(this->population[0]->getFitness() != new_best->getFitness()) exit(EXIT_FAILURE);
}

void GA::mergePopulationOffspring(){
    population.insert(population.end(), offspring.begin(), offspring.end());
    // sort(this->population.begin(), this->population.end(), SortPop);
    // offspring.clear();
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

Layout* GA::getBestOffspring() {
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
        Layout* layout = new Layout(component_list, 2);
        // layout->printComponent();
        this->population.push_back(layout);
    }
}

void GA::setBestOffspring() {
    sort(this->population.begin(), this->population.end(), SortPop);
    this->bestOffspring = population[0];
}

void GA::pushBehavior() {
    this->anytimeBehavior.push_back(this->bestOffspring->getFitness());
}

bool SortPop(Layout *layout_1, Layout *layout_2) {
    return layout_1->getFitness() < layout_2->getFitness();
}
