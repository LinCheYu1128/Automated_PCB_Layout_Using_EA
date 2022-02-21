#ifndef COMPONENTLIST_H
#define COMPONENTLIST_H

#include "Component.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

typedef struct Component_Path {
    string component_csvfile;
    string component_relativePath;
    string pinPosition_relativePath;
}Component_Path;

class ComponentList {
    private:
        map<string, ComponentProperty*> comp_data_dictionary;
        vector<ComponentProperty*> comp_data_vector;
        Component_Path comp_info = {
            "component.csv",                     // component_csvfile
            "..\\resources\\",                   // component_relativePath
            "..\\resources\\pin position\\"      // pinPosition_relativePath
        };
    public:
        // constructer, destructor
        ComponentList(/*Component_Path comp_info*/);
        ~ComponentList();
        
        // getter
        int getSize();
        ComponentProperty* getDataByName(string comp_name);
        ComponentProperty* getDataByIndex(int index);
        map<string, ComponentProperty*> getAllData();
        
        // setter
        void setData(string comp_name, ComponentProperty* comp_prop);
        void setPinPosition(string comp_name);
        void setAllData();

        // printer
        void printData(string comp_name);
        void printAllData();
};

class PinPosition_Reader {
    public:
        // constructer, destructor
        PinPosition_Reader(string filename, string relativePath);
};

vector<string> split(string s, string delim);

#endif