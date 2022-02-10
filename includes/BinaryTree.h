#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
#include "Contour.h"
#include "Component.h"
#include "ComponentList.h"

class BinaryTree {
    private:
        int side;
        ComponentList* comp_list;
        TreeNode* root;

    public:
        // constructor, destructor
        BinaryTree(ComponentList* comp_list);
        ~BinaryTree();
        
        // getter
        TreeNode* getRoot();

        // setter
        void setSingleSide();
        void setDoubleSide();

        // printer
        void printBinaryTree();
};

TreeNode* random_select_node(TreeNode* selected_node, ComponentProperty* new_comp);

#endif