// Name: Edgar Perez
// Collaborators: Shusanta Bhatter, Nick Vasicek
// Runapp header file

#ifndef _Run_H
#define _Run_H

#include "ListBT.h"
#include <fstream>
#include <string>
#include <ctype.h>

using std::ifstream;

void runapp();

void collectTable(ListBT<char, string>& morseTree, ifstream& input);

void printMorse(ListBT<char, string>& morseTree, ifstream& convert);

#endif