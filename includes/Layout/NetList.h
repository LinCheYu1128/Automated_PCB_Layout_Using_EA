#ifndef NETLIST_H
#define NETLIST_H

#include "NetList.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class NetList {
    private:
        map< string, vector<string> > list_info;
        string net_path;
        
    public:
        // constructer, destructor
        NetList();
        ~NetList();
        
        // getter
        map< string, vector<string> > getNetList();
        // setter
        void setNetList();
        void outputTwoPinNetList();
};

#endif