#ifndef LAYOUT_H
#define LAYOUT_H

#include <fstream>
#include <stack>
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
        Contour* front_contour;
        Contour* back_contour;
        float fitness;

    public:
        // constructor, destructor
        Layout(BinaryTree* tree, ComponentList* comp_list, int side);
        Layout(ComponentList* comp_list, int side);
        ~Layout();
        
        // getter
        BinaryTree* getBinaryTree(){return tree;};
        Contour* getContour();
        int getComponentNum(){return component_num;};
        float getFitness(){return fitness;};

        // setter
        void setBinaryTree(int side);
        void setContour();
        void setState(TreeNode*, Contour*);

        // printer
        void printComponent();
};

void writeCsv(Layout layout);

#endif