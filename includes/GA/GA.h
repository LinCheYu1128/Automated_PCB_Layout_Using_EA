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

        // helper
        bool SortPop(Layout const *layout_1, Layout const *layout_2);
};
void swapBranchMutation(Layout *input);
void swapSubtreeMutation(Layout *input);
void bitwiseMutation(Layout *input);
void shiftSubtreeMutation(Layout *input);
void insertMutation(Layout *input);
void scrambleMutation(Layout *input);
void swapNodeMutation(Layout *input);

#endif