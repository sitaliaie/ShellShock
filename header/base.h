#ifndef __BASE_H__
#define __BASE_H__

#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

class Base {
    public: 
        string value; //value is the connector, this is set in and, or and semicolon
        virtual bool execute() = 0; //virtual since and, or and semicolon execute
};

#endif
