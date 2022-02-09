#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
#include "Contour.h"
#include "Component.h"
#include "ComponentList.h"

class BinaryTree {
    private:
        TreeNode* root;
        Contour* contour;

    public:
        // constructor, destructor
        BinaryTree(ComponentList* comp_list);
        ~BinaryTree();
        
        // getter
        TreeNode* getRoot();

        // setter
        TreeNode* setBinaryTree(ComponentList* comp_list);

        // printer
        void printBinaryTree();
};
#endif