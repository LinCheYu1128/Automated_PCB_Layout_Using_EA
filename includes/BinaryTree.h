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

        void copyByTraverseTree(TreeNode* old_root, TreeNode* new_root);
        TreeNode* random_construct_tree(TreeNode* selected_node, ComponentProperty* new_comp);
        void delete_leaf_node(TreeNode* node);
        void delete_hasOneChild_node(TreeNode* node);
        void delete_hasBothChild_node(TreeNode* node);

    public:
        // constructor, destructor
        BinaryTree(ComponentList* comp_list);
        ~BinaryTree();
        
        // utility
        BinaryTree* copy();
        TreeNode* findRightestNode(TreeNode* node);
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

#endif