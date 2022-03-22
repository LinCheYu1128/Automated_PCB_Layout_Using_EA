#include "Component.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <math.h>
using namespace std;

ComponentProperty::ComponentProperty(string name, string color, double length, double width, double height, int voltage) {
    this->name = name;
    this->color = color;
    this->length = length;
    this->width = width;
    this->height = height;
    this->voltage = voltage;
    this->preplace_location = {0, 0};
}

ComponentProperty* ComponentProperty::copy() {
    ComponentProperty* new_comp_prop = new ComponentProperty();
    new_comp_prop->setAllInfo(this);
    return new_comp_prop;
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

void ComponentProperty::setPreplaceLocation(double x, double y) {
    this->preplace_location.x = x;
    this->preplace_location.y = y;
}

map<string, Point> ComponentProperty::getDefaultPinPosition() {
    return this->default_pin_position;
}

void ComponentProperty::setOneDefaultPinPosition(string key, Point one_pin_position) {
    this->default_pin_position[key].x = one_pin_position.x;
    this->default_pin_position[key].y = one_pin_position.y;
}

void ComponentProperty::setAllDefaultPinPosition(map<string, Point> all_pin_position) {
    this->default_pin_position.clear();
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

ComponentState::ComponentState(int voltage) {
    this->side = "";
    this->angle = 0;
    clearPoint(this->leftdown_position);
    // cout << "this->leftdown_position: " << this->leftdown_position.x << endl;
    clearPoint(this->center_position);
    this->length = 0;
    this->width = 0;
    this->margin = 0.2;
    this->voltage = voltage;
    if (voltage == 1) this->margin = this->margin + 1.3;
    else if (voltage == -1) this->margin = this->margin + 0.125;
}

ComponentState* ComponentState::copy() {
    ComponentState* new_comp_state = new ComponentState(this->voltage);
    new_comp_state->setAllInfo(this);
    return new_comp_state;
}

string ComponentState::getSide() {
    return this->side;
}

double ComponentState::getAngle() {
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
    return this->length + 2*this->margin;
}

double ComponentState::getWidth() {
    return this->width + 2*this->margin;
}

double ComponentState::getMargin() {
    return this->margin;
}

map<string, Point> ComponentState::getPinPosition(){
    return this->pin_position;
}

void ComponentState::setSide(string side) {
    this->side = side;
}

void ComponentState::setAngle(double angle) {
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

void ComponentState::setPinPosition(map<string, Point> input_position) {
    this->pin_position = input_position;
}

void ComponentState::setOnePin(string key, Point value) {
    this->pin_position[key].x = value.x;
    this->pin_position[key].y = value.y;
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

void ComponentState::setAllInfo(ComponentState* comp_state) {      
    this->setSide(comp_state->getSide());
    this->setAngle(comp_state->getAngle());
    this->setPosition(comp_state->getPosition().x, comp_state->getPosition().y);
    this->setLength(comp_state->getLength());
    this->setWidth(comp_state->getWidth());
    this->setMargin(comp_state->getMargin());
}

void ComponentState::printPinPosition() {
    auto iter = this->pin_position.begin();
    while (iter != this->pin_position.end()) {
        cout << "[ pin " << iter->first << " | x: " << iter->second.x << ", y: " << iter->second.y << "]" << endl;
        ++iter;
    }
}

void clearPoint(Point& point) {
    point.x = 0;
    point.y = 0;
}