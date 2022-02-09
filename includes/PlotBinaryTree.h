#ifndef PLOTBINARYTREE_H
#define PLOTBINARYTREE_H

#include "BinaryTree.h"

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