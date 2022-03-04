#ifndef GA_H
#define GA_H

#include "GA_Parameter.h"
#include "Layout.h"

class GA {
    private:
        GA_Parameter* parameter;
        vector<Layout*> population;
        vector<Layout*> parent;
        vector<Layout*> offspring;
        Layout* bestOffspring;
        vector<float> anytimeBehavior;
    
    public:
        // constructor, destructor
        GA();
        ~GA();

        // GA process
        vector<Layout*> parentSelect();
        void crossover();
        void mutation();
        void survivorSelect();  // Has not test yet.

        // getter
        GA_Parameter* getParameter();
        vector<Layout*> getPopulation();
        vector<Layout*> getParent();
        vector<Layout*> getOffspring();
        Layout* getBest(string attr);   // area / wirelength / PnS / all
        vector<Layout*> leftSubtreeCrossover(vector<Layout*>Parents);
        void getOutputFile();   // anytime behavior or anything needed in output file

        // setter
        void setParameter(GA_Parameter* parameter);
        void setPopulation();

        void pushBehavior();

        // // helper
        // bool SortPop(Layout const *layout_1, Layout const *layout_2);
};

// helper
bool SortPop(Layout *layout_1, Layout *layout_2);

//Crossover
Layout* leftSubtreeCrossover(vector<Layout*>Parents);
Layout* kPointCrossover(vector<Layout*>Parents, int k);
Layout* randomSubtreeCrossover(vector<Layout*>Parents);

//Mutation
int MyRandom (int i);
void testMutation ();
void swapBranchMutation(Layout *input);
void swapSubtreeMutation(Layout *input);
void bitwiseMutation(Layout *input, double prob);
void shiftSubtreeMutation(Layout *input);
void insertMutation(Layout *input);
void scrambleMutation(Layout *input);
void swapNodeMutation(Layout *input);

#endif