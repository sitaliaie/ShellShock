#ifndef __EXIT_H__
#define __EXIT_H__

//has exit(to terminate the calling process)
#include <stdlib.h> 
#include <string>
#include <iostream>

#include "command.h"

class Exit : public Command {
    public:
        Exit() {}
        bool execute();
};

#endif
