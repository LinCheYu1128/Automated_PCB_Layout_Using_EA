#ifndef MOEAD_H
#define MOEAD_H

#include "MOEAD_Parameter.h"
#include "Layout.h"

class MOEAD {
    private:
        MOEAD_Parameter* parameter;
        vector<Layout*> population;
        vector<Layout*> parent;
        Layout* offspring;
        vector<Layout*> external_population;
        vector< tuple<double, double, double> > weight_vector;
        vector<int> weight_vector_neighbors;
        vector<double> anytimeBehavior;
    
    public:
        // constructor, destructor
        MOEAD();
        ~MOEAD();

        // MOEAD process
        void parentSelect();
        void findNeighbor(int individual);
        void crossover();
        void mutation();
        void updateNeighbors();
        void evaluate(string target, int wv_index);
        void updateExternalPopulation();
        // void mergePopulationOffspring();

        // getter
        MOEAD_Parameter* getParameter();
        vector<Layout*> getPopulation();
        vector<Layout*> getParent();
        Layout* getOffspring();
        // Layout* getBest(string attr);   // area / wirelength / PnS / all
        vector<Layout*> getExternalPopulation();
        void getOutputFile();   // anytime behavior or anything needed in output file

        // setter
        void setParameter(MOEAD_Parameter* parameter);
        void setPopulation();
        void setParent();
        void setWeightVector(string filename);
        void setOffspring();
        // void setExternalPopulation();

        // utility
        int dominateRelationship(Layout *layout_1, Layout *layout_2);
        void printExternalPopulation();
        void writeCsvandPin();

        // void pushBehavior();
};

// // helper
// bool SortPop(Layout *layout_1, Layout *layout_2);

//Crossover
Layout* leftSubtreeCrossover(vector<Layout*>Parents);
Layout* kPointCrossover(vector<Layout*>Parents, int k);
Layout* randomSubtreeCrossover(vector<Layout*>Parents);
Layout* nothingCrossover(vector<Layout*>Parents);

//Mutation
int MyRandom (int i);
void swapBranchMutation(Layout *input);
void swapSubtreeMutation(Layout *input);
void bitwiseMutation(Layout *input, double prob);
void shiftSubtreeMutation(Layout *input);
void insertMutation(Layout *input);
void scrambleMutation(Layout *input);
void swapNodeMutation(Layout *input);

#endif