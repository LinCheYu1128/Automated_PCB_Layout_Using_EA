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

        // Placement
        BinaryTree* tree;
        Contour* contour;

    public:
        // constructor, destructor
        Layout(ComponentList* comp_list, int side);
        ~Layout();
        
        // getter
        BinaryTree* getComponent();
        Contour* getContour();

        // setter
        void setComponent(int side);
        void setContour();
        void setState(TreeNode*);

        // printer
        void printComponent();
};

#endif