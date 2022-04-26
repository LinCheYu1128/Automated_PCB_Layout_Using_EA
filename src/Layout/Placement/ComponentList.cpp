#include "ComponentList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

ComponentList::ComponentList(/*Component_Path comp_info*/) {
    const Component_Path comp_info = {
        "component.csv",                     // component_csvfile
        "preplace.csv",                      // preplace_csvfile
        "./../resources/",                   // component_relativePath
        "./../resources/pin position/"      // pinPosition_relativePath
    };
    this->comp_info = comp_info;
    this->setAllData();
    this->setPreplace();
}

ComponentList::~ComponentList() {
    auto iter = comp_data_dictionary.begin();
    while (iter != comp_data_dictionary.end()) {
        delete iter->second;
        ++iter;
    }
}

int ComponentList::getSize() {
    return this->comp_data_vector.size();
}

ComponentProperty* ComponentList::getDataByName(string comp_name) {
    return this->comp_data_dictionary[comp_name];
}

ComponentProperty* ComponentList::getDataByIndex(int index) {
    return this->comp_data_vector[index];
}

vector<ComponentProperty*> ComponentList::getPreplaceData() {
    return this->preplace_comp_data;
}

map<string, ComponentProperty*> ComponentList::getAllData() {
    return this->comp_data_dictionary;
}

map<string, int> ComponentList::getCompIdMap(){
    return this->comp_id_map;
}

void ComponentList::setData(string comp_name, ComponentProperty* comp_prop) {
    this->comp_data_dictionary[comp_name] = comp_prop;
    comp_data_vector.push_back(comp_prop);
}

void ComponentList::setPinPosition(string comp_name) {
    ifstream pin_file(comp_info.pinPosition_relativePath + comp_name + ".csv");
    string temp_line;
    vector<string> token_list;
    string key;
    Point point;

    if (!pin_file) {
        cout << "can't open file " << comp_name << endl;
        return;
    } else {
        // cout << "can open " << comp_name << " file" << endl;
    }

    while (getline(pin_file, temp_line, '\n')) {
        token_list = split(temp_line, ",");
        key = token_list[0];
        point.x = stod(token_list[1]);
        point.y = stod(token_list[2]);
        // cout << key << " " << point.x << " " << point.y << endl;
        this->comp_data_dictionary[comp_name]->setOneDefaultPinPosition(key, point);
    }
    pin_file.close();
}

void ComponentList::setAllData() {
    ifstream inFile(comp_info.component_relativePath + comp_info.component_csvfile);
    string temp;
    int id = 0;

    getline(inFile, temp, '\n');
    while (!inFile.eof()) {
        ComponentProperty* comp_prop = new ComponentProperty();
        getline(inFile, temp, ',' );
        comp_prop->setName(temp);
        this->comp_id_map[temp] = id;
        getline(inFile, temp, ',' );
        comp_prop->setColor(temp);
        getline(inFile, temp, ',' );
        comp_prop->setLength(stod(temp));
        getline(inFile, temp, ',' );
        comp_prop->setWidth(stod(temp));
        getline(inFile, temp, ',' );
        comp_prop->setHeight(stod(temp));
        getline(inFile, temp, '\n' );
        comp_prop->setVoltage(stoi(temp));

        this->setData(comp_prop->getName(), comp_prop);
        this->setPinPosition(comp_prop->getName());

        id ++;
    }
}

void ComponentList::setPreplace() {
    ifstream inFile(comp_info.component_relativePath + comp_info.preplace_csvfile);
    string temp;
    double x = 0;

    getline(inFile, temp, '\n');
    while (!inFile.eof()) {
        ComponentProperty* comp_prop = new ComponentProperty();
        getline(inFile, temp, ',' );
        comp_prop->setName(temp);
        getline(inFile, temp, ',' );
        comp_prop->setColor(temp);
        getline(inFile, temp, ',' );
        comp_prop->setLength(stod(temp));
        getline(inFile, temp, ',' );
        comp_prop->setWidth(stod(temp));
        getline(inFile, temp, ',' );
        comp_prop->setHeight(stod(temp));
        getline(inFile, temp, ',' );
        comp_prop->setVoltage(stoi(temp));
        getline(inFile, temp, ',');
        x = stod(temp);
        getline(inFile, temp, ',');
        comp_prop->setPreplaceLocation(x, stod(temp));
        getline(inFile, temp, ',');
        comp_prop->setSide(temp);
        getline(inFile, temp, '\n');
        comp_prop->setPierce(stoi(temp));

        this->comp_data_dictionary[comp_prop->getName()] = comp_prop;
        this->preplace_comp_data.push_back(comp_prop);
        this->setPinPosition(comp_prop->getName());

        //Piercing Pin
        if (comp_prop->getPierce()) {
            if (comp_prop->getSide() == "front") temp = "back";
            else temp = "front";
            map<string, Point> pin_pos = comp_prop->getDefaultPinPosition();
            for (auto i = pin_pos.begin(); i != pin_pos.end(); ++i) {
                ComponentProperty* pin_comp_prop = new ComponentProperty();
                pin_comp_prop->setName(i->first);
                pin_comp_prop->setColor("0");
                pin_comp_prop->setLength(1);
                pin_comp_prop->setWidth(1);
                pin_comp_prop->setHeight(1);
                pin_comp_prop->setVoltage(0);
                pin_comp_prop->setPreplaceLocation(comp_prop->getPreplace().x + i->second.x - 0.5*pin_comp_prop->getLength(), comp_prop->getPreplace().y + i->second.y - 0.5*pin_comp_prop->getWidth());
                pin_comp_prop->setSide(temp);
                this->preplace_comp_data.push_back(pin_comp_prop);
            }
        }
    }
}

void ComponentList::printData(string comp_name) {
    cout << "[ component " << comp_name << " | "
         << "name: " << this->comp_data_dictionary[comp_name]->getName()
         << ", length:" << this->comp_data_dictionary[comp_name]->getLength()
         << ", width:" << this->comp_data_dictionary[comp_name]->getWidth()
         << ", height:" << this->comp_data_dictionary[comp_name]->getHeight()
         << ", voltage:" << this->comp_data_dictionary[comp_name]->getVoltage()
         << " ]" << endl;
         this->comp_data_dictionary[comp_name]->printDefaultPinPosition();
}

void ComponentList::printAllData() {
    auto iter = comp_data_dictionary.begin();
    while (iter != comp_data_dictionary.end()) {
        cout << "[ component " << iter->first << " | "
             << "name: " << iter->second->getName()
             << ", length:" << iter->second->getLength()
             << ", width:" << iter->second->getWidth()
             << ", height:" << iter->second->getHeight()
             << ", voltage:" << iter->second->getVoltage()
             << " ]" << endl;
        iter->second->printDefaultPinPosition();
        ++iter;
    }
}

vector<string> split(string str, string delim) {
    int pos = 0;  
    string token;
    vector<string> token_list;
    while ((pos = str.find(delim)) != string::npos) {
        token = str.substr(0, pos); // store the substring
        token_list.push_back(token);
        // cout << token << " ";
        str.erase(0, pos + delim.length());  /* erase() function store the current positon and move to next token. */
    }
    token_list.push_back(str);
    // cout << str << endl; // it print last token of the string.
    return token_list;
}