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

Layout::Layout(ComponentList* comp_list) {
        this->comp_list = comp_list;
        this->component_num = 0;
        double area = 0;
        double Pns = 0;
        double wirelength = 0;
        double fitness = 0;
}

Layout::~Layout() {
    // delete this->comp_list;
    delete this->tree;
    delete this->front_contour;
    delete this->back_contour;
}

Layout* Layout::copy(){
    // ComponentList* component_list = new ComponentList();
    Layout* layout = new Layout(this->comp_list);
    layout->component_num = this->component_num;

    layout->tree = this->getBinaryTree()->copy();
    layout->front_contour = this->front_contour->copy();
    layout->back_contour = this->back_contour->copy();
    layout->fitness = this->fitness;
    layout->area = this->area;
    layout->Pns = this->Pns;
    layout->wirelength = this->wirelength;
    return layout;
}
// Layout* Layout::copy(){
//     // ComponentList* component_list = new ComponentList();
//     int side = this->getBinaryTree()->getSide();
//     BinaryTree* tree = this->getBinaryTree()->copy();
//     Layout* layout = new Layout(tree, this->comp_list, side);
//     layout->setFitness();
//     return layout;
// }

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

    root->shiftUp(contour->getContourVector()); // check whether component fuck with contour
    preplaceCheck(root); // check whether component fuck with preplace
    
    contour->addBlock(root->getComponentState()); // update contour

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
    // this->getBinaryTree()->updateTree();
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

    this->fitness = 0.4*(this->area - 700) / (1000 - 700) + 0.6*(this->Pns + 35) / (-8 + 35);
    // this->fitness = this->Pns; // -35~-8
    // this->fitness = this->area; // 700~1000
    // this->fitness = this->area / 1000 * 0.4 + this->wirelength / 300 * 0.4 + this->Pns / 5 * 0.2;
}

void Layout::setFitness(tuple<double, double, double> weight_vector){
    this->setArea();
    this->setWireLength();//memory leak
    this->setPns();

    // Pns version 1
    this->fitness = (this->area - 827.604) / (2074.21 - 827.604) * get<0>(weight_vector) + 
                    (this->wirelength - 528.805) / (723.54 - 528.805) * get<1>(weight_vector) + 
                    (this->Pns - 4.25) / (15.75 - 4.25) * get<2>(weight_vector);
    
    // Pns version 2
    // this->fitness = (this->area - 790.04) / (1962 - 790.04) * get<0>(weight_vector) + 
    //                 (this->wirelength - 492.295) / (952 - 492.295) * get<1>(weight_vector) + 
    //                 (this->Pns + 16.775) / (1.25733 + 16.775) * get<2>(weight_vector);
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
                tr_x = comp_state->getPosition().x + comp_state->getLength("outer");
                tr_y = comp_state->getPosition().y + comp_state->getWidth("outer");
                comp_in_net.push_back(make_tuple(bl_x, bl_y));
                comp_in_net.push_back(make_tuple(tr_x, tr_y));
            }
        }

        net_length = calcuHPWL(comp_in_net);
        comp_in_net.clear();
        total_net_length += net_length;
    }
    this->wirelength = total_net_length;

    delete net_list;
}

// void Layout::setPns(){
//     vector< Point > primary_part;
//     vector< Point > secondary_part;
//     stack<TreeNode*> node_stack;
//     node_stack.push(this->getBinaryTree()->getRoot());

//     // cout << "---" << endl;
//     while (node_stack.empty() == false) {
//         TreeNode* temp = node_stack.top();

//         if (temp->getComponentProp()->getVoltage() == 1) {
//             // cout << temp->getComponentProp()->getName() << "'s voltage: ";
//             // cout << temp->getComponentProp()->getVoltage() << "-> ";
//             // cout << temp->getComponentState()->getPosition().x << endl;;
//             primary_part.push_back(temp->getComponentState()->getPosition());
//         }else if (temp->getComponentProp()->getVoltage() == -1){
//             // cout << temp->getComponentProp()->getName() << "'s voltage: ";
//             // cout << temp->getComponentProp()->getVoltage() << "-> ";
//             // cout << temp->getComponentState()->getPosition().x << endl;;
//             secondary_part.push_back(temp->getComponentState()->getPosition());
//         }

//         node_stack.pop();
//         if (temp->getRightchild())
//             node_stack.push(temp->getRightchild());
//         if (temp->getLeftchild())
//             node_stack.push(temp->getLeftchild());
//     }
//     this->Pns = this->calcuTwoSide(primary_part, secondary_part);
// }

void Layout::setPns(){
    vector< TreeNode* > front_primary_part;
    vector< TreeNode* > front_secondary_part;
    vector< TreeNode* > back_primary_part;
    vector< TreeNode* > back_secondary_part;
    int back_flag = 0;
    stack<TreeNode*> node_stack;
    node_stack.push(this->getBinaryTree()->getRoot());

    // cout << "========front========" << endl;
    while (node_stack.empty() == false) {
        TreeNode* temp = node_stack.top();

        if(back_flag == 0){
            if (temp->getComponentProp()->getVoltage() == 1) {
                // cout << temp->getComponentProp()->getName() << " ";
                // cout << temp->getComponentProp()->getVoltage() << "-> ";
                // cout << temp->getComponentState()->getPosition().x << endl;;
                front_primary_part.push_back(temp);
            }else if (temp->getComponentProp()->getVoltage() == -1){
                // cout << temp->getComponentProp()->getName() << " ";
                // cout << temp->getComponentProp()->getVoltage() << "-> ";
                // cout << temp->getComponentState()->getPosition().x << endl;;
                front_secondary_part.push_back(temp);
            }
        }else if (back_flag == 1){
            if (temp->getComponentProp()->getVoltage() == 1) {
                // cout << temp->getComponentProp()->getName() << " ";
                // cout << temp->getComponentProp()->getVoltage() << "-> ";
                // cout << temp->getComponentState()->getPosition().x << endl;;
                back_primary_part.push_back(temp);
            }else if (temp->getComponentProp()->getVoltage() == -1){
                // cout << temp->getComponentProp()->getName() << " ";
                // cout << temp->getComponentProp()->getVoltage() << "-> ";
                // cout << temp->getComponentState()->getPosition().x << endl;;
                back_secondary_part.push_back(temp);
            }
        }

        if(temp->getComponentProp()->getName() == "B_RootHole") {
            // cout << endl;
            // cout << "========back========" << endl;
            back_flag = 1;
        }

        node_stack.pop();
        if (temp->getRightchild())
            node_stack.push(temp->getRightchild());
        if (temp->getLeftchild())
            node_stack.push(temp->getLeftchild());
    }
    // cout << endl;
    this->Pns = this->calcuTwoSideV2(front_primary_part, front_secondary_part, back_primary_part, back_secondary_part);
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
    
    if (MAX_X >= 29.2 + 1) {penalty = 10000;}
    if (MAX_Y >= 32.5 + 1) {penalty = 10000;}

    // return MAX_X * MAX_Y + penalty;
    return MAX_X * MAX_Y;
}

double Layout::evaluateTotalArea(){
    int side = this->getBinaryTree()->getSide();
    return this->evaluateArea(side);
}

double Layout::calcuTwoSide(vector< Point > prim_list, vector< Point > sec_list){
    
    // // version 1
    // double rightest_primary_x = 0;
    // double leftest_secondary_x = 27.2;

    // for(unsigned i = 0; i < prim_list.size(); i++){
    //     rightest_primary_x = max(prim_list[i].x, rightest_primary_x);
    // }
    // for(unsigned i = 0; i < sec_list.size(); i++){
    //     leftest_secondary_x = min(sec_list[i].x, leftest_secondary_x);
    // }

    // return rightest_primary_x - leftest_secondary_x;

    // version 2
    double primary_sum = 0;
    double secondary_sum = 0;

    for(unsigned i = 0; i < prim_list.size(); i++){
        primary_sum += prim_list[i].x;
    }
    for(unsigned i = 0; i < sec_list.size(); i++){
        secondary_sum += sec_list[i].x;
    }

    double primary_avg = primary_sum / prim_list.size();
    double secondary_avg = secondary_sum / sec_list.size();

    return primary_avg - secondary_avg;
}

double Layout::calcuTwoSideV2(vector< TreeNode* > f_prim_list, vector< TreeNode* > f_sec_list, vector< TreeNode* > b_prim_list, vector< TreeNode* > b_sec_list){
    
    // version 1
    // double f_rightest_primary_x = 0;
    // double f_leftest_secondary_x = 27.2;
    // double b_rightest_primary_x = 0;
    // double b_leftest_secondary_x = 27.2;

    // for(unsigned i = 0; i < f_prim_list.size(); i++){
    //     f_rightest_primary_x = max(f_prim_list[i]->getComponentState()->getPosition().x + f_prim_list[i]->getComponentState()->getLength("outer")
    //                                 , f_rightest_primary_x);
    //     // cout << f_prim_list[i]->getComponentProp()->getName() << endl;
    //     // cout << f_rightest_primary_x << endl;
    // }
    // for(unsigned i = 0; i < f_sec_list.size(); i++){
    //     f_leftest_secondary_x = min(f_sec_list[i]->getComponentState()->getPosition().x, f_leftest_secondary_x);
    //     // cout << f_sec_list[i]->getComponentProp()->getName() << endl;
    //     // cout << f_leftest_secondary_x << endl;
    // }
    // double front_seperate = f_rightest_primary_x - f_leftest_secondary_x;

    // for(unsigned i = 0; i < b_prim_list.size(); i++){
    //     b_rightest_primary_x = max(b_prim_list[i]->getComponentState()->getPosition().x + b_prim_list[i]->getComponentState()->getLength("outer")
    //                                 , b_rightest_primary_x);
    //     // cout << b_prim_list[i]->getComponentProp()->getName() << endl;
    //     // cout << b_rightest_primary_x << endl;
    // }
    // for(unsigned i = 0; i < b_sec_list.size(); i++){
    //     b_leftest_secondary_x = min(b_sec_list[i]->getComponentState()->getPosition().x, b_leftest_secondary_x);
    //     // cout << b_sec_list[i]->getComponentProp()->getName() << endl;
    //     // cout << b_leftest_secondary_x << endl;
    // }
    // double back_seperate = b_rightest_primary_x - b_leftest_secondary_x;

    // version 1 modifiy
    double f_leftest_primary_x = 27.2;
    double f_rightest_secondary_x = 0;
    double b_leftest_primary_x = 27.2;
    double b_rightest_secondary_x = 0;


    for(unsigned i = 0; i < f_sec_list.size(); i++){
        f_rightest_secondary_x = max(f_sec_list[i]->getComponentState()->getPosition().x + f_sec_list[i]->getComponentState()->getLength("outer")
                                    , f_rightest_secondary_x);
        // cout << f_prim_list[i]->getComponentProp()->getName() << endl;
        // cout << f_rightest_primary_x << endl;
    }
    for(unsigned i = 0; i < f_prim_list.size(); i++){
        f_leftest_primary_x = min(f_prim_list[i]->getComponentState()->getPosition().x, f_leftest_primary_x);
        // cout << f_sec_list[i]->getComponentProp()->getName() << endl;
        // cout << f_leftest_secondary_x << endl;
    }
    double front_seperate = f_rightest_secondary_x - f_leftest_primary_x;

    for(unsigned i = 0; i < b_sec_list.size(); i++){
        b_rightest_secondary_x = max(b_sec_list[i]->getComponentState()->getPosition().x + b_sec_list[i]->getComponentState()->getLength("outer")
                                    , b_rightest_secondary_x);
        // cout << b_prim_list[i]->getComponentProp()->getName() << endl;
        // cout << b_rightest_primary_x << endl;
    }
    for(unsigned i = 0; i < b_prim_list.size(); i++){
        f_leftest_primary_x = min(b_prim_list[i]->getComponentState()->getPosition().x, f_leftest_primary_x);
        // cout << b_sec_list[i]->getComponentProp()->getName() << endl;
        // cout << b_leftest_secondary_x << endl;
    }
    double back_seperate = b_rightest_secondary_x - f_leftest_primary_x;

    if((f_prim_list.size() == 0 || f_sec_list.size() == 0) || (b_prim_list.size() == 0 || b_sec_list.size() == 0)){
        return max(back_seperate, front_seperate);
    }else{
        if(back_seperate < 0) back_seperate = 0;
        if(front_seperate < 0) front_seperate = 0;
        return (back_seperate + front_seperate) / 2;
    }

    // // version 2
    // double f_rightest_primary_sum = 0;
    // double f_leftest_secondary_sum = 0;
    // double b_rightest_primary_sum = 0;
    // double b_leftest_secondary_sum = 0;

    // for(unsigned i = 0; i < f_prim_list.size(); i++){
    //     f_rightest_primary_sum += f_prim_list[i].x;
    // }
    // for(unsigned i = 0; i < f_sec_list.size(); i++){
    //     f_leftest_secondary_sum += f_sec_list[i].x;
    // }
    // double f_rightest_primary_avg = f_rightest_primary_sum / f_prim_list.size();
    // double f_leftest_secondary_avg = f_leftest_secondary_sum / f_sec_list.size();

    // for(unsigned i = 0; i < b_prim_list.size(); i++){
    //     b_rightest_primary_sum += b_prim_list[i].x;
    // }
    // for(unsigned i = 0; i < b_sec_list.size(); i++){
    //     b_leftest_secondary_sum += b_sec_list[i].x;
    // }
    // double b_rightest_primary_avg = b_rightest_primary_sum / b_prim_list.size();
    // double b_leftest_secondary_avg = b_leftest_secondary_sum / b_sec_list.size();

    // return max(f_rightest_primary_avg - f_leftest_secondary_avg, b_rightest_primary_avg - b_leftest_secondary_avg);

}

void Layout::preplaceCheck(TreeNode* node) {
    Point node_left_bot = node->getComponentState()->getPosition();
    double y = node_left_bot.y;
    vector<ComponentProperty*> preplace_comp = this->comp_list->getPreplaceData();
    for (auto i = preplace_comp.begin(); i != preplace_comp.end(); i++) {
        if ((*i)->getSide() == node->getComponentState()->getSide()) {
            Point comp_left_bot = (*i)->getPreplace();
            if (node_left_bot.x < comp_left_bot.x + (*i)->getLength()\
            && comp_left_bot.x < node_left_bot.x + node->getComponentState()->getLength("outer")\
            && node_left_bot.y < comp_left_bot.y + (*i)->getWidth()\
            && comp_left_bot.y < node_left_bot.y + node->getComponentState()->getWidth("outer")) y = max(y, comp_left_bot.y + (*i)->getWidth());
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
        // cout << current->getComponentState()->getPosition().x << endl;
        nodes.pop();
        ComponentProperty* prop = current->getComponentProp();
        ComponentState* state = current->getComponentState();
        double x = (state->getAngle()==90 || state->getAngle()==270)?prop->getWidth():prop->getLength();
        double y = (state->getAngle()==90 || state->getAngle()==270)?prop->getLength():prop->getWidth();
        layout_data << prop->getName() << "," 
                    << prop->getColor() << ","
                    << x << ","
                    << y << ","
                    // << prop->getLength() << ","
                    // << prop->getWidth() << ","
                    << prop->getHeight() << ","
                    << prop->getVoltage() << ","
                    << state->getPosition().x<< ","
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
    // cout << "write Pin" << endl;
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
        // map<string, Point> temp_contain = current->getComponentProp()->getDefaultPinPosition();
        // cout << temp_contain.size() << endl;
        // state->printPinPosition();
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
    // Preplace pin position
    vector<ComponentProperty*> preplace_comp = layout_tree->getComponentList()->getPreplaceData();
    for (auto i = preplace_comp.begin(); i != preplace_comp.end(); i++) {
        map<string, Point> temp_preplace = (*i)->getDefaultPinPosition();
        for (auto j = temp_preplace.begin(); j != temp_preplace.end(); j++) {
            pin_data << (*i)->getName() << ","
                     << j->first << ","
                     << 0.2 << ","
                     << 0.2 << ","
                     << j->second.x + (*i)->getPreplace().x << ","
                     << j->second.y + (*i)->getPreplace().y << "\n";
        }
    }

    pin_data.close();
}
