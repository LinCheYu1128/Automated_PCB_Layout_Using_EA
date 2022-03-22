#ifndef COMPONENT_H
#define COMPONENT_H

#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
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
        Point preplace_location;

    public:
        // constructor, destructor
        ComponentProperty(string name="", string color="", double length=0, double width=0, double height=0, int voltage=0);
        ~ComponentProperty() {};

        ComponentProperty* copy();

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
        void setPreplaceLocation(double x, double y);
        
        // printer
        void printDefaultPinPosition();
};


class ComponentState {
    private:
        string side;
        double angle;
        Point leftdown_position;
        Point center_position;
        double length;
        double width;
        double margin;
        int voltage;
        map<string, Point> pin_position;


    public:
        // constructor, destructor
        ComponentState(int voltage);
        ~ComponentState() {};

        ComponentState* copy();

        // getter
        string getSide();
        double getAngle();
        Point getPosition();
        double getLength();
        double getWidth();
        double getMargin();
        map<string, Point> getPinPosition();
        
        // setter
        void setSide(string side);
        void setAngle(double angle);
        void setPosition(double x, double y);
        void setLength(double length);
        void setWidth(double width);
        void setMargin(double margin);
        void setPinPosition(map<string, Point> input_position);
        void setOnePin(string key, Point value);
        void setAllInfo(ComponentState* comp_state);

        // printer
        void printPinPosition();

};

void clearPoint(Point& point);

#endif