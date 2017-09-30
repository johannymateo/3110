// Johanny Mateo
// CISC 3110 - Assignment 3
// Change function arrays to pointers

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// fn to add items to arrays, returns nothing and
// accepts ptr to prodIDArr, ptr to priceArr, ptr to QOHArr,
// and counter of current arr loc
void addItem(string *, double *, int *, int &);
// fn to find index of productID, retuns index as int,
// accepts ptr to prodIDArr, prodID, and up to where is the arr filled
int findID(const string *, string, int);
// fn to update price, returns nothing
// accepts ptr to prodIDArr, ptr to priceArr, and array fill loc
void updateItem(const string *, double *, int);
// fn to update quantity, returns nothing
// accepts ptr to prodIDArr, ptr to QOHArr, and array fill loc
void updateItem(const string *, int *, int);
// fn to display item, returns nothing
// accepts ptr to prodIDArr, ptr to priceArr, ptr to QOHArr, and array fill loc
void displayItem(const string *, const double *, const int *, int);
// fn to print DB, returns nothing
// accepts ptr to prodIDArr, ptr to priceArr, ptr to QOHArr, and array fill loc
void printDB(const string *, const double *, const int *, int);
// fn to display switch instructions, returns choice, accepts nothing
int instructions();
// fn to check for and correct prodID duplicate, returns true if it exists
// accepts ptr to prodIDArr, prodID by reference, and arr insert loc
bool dupeCheck(const string *, string &, int);

// array to have 1000 locations
const int DBMAX = 1000;

int main()
{
    string prodIDArr[DBMAX];
    double priceArr[DBMAX];
    // items is used to keep track of up to where are the arrays are filled
    int QOHArr[DBMAX], choice, items = 0;

    // print the menu instructions
    choice = instructions();

    while (choice != 6) {       // 6 is exit; skip this loop and return to OS
        switch (choice) {
            case 1:
                addItem(prodIDArr, priceArr, QOHArr, items);
                break;
            case 2:
                updateItem(prodIDArr, priceArr, items);
                break;
            case 3:
                updateItem(prodIDArr, QOHArr, items);
                break;
            case 4:
                displayItem(prodIDArr, priceArr, QOHArr, items);
                break;
            case 5:
                printDB(prodIDArr, priceArr, QOHArr, items);
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = instructions();    // bring up menu again
    }
    return 0;
}

void addItem(string *prodIDArr, double *priceArr, int *QOHArr, int &items)
{
    char ans; // ans is to keep adding items
    bool dupe;  // is there an uncorrected duplicate?
    string prodID;

    if (items < DBMAX) {        // makes sure not to go out of bounds in array
        cerr << "Item " << items+1 << " - Enter the product ID, 0 to stop: ";
        cin >> prodID;

        // !dupe means that last dupe was corrected or there were none
        while ((prodID != "0") && !dupe) {
            dupe = dupeCheck(prodIDArr, prodID, items);
            // if dupe is false, there are no dupes, continue with entry, else
            // skip this; while loop will also be false, and fn will return
            if (!dupe) {         // there is no dupe, add this prodID
                *(prodIDArr + items) = prodID;
                cerr << "Enter the price: ";
                cin >> *(priceArr + items);
                cerr << "Enter the quantity: ";
                cin >> *(QOHArr + items);
                items++;        // go to next array location
                cerr << "\nItem " << items+1
                     << " - Enter the product ID, 0 to stop: ";
                cin >> prodID;
            }
        }
    }
    cerr << endl;
    return;
}

int findID(const string *prodIDArr, string findID, int filled)
{
    for (int i = 0; i < filled; i++)
        if (*(prodIDArr + i) == findID)
            return i;   // if it is found, return i
    return -1;          // -1 to know that product id wasn't found
}

void updateItem(const string *prodIDArr, double *priceArr, int filled)
{
    int editLoc;            // the index of item to be updated
    string editID;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(prodIDArr, editID, filled);

    if (editLoc == -1) {            // ID not found
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new price: ";
        cin >> *(priceArr + editLoc);
        cerr << "\nProduct ID: "<< *(prodIDArr + editLoc)
             << "\nUpdated price: " << *(priceArr + editLoc) << "\n\n";
        return;
    }
}

void updateItem(const string *prodIDArr, int *QOHArr, int filled)
{
    int editLoc;            // the index of item to be updated
    string editID;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(prodIDArr, editID, filled);

    if (editLoc == -1) {            // ID not found
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new quantity: ";
        cin >> *(QOHArr + editLoc);
        cerr << "\nProduct ID: " << *(prodIDArr + editLoc)
             << "\nUpdated quantity: " << *(QOHArr + editLoc) << "\n\n";
        return;
    }
}

void displayItem(const string *prodIDArr, const double *priceArr, const int *QOHArr, int filled)
{
    int loc;            // loc to be displayed
    string displayID;

    cerr << "What is the product ID: ";
    cin >> displayID;
    loc = findID(prodIDArr, displayID, filled);

    if (loc == -1) {        // ID not found
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {
        cerr << "\nProduct ID: " << *(prodIDArr + loc) << "\nPrice: "
             << *(priceArr + loc) << "\nQuantity: " << *(QOHArr + loc)
             << "\n\n";
    return;
    }
}

void printDB(const string *prodIDArr, const double *priceArr, const int *QOHArr, int filled)
{
    cerr << setw(10) << "Item No. |" << setw(13) << " Product ID |"
         << setw(10) << " Price |" << setw(10) << " Quantity\n";
    cerr << "------------------------------------------\n";

    for (int i = 0; i < filled; i++) {
        cerr << setw(8) << i+1 << " | " << setw(13) << *(prodIDArr + i) + " | "
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

bool dupeCheck(const string *prodIDArr, string &prodID, int currLoc)
{
    char ans;           // enter new ID?
    bool exists;        // does a dupe exist?

    do {
        // -1 means prodID doesn't exist
        if (findID(prodIDArr, prodID, currLoc) != -1) {
            exists = true;
            cerr << "This item already exists."
                 << " Would you like to input a new product ID? (Y/N): ";
            cin >> ans;

            if (ans == 'y' || ans == 'Y') {
                cerr << "Item " << currLoc + 1 << " - Enter the product ID: ";
                cin >> prodID;
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
