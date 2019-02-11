#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "../header/command.h"
#include "../header/exit.h"
#include "../header/testing.h"

using namespace std;
using namespace boost;

int main() {
    while(1) {
        Command * current = new Command(); //allocate memory for user cmds
        parsingInput(current->commands); //split commands into separate strings
        
        //check if user entered an exit cmd
        if(exitEntered(current->commands)) {
            Exit * userExit = new Exit(); //if they did make an exit obj
            userExit->execute(); //this will end the program
        }
        
        //check to see if input has any comments using #
        unsigned int i;
        unsigned int j;
        unsigned int index;
        /*goes through the vector and checks each string for a #
        checks if the # is connected to the string (like #hello) using front()
        checks for a standalone comment (like "# blah blah")*/
        for(i = 0; i < current->commands.size(); i++) {
            if(current->commands.at(i) == "#" || 
              current->commands.at(i).front() == '#') {
                index = i; //finds the index in the vector
                if(current->commands.at(index).front() == '#') {
                    //here we remove the # (like #hello to just hello)
                    current->commands.at(index) = 
                    current->commands.at(index).substr(1);
                }
                /*starting at the end until the index of the # is reached.
                basically this sets the # and everything after it to null
                because we dont care about comments (dont execute them)*/
                for(j = current->commands.size() - 1; j >= index; j--) {
                    current->commands.pop_back();
                }
                //get out of the loop after the comment is removed
                break;
            }
        }
    
        //rshell functionality begins here
        executeCmd(current->commands);    
    }
    return 0;
}
