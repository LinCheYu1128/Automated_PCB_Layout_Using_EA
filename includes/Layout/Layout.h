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
#include "NetList.h"

class Layout {
    private:
        ComponentList* comp_list;
        int component_num;

        // Placement
        BinaryTree* tree;
        Contour* front_contour;
        Contour* back_contour;
        double area = 0;
        double Pns = 0;
        double wirelength = 0;
        double fitness = 0;

    public:
        // constructor, destructor
        Layout(BinaryTree* tree, ComponentList* comp_list, int side);
        Layout(ComponentList* comp_list, int side);
        Layout(ComponentList* comp_list);
        ~Layout();

        Layout* copy();
        
        // getter
        BinaryTree* getBinaryTree();
        Contour* getContour(string side);
        int getComponentNum();
        double getFitness();
        double getArea();
        double getWireLength();
        double getPns();

        // setter
        void setBinaryTree(int side);
        void setContour();
        void setState(TreeNode*, Contour*);
        void updateLayout();
        void setFitness();
        void setFitness(tuple<double, double, double> weight_vector);
        void setArea();
        void setWireLength();
        void setPns();

        // printer
        void printComponent();

        // utility
        double evaluateArea(int side);
        double evaluateTotalArea();
        double calcuHPWL(vector< tuple<double, double> > comp_in_net);
        double calcuTwoSide(vector< Point > prim_list, vector< Point > sec_list);

};

void writeCsv(Layout* layout, string filename="placement.csv");
void writePin(Layout* layout, string filename="pin.csv");
// void writeBehavior(vector<double> GA_behavior, string filename);

#endif