#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
#include "Contour.h"
#include "Component.h"

class BinaryTree {
    private:
        TreeNode* root;
        Contour* contour;

    public:
        // constructor, destructor
        BinaryTree(ComponentProperty* comp_prop);
        ~BinaryTree();
        
        // getter
        
        // setter
        
        // printer
        void printBinaryTree();
};

#endif