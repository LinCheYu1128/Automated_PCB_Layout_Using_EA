#ifndef TREENODE_H
#define TREENODE_H

#include "Data.h"

class TreeNode {
    private:
        TreeNode* leftchild;
        TreeNode* rightchild;
        TreeNode* parent;
        Data* data;

    public:
        // constructor, destructor
        TreeNode(Data* data);
        ~TreeNode();

        // getter
        void printTreeNode();

        // setter
        void setData(Data* data);
        
        // printer
};

#endif