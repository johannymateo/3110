// Johanny Mateo
// CISC 3110 - Assignment 4
// Dynamically Allocate All Arrays
// Make ProdID 2D array
// Delete items
// Double array size if needed

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int PRODIDLIM = 5;        // PROD ID cannot have more than 4 chars + null

// fn to add items to arrays, returns nothing and
// accepts ptr to prodIDArr, ptr to priceArr, ptr to QOHArr,
// and counter of current arr loc
// max is the const int for max no. of items, it is not to be changed
void addItem(char **, double *, int *, int &, const int);
// fn to find index of productID, retuns index as int,
// accepts ptr to prodIDArr, and up to where is the arr filled
int findID(const char **, const int);
// fn to update price, returns nothing
// accepts ptr to prodIDArr, ptr to priceArr, and array fill loc
void updateItem(const char **, double *, const int);
// fn to update quantity, returns nothing
// accepts ptr to prodIDArr, ptr to QOHArr, and array fill loc
void updateItem(const char **, int *, const int);
// fn to display item, returns nothing
// accepts ptr to prodIDArr, ptr to priceArr, ptr to QOHArr, and array fill loc
void displayItem(const char **, const double *, const int *, const int);
// fn to print DB, returns nothing
// accepts ptr to prodIDArr, ptr to priceArr, ptr to QOHArr, and array fill loc
void printDB(const char **, const double *, const int *, const int);
// fn to display switch instructions, returns choice, accepts nothing
int instructions();
// fn to check for and correct prodID duplicate, returns true if it exists
// accepts ptr to prodIDArr, prodID by reference, and arr insert loc
// bool dupeCheck(const string *, string &, int);

int main()
{
    // filled ptr is used to keep track of up to where are the arrays are filled
    int max, choice, items = 0;

    // print the menu instructions

    cout << "How many items would you like to add to the database: ";
    cin >> max;
    cin.clear();        // clear the null terminator from the buffer

    choice = instructions();

    // create arrays on the heap
    // REVIEW: Have they been deleted and ptrs reset to null?
    // prodIDArr
    // declare a pointer(that will point to the entirety of the 2D array/rows), that will then point to chars
        // pointer -> pointer -> char
    char **prodIDArr = NULL;
    // on the heap, create an array with the max number of rows. This array, will contain pointers that willl then point to chars (ex, make 1000 pointers. Those 1000 pointers will point to 5 pointers that will tell u the char)
    prodIDArr = new char*[max];
        // declare c-string arr
        // go through each row
        for (int row = 0; row < max; row++) {
            // on the heap, inside of each row of arrays, create another array with 5 locations for the chars
            prodIDArr[row] = new char[PRODIDLIM];
        }
    // price pointer & array
    double *priceArr = new double[max];
    // QOH pointer and array
    int *QOHArr = new int[max];

    while (choice != 6) {       // 6 is exit; skip this loop and return to OS
        switch (choice) {
            case 1:
                addItem(prodIDArr, priceArr, QOHArr, items, max);
                break;
            /*case 2:
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
                break;*/
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = instructions();    // bring up menu again
    }

    // delete arrays on heap & reset pointers

    // for the 2D Array:
    // delete the contents in each row (delete the product IDs arrays)
    for (int row = 0; row < max; row++) {
        delete [] prodIDArr[row];
    }
    // now delete the rows themselves (delete the pointers that used to point to the arrays for the product ID's)
    delete [] prodIDArr;
    // nothing on the heap, set the pointer to point to null
    prodIDArr = NULL;

    delete [] priceArr;
    priceArr = NULL;

    delete [] QOHArr;
    QOHArr = NULL;

    return 0;
}

// max is const because it is not to be changed inside this func
void addItem(char **prodIDArr, double *priceArr, int *QOHArr, int &items, const int max)
{
    int col = 0;    // Prod ID input will always start at loc 0
    cout << "Product ID Numbers must be in the format of 2 letters followed by 2 numbers. Example: AA00\n";



    while (items < max) {   // while the array has empty space

        for (int row = 0; row < max; row++) {
            cout << "Item " << items+1 << " out of " << max << ". Enter 0000 to stop: ";
            // if they do not want to continue
            cin.getline(prodIDArr[row], PRODIDLIM);
            items++;

            if (strcmp(prodIDArr[row], "0000") == 0) {
                items--;    // dont count the 0000
                return;
            }
        }
    }
    return;
}

/*
void addItem(char *prodIDArr, double *priceArr, int *QOHArr, int &items, const int max)
{
    char ans; // ans is to keep adding items
    bool dupe;  // is there an uncorrected duplicate?
    string prodID;

    if (items < max) {        // makes sure not to go out of bounds in array
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
*/

/*
int findID(const char **prodIDArr, const int filled)
{
    for (int i = 0; i < filled; i++)
        if (*(prodIDArr + i) == findID)
            return i;   // if it is found, return i
    return -1;          // -1 to know that product id wasn't found
}
*/

/*
int findID(const char **prodIDArr, const string findMe, const int filled)
{
    for (int row = 0; row < filled; row++ {
        for (int col = 0; col < PRODIDLIM; col++) {
            if
        }
    }
}
*/
/*
void updateItem(const char **prodIDArr, double *priceArr, const int filled)
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
*/
/*
void updateItem(const char **prodIDArr, int *QOHArr, const int filled)
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
*/
/*
void displayItem(const char **prodIDArr, const double *priceArr, const int *QOHArr, const int filled)
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
*/
/*
void printDB(const char **prodIDArr, const double *priceArr, const int *QOHArr, const int filled)
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
*/

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

/*
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
*/
