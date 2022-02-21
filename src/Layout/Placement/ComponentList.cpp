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
        "./../resources/",                   // component_relativePath
        "./../resources/pin position/"      // pinPosition_relativePath
    };

    this->comp_info = comp_info;
    this->setAllData();
}

ComponentList::~ComponentList() {
    auto iter = comp_data_dictionary.begin();
    while (iter != comp_data_dictionary.end()) {
        delete iter->second;
        ++iter;
    }
}

int ComponentList::getSize() {
    return this->comp_data_dictionary.size();
}

ComponentProperty* ComponentList::getDataByName(string comp_name) {
    return this->comp_data_dictionary[comp_name];
}

ComponentProperty* ComponentList::getDataByIndex(int index) {
    return this->comp_data_vector[index];
}

map<string, ComponentProperty*> ComponentList::getAllData() {
    return this->comp_data_dictionary;
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
        comp_data_dictionary[comp_name]->setOneDefaultPinPosition(key, point);
    }

    pin_file.close();
}

void ComponentList::setAllData() {
    ifstream inFile(comp_info.component_relativePath + comp_info.component_csvfile);
    string temp;

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
        getline(inFile, temp, '\n' );
        comp_prop->setVoltage(stod(temp));

        this->setData(comp_prop->getName(), comp_prop);
        this->setPinPosition(comp_prop->getName());
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