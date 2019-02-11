#include "../header/exit.h"

bool Exit::execute() {
    cout << "Exiting Rshell." << endl; //message informs user
    exit(0); //successful program termination
    return true; 
    //if the process terminates should return a true
}
