#include "Layout.h"
#include <iostream>
using namespace std;

void debug() {
    Contour* contour = new Contour();
    ComponentState* comp1 = new ComponentState();
    comp1->setLength(2);
    comp1->setWidth(2);
    comp1->setPosition(0,0);
    contour->addBlock(comp1);

    ComponentState* comp2 = new ComponentState();
    comp2->setLength(1);
    comp2->setWidth(3);
    comp2->setPosition(2,0);
    contour->addBlock(comp2);

    ComponentState* comp3 = new ComponentState();
    comp3->setLength(3);
    comp3->setWidth(4);
    comp3->setPosition(3,0);
    contour->addBlock(comp3);

    ComponentState* comp4 = new ComponentState();
    comp4->setLength(1);
    comp4->setWidth(1);
    comp4->setPosition(4,5);
    contour->addBlock(comp4);

    ComponentState* comp5 = new ComponentState();
    comp5->setLength(2.5);
    comp5->setWidth(1.5);
    comp5->setPosition(0,3);
    contour->addBlock(comp5);

    contour->printContour();
}