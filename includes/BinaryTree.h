#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
#include "Contour.h"
#include "Component.h"
#include "../includes/ComponentList.h"

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
        
        // printer
        void printBinaryTree();
        void plotBinaryTree();
};

class PlotBinaryTree {
private:
        BinaryTree* tree;

    public:
        // constructor, destructor
        PlotBinaryTree(BinaryTree* tree);
        ~PlotBinaryTree();
        
        // getter
        
        // setter
        
        // printer
        void plotBinaryTree();
        void plotBinaryTree(TreeNode* node);
        void plotBinaryTree(string prefix, TreeNode* node, bool isLeft);
};

#endif