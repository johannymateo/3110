#include "Database.h"
#include "Phone.h"
#include <iostream>
using namespace std;

void Database::sizePrompt()
{
    int size;
    cout << "How many items do you want to add?\n";
    cin >> size;

    // array size has to be greater than 0
    while (size <= 0) {
        cout << "Please enter a number greater than 0\n";
        cin >> size;
    }

    this->dbSize = size;    // size is valid, set it to the dbSize

    // call the constructor to make the array
    Database();
    return;
}

Database::Database()
{
    // make an array; calls the phone constructor
    this->phoneArr = new Phone[this->dbSize];
}

Database::Database(const Database &other)
{
    // make phoneArr ptr to point to a new arr of size of the original arr
    this->phoneArr = new Phone[other.dbSize];

    // copy elts
    for (int i = 0; i < other.dbSize; i++)
        this->(phoneArr + i) = *(other.phoneArr + i);
}

Database::~Database()
{
    delete [] phoneArr;
}
