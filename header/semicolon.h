#ifndef __SEMICOLON_H__
#define __SEMICOLON_H__

#include "connector.h"

class Semicolon : public Connector {
    public:
        string value = ";"; //semicolon value
        Semicolon() : Connector() {} //using the connector constructor
        Semicolon(Base * left, Base * right); //setting left and right children
        
        bool execute();
};

#endif
