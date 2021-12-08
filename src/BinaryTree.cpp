#include "../includes/BinaryTree.h"
#include <cwchar>

BinaryTree::BinaryTree(ComponentList* comp_list) {
    root = new TreeNode(comp_list->getData("T501"));
    root->setLeftchild(comp_list->getData("M503"));
    root->setRightchild(comp_list->getData("D508"));
    root->getLeftchild()->setLeftchild(comp_list->getData("R532"));
    root->getLeftchild()->setRightchild(comp_list->getData("Q504"));
    root->getLeftchild()->getLeftchild()->setRightchild(comp_list->getData("ZD501"));
    root->getLeftchild()->getRightchild()->setRightchild(comp_list->getData("R517"));
    root->getRightchild()->setRightchild(comp_list->getData("L501"));

    cout << "construct tree successfully" << endl;
    contour = new Contour();
}

TreeNode* BinaryTree::getRoot() {
    return root;
}

void BinaryTree::printBinaryTree() {
    root->printTreeNode();
}

void BinaryTree::plotBinaryTree() {
    PlotBinaryTree* plot_tree = new PlotBinaryTree(this);
    plot_tree->plotBinaryTree();
}

///////////////////////////////////////////////////////////////////////

PlotBinaryTree::PlotBinaryTree(BinaryTree* tree) {
    this->tree = tree;
}

void PlotBinaryTree::plotBinaryTree() {
    plotBinaryTree(tree->getRoot());
}

void PlotBinaryTree::plotBinaryTree(TreeNode* node) {
    plotBinaryTree("", node, false);
}

void PlotBinaryTree::plotBinaryTree(string prefix, TreeNode* node, bool isLeft) {
    if( node != nullptr ) {
        cout << prefix;
        cout << (isLeft ? "|-- " : "\\-- ");

        // print the value of the node
        cout << node->getComponentProp()->getName() << endl;

        // enter the next tree level - left and right branch
        plotBinaryTree(prefix + (isLeft ? "|   " : "    "), node->getLeftchild(), true);
        plotBinaryTree(prefix + (isLeft ? "|   " : "    "), node->getRightchild(), false);
    }
}