#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <queue>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "../header/command.h"
#include "../header/exit.h"
#include "../header/testing.h"

using namespace std;
using namespace boost;

void parsingInput(vector<string> &cmds) {
    string input;
    
    input = userInput(); //get the input from the prompt
    split(cmds, input, is_any_of(" ")); //split using boost library
}

string userInput() {
    //extra credit
    //no clue what i am doing other than following the manual
    //structuring this like the other syscalls ive made
    
    char hostname[256];
    char *login;
    char buf[1024];
    
    if(gethostname(hostname, 256) == -1) {
	perror("hostname()");
    }

    login = getlogin();
	
    if(login == NULL) {
	perror("getlogin()");
    }
	
    string clientInput;
    
    cout << login << "@" << hostname << "$ "; //cout to prompt an input
    //string clientInput;
    //cout << "$ ";
    getline(cin, clientInput); //get the whole line
    return clientInput; //return the input to parsingInput to split
}

bool exitEntered(vector<string> cmds) {
    if(cmds.at(0) == "exit") {
        return true;
    } 
    return false;
}

bool isOperator(vector<string> cmds, int index) {
    int size;
    
    size = cmds.size();
    
    /*basically if there is no operator detected, 
    then its not an operator*/
    if(index <= -1 || index >= size) {
        return false;
    }
    // if any of the connectors are detected, then its an operator
    //initially had the line below chopped in half but exit wasnt working properly
    if(cmds.at(index) == "||" || cmds.at(index) == "&&" || cmds.at(index) == ";" || cmds.at(index).back() == ';') {
        return true;        
    }
    return false;
}

vector<string> findOperators(vector<string> cmds) {
    vector<string> operators;
    
    //want to make a separate vector of strings with just the operators
    for(unsigned int i = 0; i < cmds.size(); i++) {
        //checking to see if the string at the given index is an operator
        if(isOperator(cmds, i)) {
            //if it is an operator then push_back into a vector
            operators.push_back(cmds.at(i));
        }
    }
    
    return operators;
}

void semicolon(vector<string> cmds, unsigned index) {
    //check to see if a string ends with a semicolon
    if(cmds.at(index).back() == ';') {
        /*if it does then set the word at that index
        to the word at that index sans the semicolon*/
        cmds.at(index) = cmds.at(index).substr(0, cmds.at(index).size() - 1);
    }
    
    //make a vector of strings for the left and right commands to be held
    vector<string> leftcmd;
    vector<string> rightcmd;
    
    //if only one command is entered
    if(index == 0) {
        leftcmd.push_back(cmds.at(0));
    }
    /*if more than one cmd is entered then push back just the first 
    command until the index is reached
    ex) if its blah blah; yadda yadda then itll just push back blah blah*/
    else {
        for(unsigned int i = 0; i < index; i++) {
            leftcmd.push_back(cmds.at(i));
        }
    }
    
    //same concept but it starts from index + 1 to get the second command
    for(unsigned int i = index + 1; i < cmds.size(); i++) {
        rightcmd.push_back(cmds.at(i));
    }
    
    //next, execute each side
    executeCmd(leftcmd);
    executeCmd(rightcmd);
}

bool executeCmd(vector<string> cmds) {
    vector<string> ops = findOperators(cmds);
    
    // --------------------- Assignment 3 --------------------- 
    // create a stack so we can keep count of how many parentheses are in the commands
    // use stack instead of queue so they can iterate in correct order
    stack<string> depthStack;
    // keep track of '('
    int beginCnt = 0;
    // keep track of ')'
    int endCnt = 0;

    for (unsigned int i = 0; i < cmds.size(); i++) {
        if (cmds.at(i).front() == '(') {
            beginCnt++;
        }
        if (cmds.at(i).back() == ')') {
            endCnt++;
        }
    }
    
    // will not run if the amount of '(' does not equal to ')'
    if (beginCnt != endCnt) {
        cout << "Error: Parentheses don't match." << endl;
        return false;
    }

    // ---------------------------------------------------------
    
    for(unsigned int index = 0; index < cmds.size(); index++) {
        if(!ops.empty()) {
            int opIndex;
            
            for(unsigned int i = 0; i < ops.size(); i++) {
                if(ops.at(i) == "||") {
                    opIndex = i;
                }
            }
            
            for(unsigned int i = 0; i < ops.size(); i++) {
                if(ops.at(i) == "&&") {
                    opIndex = i;
                }
            }
            
            for(unsigned int i = 0; i < cmds.size(); i++) {
                if(cmds.at(i) == ops.at(opIndex)) {
                    index = i;
                }
            }
        }

        // ------------------------------ Assignment 3 --------------------------
        
        // to check if there is parentheses in the beginning of each commands 
        if (cmds.at(index).front() == '(') {
            cmds.at(index) = cmds.at(index).substr(1);
            depthStack.push(cmds.at(index));
            for (unsigned j = 0; j < cmds.size(); j++) {
                if (cmds.at(j).back() == ')') {
                    cmds.at(j) = cmds.at(j).substr(0, cmds.at(j).size() - 1);
                    break;
                }
            }
        }

        // --------------------------------------------------------------------
        
        //semicolon
        if(cmds.at(index) == ";" || cmds.at(index).back() == ';') {
            /*goes into semicolon fcn to remove the semicolon and 
            then makes another call to execute*/
            semicolon(cmds, index);
            return true;
        }
        //and
        else if(cmds.at(index) == "&&") {
            vector<string> leftcmd;
            vector<string> rightcmd;
            
            //need to execute from left to right
            stack<string> leftStack;
            
            //need to flip the orientation of the commands
            for(int j = index - 1; j >= 0; j--) {
                //first put them into a stack
                leftStack.push(cmds.at(j));
            }
            while(!leftStack.empty()) {
                //then put into a vector
                leftcmd.push_back(leftStack.top());
                leftStack.pop();
            }
            for(unsigned int j = index + 1; j < cmds.size(); j++) {
                //put the right most element into the rightcmd vector
                rightcmd.push_back(cmds.at(j));
            }
            if(executeCmd(leftcmd) && executeCmd(rightcmd)) {
                //call execute again
                return true;
            }
        }
        //or
        else if(cmds.at(index) == "||") {
            //doing basically the same as above but with ||
            vector<string> leftcmd;
            stack<string> leftStack;
            
            for(int j = index - 1; j >= 0; j--) {
                leftStack.push(cmds.at(j));
            }
            while(!leftStack.empty()) {
                leftcmd.push_back(leftStack.top());
                leftStack.pop();
            }
            if(executeCmd(leftcmd)) {
                return true;
            }
            else {
                vector<string> rightcmd;
        
                for(unsigned int j = index + 1; j < cmds.size(); j++) {
                    cout << cmds.at(j) << endl;
                    rightcmd.push_back(cmds.at(j));
                }
                if(executeCmd(rightcmd)) {
                    return true;
                }
            }
            return false;
        }
        // -------------------------------------
        // this function check for key word "test" or ( "[" and "]" )
        else if ((cmds.at(index) == "test" || ((cmds.at(index) == "[") && (cmds.at(index + 3) == "]")))) {
            // this if statement check for flag "-e" (if the file exist or not)
            if (cmds.at(index + 1) == "-e") {
                if (fileExists(cmds.at(index + 2))) {
                    cout << "(True)" << endl;
                    return true;
                }
                else {
                    cout << "(False)" << endl;
                    return false;
                }
            }
            // this if statement check for flag "-d" (if it is a Diectory or not)
            else if (cmds.at(index + 1) == "-d") {
                if (isDirectory(cmds.at(index + 2))) {
                    cout << "(True)" << endl;
                    return true;
                }
                else {
                    cout << "(False)" << endl;
                    return false;
                }
            }
            // this if statement check for flag "-f" (if it is a File or not)
            else if (cmds.at(index + 1) == "-f") {
                if (isFile(cmds.at(index + 2))) {
                    cout << "(True)" << endl;
                    return true;
                }
                else {
                    cout << "(False)" << endl;
                    return false;
                }
            }
            // if the user did not input any flag, it will check if the input file exist or not by default
            else {
                if (fileExists(cmds.at(index + 1))) {
                    cout << "(True)" << endl;
                    return true;
                }
                else {
                    cout << "(False)" << endl;
                    return false;
                }
            }
        }
        // ------------------------------ Assignment 4 --------------------------
        //here is >
        else if(cmds.at(index) == ">") {
            vector<string> leftcmd;
            string rightcmd;
            //right cmd is basically the element after the ">"
            rightcmd = cmds.at(index + 1);
            //this will populate the vector with the cmd before the ">"
            for(unsigned int j = 0; j != index; j++) {
                leftcmd.push_back(cmds.at(j));
            }
            
            /* follow youtube video for dup
            saving the stdout file descriptor which is used for cout
            |0 stdin|
            |1 stdout|
            |2 stderr|
            ^a great drawing, i know :) */
            
            int save_stdout;
            save_stdout = dup(1);
            
            //to get the file descriptor, use open()
            int fd;
            /* open the file as determined by rightcmd
            if no file exists, create it and make it write only
            "if the file exists and is a regular file, and the file 
            is successfully opened ... or O_WRONLY, its length is 
            truncated to 0" something something following a video
            also the guy in the video used some bit thing at the 
            end for the mode but apparently thats bad practice lol 
            s_irwxu is "read, write, execute/search by owner" 
            using truncate bc > overwrites */
            fd = open((char*)rightcmd.c_str(), O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
            
            if(fd < 0) {
                //if open() fails it returns a -1
                perror("fd");
                return false;
            }
            
            //dup2(int oldfd, int newfd)
            if(dup2(fd, 1) < 0) {
                //same thing here, if dup2() fails a -1 is returned
                perror("dup2");
                return false;
            }
            
            executeCmd(leftcmd);
            
            if(dup2(save_stdout, 1) < 0) {
                perror("dup2");
                return false;
            }
            
            //close the file descriptor
            close(save_stdout);
            return true;
        }
        //here is >>
        else if(cmds.at(index) == ">>") {
            vector<string> leftcmd;
            string rightcmd;
            //right cmd is basically the element after the ">>"
            rightcmd = cmds.at(index + 1);
            //this will populate the vector with the cmd before the ">>"
            for(unsigned int j = 0; j != index; j++) {
                leftcmd.push_back(cmds.at(j));
            }
            
            int save_stdout;
            save_stdout = dup(1);
            
            int fd;
            //open file in append mode, not trunc, bc >> appends to the end of the file
            fd = open((char*)rightcmd.c_str(), O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);
            if(fd < 0) {
                //if open() fails it returns a -1
                perror("fd");
                return false;
            }
            //dup2(int oldfd, int newfd)
            if(dup2(fd, 1) < 0) {
                //same thing here, if dup2() fails a -1 is returned
                perror("dup2");
                return false;
            }
            
            executeCmd(leftcmd);
            
            if(dup2(save_stdout, 1) < 0) {
                perror("dup2");
                return false;
            }
            
            //close the file descriptor
            close(save_stdout);
            return true;
        }
        //here is <
        else if(cmds.at(index) == "<") {
            //this one accepts input from a file
            ifstream aFile(cmds.at(index + 1).c_str());
            string input;
            
            if(aFile.is_open()){
                while(getline(aFile, input)) {
                    vector<string> copy;
                    copy.push_back(cmds.at(0));
                    copy.push_back(input);
                    executeCmd(copy);
                }
                return true;
            }
            return false;
        }
	//here is |
	else if(cmds.at(index) == "|") {
            vector<string> leftcmd;
            vector<string> rightcmd;
            vector<string> deleteFile;
            
            //will delete dummy file after executing
            deleteFile.push_back("rm");
            deleteFile.push_back("-rf");
            deleteFile.push_back("file.txt");
            
            //populate one vector with the command before the pipe
            for(unsigned int i = 0; i < index; i++) {
                leftcmd.push_back(cmds.at(i));
            }
            
            //redirect here
            leftcmd.push_back(">");
            leftcmd.push_back("file.txt");
            executeCmd(leftcmd);
            
            //populate the other with the cmd after the pipe
            for(unsigned int i = index + 1; i < cmds.size(); i++) {
                rightcmd.push_back(cmds.at(i));
            }
            
            rightcmd.push_back("file.txt");
            executeCmd(rightcmd);
            executeCmd(deleteFile);
            
            return true;
	}
    }
    
    /*follow video about fork and exec
    initially put 100 as the value but things werent working out with that
    so 500 for overkill :)*/
    char* args[500];
    /*exec takes in a char* and an arg
    we need to put the command into a cstring to put it into
    a char* array*/
    for(unsigned i = 0; i < cmds.size(); i++) {
        args[i] = (char*)cmds.at(i).c_str();
    }
    
    /*need to set the last element to null or else gross 
    errors will happen*/
    args[cmds.size()] = 0;
    
    //honestly just following the manual at this point lol
    pid_t pid = fork();
    
    if(pid == 0) {
        //check if the process failed
        if(execvp(args[0], args) == -1) {
            perror("exec");
            return false;
        }
    }
    if(pid > 0) {
        if(wait(0) == -1) {
           perror("wait"); 
        }
    }
    
    return true;
}

// ------------------- Assignment 3 ----------------------

bool fileExists(string& fileName) {
    struct stat buf;

    return(stat(fileName.c_str(), &buf) == 0);
}

bool isDirectory (string& fileName) {
    struct stat path;

    if (stat(fileName.c_str(), &path) == 0) {
        if (path.st_mode & S_IFDIR) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

bool isFile (string& fileName) {
    struct stat filePath;

    if (stat(fileName.c_str(), &filePath) == 0) {
        if (filePath.st_mode & S_IFREG) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}
