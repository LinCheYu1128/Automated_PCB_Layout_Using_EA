# ifndef ROUTE_H
# define ROUTE_H

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
    const unsigned long long Coordinate;
    int Capacity;
    int Demand;
    // unsigned Tag;
public:
    ~Grid();
    Grid(unsigned long long Coordinate, int Capacity);
    unsigned long long getCoordinate() const { return Coordinate; }
    int getSupply() const { return Capacity - Demand; }
    int getDemand() const { return Demand; }
    int getCapacity() const { return Capacity; }
    
    bool isOverflow() const { return getSupply() < 0; }
    void addDemand(int Val) { Demand += Val; }
    void addCapacity(int Val) { Capacity += Val; }
};

# endif
