#include "Contour.h"
#include "console.h"
#include <iostream>
using namespace std;

Contour::Contour() {
    Point p = {0,0};
    this->contour.push_back(p);
    // cout << "build contour successfully!" << endl;
}

Contour::~Contour() {}

Contour* Contour::copy() {
    Contour* new_contour = new Contour();
    for (unsigned int i = 0; i < this->contour.size(); i++){
        new_contour->contour.push_back(this->contour.at(i));
    }
    return new_contour;
}

vector<Point> Contour::getContourVector(){
    return this->contour;
}

int Contour::getSize(){
    return this->contour.size();
}

void Contour::printContour(){
    for (unsigned int i = 0; i < this->contour.size(); i++){
        cout << "(" << this->contour.at(i).x << ", " << this->contour.at(i).y << ")" << endl;
    }
    return;
}

void Contour::addBlock(ComponentState* Block){
    Point p = Block->getPosition();
    Point front = {p.x, p.y + Block->getWidth("outer")};
    int bp = 0; // begin point
    for (unsigned int i = 0; i < this->contour.size(); i++){
        if (this->contour.at(i).x >= p.x ){
            if (this->contour.at(i).x > p.x + Block->getLength("outer")) {
                // in single contour
                Point back = {p.x + Block->getLength("outer"), contour.at(i-1).y};
                this->contour.insert(this->contour.begin() + i, {front, back});
                return;
            }
            else {bp = i; break;}
        }
    }
    for (unsigned int j = bp; j < this->contour.size(); j++){
        if (this->contour.at(j).x > p.x + Block->getLength("outer")) {
            // across different contour
            Point back = {p.x + Block->getLength("outer"), contour.at(j-1).y};
            this->contour.erase(this->contour.begin() + bp, this->contour.begin() + j);
            this->contour.insert(this->contour.begin() + bp, {front, back});
            return;
        }
    }
    // exceed current contour
    Point back = {p.x + Block->getLength("outer"), 0};
    this->contour.erase(this->contour.begin() + bp, this->contour.end());
    this->contour.insert(this->contour.end(), {front, back});
}