#ifndef __AND_H__
#define __AND_H__

#include "connector.h"

class And : public Connector {
    public:
        string value = "&&"; //&& is the command
        And() : Connector() {} //using the connector constructor
        And(Base * left, Base * right); //left and right child get set here
        
        bool execute();
};

#endif
