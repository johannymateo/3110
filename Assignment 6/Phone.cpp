#include "Phone.h"
#include <cctype>
#include <string>
#include <cstring>

//default cnstructor
Phone::Phone()
{
    prodID = "";
    name = "";
    price = 0.00;
    QOH = 0;
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

    else {              // valid format, set it to the prodID and return true
        this->prodID = prodID;
        return true;
    }
}
