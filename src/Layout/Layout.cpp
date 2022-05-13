#include "Layout.h"
#include "console.h"
#include <iostream>

using namespace std;

Layout::Layout(BinaryTree* tree, ComponentList* comp_list, int side){
    this->comp_list = comp_list;
    this->tree = tree;
    this->setContour();
    // this->tree->updateTree();

    if (side == 1) this->setState(this->tree->getRoot(), "front");
    else if (side == 2) {
        this->setState(this->tree->getRoot()->getLeftchild(), "front");
        this->setState(this->tree->getRoot()->getRightchild(), "back");
    }
    else {cout << "unknown side" << endl; exit(0);} 
    this->component_num = comp_list->getSize();

    // cout << "front contour:" << endl;
    // this->front_contour->printContour();
    // cout << "back contour:" << endl;
    // this->back_contour->printContour();
}

Layout::Layout(ComponentList* comp_list, int side) {
    this->comp_list = comp_list;
    this->setBinaryTree(side);
    this->setContour();
    // this->tree->updateTree();

    if (side == 1) this->setState(this->tree->getRoot(), "front");
    else if (side == 2) {
        this->setState(this->tree->getRoot()->getLeftchild(), "front");
        this->setState(this->tree->getRoot()->getRightchild(), "back");
    }
    else {cout << "unknown side" << endl; exit(0);}
    this->component_num = comp_list->getSize();

    // cout << "front contour:" << endl;
    // this->front_contour->printContour();
    // cout << "back contour:" << endl;
    // this->back_contour->printContour();
}

Layout::~Layout() {
    // delete this->comp_list;
    delete this->tree;
    delete this->front_contour;
    delete this->back_contour;
}

Layout* Layout::copy(){
    // ComponentList* component_list = new ComponentList();
    int side = this->getBinaryTree()->getSide();
    BinaryTree* tree = this->getBinaryTree()->copy();
    Layout* layout = new Layout(tree, this->comp_list, side);
    layout->setFitness();
    return layout;
}

BinaryTree* Layout::getBinaryTree(){
    return this->tree;
}

int Layout::getComponentNum(){
    return this->component_num;
}

double Layout::getFitness(){
    return this->fitness;
}

Contour* Layout::getContour(string side){
    if (side == "front"){
        return this->front_contour;
    }else {
        return this->back_contour;
    }
}

double Layout::getArea() {
    return this->area;
}

double Layout::getWireLength(){
    return this->wirelength;
}

double Layout::getPns(){
    return this->Pns;
}

void Layout::setBinaryTree(int side) {
    this->tree = new BinaryTree(this->comp_list);
    if (side == 1) { this->tree->setSingleSide(); }
    if (side == 2) { this->tree->setDoubleSide(); }
}

void Layout::setContour() {
    this->front_contour = new Contour();
    this->back_contour = new Contour();
}

void Layout::setState(TreeNode* root, string side) {
    Contour* contour;
    root->getComponentState()->setSide(side);
    if (side == "front") {
        contour = this->front_contour;
    }
    else if (side == "back") {
        contour = this->back_contour;
    }
    else {cout << "Unknown side name." << endl; exit(0);}
    // cout << "---------------------------------------------------" << endl;
    // cout << root->getComponentProp()->getName() << endl;
    // if(root->getLeftchild()){
    //     cout << "left child: " << root->getLeftchild()->getComponentProp()->getName() << endl;
    // }else{
    //     cout << "left child: null" << endl;
    // }
    // if(root->getRightchild()){
    //     cout << "right child: " << root->getRightchild()->getComponentProp()->getName() << endl;
    // }else{
    //     cout << "right child: null" << endl;
    // }
    // cout << "contour" ;
    // contour->printContour();
    root->shiftUp(contour->getContourVector());
    preplaceCheck(root);
    // cout << "block w: " << root->getComponentState()->getWidth() << endl;
    // cout << "block l: " << root->getComponentState()->getLength() << endl;
    // cout << "block position: (" << root->getComponentState()->getPosition().x << "," << root->getComponentState()->getPosition().y << ")" << endl;
    contour->addBlock(root->getComponentState());

    if (root->getLeftchild()) {
        // cout << "search left ";
        setState(root->getLeftchild(), side);
    }
    if (root->getRightchild()) {
        // cout << "search right ";
        setState(root->getRightchild(), side);
    }
}

void Layout::updateLayout(){
    this->setContour();
    this->getBinaryTree()->updateTree();
    if (this->tree->getSide() == 1) this->setState(this->tree->getRoot(), "front");
    else if (this->tree->getSide() == 2) {
        this->setState(this->tree->getRoot()->getLeftchild(), "front");
        this->setState(this->tree->getRoot()->getRightchild(), "back");
    }
    else {cout << "unknown side" << endl; exit(0);} 
}

void Layout::setFitness(){
    this->setArea();
    // this->setWireLength();
    this->setPns();


    this->fitness = this->area + this->Pns/10;

    // this->fitness = this->area;
    // this->fitness = this->area / 1000 * 0.4 + this->wirelength / 300 * 0.4 + this->Pns / 5 * 0.2;

    // this->fitness = this->area + this->wirelength + this->Pns;
    // this->fitness = this->area / 750 *0.4 + this->wirelength / 270 * 0.4 + this->Pns / 10 * 0.2;

}

void Layout::setArea() {
    this->area = this->evaluateTotalArea();
}

void Layout::setWireLength(){
    NetList* net_list = new NetList();
    map< string, vector<string> > netlist = net_list->getNetList();

    map< string, vector<string> >::iterator net_iter;
    Point pin_iter;
    vector< tuple<double, double> > comp_in_net;    // Coordinate of every component in each net.
    double net_length = 0;
    double total_net_length = 0;
    string component_name, pin_num;
    map<string, int> name2id = this->getBinaryTree()->getComponentList()->getCompIdMap();

    for (net_iter = netlist.begin(); net_iter != netlist.end(); net_iter++) {
        for (unsigned c = 0; c < net_iter->second.size(); c++) {
            if (net_iter->second.at(c).at(4) == '-') {
                component_name = component_name.assign(net_iter->second.at(c), 0, 4);
            }
            else if (net_iter->second.at(c).at(5) == '-') {
                component_name = component_name.assign(net_iter->second.at(c), 0, 5);
            }
            if (component_name == "C509" || component_name == "C510") {
                int T501_id = name2id["T501"];
                double width = this->getBinaryTree()->getTreeNodeMap().at(T501_id)->getComponentState()->getPosition().x + 11;
                double length = this->getBinaryTree()->getTreeNodeMap().at(T501_id)->getComponentState()->getPosition().y + 10.25;
                // cout << "(" << width << ", " << length << ")" << endl;
                comp_in_net.push_back(make_tuple(width, length));
            }
            else if (component_name == "M503") {
                pin_num = pin_num.assign(net_iter->second.at(c), 5, 6);
                int M503_id = name2id["M503"];
                pin_iter = this->getBinaryTree()->getTreeNodeMap().at(M503_id)->getComponentState()->getPinPosition()[pin_num];
                comp_in_net.push_back(make_tuple(pin_iter.x, pin_iter.y));
            }
            else if (component_name == "T501") {
                pin_num = pin_num.assign(net_iter->second.at(c), 5, 6);
                int T501_id =name2id["T501"];
                pin_iter = this->getBinaryTree()->getTreeNodeMap().at(T501_id)->getComponentState()->getPinPosition()[pin_num];
                comp_in_net.push_back(make_tuple(pin_iter.x, pin_iter.y));
            }
            else {
                double bl_x, bl_y, tr_x, tr_y;  // bottom_left & top_right of component
                int compid = name2id[component_name];
                ComponentState* comp_state = this->getBinaryTree()->getTreeNodeMap().at(compid)->getComponentState();
                bl_x = comp_state->getPosition().x;
                bl_y = comp_state->getPosition().y;
                tr_x = comp_state->getPosition().x + comp_state->getLength();
                tr_y = comp_state->getPosition().y + comp_state->getWidth();
                comp_in_net.push_back(make_tuple(bl_x, bl_y));
                comp_in_net.push_back(make_tuple(tr_x, tr_y));
            }
        }

        net_length = calcuHPWL(comp_in_net);
        comp_in_net.clear();
        total_net_length += net_length;
    }
    this->wirelength = total_net_length;
}

void Layout::setPns(){
    vector< Point > primary_part;
    vector< Point > secondary_part;
    stack<TreeNode*> node_stack;
    node_stack.push(this->getBinaryTree()->getRoot());

    // cout << "---" << endl;
    while (node_stack.empty() == false) {
        TreeNode* temp = node_stack.top();

        if (temp->getComponentProp()->getVoltage() == 1) {
            // cout << temp->getComponentProp()->getName() << "'s voltage: ";
            // cout << temp->getComponentProp()->getVoltage() << "-> ";
            // cout << temp->getComponentState()->getPosition().x << endl;;
            primary_part.push_back(temp->getComponentState()->getPosition());
        }else if (temp->getComponentProp()->getVoltage() == -1){
            // cout << temp->getComponentProp()->getName() << "'s voltage: ";
            // cout << temp->getComponentProp()->getVoltage() << "-> ";
            // cout << temp->getComponentState()->getPosition().x << endl;;
            secondary_part.push_back(temp->getComponentState()->getPosition());
        }

        node_stack.pop();
        if (temp->getRightchild())
            node_stack.push(temp->getRightchild());
        if (temp->getLeftchild())
            node_stack.push(temp->getLeftchild());
    }
    this->Pns = this->calcuTwoSide(primary_part, secondary_part);
}

double Layout::calcuHPWL(vector< tuple<double, double> > comp_in_net) {
    double bl_x, bl_y, tr_x, tr_y, WL;
    bl_x = get<0>(comp_in_net.at(0));
    tr_x = bl_x;
    bl_y = get<1>(comp_in_net.at(0));
    tr_y = bl_y;

    for (unsigned i = 1; i < comp_in_net.size(); i++) {
        if (bl_x > get<0>(comp_in_net.at(i)))
            bl_x = get<0>(comp_in_net.at(i));
        if (bl_y > get<1>(comp_in_net.at(i)))
            bl_y = get<1>(comp_in_net.at(i));
        if (tr_x < get<0>(comp_in_net.at(i)))
            tr_x = get<0>(comp_in_net.at(i));
        if (tr_y < get<1>(comp_in_net.at(i)))
            tr_y = get<1>(comp_in_net.at(i));
    }

    WL = (tr_x - bl_x) + (tr_y - bl_y);
    // cout << "WL = " << WL << endl;

    return WL;
}

void Layout::printComponent() {
    this->tree->printBinaryTree();
}

// double Layout::evaluateArea(int side){
//     double MAX_X = 0;
//     double MAX_Y = 0;

//     if (side == 0){
//         for (int i = 0; i < this->getContour("front")->getSize(); i++) {
//             MAX_X = max(MAX_X, this->getContour("front")->getContourVector().at(i).x);
//             MAX_Y = max(MAX_Y, this->getContour("front")->getContourVector().at(i).y);
//         }
//     }else if (side == 1){
//         for (int i = 0; i < this->getContour("back")->getSize(); i++) {
//             MAX_X = max(MAX_X, this->getContour("bcak")->getContourVector().at(i).x);
//             MAX_Y = max(MAX_Y, this->getContour("back")->getContourVector().at(i).y);
//         }
//     }
//     return MAX_X * MAX_Y;
// }

// double Layout::evaluateTotalArea(){
    
//     double front_area = 0;
//     double back_area = 0;
    
//     if (this->getBinaryTree()->getSide() == 1){
//         int side = 0;
//         front_area = this->evaluateArea(side);
//         back_area = 0;
//     }else if (this->getBinaryTree()->getSide() == 2){
//         int side = 0;
//         front_area = this->evaluateArea(side);
//         side = 1;
//         back_area = this->evaluateArea(side);
//     }
//     return front_area + back_area;
// }
double Layout::evaluateArea(int side){
    double MAX_X = 0;
    double MAX_Y = 0;
    double penalty = 0;

    if (side == 1){
        for (int i = 0; i < this->getContour("front")->getSize(); i++) {
            MAX_X = max(MAX_X, this->getContour("front")->getContourVector().at(i).x);
            MAX_Y = max(MAX_Y, this->getContour("front")->getContourVector().at(i).y);
        }
    }else if (side == 2){
        for (int i = 0; i < this->getContour("front")->getSize(); i++) {
            MAX_X = max(MAX_X, this->getContour("front")->getContourVector().at(i).x);
            MAX_Y = max(MAX_Y, this->getContour("front")->getContourVector().at(i).y);
        }
        for (int i = 0; i < this->getContour("back")->getSize(); i++) {
            MAX_X = max(MAX_X, this->getContour("bcak")->getContourVector().at(i).x);
            MAX_Y = max(MAX_Y, this->getContour("back")->getContourVector().at(i).y);
        }
    }

    
    if (MAX_X >= 29.2 + 1) {penalty += 10000*MAX_X;}
    if (MAX_Y >= 32.5 + 1) {penalty += 10000*MAX_Y;}

    return MAX_X * MAX_Y  + penalty;
}

double Layout::evaluateTotalArea(){
    int side = this->getBinaryTree()->getSide();
    return this->evaluateArea(side);
}

// double Layout::calcuTwoSide(vector< Point > prim_list, vector< Point > sec_list){
//     double primary_x = 0.0;
//     double secondary_x = 0.0;

//     for(unsigned i = 0; i < prim_list.size(); i++){
//         primary_x += prim_list[i].x;
//     }
//     for(unsigned i = 0; i < sec_list.size(); i++){
//         secondary_x += sec_list[i].x;
//     }

//     // return abs(primary_x / prim_list.size() - secondary_x / sec_list.size()) * -1;
//     return primary_x / prim_list.size() + (secondary_x / sec_list.size() - 29.2);
// }

double Layout::calcuTwoSide(vector< Point > prim_list, vector< Point > sec_list){
    double rightest_primary_x = 0;
    double leftest_secondary_x = 27.2;

    for(unsigned i = 0; i < prim_list.size(); i++){
        rightest_primary_x = max(prim_list[i].x, rightest_primary_x);
    }
    for(unsigned i = 0; i < sec_list.size(); i++){
        leftest_secondary_x = min(sec_list[i].x, leftest_secondary_x);
    }

    // return abs(primary_x / prim_list.size() - secondary_x / sec_list.size()) * -1;

//     return 10 * primary_x - secondary_x /*/ prim_list.size() + (secondary_x / sec_list.size() - 29.2)*/;
  return rightest_primary_x - leftest_secondary_x;
}

void Layout::preplaceCheck(TreeNode* node) {
    Point node_left_bot = node->getComponentState()->getPosition();
    double y = node_left_bot.y;
    vector<ComponentProperty*> preplace_comp = this->comp_list->getPreplaceData();
    for (auto i = preplace_comp.begin(); i != preplace_comp.end(); i++) {
        if ((*i)->getSide() == node->getComponentState()->getSide()) {
            Point comp_left_bot = (*i)->getPreplace();
            if (node_left_bot.x < comp_left_bot.x + (*i)->getLength()\
            && comp_left_bot.x < node_left_bot.x + node->getComponentState()->getLength()\
            && node_left_bot.y < comp_left_bot.y + (*i)->getWidth()\
            && comp_left_bot.y < node_left_bot.y + node->getComponentState()->getWidth()) y = max(y, comp_left_bot.y + (*i)->getWidth());
            // rec1[0] < rec2[2] && rec2[0] < rec1[2] && rec1[1] < rec2[3] && rec2[1] < rec1[3];
        } 
    }
    node->getComponentState()->setPosition(node_left_bot.x, y);
}

void writeCsv(Layout* layout, string filename){
    BinaryTree* layout_tree = layout->getBinaryTree();

    // vector<TreeNode*> temp = layout_tree->ExtractTree(layout_tree->getRoot()->getID());
    // for(unsigned i = 0; i < temp.size(); i++){
    //     cout << temp[i]->getComponentProp()->getName() << " ";
    // }
    // cout << endl;

    std::ofstream layout_data;
    layout_data.open(filename);
    stack<TreeNode*> nodes;
    nodes.push(layout_tree->getRoot());
    while (nodes.size() > 0) {
        TreeNode *current = nodes.top();
        nodes.pop();
        ComponentProperty* prop = current->getComponentProp();
        ComponentState* state = current->getComponentState();
        layout_data << prop->getName() << "," 
                    << prop->getColor() << ","
                    << state->getLength() << ","
                    << state->getWidth() << ","
                    << prop->getHeight() << ","
                    << prop->getVoltage() << ","
                    << state->getPosition().x << ","
                    << state->getPosition().y << ","
                    << state->getMargin() << ","
                    << state->getAngle() << ","
                    << state->getSide() << ",";
        if (current->getLeftchild()) layout_data << current->getLeftchild()->getComponentProp()->getName() << ",";
        else layout_data << "null" << ",";
        if (current->getRightchild()) layout_data << current->getRightchild()->getComponentProp()->getName() << ",";
        else layout_data << "null" << ",";
        layout_data << "\n";

        if (current->getRightchild()) nodes.push(current->getRightchild());
        if (current->getLeftchild()) nodes.push(current->getLeftchild());
    }
    layout_data.close();
}

void writePin(Layout* layout, string filename) {
    BinaryTree* layout_tree = layout->getBinaryTree();
    map<string, Point>::iterator iter;

    // vector<TreeNode*> temp = layout_tree->ExtractTree(layout_tree->getRoot()->getID());
    // for(unsigned i = 0; i < temp.size(); i++){
    //     cout << temp[i]->getComponentProp()->getName() << " ";
    // }
    // cout << endl;
    
    std::ofstream pin_data;
    pin_data.open (filename);
    stack<TreeNode*> nodes;
    nodes.push(layout_tree->getRoot());
    while (nodes.size() > 0) {
        TreeNode *current = nodes.top();
        nodes.pop();
        ComponentProperty* prop = current->getComponentProp();
        ComponentState* state = current->getComponentState();

        map<string, Point> temp_contain = current->getComponentState()->getPinPosition();
        for (iter = temp_contain.begin(); iter != temp_contain.end(); iter++) {
            pin_data << prop->getName() << ","
                     << iter->first << ","
                     << 0.2 << ","
                     << 0.2 << ","
                     << iter->second.x + state->getPosition().x << ","
                     << iter->second.y + state->getPosition().y << "\n";
        }

        if (current->getRightchild()) nodes.push(current->getRightchild());
        if (current->getLeftchild()) nodes.push(current->getLeftchild());

    }
    pin_data.close();
}
