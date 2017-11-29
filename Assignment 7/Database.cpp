#include "Database.h"
#include "Phone.h"
#include <iostream>
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;

Database::Database()
{
    // sets the phone array items to 0
    items = 0;
}

// to add a phone object
void Database::addItem()
{
    string tempID, tempName;
    double tempPrice;
    int tempQOH;
    bool dupe = false, valid;    // continue with entry?; are there duplicates?

    cerr << "The product ID must be 4 characters. Two letters, followed by two numbers.\n\n";

    // while there is space, they want to continue, and there are no uncorrected dupes
    while ( (items < SIZE) && (!dupe) ) {

        cerr << "Item " << items+1 << endl;
        cerr << "Enter the product ID, \"0000\" to stop entry: ";
        cin.ignore();
        cin >> tempID;

        // if they entered 0000, they do not want to continue, return
        if (tempID == "0000")
            return;

        // check if tempID is the correct format
        valid = (phoneArr + items)->prodIDCheck(tempID);
        // if fn returns false, this means the format is incorrect
        while (!valid) {
            cerr << "Please enter 4 characters in the format AA00: ";
            cin >> tempID;
            valid = (phoneArr + items)->prodIDCheck(tempID);
        }

        dupe = dupeCheck(tempID); // does this ID already exist?

        if (!dupe) {  // if the last entered ID is not a duplicate
            // send the temporary variables to the obj
            cerr << "Enter the product name: ";
            cin.ignore();
            getline(cin, tempName);
            cerr << "Enter the price: ";
            cin >> tempPrice;
            cerr << "Enter the quantity: ";
            cin >> tempQOH;

            // invoke the constructor on the temp obj
            Phone tempObj(tempID, tempName, tempPrice, tempQOH);
            // the tempObj is the object that is going into this loc
            phoneArr[items] = tempObj;


            items++;    // increase item count by 1
            cerr << endl;
        }
    }
    cerr << endl;
    return;
}

// checks if ID already exists & returns if this is true or false. Accepts obj arr, tempID, and how many objs already exist
bool Database::dupeCheck(string &tempID)
{
    char ans;           // enter a new ID?
    bool exists, valid;        // does a dupe exists?

    do {        // -1 means the item does not exist
        if ( findID(tempID) != -1 ) {
            exists = true;
            cerr << "This item already exists. "
                 << "Would you like to input a new product ID? (Y/N): ";
            cin >> ans;

            if (ans == 'y' || ans == 'Y') {
                cerr << "Enter the new product ID: ";
                cin >> tempID;
                valid = (phoneArr + items)->prodIDCheck(tempID);
                while (!valid) {
                    cerr << "Enter the new product ID: ";
                    cin >> tempID;
                    valid = (phoneArr + items)->prodIDCheck(tempID);
                }
            }
        }
        else
            exists = false;
    } while ( (ans == 'y' || ans == 'Y') && exists);
    // repeat this loop while a dupe was found & they input a new ID

    if (exists)
        return true;    // a dupe was found, but they did not want to correct it
    else
        return false;   // a dupe was not found
}

// checks for prodID and returns loc. in arr. Accepts obj arr, string to find, and how many items are in the arr
int Database::findID(string findMe) const
{
    for (int i = 0; i < items; i++)
        if ( findMe == (phoneArr + i)->getID() )
            return i;   // it found the ID, return the arr loc

    return -1;  // -1 to indicate it didn't find the ID
}

void Database::updatePrice()
{
    int editLoc;        // location of item to be updated
    string editID;      // ID of item to be edited
    double tempPrice;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(editID);

    if (editLoc != -1) {        // it found ID
        cerr << "Enter the new price: ";
        cin >> tempPrice;

        (phoneArr + editLoc)->setPrice(tempPrice);
        cerr << "\nProduct ID: " << (phoneArr + editLoc)->getID()
             << "\nUpdated price: " << (phoneArr + editLoc)->getPrice()
             << endl << endl;
        return;
    }
    else {      // it did not find ID
        cerr << "Product ID not found.\n\n";
        return;
    }
}

void Database::updateQOH()
{
    int editLoc;        // location of item to be updated
    string editID;      // ID of item to be edited
    int tempQOH;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(editID);

    if (editLoc != -1) {        // it found ID
        cerr << "Enter the new quantity: ";
        cin >> tempQOH;

        (phoneArr + editLoc)->setQOH(tempQOH);
        cerr << "\nProduct ID: " << (phoneArr + editLoc)->getID()
             << "\nUpdated quantity: " << (phoneArr + editLoc)->getQOH()
             << endl << endl;
    }
    else {      // it did not find ID
        cerr << "Product ID not found.\n\n";
    }

    return;
}

int Database::queryInstructions() const
{
    int decision;

    cerr << "1. Display by Product ID" << endl
         << "2. Display by Product Name" << endl
         << "3. Display by Price" << endl
         << "4. Display by Quantity on Hand" << endl
         << "5. Return to Previous Menu" << endl
         << "Make a choice: ";

    cin >> decision;
    cerr << endl;

    return decision;
}

void Database::queryDB() const
{
    int choice;

    choice = queryInstructions();       // display instructions, save choice
    while (choice != 5) {   // 5 is to return to previous menu
        switch (choice) {
            case 1:
                displayByID();
                break;
            case 2:
                displayByName();
                break;
            case 3:
                displayByPrice();
                break;
            case 4:
                displayByQOH();
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = queryInstructions();   // brings up menu again
    }
    return;
}

void Database::displayByID() const
{
    string displayID;
    int loc;

    cerr << "What is the product ID: ";
    cin >> displayID;

    loc = findID(displayID);

    if (loc != -1) {    // if found print info
        printTableHeading();
        printQueryResults(loc);
    }
    else {
        cerr << "Product ID not found.\n";
    }
    cerr << endl;
    return;
}

void Database::displayByName() const
{
    string displayName;
    int loc;
    bool found = false;

    cerr << "What is the product name: ";
    cin.ignore();
    getline(cin, displayName);

    printTableHeading();

    for (int i = 0; i < items; i++) {
        if ( displayName == (phoneArr + i)->getName() ){
            found = true;   // name was found
            printQueryResults(i);
        }
    }

    if (!found) {
        cerr << "No product with that name was found.\n";
    }
    cerr << endl;
    return;
}

void Database::printTableHeading() const
{
    cerr << setw(13) << " Product ID |" << setw(15) << " Product Name |"
        << setw(13) << " Price |" << setw(8) << " Quantity\n";
    cerr << "---------------------------------------------------\n";

    return;
}

void Database::printQueryResults(int i) const
{
    cerr << setw(11) << (phoneArr + i)->getID() << " | " << setw(15)
         << (phoneArr + i)->getName() + " | " << setw(10)
         << setprecision(2) << fixed << (phoneArr + i)->getPrice() << " | "
         << setw(8) << (phoneArr + i)->getQOH() << endl;

    return;
}

void Database::displayByPrice() const
{
    double minPrice, maxPrice;
    bool found = false;

    cerr << "What is the minimum price: ";
    cin >> minPrice;
    cerr << "What is the maximum price: ";
    cin >> maxPrice;

    printTableHeading();

    for (int i = 0; i < items; i++) {
        // if curr loc price is within the range of min & max price
        // min <= i <= max
        if ( (minPrice <= (phoneArr + i)->getPrice() ) &&
             ( (phoneArr + i)->getPrice() <= maxPrice )
        ) {
                 found = true;
                 printQueryResults(i);
        }
    }

    if (!found)
        cerr << "No product within that price range was found.\n";

    cerr << endl;
    return;
}

void Database::displayByQOH() const
{
    double minQOH, maxQOH;
    bool found = false;

    cerr << "What is the minimum quantity: ";
    cin >> minQOH;
    cerr << "What is the maximum quantity: ";
    cin >> maxQOH;

    printTableHeading();

    for (int i = 0; i < items; i++) {
        // if curr loc qoh is within the range of min & max qoh
        // min <= i <= max
        if ( (minQOH <= (phoneArr + i)->getQOH() ) &&
             ( (phoneArr + i)->getQOH() <= maxQOH )
         ) {
                 found = true;
                 printQueryResults(i);
        }
    }

    if (!found)
        cerr << "No product within that price range was found.\n";

    cerr << endl;
    return;
}

void Database::printDB() const
{
    printTableHeading();

    for (int i = 0; i < items; i++) {
        cerr << setw(11) << (phoneArr + i)->getID() << " | " << setw(15)
             << (phoneArr + i)->getName() + " | " << setw(10)
             << setprecision(2) << fixed << (phoneArr + i)->getPrice() << " | "
             << setw(8) << (phoneArr + i)->getQOH() << endl;
    }
    cerr << endl;

    return;
}

void Database::deleteItem()
{
    string deleteID;
    int deleteLoc;

    cerr << "What is the product ID: ";
    cin >> deleteID;

    deleteLoc = findID(deleteID);

    if (deleteLoc != -1) {
        // overwrite the loc to be deleted with the last loc
        *(phoneArr + deleteLoc) = *(phoneArr + (items-1));
        // 1 less item
        items--;
        cerr << "Item deleted.";
    }
    else
        cerr << "Product ID not found.";

    cerr << endl << endl;
    return;
}
