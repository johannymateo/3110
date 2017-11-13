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

bool Phone::prodIDCheck(string tempID)
{
    if (
        !(isalpha(tempID[0]) && isalpha(tempID[1])) ||    // is it a letter
        !(isdigit(tempID[2]) && isdigit(tempID[3])) ||    // is it a number
        !(tempID.length() == 4)                            // is it 4 chars
    ) {
        return false;   // return false if invalid format
    }

    else {              // valid format, set it to the prodID and return true
        prodID = tempID;
        return true;
    }
}
