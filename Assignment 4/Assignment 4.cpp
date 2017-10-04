// Johanny Mateo
// CISC 3110 - Assignment 3
// Change function arrays to pointers

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// fn to add items to arrays, returns nothing and
// accepts ptr to phoneNameArr, ptr to priceArr, ptr to QOHArr,
// counter of current arr loc, and dbmax
void addItem(string *, double *, int *, int &, int);
// fn to find index of productID, retuns index as int,
// accepts ptr to phoneNameArr, phoneName, up to where is the arr filled
int findID(const string *, string, int);
// fn to update price, returns nothing
// accepts ptr to phoneNameArr, ptr to priceArr,array fill loc
void updateItem(const string *, double *, int);
// fn to update quantity, returns nothing
// accepts ptr to phoneNameArr, ptr to QOHArr, array fill loc
void updateItem(const string *, int *, int);
// fn to display item, returns nothing
// accepts ptr to phoneNameArr, ptr to priceArr, ptr to QOHArr, array fill loc 
void displayItem(const string *, const double *, const int *, int);
// fn to print DB, returns nothing
// accepts ptr to phoneNameArr, ptr to priceArr, ptr to QOHArr,
// array fill loc
void printDB(const string *, const double *, const int *, int);
// fn to display switch instructions, returns choice, accepts nothing
int instructions();
// fn to check for and correct phoneName duplicate, returns true if it exists
// accepts ptr to phoneNameArr, phoneName by reference,
// arr insert loc
bool dupeCheck(const string *, string &, int);
// function to delete, phoneNameArr, accepts string for phoneName, and items #
// function to growarray

// phone name limit can only have 4 chars + null
const int PRODCHAR = 5;
const int DBMAX = 1000;

int main()
{
     // items is used to keep track of up to where are the arrays are filled
    int choice, items = 0, dynamicDBMax;
    

    cout << "How many items would you like to add: ";
    cin >> dynamicDBMax;
    cout << endl;

    char prodIDArr[DBMAX][PRODCHAR];
    string* phoneNameArr = new string[dynamicDBMax];
    double* priceArr = new double[DBMAX];
    int* QOHArr = new int[DBMAX];
    
    // print the menu instructions
    choice = instructions();

    while (choice != 6) {       // 6 is exit; skip this loop and return to OS
        switch (choice) {
            case 1:
                addItem(phoneNameArr, priceArr, QOHArr, items, dynamicDBMax);
                break;
            case 2:
                updateItem(phoneNameArr, priceArr, items);
                break;
            case 3:
                updateItem(phoneNameArr, QOHArr, items);
                break;
            case 4:
                displayItem(phoneNameArr, priceArr, QOHArr, items);
                break;
            case 5:
                printDB(phoneNameArr, priceArr, QOHArr, items);
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = instructions();    // bring up menu again
    }

    delete [] phoneNameArr;
    phoneNameArr = NULL;
    delete [] priceArr;
    priceArr = NULL;
    delete [] QOHArr;
    QOHArr = NULL;

    return 0;
}

void addItem(string *phoneNameArr, double *priceArr, int *QOHArr, int &items, int max)
{
    char ans; // ans is to keep adding items
    bool dupe;  // is there an uncorrected duplicate?
    string phoneName;

    // while we are in the bounds of the array, they want to continue, and there are no duplicates (or corrected ones):
    while ((items < max) && (phoneName != "0") && (!dupe)) {
        cerr << "Item " << items+1 << " - Enter the phone name, 0 to stop: ";
        cin >> phoneName;

        dupe = dupeCheck(phoneNameArr, phoneName, items);
        // if dupe is false, there are no dupes, continue with entry, else
        // skip this; while loop will also be false, and fn will return
        if (!dupe) {         // there is no dupe, add this phoneName
            *(phoneNameArr + items) = phoneName;
            cerr << "Enter the price: ";
            cin >> *(priceArr + items);
            cerr << "Enter the quantity: ";
            cin >> *(QOHArr + items);
            cout << endl;
            items++;        // go to next array location
        }
    }
    cerr << endl;
    return;
}

int findID(const string *phoneNameArr, string findID, int filled)
{
    for (int i = 0; i < filled; i++)
        if (*(phoneNameArr + i) == findID)
            return i;   // if it is found, return i
    return -1;          // -1 to know that product id wasn't found
}

void updateItem(const string *phoneNameArr, double *priceArr, int filled)
{
    int editLoc;            // the index of item to be updated
    string editID;

    cerr << "What is the phone name: ";
    cin >> editID;
    editLoc = findID(phoneNameArr, editID, filled);

    if (editLoc == -1) {            // ID not found
        cerr << "Phone name not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new price: ";
        cin >> *(priceArr + editLoc);
        cerr << "\nProduct ID: "<< *(phoneNameArr + editLoc)
             << "\nUpdated price: " << *(priceArr + editLoc) << "\n\n";
        return;
    }
}

void updateItem(const string *phoneNameArr, int *QOHArr, int filled)
{
    int editLoc;            // the index of item to be updated
    string editID;

    cerr << "What is the phone name: ";
    cin >> editID;
    editLoc = findID(phoneNameArr, editID, filled);

    if (editLoc == -1) {            // ID not found
        cerr << "Phone name not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new quantity: ";
        cin >> *(QOHArr + editLoc);
        cerr << "\nProduct ID: " << *(phoneNameArr + editLoc)
             << "\nUpdated quantity: " << *(QOHArr + editLoc) << "\n\n";
        return;
    }
}

void displayItem(const string *phoneNameArr, const double *priceArr, const int *QOHArr, int filled)
{
    int loc;            // loc to be displayed
    string displayID;

    cerr << "What is the phone name: ";
    cin >> displayID;
    loc = findID(phoneNameArr, displayID, filled);

    if (loc == -1) {        // ID not found
        cerr << "Phone name not found.\n\n";
        return;
    }
    else {
        cerr << "\nProduct ID: " << *(phoneNameArr + loc) << "\nPrice: "
             << *(priceArr + loc) << "\nQuantity: " << *(QOHArr + loc)
             << "\n\n";
    return;
    }
}

void printDB(const string *phoneNameArr, const double *priceArr, const int *QOHArr, int filled)
{
    cerr << setw(10) << "Item No. |" << setw(13) << " Phone name |"
         << setw(10) << " Price |" << setw(10) << " Quantity\n";
    cerr << "------------------------------------------\n";

    for (int i = 0; i < filled; i++) {
        cerr << setw(8) << i+1 << " | " << setw(13) << *(phoneNameArr + i) + " | "
             << setw(7) << setprecision(2) << fixed << *(priceArr + i) << " | "
             << setw(8) << *(QOHArr + i) << endl;
    }

    cerr << endl;
    return;
}

int instructions()
{
    int decision;
    cerr << "1. Add Item" << endl << "2. Update Item Price" << endl
         << "3. Update Item Quantity" << endl << "4. Display Item" << endl
         << "5. Print Database" << endl << "6. Exit Program" << endl
         << "Make a choice: ";
    cin >> decision;
    cerr << endl;
    return decision;
}

bool dupeCheck(const string *phoneNameArr, string &phoneName, int currLoc)
{
    char ans;           // enter new ID?
    bool exists;        // does a dupe exist?

    do {
        // -1 means phoneName doesn't exist
        if (findID(phoneNameArr, phoneName, currLoc) != -1) {
            exists = true;
            cerr << "This item already exists."
                 << " Would you like to input a new phone name? (Y/N): ";
            cin >> ans;

            if (ans == 'y' || ans == 'Y') {
                cerr << "Item " << currLoc + 1 << " - Enter the phone name: ";
                cin >> phoneName;
            }
        }
        else
            exists = false;
    } while ((ans == 'y' || ans == 'Y') && exists);
    // while there was a dupe found and they decided to input a new ID

    if (exists)         // there is an uncorrected dupe, return true
        return true;
    else                // there are no dupes, or it was corrected, return false
        return false;
}


