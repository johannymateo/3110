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
void displayID(const char [][PRODCHAR], const string *, const double *, const int *, int);
// fn to display query results, accepts all arrays, for loop i location, and fill
// returns nothing
void printQueryResults(const char [][PRODCHAR], const string *, const double *, const int *, int, int);
// fn to print DB, returns nothing
// accepts ptr to prodNameArr, ptr to priceArr, ptr to QOHArr, and array fill loc
void printDB(const char [][PRODCHAR], const string *, const double *, const int *, int);
// fn to display switch instructions, returns choice, accepts nothing
int instructions();
// fn to check for and correct prodName duplicate, returns true if it exists
// accepts ptr to prodNameArr, prodName by reference, and arr insert loc
bool dupeCheck(char [][PRODCHAR], int);
// fn to check prod id format. accepts prod id char ptr
void prodIDCheck(char [][PRODCHAR], int);
// fn to delete item. Takes prodID, prodName, price, QOH, and filled
void deleteItem(char [][PRODCHAR], string *, double*, int *, int &);
// fn to grow then return price array, also accepts dynamic size
double *growArray(double *, int);
//fn to query databse, accepts all arrays and fill value
void queryDB(const char [][PRODCHAR], const string *, const double *, const int *, int);
// fn to print query switch instructions
int queryInstructions();
//function to print table heading in output
void printTableHeading();

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
                queryDB(prodIDArr, prodNameArr, priceArr, QOHArr, items);
                break;
            case 5:
                printDB(prodIDArr, prodNameArr, priceArr, QOHArr, items);
                break;
            case 6:
                deleteItem(prodIDArr, prodNameArr, priceArr, QOHArr, items);
                break;
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

    cerr << "The product ID must be 4 characters. Two letters, followed by two numbers.\nPlease note that product ID's will automatically be converted into upper case characters.\n\n";

    // while we are in the bounds of the array, they want to continue, and there are no duplicates (or they were corrected):
    while ((items < max) && (cont) && (!dupe)) {

        cerr << "Item " << items+1 << endl;

        // input product ID and make sure it is correct format
        // returns false if they want to stop entry
        cerr << "Enter the product ID, 0000 to stop entry: ";
        cin.getline(prodIDArr[items], PRODCHAR);

        if ( strcmp(prodIDArr[items], "0000") == 0)
            cont = false;   // they do not want to continue
        else
            prodIDCheck(prodIDArr, items);  // make sure it is a valid prodID

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

    cerr << "What is the product ID: ";
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
        cerr << "\nProduct ID: " << prodIDArr[editLoc]
             << "\nUpdated quantity: " << *(QOHArr + editLoc) << "\n\n";
        return;
    }
}

void displayID(const char prodIDArr[][PRODCHAR], const string *prodName, const double *priceArr, const int *QOHArr, int filled)
{
    int loc;            // loc to be displayed
    char displayID[PRODCHAR];

    cerr << "What is the product ID: ";
    cin.getline(displayID, PRODCHAR);
    loc = findID(prodIDArr, displayID, filled);

    if (loc == -1) {        // ID not found
        cerr << "The product ID was not found.\n\n";
        return;
    }
    else {
        cerr << "\nProduct ID: " << prodIDArr[loc]
             << "\nProduct Name: " << *(prodName +loc)
             << "\nPrice: " << *(priceArr + loc)
             << "\nQuantity: " << *(QOHArr + loc) << "\n\n";
    return;
    }
}

void printDB(const char prodIDArr[][PRODCHAR], const string *prodNameArr, const double *priceArr, const int *QOHArr, int filled)
{
    printTableHeading();

    for (int i = 0; i < filled; i++) {
        cerr << setw(11) << prodIDArr[i] << " | " << setw(15) << *(prodNameArr + i) + " | "
             << setw(10) << setprecision(2) << fixed << *(priceArr + i) << " | "
             << setw(8) << *(QOHArr + i) << endl;
    }
    return;
}

int instructions()
{
    int decision;
    cerr << "1. Add Item" << endl << "2. Update Item Price" << endl
         << "3. Update Item Quantity" << endl << "4. Query Database" << endl
         << "5. Print Database" << endl << "6. Delete Item" << endl
         << "7. Exit Program" << endl
         << "Make a choice: ";
    cin >> decision;
    cin.ignore();
    cerr << endl;
    return decision;
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
    cin.ignore();
    cerr << endl;
    return decision;
}

bool dupeCheck(char prodIDArr[][PRODCHAR], int currLoc)
{
    char ans;           // enter new ID?
    bool exists;        // does a dupe exist?
    char findProdID[PRODCHAR];

    do {
        strcpy(findProdID, prodIDArr[currLoc]);
        // -1 means prodID doesn't exist
        if (findID(prodIDArr, findProdID, currLoc) != -1) {
            exists = true;
            cerr << "This item already exists."
                 << " Would you like to input a new product ID? (Y/N): ";
            cin >> ans;
            cin.ignore();

            if (ans == 'y' || ans == 'Y') {
                cerr << "Enter the new product ID: ";
                cin.getline(prodIDArr[currLoc], PRODCHAR);
                prodIDCheck(prodIDArr, currLoc);
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

void prodIDCheck(char prodIDArr[][PRODCHAR], int row)
{
    while (// entire statement will be false if it is not the correct format
        !( // negate the false to have the loop run
        (prodIDArr[row][0] >= 65 && prodIDArr[row][0] <= 122) &&
        (prodIDArr[row][1] >= 65 && prodIDArr[row][1] <= 122) &&
        (prodIDArr[row][2] >= 48 && prodIDArr[row][2] <= 57) &&
        (prodIDArr[row][3] >= 48 && prodIDArr[row][3] <= 57)
        ) ) {
        cerr << "Please enter 4 characters in the format AA00: ";
        cin.getline(prodIDArr[row], PRODCHAR);
        }
    // it is the correct format, change the first 2 chars to capital letters
    if (islower(prodIDArr[row][0]))
        prodIDArr[row][0] -= 32;
    if (islower(prodIDArr[row][1]))
        prodIDArr[row][1] -= 32;
    return;
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
    else {
        // overwrite the delete location with the last filled location
        strcpy(prodIDArr[deleteLoc], prodIDArr[items-1]);
        *(prodNameArr + deleteLoc) = *(prodNameArr + (items-1));
        *(priceArr + deleteLoc) = *(priceArr + (items-1));
        *(QOHArr + deleteLoc) = *(QOHArr + (items-1));
        // -1 item
        items--;
        cerr << "Item deleted.\n\n";
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

void queryDB(const char prodIDArr[][PRODCHAR], const string *prodNameArr, const double *priceArr, const int *QOHArr, int filled)
{
    // display menu and get choice
    int choice = queryInstructions(), QOHMin, QOHMax;
    string prodName;
    double priceMin, priceMax;
    bool found;     // was their query found?

    while (choice != 5) { // 5 is to return to previous menu
        switch (choice) {
            case 1:
                displayID(prodIDArr, prodNameArr, priceArr, QOHArr, filled);
                break;
            case 2:
                cerr << "What is the product ID: ";
                getline(cin, prodName);

                printTableHeading();
                found = false;  // it has not been found yet
                for (int i = 0; i < filled; i++) {
                    if (*(prodNameArr + i) == prodName) {

                    found = true;   // ID is a match, print the info
                    printQueryResults(prodIDArr, prodNameArr, priceArr, QOHArr, i, filled);
                    }
                }

                if (!found)
                    cerr << "No product with that name was found.";

                cerr << endl << endl;
                break;
            case 3:
                cerr << "What is the minimum price: ";
                cin >> priceMin;
                cin.ignore();
                cerr << "What is the maximum price: ";
                cin >> priceMax;
                cin.ignore();

                printTableHeading();
                found = false;  // it has not been found yet
                for (int i = 0; i < filled; i++) {
                    if ( (*(priceArr + i) >= priceMin) && (*(priceArr + i) <= priceMax) ) {

                    found = true;   // ID is a match, print the info
                    printQueryResults(prodIDArr, prodNameArr, priceArr, QOHArr, i, filled);
                    }
                }

                if (!found)
                    cerr << "No product within that price range was found.";

                cerr << endl << endl;
                break;
            case 4:
                cerr << "What is the minimum quantity: ";
                cin >> QOHMin;
                cin.ignore();
                cerr << "What is the maximum quantity: ";
                cin >> QOHMax;
                cin.ignore();

                printTableHeading();
                found = false;  // it has not been found yet
                for (int i = 0; i < filled; i++) {
                    if ( (*(QOHArr + i) >= QOHMin) && (*(QOHArr + i) <= QOHMax) ) {
                    found = true;   // ID is a match, print the info
                    printQueryResults(prodIDArr, prodNameArr, priceArr, QOHArr, i, filled);
                    }
                }

                if (!found)
                    cerr << "No product within that price range was found.";

                cerr << endl << endl;
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = queryInstructions();   // bring up menu again
    }
    return;
}

void printQueryResults(const char prodIDArr[][PRODCHAR], const string *prodNameArr, const double *priceArr, const int *QOHArr, int i, int filled) {
    cerr << setw(11) << prodIDArr[i] << " | " << setw(15)
         << *(prodNameArr + i) + " | " << setw(10)
         << setprecision(2) << fixed << *(priceArr + i) << " | "
         << setw(8) << *(QOHArr + i);
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
