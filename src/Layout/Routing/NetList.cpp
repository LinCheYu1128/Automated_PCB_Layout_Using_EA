#include "NetList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

NetList::NetList(){
    this->net_path = "./../resources/FSL020-000GP5A_edited.net";
    this->setNetList();
    
}

NetList::~NetList(){

}

map< string, vector<string> > NetList::getNetList(){
    return this->list_info;
}

void NetList::outputTwoPinNetList(){
    ofstream OutFile("./../resources/net.csv");
    for(auto net: this->list_info){
        if(net.second.size()!=2) continue;
        else{
            OutFile << net.first<<",";
            for(auto pin: net.second){
                OutFile << pin << ",";
            }
            OutFile << endl;
        }
    }
}
void NetList::setNetList(){
    ifstream inFile(this->net_path);
    string temp;
    string net_name;
    vector<string> tempNet;
    
    while (!inFile.eof())
    {
        getline(inFile, temp);

        if (temp[0] == '(') {
            
            getline(inFile, temp);
            net_name = temp;
            getline(inFile, temp);

            while (temp[0] != ')') {

                tempNet.push_back(temp);

                getline(inFile, temp);
            }

            list_info[net_name] = tempNet;
            tempNet.clear();

        }
    }

}