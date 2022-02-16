#include "Component.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

ComponentProperty::ComponentProperty() {
    this->name = "";
    this->color = "";
    this->length = 0;
    this->width = 0;
    this->height = 0;
    this->voltage = 0;
}

string ComponentProperty::getName() {
    return this->name;
}
void ComponentProperty::setName(string name) {
    this->name = name;
}

string ComponentProperty::getColor() {
    return this->color;
}
void ComponentProperty::setColor(string color) {
    this->color = color;
}

double ComponentProperty::getLength() {
    return this->length;
}
void ComponentProperty::setLength(double length) {
    this->length = length;
}

double ComponentProperty::getWidth() {
    return this->width;
}
void ComponentProperty::setWidth(double width) {
    this->width = width;
}

double ComponentProperty::getHeight() {
    return this->height;
}
void ComponentProperty::setHeight(double height) {
    this->height = height;
}

int ComponentProperty::getVoltage() {
    return this->voltage;
}
void ComponentProperty::setVoltage(int voltage) {
    this->voltage = voltage;
}

map<string, Point> ComponentProperty::getDefaultPinPosition() {
    return this->default_pin_position;
}

void ComponentProperty::setOneDefaultPinPosition(string key, Point one_pin_position) {
    this->default_pin_position[key].x = one_pin_position.x;
    this->default_pin_position[key].y = one_pin_position.y;
}

void ComponentProperty::setAllDefaultPinPosition(map<string, Point> all_pin_position) {
    auto iter = all_pin_position.begin();
    while (iter != all_pin_position.end()) {
        this->setOneDefaultPinPosition(iter->first, iter->second);
        ++iter;
    }
}

void ComponentProperty::setAllInfo(ComponentProperty* comp_prop) {
    this->setName(comp_prop->getName());
    this->setColor(comp_prop->getColor());
    this->setLength(comp_prop->getLength());
    this->setWidth(comp_prop->getWidth());
    this->setHeight(comp_prop->getHeight());
    this->setVoltage(comp_prop->getVoltage());
    this->setAllDefaultPinPosition(comp_prop->getDefaultPinPosition());
}

void ComponentProperty::printDefaultPinPosition() {
    auto iter = this->default_pin_position.begin();
    while (iter != this->default_pin_position.end()) {
        cout << "[ pin " << iter->first << " | x: " << iter->second.x << ", y: " << iter->second.y << "]" << endl;
        ++iter;
    }
}

ComponentState::ComponentState() {
    this->side = "";
    this->angle = 0;
    clearPoint(this->leftdown_position);
    clearPoint(this->center_position);
    this->length = 0;
    this->width = 0;
    this->margin = 0;
}

string ComponentState::getSide() {
    return this->side;
}

int ComponentState::getAngle() {
    return this->angle;
}

Point ComponentState::getPosition() {
    return this->leftdown_position;
    // if (location == "center") {
    //     return this->center_position;
    // } else {
    //     return this->leftdown_position;
    // }
}

double ComponentState::getLength() {
    return this->length;
}

double ComponentState::getWidth() {
    return this->width;
}

double ComponentState::getMargin() {
    return this->margin;
}

void ComponentState::setSide(string side) {
    this->side = side;
}

void ComponentState::setAngle(int angle) {
    this->angle = angle;
    // this->rotatePinPosition(angle);
}

void ComponentState::setPosition(double x, double y) {
    this->leftdown_position.x = x;
    this->leftdown_position.y = y;
    this->center_position.x = x + this->length/2;
    this->center_position.y = y + this->width/2;
}

void ComponentState::setLength(double length) {
    this->length = length;
}

void ComponentState::setWidth(double width) {
    this->width = width;
}

void ComponentState::setMargin(double margin) {
    this->margin = margin;
}

// void ComponentState::rotatePinPosition(int angle) {
//     map<string, Point> pin_position = this->pin_position;
//     map<string, Point>::iterator iter;
//     double PI = 3.1415926;
//     Point origin = this->getPosition();
//     origin.x += this->getLength()/2;
//     origin.y += this->getWidth()/2;
//     double pin_position_X, pin_position_Y,
//            pin_trans_position_X, pin_trans_position_Y,
//            pin_abs_position_X, pin_abs_position_Y;
//     int angle = this->getAngle();
//     for (iter = pin_position.begin(); iter != pin_position.end(); iter++) {
//         pin_position_X = get<0>(iter->second) - this->component_.length/2;
//         pin_position_Y = get<1>(iter->second) - this->component_.width/2;
//         if (this->coor_Z_ == 1) {
//             pin_position_X *= -1;
//         }
//         pin_trans_position_X = cos(angle*PI/2) * pin_position_X - sin(angle*PI/2) * pin_position_Y;
//         pin_trans_position_Y = sin(angle*PI/2) * pin_position_X + cos(angle*PI/2) * pin_position_Y;
//         pin_abs_position_X = origin_X + pin_trans_position_X;
//         pin_abs_position_Y = origin_Y + pin_trans_position_Y;
//         this->pin_position[iter->first] = make_tuple(pin_abs_position_X, pin_abs_position_Y);
//     }
// }

void clearPoint(Point point) {
    point.x = 0;
    point.y = 0;
}