#include "../includes/Data.h"

Data::Data(ComponentProperty* comp_prop) {
    this->comp_prop = new ComponentProperty();
    this->comp_state = new ComponentState();
    this->comp_prop->setAllPinPosition(comp_prop->getPinPosition());
}

void Data::printData() {
    cout << "Component name: " << comp_prop->getName() << endl;
    cout << "Component color: " << comp_prop->getColor() << endl;
    cout << "Component length: " << comp_prop->getLength() << endl;
    cout << "Component width: " << comp_prop->getWidth() << endl;
    cout << "Component height: " << comp_prop->getHeight() << endl;
    cout << "Component voltage: " << comp_prop->getVoltage() << endl;
    cout << "Component pin position: " << endl;
    comp_prop->printPinPosition();
    cout << "Component branch: " << comp_state->getBranch() << endl;
    cout << "Component side: " << comp_state->getSide() << endl;
    cout << "Component angle: " << comp_state->getAngle() << endl;
    cout << "Component coor_X: " << comp_state->getCoordX() << endl;
    cout << "Component coor_Y: " << comp_state->getCoordY() << endl;
    cout << "Component margin: " << comp_state->getMargin() << endl;
}