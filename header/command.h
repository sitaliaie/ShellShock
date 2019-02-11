#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <vector>
#include <string>
#include <iostream>

#include "base.h"

class Command : public Base {
    public:
        vector<string> commands;
        Command() {}
        bool execute();
};

#endif
