#ifndef PROGRAM_H
#define PROGRAM_H

#include "Database.h"
#include "Phone.h"
#include <iostream>
using namespace std;

class Program {
private:
    Database db;
    void instructions();        // displays instructions/menu
    void switchMenu(int);       // does what the user wants
public:
    Program()
    {   instructions(); }   // calls the instructions
};
#endif
