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
        ~Contour();
        Contour* copy();

        // getter
        vector<Point> getContourVector();
        int getSize();
        
        // setter
        
        // printer
        void printContour();

        void addBlock(ComponentState*);
};

#endif