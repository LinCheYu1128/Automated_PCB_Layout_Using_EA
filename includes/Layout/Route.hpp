# ifndef ROUTE_H
# define ROUTE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

class Route{
private:
    int SRowIdx, SColIdx, SLayIdx;
    int ERowIdx, EColIdx, ELayIdx;
public:
    Route(int,int,int,int,int,int);
    int getSRowIdx() { return SRowIdx; }
    int getSColIdx() { return SColIdx; }
    int getSLayIdx() { return SLayIdx; }
    int getERowIdx() { return ERowIdx; }
    int getEColIdx() { return EColIdx; }
    int getELayIdx() { return ELayIdx; }
};

class Grid{
private:
    unsigned int Coordinate;
    int Capacity;
    int Demand;
public:
    ~Grid();
    Grid(unsigned int Coordinate, int Capacity);
    unsigned int getCoordinate() { return Coordinate; }
    int getSupply() { return Capacity - Demand; }
    int getDemand() { return Demand; }
    int getCapacity() { return Capacity; }
    
    bool isOverflow() { return getSupply() < 0; }
    void addDemand(int Val) { Demand += Val; }
    void addCapacity(int Val) { Capacity += Val; }
};

struct Coordinate{
    float x, y;
};


class Pin{
    private:
        string PinName;
        Coordinate position;
    public:
        Pin(string, float, float);
        string getPinName(){return PinName;}
        Coordinate getCoordinate(){return position;}
};

class Cell{
private:
    string CellName;
    vector<Pin> Pins;
    Coordinate position;
    Coordinate area;
public:
    Cell(string, vector<Pin>, float, float, float, float);
    string getCellName(){return CellName;}
    vector<Pin> getPins(){return Pins;}
    Coordinate getCoordinate(){return position;}
    
};

class CellList{
private:
    vector<Cell*> Cells;
public:
    CellList();
    ~CellList();
    vector<Cell*> getCellList(){return Cells;}
};



// class Net{
// private:
//     /* data */
// public:
//     Net(/* args */);
//     ~Net();
// };




# endif
