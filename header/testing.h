#ifndef __TESTING_H__
#define __TESTING_H__

void parsingInput(vector<string> &cmds);
string userInput();
bool exitEntered(vector<string> cmds);
bool isOperator(vector<string> cmds, int index);
vector<string> findOperators(vector<string> cmds);
void semicolon(vector<string> cmds, unsigned index);
bool executeCmd(vector<string> cmds);
// ------------------ Assignment 3 ----------------------

bool fileExists (string& fileName);
bool isDirectory (string& filename);
bool isFile (string& fileName); 


// -------------------------------------------------------



#endif
