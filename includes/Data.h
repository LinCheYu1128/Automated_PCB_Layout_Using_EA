#ifndef DATA_H
#define DATA_H

#include "Component.h"

class Data {
    private:
        ComponentProperty* comp_prop;
        ComponentState* comp_state;

    public:
        // constructor, destructor
        Data(ComponentProperty* comp_prop);
        ~Data();
        
        // getter
        
        // setter

        // printer
        void printData();
};

#endif