#ifndef __OR_H__
#define __OR_H__

#include "connector.h"

class Or : public Connector {
    public:
        string value = "||"; //string val for or
        Or() : Connector() {} //using the connector constructor
        Or(Base * left, Base * right); //setting the left and right children
        
        bool execute();
};

#endif
