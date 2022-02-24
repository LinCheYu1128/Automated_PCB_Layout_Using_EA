#ifndef LAYOUT_H
#define LAYOUT_H

#include "BinaryTree.h"
#include "Component.h"
#include "ComponentList.h"
#include "Contour.h"
#include "TreeNode.h"
#include "PlotBinaryTree.h"

class Layout {
    private:
        ComponentList* comp_list;
        int component_num;

        // Placement
        BinaryTree* tree;
        Contour* contour;
        float fitness;

    public:
        // constructor, destructor
        Layout(ComponentList* comp_list, int side);
        ~Layout();
        
        // getter
        BinaryTree* getBinaryTree();
        Contour* getContour();
        int getComponentNum();
        float getFitness();

        // setter
        void setBinaryTree(int side);
        void setContour();

        // printer
        void printComponent();
};

#endif