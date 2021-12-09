#ifndef UTILITY_H
#define UTILITY_H

#include "Component.h"

typedef struct Component_Path {
    string component_csvfile;
    string component_relativePath;
    string pinPosition_relativePath;
}Component_Path;

class ComponentList {
    private:
        map<string, ComponentProperty*> comp_data;
        Component_Path comp_info;
    public:
        // constructer, destructor
        ComponentList(Component_Path comp_info);
        ~ComponentList();
        
        // getter
        ComponentProperty* getData(string comp_name);
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

#endif