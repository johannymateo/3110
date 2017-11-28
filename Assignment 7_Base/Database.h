#ifndef DATABASE_H
#define DATABASE_H

#include "Phone.h"
using namespace std;

class Database {
private:
    static const int SIZE = 1000;
    Phone phoneArr[SIZE];            // pointer for array of phones
    int items;                      // how many items exist
    bool dupeCheck(string &);
    int findID(string) const;
    int queryInstructions() const;
    void displayByID() const;
    void displayByName() const;
    void printTableHeading() const;
    void printQueryResults(int) const;
    void displayByPrice() const;
    void displayByQOH() const;

public:
    Database();                     // constructor
    void addItem();
    void updatePrice();
    void updateQOH();
    void queryDB() const;
    void printDB() const;
    void deleteItem();

};

#endif
