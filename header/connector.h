#ifndef __CONNECTOR_H__
#define __CONNECTOR_H__

#include "base.h"

class Connector : public Base {
    protected:
        Base * left; //left is the left command
        Base * right; //right is the right command
    
    public:
        Connector() : Base() {}; //using the base constructor (each connector has a value)
        Connector(Base * left, Base * right); //setting the left and right children
        virtual bool execute() = 0; //should be virtual (connectors do this, not the class)
    
};

#endif
