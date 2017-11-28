#ifndef PROGRAM_H
#define PROGRAM_H

#include "Database.h"
#include "Phone.h"
#include <iostream>
using namespace std;

class Program {
private:
    Database db;
    void instructions();
    void menu(int);
public:
    Program();
};
#endif
