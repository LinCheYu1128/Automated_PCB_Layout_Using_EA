#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "TreeNode.h"
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
        TreeNode* traverseUpdateTree(TreeNode* node);

    public:
        // constructor, destructor
        BinaryTree(ComponentList* comp_list);
        
        ~BinaryTree();
        
        // utility
        BinaryTree* copy();
        void swap(int id_1, int id_2);
        void changetoroot(TreeNode* node);
        void delete_node(int ID);
        void updateTree();
        TreeNode* findRightestNode(TreeNode* node);
        TreeNode* findLeafNode(TreeNode* node);
        vector<TreeNode*> ExtractTree(int extractID);
        void ModifyTree(vector<TreeNode*> node_permu);
        void ModifyDoubleSidedTree(vector<TreeNode*> node_permu_front, vector<TreeNode*> node_permu_back);
        void varifyTree();

        // getter
        TreeNode* getRoot();
        int getSide();
        map<int, TreeNode*> getTreeNodeMap();
        ComponentList* getComponentList();

        // setter
        void setRoot(TreeNode* node);
        void setSide(int side);
        void setSingleSide();
        void setDoubleSide();
        void updateTreeNodeMap();

        // printer
        void printBinaryTree();
};



#endif