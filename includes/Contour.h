#ifndef CONTOUR_H
#define CONTOUR_H
#include "BinaryTree.h"

class Contour {
    private:
        // first point of each line
        vector<Point> contour;

    public:
        // constructor
        Contour();

        // getter
        vector<Point> getContour();
        
        // setter
        
        // printer
        void printContour();

        void addBlock(ComponentState*);
};

#endif