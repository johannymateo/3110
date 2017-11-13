// Johanny Mateo
// CISC 3110 - Assignment 6
// Make phone objects

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include "Phone.h"
using namespace std;

const int SIZE = 1000;

int instructions();
void addItem(Phone *, int &);
//void prodIDCheck(string &);
bool dupeCheck(Phone *, string &, int);
int findID(const Phone *, string, int);
void updatePrice(Phone *, int);
void updateQOH(Phone *, int);
int queryInstructions();
void queryDB(const Phone *, int);
void displayByID(const Phone *, int);
void displayByName(const Phone *, int);
void printTableHeading();
void printQueryResults(const Phone *, int);
void displayByPrice(const Phone *, int);
void displayByQOH(const Phone *, int);
void printDB(const Phone *, int);
void deleteItem(Phone *, int &);
Phone *growArray(Phone *, int &);

int main ()
{
    int choice, items = 0;
    Phone phoneArr[SIZE];

    // print meu instructions
    choice = instructions();

    while (choice != 7) {       // 7 is exit; skip this loop and return to OS
        switch (choice) {
            case 1:
                addItem(phoneArr, items);
                break;
            case 2:
                updatePrice(phoneArr, items);
                break;
            case 3:
                updateQOH(phoneArr, items);
                break;
            case 4:
                queryDB(phoneArr, items);
                break;
            case 5:
                printDB(phoneArr, items);
                break;
            case 6:
                deleteItem(phoneArr, items);
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = instructions();    // bring up menu again
    }

    return 0;
}

//displays instructions, returns menu choice
int instructions()
{
    int decision;
    cerr << "1. Add Item" << endl << "2. Update Item Price" << endl
         << "3. Update Item Quantity" << endl << "4. Query Database" << endl
         << "5. Print Database" << endl << "6. Delete Item" << endl
         << "7. Exit Program" << endl
         << "Make a choice: ";
    cin >> decision;
    cerr << endl;
    return decision;
}

// to add a phone object. Accepts array, how many objs already exists, max size of DB
void addItem(Phone *phoneArr, int &items)
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

        dupe = dupeCheck(phoneArr, tempID, items); // does this ID already exist?

        if (!dupe) {  // if the last entered ID is not a duplicate
            // send the temporary variables to the obj
            cerr << "Enter the product name: ";
            cin.ignore();
            getline(cin, tempName);
            (phoneArr + items)->setName(tempName);
            cerr << "Enter the price: ";
            cin >> tempPrice;
            (phoneArr + items)->setPrice(tempPrice);
            cerr << "Enter the quantity: ";
            cin >> tempQOH;
            (phoneArr + items)->setQOH(tempQOH);

            items++;    // increase item count by 1
            cerr << endl;
        }
    }
    cerr << endl;
    return;
}

// checks if ID already exists & returns if this is true or false. Accepts obj arr, tempID, and how many objs already exist
bool dupeCheck(Phone *phoneArr, string &tempID, int items)
{
    char ans;           // enter a new ID?
    bool exists, valid;        // does a dupe exists?

    do {        // -1 means the item does not exist
        if ( findID(phoneArr, tempID, items) != -1 ) {
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
int findID(const Phone *phoneArr, string findMe, int items)
{
    for (int i = 0; i < items; i++)
        if ( findMe == (phoneArr + i)->getID() )
            return i;   // it found the ID, return the arr loc

    return -1;  // -1 to indicate it didn't find the ID
}

void updatePrice(Phone *phoneArr, int items)
{
    int editLoc;        // location of item to be updated
    string editID;      // ID of item to be edited
    double tempPrice;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(phoneArr, editID, items);

    if (editLoc != -1) {        // it found ID
        cerr << "Enter the new price: ";
        cin >> tempPrice;

        (phoneArr + editLoc)->setPrice(tempPrice);
        cerr << "\nProduct ID: " << (phoneArr + editLoc)->getID()
            << "\nUpdated price: " << (phoneArr + editLoc)->getPrice();
        return;
    }
    else {      // it did not find ID
        cerr << "Product ID not found.\n\n";
        return;
    }
}

void updateQOH(Phone *phoneArr, int items)
{
    int editLoc;        // location of item to be updated
    string editID;      // ID of item to be edited
    int tempQOH;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(phoneArr, editID, items);

    if (editLoc != -1) {        // it found ID
        cerr << "Enter the new quantity: ";
        cin >> tempQOH;

        (phoneArr + editLoc)->setQOH(tempQOH);
        cerr << "\nProduct ID: " << (phoneArr + editLoc)->getID()
            << "\nUpdated quantity: " << (phoneArr + editLoc)->getQOH();
    }
    else {      // it did not find ID
        cerr << "Product ID not found.\n\n";
    }

    return;
}

int queryInstructions()
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

void queryDB (const Phone *phoneArr, int items)
{
    int choice;

    choice = queryInstructions();       // display instructions, save choice
    while (choice != 5) {   // 5 is to return to previous menu
        switch (choice) {
            case 1:
                displayByID(phoneArr, items);
                break;
            case 2:
                displayByName(phoneArr, items);
                break;
            case 3:
                displayByPrice(phoneArr, items);
                break;
            case 4:
                displayByQOH(phoneArr, items);
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = queryInstructions();   // brings up menu again
    }
    return;
}

void displayByID(const Phone *phoneArr, int items)
{
    string displayID;
    int loc;

    cerr << "What is the product ID: ";
    cin >> displayID;

    loc = findID(phoneArr, displayID, items);

    if (loc != -1) {    // if found print info
        printTableHeading();
        printQueryResults(phoneArr, loc);
    }
    else {
        cerr << "\nProduct ID not found.\n";
    }

    return;
}

void displayByName(const Phone *phoneArr, int items)
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
            printQueryResults(phoneArr, i);
            cerr << endl;
        }
    }

    if (!found) {
        cerr << "\nNo product with that name was found.\n\n";
    }

    return;
}

void printTableHeading()
{
    cerr << endl;
    cerr << setw(13) << " Product ID |" << setw(15) << " Product Name |"
        << setw(13) << " Price |" << setw(8) << " Quantity\n";
    cerr << "---------------------------------------------------\n";

    return;
}

void printQueryResults( const Phone *phoneArr, int i)
{
    cerr << setw(11) << (phoneArr + i)->getID() << " | " << setw(15)
         << (phoneArr + i)->getName() + " | " << setw(10)
         << setprecision(2) << fixed << (phoneArr + i)->getPrice() << " | "
         << setw(8) << (phoneArr + i)->getQOH();

    return;
}

void displayByPrice(const Phone *phoneArr, int items)
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
                 printQueryResults(phoneArr, i);
                 cerr << endl << endl;
        }
    }

    if (!found)
        cerr << "No product within that price range was found.\n\n";

    return;
}

void displayByQOH(const Phone *phoneArr, int items)
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
                 printQueryResults(phoneArr, i);
                 cerr << endl << endl;
        }
    }

    if (!found)
        cerr << "No product within that price range was found.\n\n";

    return;
}

void printDB(const Phone *phoneArr, int items)
{
    printTableHeading();

    for (int i = 0; i < items; i++) {
        cerr << setw(11) << (phoneArr + i)->getID() << " | " << setw(15)
             << (phoneArr + i)->getName() + " | " << setw(10)
             << setprecision(2) << fixed << (phoneArr + i)->getPrice() << " | "
             << setw(8) << (phoneArr + i)->getQOH() << endl;
    }
    cerr << endl << endl;

    return;
}

void deleteItem(Phone *phoneArr, int &items)
{
    string deleteID;
    int deleteLoc;

    cerr << "What is the product ID: ";
    cin >> deleteID;

    deleteLoc = findID(phoneArr, deleteID, items);

    if (deleteLoc != -1) {
        // overwrite the loc to be deleted with the last loc
        *(phoneArr + deleteLoc) = *(phoneArr + (items-1));
        // 1 less item
        items--;
        cerr << "Item deleted.\n\n";
    }
    else
        cerr << "Product ID not found.\n\n";

    return;
}
