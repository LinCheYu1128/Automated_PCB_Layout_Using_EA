#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
#include "Contour.h"
#include "Component.h"
#include "ComponentList.h"

class BinaryTree {
    private:
        int side;   // 0: single side, 1: double side
        ComponentList* comp_list;
        TreeNode* root;
        Contour* contour;

    public:
        // constructor, destructor
        BinaryTree(ComponentList* comp_list);
        ~BinaryTree();
        
        // getter
        TreeNode* getRoot();

        // setter
        void setBinaryTree();
        void setSingleSide();
        void setDoubleSide();

        // printer
        void printBinaryTree();
};

TreeNode* random_select_node(TreeNode* selected_node, ComponentProperty* new_comp);

#endif