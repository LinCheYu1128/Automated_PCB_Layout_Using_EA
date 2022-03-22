#ifndef NETLIST_H
#define NETLIST_H

#include "NetList.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

// class Net{
//     private:
//     /* data */
//     public:
//         Net(/* args */);
//         ~Net();
// };

class NetList {
    private:
        map< string, vector<string> > list_info;
        string net_path;
        // vector <Net*> netlist;
    public:
        // constructer, destructor
        NetList();
        ~NetList();
        
        // getter
        map< string, vector<string> > getNetList();
        // vector< Net*>
        // setter
        void setNetList();
        void outputTwoPinNetList();

};



#endif