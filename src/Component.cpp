#include "../includes/Component.h"

ComponentProperty::ComponentProperty() {
    name = "";
    color = "";
    length = 0;
    width = 0;
    height = 0;
    voltage = 0;
}

string ComponentProperty::getName() {
    return name;
}
void ComponentProperty::setName(string name) {
    this->name = name;
}

string ComponentProperty::getColor() {
    return color;
}
void ComponentProperty::setColor(string color) {
    this->color = color;
}

double ComponentProperty::getLength() {
    return length;
}
void ComponentProperty::setLength(double length) {
    this->length = length;
}

double ComponentProperty::getWidth() {
    return width;
}
void ComponentProperty::setWidth(double width) {
    this->width = width;
}

double ComponentProperty::getHeight() {
    return height;
}
void ComponentProperty::setHeight(double height) {
    this->height = height;
}

int ComponentProperty::getVoltage() {
    return voltage;
}
void ComponentProperty::setVoltage(int voltage) {
    this->voltage = voltage;
}

map<string, Point> ComponentProperty::getPinPosition() {
    return pin_position;
}

void ComponentProperty::setPinPosition(string key, Point pin_position) {
    this->pin_position[key].x = pin_position.x;
    this->pin_position[key].y = pin_position.y;
}

void ComponentProperty::setAllPinPosition(map<string, Point> pin_position) {
    auto iter = pin_position.begin();
    while (iter != pin_position.end()) {
        setPinPosition(iter->first, iter->second);
        ++iter;
    }
}

void ComponentProperty::setAllInfo(ComponentProperty* comp_prop) {
    setName(comp_prop->getName());
    setColor(comp_prop->getColor());
    setLength(comp_prop->getLength());
    setWidth(comp_prop->getWidth());
    setHeight(comp_prop->getHeight());
    setVoltage(comp_prop->getVoltage());
    setAllPinPosition(comp_prop->getPinPosition());
}

void ComponentProperty::printPinPosition() {
    auto iter = pin_position.begin();
    while (iter != pin_position.end()) {
        cout << "[ pin " << iter->first << " | x: " << iter->second.x << ", y: " << iter->second.y << "]" << endl;
        ++iter;
    }
}

ComponentState::ComponentState() {
    side = "";
    angle = 0;
    coor_X = 0;
    coor_Y = 0;
    margin = 0;
}

string ComponentState::getSide() {
    return side;
}

int ComponentState::getAngle() {
    return angle;
}

double ComponentState::getCoordX() {
    return coor_X;
}

double ComponentState::getCoordY() {
    return coor_Y;
}

double ComponentState::getMargin() {
    return margin;
}