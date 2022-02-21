#ifndef LAYOUT_H
#define LAYOUT_H

#include "BinaryTree.h"
#include "ComponentList.h"

class Layout {
    private:
        ComponentList* comp_list;

        // Placement
        BinaryTree* tree;
        Contour* contour;
        float fitness;

    public:
        // constructor, destructor
        Layout(ComponentList* comp_list, string side);
        ~Layout();
        
        // getter
        BinaryTree* getComponent();
        Contour* getContour();
        float getFitness();

        // setter
        void setComponent(string side);
        void setContour();

        // printer
        void printComponent();
};

#endif