#ifndef GRID_H
#define GRID_H

#include "Grid.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Grid{
private:
    const unsigned long long Coordinate;
    int Capacity;
    int Demand;
    unsigned Tag;
public:
    Grid(/* args */);
    ~Grid();
};


#endif