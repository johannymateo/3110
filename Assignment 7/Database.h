#ifndef DATABASE_H
#define DATABASE_H
#include "Phone.h"
using namespace std;

class Database {
private:
    Phone *phoneArr;    // pointer for array of phones
    int dbSize;        // how many phone objects do you want?
    int items;          // how many items exist

public:
    void sizePrompt();              // what will the array size be?
    Database();                    // constructor
    Database(const Database &);       // copy constructor
    ~Database();                  // destructor



};


#endif
