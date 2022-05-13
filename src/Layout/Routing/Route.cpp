#include "Route.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

Grid:: Grid(unsigned int Coordinate, int Capacity){
    this->Coordinate = Coordinate;
    this->Capacity = Capacity;
}
Pin:: Pin(string name, float x, float y){
    this->position.x = x;
    this->position.y = y;
    this->PinName = name;
}

Cell:: Cell(string name,vector<Pin> pins, float x, float y, float width, float high){
    this->position.x = x;
    this->position.y = y;
    this->CellName = name;
    this->Pins = pins;
    this->area.x = width;
    this->area.y = high;
}

CellList:: CellList(){
    ifstream inFile("./../resources/cell.cell");
    string cell_name;
    int cell_number;
    float X,Y;
    float high,width;
    float cx,cy;
    int pin_number;
    string pin_name;
    inFile>>cell_number;
    cout << cell_number << endl;
    
    for(int i=0; i < cell_number; i++){
        inFile>>cell_name >> X >> Y >> width >> high;
        cout << cell_name <<endl;
        inFile>>pin_number;
        vector<Pin> Pins;
        for(int j=0; j<pin_number; j++){
            inFile >> pin_name;
            inFile >> cx >> cy;
            Pins.emplace_back(pin_name,cx,cy);
        }
        Cells.emplace_back(new Cell(cell_name, Pins, width, high, X, Y));
    }
}
// Cell:: Cell()