#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <map>
using namespace std;

typedef struct Point {
    double x;
    double y;
}Point;

class ComponentProperty {
    private:
        string name;
        string color;
        double length;
        double width;
        double height;
        int voltage;
        map<string, Point> default_pin_position;

    public:
        // constructor, destructor
        ComponentProperty();
        ~ComponentProperty() {};

        // getter
        string getName();
        string getColor();
        double getLength();
        double getWidth();
        double getHeight();
        int getVoltage();
        map<string, Point> getDefaultPinPosition();

        // setter
        void setName(string name);
        void setColor(string color);
        void setLength(double length);
        void setWidth(double width);
        void setHeight(double height);
        void setVoltage(int voltage);
        void setOneDefaultPinPosition(string key, Point one_pin_position);
        void setAllDefaultPinPosition(map<string, Point> all_pin_position);
        void setAllInfo(ComponentProperty* comp_prop);
        
        // printer
        void printDefaultPinPosition();
};


class ComponentState {
    private:
        string side;
        int angle;
        Point leftdown_position;
        Point center_position;
        double length;
        double width;
        double margin;
        map<string, Point> pin_position;

    public:
        // constructor, destructor
        ComponentState();
        ~ComponentState() {};

        // getter
        string getSide();
        int getAngle();
        Point getPosition();
        double getLength();
        double getWidth();
        double getMargin();
        map<string, Point> getPinPosition();
        
        // setter
        void setSide(string side);
        void setAngle(int angle);
        void setPosition(double x, double y);
        void setLength(double length);
        void setWidth(double width);
        void setMargin(double margin);
        // void rotatePinPosition(int angle);

        // printer

};

void clearPoint(Point point);

#endif