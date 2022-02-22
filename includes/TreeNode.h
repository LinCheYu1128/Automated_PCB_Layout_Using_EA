#ifndef TREENODE_H
#define TREENODE_H

#include "Component.h"
#include <iostream>
#include <map>
using namespace std;

class TreeNode {
    private:
        int id;
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
        int getID();
        string getBranch();
        TreeNode* getChild(string branch);
        TreeNode* getLeftchild();
        TreeNode* getRightchild();
        TreeNode* getParent();
        ComponentProperty* getComponentProp();
        ComponentState* getComponentState();
        
        // setter
        void copyTreeNode(TreeNode* node);
        void setID(int id);
        void setBranch(string branch);
        void setChild(string branch, TreeNode* node);
        void setLeftchild(TreeNode* node);
        void setRightchild(TreeNode* node);
        void setParent(TreeNode* parent);
        void setComponentProp(ComponentProperty* comp_prop);
        void setComponentState(ComponentState* comp_state);

        // void changeParent(TreeNode* parent, string branch);
        
        // printer
        void printTreeNode();
};

#endif