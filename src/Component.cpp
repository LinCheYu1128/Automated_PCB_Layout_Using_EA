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
    this->position.x = 0;
    this->position.y = 0;
    this->margin = 0;
}

string ComponentState::getSide() {
    return this->side;
}

int ComponentState::getAngle() {
    return this->angle;
}

Point ComponentState::getPosition() {
    return this->position;
}

double ComponentState::getMargin() {
    return this->margin;
}