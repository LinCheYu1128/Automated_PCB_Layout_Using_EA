#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
#include "Contour.h"
#include "Component.h"
#include "ComponentList.h"

class BinaryTree {
    private:
        int side;
        map<int, TreeNode*> TreeNode_map;
        ComponentList* comp_list;
        TreeNode* root;

    public:
        // constructor, destructor
        BinaryTree(ComponentList* comp_list);
        ~BinaryTree();
        
        BinaryTree* copy();
        void copyNode(TreeNode* old_root, TreeNode* new_root);
        void delete_node(TreeNode* node);

        // getter
        TreeNode* getRoot();
        int getSide();
        map<int, TreeNode*> getTreeNodeMap();

        // setter
        void setRoot(TreeNode* node);
        void setSide(int side);
        void setSingleSide();
        void setDoubleSide();

        // printer
        void printBinaryTree();
};

TreeNode* random_select_node(TreeNode* selected_node, ComponentProperty* new_comp);

#endif