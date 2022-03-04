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
        double area;
        double Pns;
        double wirelength;
        double fitness;

    public:
        // constructor, destructor
        Layout(BinaryTree* tree, ComponentList* comp_list, int side);
        Layout(ComponentList* comp_list, int side);
        ~Layout();
        
        // getter
        BinaryTree* getBinaryTree();
        Contour* getContour(string side);
        int getComponentNum();
        double getFitness(){return fitness;};
        double getArea();

        // setter
        void setBinaryTree(int side);
        void setContour();
        void setState(TreeNode*, Contour*);
        void setFitness();
        void setArea();

        // printer
        void printComponent();

        // utility
        double evaluateArea(int side);
        double evaluateTotalArea();
};

void writeCsv(Layout layout);

#endif