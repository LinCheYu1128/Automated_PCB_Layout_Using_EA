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
        ComponentState* getComponentState();
        
        // setter
        void setLeftchild(TreeNode* node);
        void setRightchild(TreeNode* node);
        void setParent(TreeNode* parent);
        void setTreeNode(TreeNode* node);
        void setComponentProp(ComponentProperty* comp_prop);
        void setComponentState(ComponentState* comp_state);
        
        // printer
        void printTreeNode();
};

#endif