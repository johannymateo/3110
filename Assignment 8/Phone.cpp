#include "Phone.h"
#include <cctype>
#include <string>
#include <cstring>

//default constructor
Phone::Phone()
{
    prodID = "";
    name = "";
    price = 0.00;
    QOH = 0;
}

// set the object data
Phone::Phone(string prodID, string name, double price, int QOH)
{
    this->prodID = prodID;
    this->name = name;
    this->price = price;
    this->QOH = QOH;
}

bool Phone::prodIDCheck(string prodID)
{
    if (
        !(isalpha(prodID[0]) && isalpha(prodID[1])) ||    // is it a letter
        !(isdigit(prodID[2]) && isdigit(prodID[3])) ||    // is it a number
        !(prodID.length() == 4)                            // is it 4 chars
    ) {
        return false;   // return false if invalid format
    }

    else           // valid format, return true
        return true;
}
