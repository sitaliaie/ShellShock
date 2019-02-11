# Rshell
#### Written By

* Hau Chen \([github]\)(https://github.com/HauChen)
* Stephanie Italiaie \([github]\)(https://github.com/sitaliaie)

## Introduction

ShellShock is a command line interface written in C++. It will execute bash-like commands with support for connectors ("||", "&&", ";") and comments ("#"). This shell also supports path testing and precedence of operations.  

## Usage
Clone the repository to your computer.

Navigate to the cloned directory's src folder.

`cd src`

Compile and run using

`make`

`./a.out`

## Design
We will be using a composite design strategy where “cmd” and “connector” act as composite classes. "exit", "||", "&&", and ";" are the leaves in this project that inherit from the composites. User interface and expression parsing is done in the main file with the Boost C++ library.

# Known Bugs
### From Phase 1
* putting in `ls -a; echo hello; mkdir test` will do the ls -a and mkdir test but will output a newline instead of echoing hello
* with `ls -a; echo hello && mkdir test || echo world; git status`, won't output a fatal error for git status but will also not do git status, will make directory, will do `ls -a`, will echo hello 
* typing in `ls -a, echo hello world; mkdir test` will do the same thing as in point 2, but will output hello and not world
* typing in just a comment like `#echo hello` will return a segmentation fault, but putting in `ls #echo hello` will work as intended
* putting in something like `ls; exit` will return an infinite loop 
* putting in two commands like `echo hello; ls -a` will throw an out of range error
### From Phase 2
* precedence operator not fully supported; 
* `test -e test/file/path` and any sort of version of this line (a different flag) will always return false
   - Not sure if this is the intended function
* `[-e test/file/path]` in any form (a different flag) will return `exec: No such file or directory`, but will output false if there are spaces after and before the brackets like so: `[ -e test/file/path ]`
   - Again, not sure if this is intended
* `(echo A && echo B) || (echo C && echo D)` will return an infinite loop where the console will cout `Error: Parentheses don't match.`
   - We have no clue why this happens, but we are working on a fix; same thing occurs with `(echo hello && echo bye)` 
   - The error occurs with the format `(command && command)`
### From Phase 3
 * When using control-D short cut in our rhsell, it will output an infinite loop of printing our shell username, and has to force quit using control-C
 * Not really an error, but more of a muisance. Say you use `make` to compile the program in the src folder. This generates a .o file for each .cpp. After this, say you do a `ls > input.txt`. Doing this will put each of the files (.o, .cpp, and the a.out file) into the text file. This functionality is quite fine and expected, but doing a `cat < input.txt` will cause the terminal to become a chaotic mess, usually needing termination with ctrl-c. Not sure if it's an infinite loop because the first time we encountered it, we immediately put a stop to it. Pretty sure it's outputting the .o files and what is written in them, but we can't understand the code in there so it's not really needed. Long story short, should an input file have file names and you as the user would like to cat the files in there, make sure that the files in the text file are ONLY .cpp files or your terminal will look like it's being hacked.

# Fixed Bugs
* ~~git status will return a fatal error (fatal: Not a git repository (or any of the parent directories): .git) (needed to test on hammer, not actually an issue)~~
* ~~used to be able to exit rshell by typing exit once, but now takes two attempts to exit~~ (fixed 11/17)
* ~~when trying to do googletest and run the make command, it will output error because it is not able to target our test.cpp file~~ (fixed 11/28)
* ~~when try to complied test.cpp file, it output error of not able to locat the file gtest/gtest.h~~ (fixed 11/28)
