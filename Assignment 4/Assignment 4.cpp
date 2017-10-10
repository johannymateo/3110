// Johanny Mateo
// CISC 3110 - Assignment 4

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;


const int DBMAX = 1000;
const int PRODCHAR = 5;

// fn to add items to arrays, returns nothing and
// accepts prodIDArr, prodNameArr,priceArr, QOHArr,
// counter of current arr loc, and size of dynamic arrays
void addItem(char [][PRODCHAR], string *, double *, int *, int &, int);
// fn to find index of productID, retuns index as int,
// accepts ptr to prodNameArr, prodName, and up to where is the arr filled
int findID(const char [][PRODCHAR], char *, int);
// fn to update price, returns nothing
// accepts ptr to prodNameArr, ptr to priceArr, and array fill loc
void updateItem(const char [][PRODCHAR], double *, int);
// fn to update quantity, returns nothing
// accepts ptr to prodNameArr, ptr to QOHArr, and array fill loc
void updateItem(const char [][PRODCHAR], int *, int);
// fn to display item, returns nothing
// accepts ptr to prodNameArr, ptr to priceArr, ptr to QOHArr, and array fill loc
void displayItem(const char [][PRODCHAR], const double *, const int *, int);
// fn to print DB, returns nothing
// accepts ptr to prodNameArr, ptr to priceArr, ptr to QOHArr, and array fill loc
void printDB(const char [][PRODCHAR], const string *, const double *, const int *, int);
// fn to display switch instructions, returns choice, accepts nothing
int instructions();
// fn to check for and correct prodName duplicate, returns true if it exists
// accepts ptr to prodNameArr, prodName by reference, and arr insert loc
bool dupeCheck(char [][PRODCHAR], int);
// fn to check prod id format. accepts prod id char ptr
bool prodIDCheck(char [][PRODCHAR], int);
// fn to delete item. Takes prodID, prodName, price, QOH, and filled
void deleteItem(char [][PRODCHAR], string *, double*, int *, int &);
// fn to grow price array
double *growArray(double *, int);

int main()
{
    // items is used to keep track up to where the database is filled
    int choice, items = 0, dynamicDBMAX;
    char prodIDArr[DBMAX][PRODCHAR];
    string prodNameArr[DBMAX];

    // arrays on the stack have max 1000 locations
    cerr << "How many items would you like to add (Up to 1000 items): ";
    cin >> dynamicDBMAX;
    cin.ignore();
        while (dynamicDBMAX > 1000) {
            cerr << "Please enter less than 1000 items.\n"
                 << "How many items would you like to add: ";
            cin >> dynamicDBMAX;
            cin.ignore();
        }
    cerr << endl;

    // create arrays on the heap
    double* priceArr = new double[dynamicDBMAX];
    // grow the price array
    priceArr = growArray(priceArr, dynamicDBMAX);
    int* QOHArr = new int[dynamicDBMAX];

    // print the menu instructions
    choice = instructions();

    while (choice != 7) {       // 7 is exit; skip this loop and return to OS
        switch (choice) {
            case 1:
                addItem(prodIDArr, prodNameArr, priceArr, QOHArr, items, dynamicDBMAX);
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
                printDB(prodIDArr, prodNameArr, priceArr, QOHArr, items);
                break;
            case 6:
                deleteItem(prodIDArr, prodNameArr, priceArr, QOHArr, items);
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = instructions();    // bring up menu again
    }

    // delete things on the heap and nullify dangling pointers
    delete [] priceArr;
    priceArr = NULL;
    delete [] QOHArr;
    QOHArr = NULL;

    return 0;
}

void addItem(char prodIDArr[][PRODCHAR], string *prodNameArr, double *priceArr, int *QOHArr, int &items, int max)
{
    bool dupe;  // is there an uncorrected duplicate?
    bool cont;   // continue entry?
    string prodName;

    cerr << "The product ID must be 4 characters. Two letters, followed by 2 numbers.\n";

    // while we are in the bounds of the array, they want to continue, and there are no duplicates (or they were corrected):
    while ((items < max) && (cont) && (!dupe)) {

        cerr << "Item " << items+1 << endl;

        // input product ID and make sure it is correct format
        // returns false if they want to stop entry
        cont = prodIDCheck(prodIDArr, items);

        if (cont) {
            dupe = dupeCheck(prodIDArr, items);
            // if dupe is false, there are no dupes, continue with entry, else
            // skip this; while loop will also be false, and fn will return
            if (!dupe) {         // there is no dupe, add this prodID
                cerr << "Enter the product name: ";
                getline(cin, *(prodNameArr + items));
                cerr << "Enter the price: ";
                cin >> *(priceArr + items);
                cin.ignore();
                cerr << "Enter the quantity: ";
                cin >> *(QOHArr + items);
                cin.ignore();
                cerr << endl;
                items++;        // go to next array location
            }
        }
    }
    cerr << endl;
    return;
}

int findID(const char prodIDArr[][PRODCHAR], char *findID, int filled)
{
    for (int row = 0; row < filled; row++)
        if ( strcmp(prodIDArr[row], findID) == 0)
            return row;   // if it is found, return that row
    return -1;          // -1 to know that product id wasn't found
}

void updateItem(const char prodIDArr[][PRODCHAR], double *priceArr, int filled)
{
    int editLoc;            // row of item to be updated
    char editID[PRODCHAR];

    cerr << "What is the product ID: ";
    cin.getline(editID, PRODCHAR);
    editLoc = findID(prodIDArr, editID, filled);

    if (editLoc == -1) {            // ID not found
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new price: ";
        cin >> *(priceArr + editLoc);
        cin.ignore();
        cerr << "\nProduct ID: "<< prodIDArr[editLoc]
             << "\nUpdated price: " << *(priceArr + editLoc) << "\n\n";
        return;
    }
}

void updateItem(const char prodIDArr[][PRODCHAR], int *QOHArr, int filled)
{
    int editLoc;            // row of item to be updated
    char editID[PRODCHAR];

    cerr << "What is the product name: ";
    cin.getline(editID, PRODCHAR);
    editLoc = findID(prodIDArr, editID, filled);

    if (editLoc == -1) {            // ID not found
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new quantity: ";
        cin >> *(QOHArr + editLoc);
        cin.ignore();
        cerr << "\nProduct name: " << prodIDArr[editLoc]
             << "\nUpdated quantity: " << *(QOHArr + editLoc) << "\n\n";
        return;
    }
}

void displayItem(const char prodIDArr[][PRODCHAR], const double *priceArr, const int *QOHArr, int filled)
{
    int loc;            // loc to be displayed
    char displayID[PRODCHAR];

    cerr << "What is the product ID: ";
    cin.getline(displayID, PRODCHAR);
    loc = findID(prodIDArr, displayID, filled);

    if (loc == -1) {        // ID not found
        cerr << "Product name not found.\n\n";
        return;
    }
    else {
        cerr << "\nProduct name: " << prodIDArr[loc] << "\nPrice: "
             << *(priceArr + loc) << "\nQuantity: " << *(QOHArr + loc)
             << "\n\n";
    return;
    }
}

void printDB(const char prodIDArr[][PRODCHAR], const string *prodNameArr, const double *priceArr, const int *QOHArr, int filled)
{
    cerr << setw(10) << "Product ID. |" << setw(13) << " Product Name |"
         << setw(10) << " Price |" << setw(10) << " Quantity\n";
    cerr << "------------------------------------------\n";

    for (int i = 0; i < filled; i++) {
        cerr << setw(8) << prodIDArr[i] << " | " << setw(13) << *(prodNameArr + i) + " | "
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
         << "5. Print Database" << endl << "6. Delete Item" << endl
         << "7. Exit Program" << endl
         << "Make a choice: ";
    cin >> decision;
    cin.ignore();
    cerr << endl;
    return decision;
}

bool dupeCheck(char prodIDArr[][PRODCHAR], int currLoc)
{
    char ans;           // enter new ID?
    bool exists;        // does a dupe exist?
    char prodID[PRODCHAR];  // to be sent to the find fn

    do {
        strcpy(prodID, prodIDArr[currLoc]);
        // -1 means prodName doesn't exist, if it is 0000, they want to return
        if (findID(prodIDArr, prodID, currLoc) != -1) {
            exists = true;
            cerr << "This item already exists."
                 << " Would you like to input a new product ID? (Y/N): ";
            cin >> ans;
            cin.ignore();

            // they want to try again, promt to enter a product ID again
            if (ans == 'y' || ans == 'Y') {
                // reenter product ID
                prodIDCheck(prodIDArr, currLoc);
            }
        }
        else
            exists = false;
    } while ((ans == 'y' || ans == 'Y') && exists);
    // while there was a dupe found and they decided to input a new ID

    if (exists)         // there is an uncorrected dupe, return true
        return true;
    else    // dupe was corrected, continue
        return false;
}

bool prodIDCheck(char prodIDArr[][PRODCHAR], int row)
{
    cerr << "Enter the product ID, 0000 to stop entry: ";
    cin.getline(prodIDArr[row], PRODCHAR);

    if ( strcmp(prodIDArr[row], "0000") == 0)
        return false;   // return, they do not want to continue
    /*else {
        while ( !(// first 2 chars are not letters
                (isalpha(prodIDArr[row][1]) != 0) &&
                (isalpha(prodIDArr[row][2]) != 0) &&
                // the last 2 chars are not numbers
                (isdigit(prodIDArr[row][3]) != 0) &&
                (isdigit(prodIDArr[row][4]) != 0)) ){

            cerr << "Please enter 4 characters in the format AA00: ";
            cin.getline(prodIDArr[row], PRODCHAR);
        }
    }*/
    // they want to continue and entry is correct, return
    return true;
}

void deleteItem(char prodIDArr[][PRODCHAR], string *prodNameArr, double *priceArr, int *QOHArr, int &items)
{
    int deleteLoc;
    char deleteID[PRODCHAR];

    cerr << "What is the product ID: ";
    cin.getline(deleteID, PRODCHAR);
    deleteLoc = findID(prodIDArr, deleteID, items);

    if (deleteLoc == -1) {
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {  // rewrite the item to be deleted with the last loc
        // overwrite the delete location with the last location
        strcpy(prodIDArr[deleteLoc], prodIDArr[items]);
        *(prodNameArr + deleteLoc) = *(prodNameArr + items);
        *(priceArr + deleteLoc) = *(priceArr + items);
        *(QOHArr + deleteLoc) = *(QOHArr + items);
        // -1 item
        items--;
        cout << "Item deleted.\n";
        return;
    }
}

double *growArray(double *priceArr, int size)
{
    // create a new array with twice the size
    double *priceArrGrown = new double[size*2];

    // copy everything from old array to new array
    for (int i = 0; i < size*2; i++)
        *(priceArrGrown + i) = *(priceArr + i);

    // old array has been copied over, delete it from the heap
    delete [] priceArr;
    // return the new array
    return priceArrGrown;
}
