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
    
    public:
        // constructor, destructor
        GA();
        ~GA();

        // GA process
        vector<Layout*> selectParent();
        void crossover();
        void mutation();

        // getter
        GA_Parameter* getParameter();
        vector<Layout*> getPopulation();
        vector<Layout*> getParent();
        vector<Layout*> getOffspring();
        Layout* getBest(string attr);   // area / wirelength / PnS / all

        // setter
        void setParameter(GA_Parameter* parameter);
        void setPopulation();
};

#endif