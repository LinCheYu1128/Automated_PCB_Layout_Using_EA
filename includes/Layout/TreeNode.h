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
        ComponentProperty* comp_prop;
        ComponentState* comp_state;
    
    protected:
        TreeNode* leftchild;
        TreeNode* rightchild;
        TreeNode* parent;

    public:
        // constructor, destructor
        TreeNode(ComponentProperty* comp_prop);
        ~TreeNode();

        // utility
        TreeNode* copy();
        void disconnect(string branch="all");
        bool search(int ID);
        void updateState(vector<Point>);

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
        void setID(int id);
        void setBranch(string branch);
        void setChild(TreeNode* node, string branch);
        void setLeftChild(TreeNode* node);
        void setRightChild(TreeNode* node);
        void setParent(TreeNode* parent, string branch);
        void setComponentProp(ComponentProperty* comp_prop);
        void setComponentState(ComponentState* comp_state);

        // void changeParent(TreeNode* parent, string branch);
        
        // printer
        void printTreeNode();
};

#endif
