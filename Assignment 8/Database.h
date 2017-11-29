#ifndef DATABASE_H
#define DATABASE_H

#include "Phone.h"
using namespace std;

class Database {
private:
    int dbSize;                     // dynamic size of db
    Phone *phoneArr;                // pointer for array of phones
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
    void growPhoneArr();                 // grow array when almost full

public:

    Database()                               // constructor
    {   sizePrompt();
        phoneArr = new Phone[dbSize];
        items = 0;    }

    Database(const Database &other)          // copy constructor
    {   this->items = other.items;
        this->dbSize = other.dbSize;
        this->phoneArr = new Phone[this->dbSize];
        for (int i = 0; i < this->dbSize; i++)
            this->phoneArr[i] = other.phoneArr[i];  }

    ~Database()
    {   delete [] phoneArr; }

    const Database operator= (const Database &);

    void sizePrompt();                          // what size array?
    void addItem();
    void updatePrice();
    void updateQOH();
    void queryDB() const;
    void printDB() const;
    void deleteItem();
};

#endif
