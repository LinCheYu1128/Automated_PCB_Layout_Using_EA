#ifndef TREENODE_H
#define TREENODE_H

#include "Component.h"
#include <iostream>
#include <map>
using namespace std;

class TreeNode {
    private:
        string branch;
        TreeNode* leftchild;
        TreeNode* rightchild;
        TreeNode* parent;
        ComponentProperty* comp_prop;
        ComponentState* comp_state;

    public:
        // constructor, destructor
        TreeNode(ComponentProperty* comp_prop);
        ~TreeNode();

        TreeNode* copy();

        // getter
        string getBranch();
        TreeNode* getLeftchild();
        TreeNode* getRightchild();
        TreeNode* getParent();
        ComponentProperty* getComponentProp();
        
        // setter
        void setLeftchild(ComponentProperty* comp_prop);
        void setRightchild(ComponentProperty* comp_prop);
        void setParent(TreeNode* parent);
        void setTreeNode(ComponentProperty* comp_prop);
        
        // printer
        void printTreeNode();
};

#endif