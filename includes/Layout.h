#ifndef LAYOUT_H
#define LAYOUT_H

#include "BinaryTree.h"
#include "ComponentList.h"
#include "Contour.h"

class Layout {
    private:
        ComponentList* comp_list;

        // Placement
        BinaryTree* tree;
        Contour* contour;

    public:
        // constructor, destructor
        Layout(ComponentList* comp_list, string side);
        ~Layout();
        
        // getter
        BinaryTree* getComponent();
        Contour* getContour();

        // setter
        void setComponent(string side);
        void setContour();

        // printer
        void printComponent();
};

#endif