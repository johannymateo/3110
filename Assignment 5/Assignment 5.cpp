// Johanny Mateo
// CISC 3110 - Assignment 5
// Convert an array to vector

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <vector>
using namespace std;

// fn to add items to arrays, returns nothing and
// accepts prodIDVect, nameVect,priceVect, QOHVect,
// counter of current arr loc, and size of dynamic arrays
void addItem(vector<string> &, vector<string> &, vector<double> &, vector<int> &);
// fn to find index of productID, retuns index as int,
// accepts ptr to nameVect, prodName, and up to where is the arr filled
int findID(vector<string>, string);
// fn to update price, returns nothing
// accepts ptr to nameVect, ptr to priceVect, and array fill loc
void updateItem(vector<string>, vector<double> &);
// fn to update quantity, returns nothing
// accepts ptr to nameVect, ptr to QOHVect, and array fill loc
void updateItem(vector<string>, vector<int> &);
// fn to display item, returns nothing
// accepts ptr to nameVect, ptr to priceVect, ptr to QOHVect, and array fill loc
void displayID(vector<string>, vector<string>, vector<double>, vector<int>);
// fn to display query results, accepts all arrays, for loop i location, and fill
// returns nothing
void printQueryResults(vector<string>, vector<string>, vector<double>, vector<int>, int);
// fn to print DB, returns nothing
// accepts ptr to nameVect, ptr to priceVect, ptr to QOHVect, and array fill loc
void printDB(vector<string>, vector<string>, vector<double>, vector<int>);
// fn to display switch instructions, returns choice, accepts nothing
int instructions();
// fn to check for and correct prodName duplicate, returns true if it exists
// accepts ptr to nameVect, prodName by reference, and arr insert loc
bool dupeCheck(vector<string> &, string &);
// fn to check prod id format. accepts prod id char ptr
void prodIDCheck(string &);
// fn to delete item. Takes prodID, prodName, price, QOH, and filled
void deleteItem(vector<string> &, vector<string> &, vector<double> &, vector<int> &);
//fn to query databse, accepts all arrays and fill value
void queryDB(vector<string>, vector<string>, vector<double>, vector<int>);
// fn to print query switch instructions
int queryInstructions();
//function to print table heading in output
void printTableHeading();

int main()
{
    // items is used to keep track up to where the database is filled
    int choice;
    vector<string> prodIDVect;
    vector<string> nameVect;
    vector<double> priceVect;
    vector<int> QOHVect;

    // print the menu instructions
    choice = instructions();

    while (choice != 7) {       // 7 is exit; skip this loop and return to OS
        switch (choice) {
            case 1:
                addItem(prodIDVect, nameVect, priceVect, QOHVect);
                break;
            case 2:
                updateItem(prodIDVect, priceVect);
                break;
            case 3:
                updateItem(prodIDVect, QOHVect);
                break;
            case 4:
                queryDB(prodIDVect, nameVect, priceVect, QOHVect);
                break;
            case 5:
                printDB(prodIDVect, nameVect, priceVect, QOHVect);
                break;
            case 6:
                deleteItem(prodIDVect, nameVect, priceVect, QOHVect);
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = instructions();    // bring up menu again
    }

    return 0;
}

void addItem(vector<string> &prodIDVect, vector<string> &nameVect, vector<double> &priceVect, vector<int> &QOHVect)
{
    bool dupe;  // is there an uncorrected duplicate?
    string prodID, nameTemp;
    double priceTemp;
    int QOHTemp;

    cerr << "The product ID must be 4 characters. Two letters, followed by two numbers.\n";

    // while there are no duplicates (or they were corrected):
    while (!dupe) {
        cerr << "Item " << prodIDVect.size()+1 << endl;
        cerr << "Enter the product ID, type \"0\" to stop entry: ";
        cin >> prodID;

            if (prodID == "0")  // they do not wish to continue, return to menu
                return;
            else {  // they want to continue, resume entry
                prodIDCheck(prodID);  // make sure it is a valid prodID
                dupe = dupeCheck(prodIDVect, prodID);
                // if dupe is false, there are no dupes, continue with entry, else skip this; while loop will also be false, and fn will return
                if (!dupe) {         // there is no dupe, continue with entry
                    cerr << "Enter the product name: ";
                    cin.ignore();
                    getline(cin, nameTemp);
                    nameVect.push_back(nameTemp);
                    cerr << "Enter the price: ";
                    cin >> priceTemp;
                    priceVect.push_back(priceTemp);
                    cerr << "Enter the quantity: ";
                    cin >> QOHTemp;
                    QOHVect.push_back(QOHTemp);
                    cerr << endl;
                }
            }
        }
    cerr << endl;
    return;
}

int findID(vector<string> prodIDVect, string findID)
{
    for (int i = 0; i < prodIDVect.size(); i++)
        if ( prodIDVect[i] == findID)
            return i;   // if it is found, return that location
    return -1;          // -1 to know that product id wasn't found
}

void updateItem(vector<string> prodIDVect, vector<double> &priceVect)
{
    int editLoc;            // location of item to be updated
    string editID;
    double priceTemp;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(prodIDVect, editID);

    if (editLoc == -1) {            // ID not found
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new price: ";
        cin >> priceTemp;
        priceVect[editLoc] = priceTemp;
        cerr << "\nProduct ID: "<< prodIDVect[editLoc]
             << "\nUpdated price: " << priceVect[editLoc] << "\n\n";
        return;
    }
}

void updateItem(vector<string> prodIDVect, vector<int> &QOHVect)
{
    int editLoc;            // row of item to be updated
    string editID;
    int QOHTemp;

    cerr << "What is the product ID: ";
    cin >> editID;
    editLoc = findID(prodIDVect, editID);

    if (editLoc == -1) {            // ID not found
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {
        cerr << "Enter the new quantity: ";
        cin >> QOHTemp;
        QOHVect[editLoc] = QOHTemp;
        cerr << "\nProduct ID: " << prodIDVect[editLoc]
             << "\nUpdated quantity: " << QOHVect[editLoc] << "\n\n";
        return;
    }
}

void displayID(vector<string> prodIDVect, vector<string> nameVect, vector<double> priceVect, vector<int> QOHVect)
{
    int loc;            // loc to be displayed
    string displayID;

    cerr << "What is the product ID: ";
    cin >> displayID;
    loc = findID(prodIDVect, displayID);

    if (loc == -1) {        // ID not found
        cerr << "The product ID was not found.\n\n";
        return;
    }
    else {
        cerr << "\nProduct ID: " << prodIDVect[loc]
             << "\nProduct Name: " << nameVect[loc]
             << "\nPrice: " << priceVect[loc]
             << "\nQuantity: " << QOHVect[loc] << "\n\n";
    return;
    }
}

void printDB(vector<string> prodIDVect, vector<string> nameVect, vector<double> priceVect, vector<int> QOHVect)
{
    printTableHeading();

    for (int i = 0; i < prodIDVect.size(); i++) {
        cerr << setw(11) << prodIDVect[i] << " | " << setw(15) << nameVect[i] + " | "
             << setw(10) << setprecision(2) << fixed << priceVect[i] << " | "
             << setw(8) << QOHVect[i] << endl;
    }
    cerr << endl << endl;
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
    cerr << endl;
    return decision;
}

bool dupeCheck(vector<string> &prodIDVect, string &prodID)
{
    char ans;           // enter new ID?
    bool exists;        // does a dupe exist?

    do {
        // -1 means prodID doesn't exist
        if (findID(prodIDVect, prodID) != -1) {
            exists = true;
            cerr << "This item already exists."
                 << " Would you like to input a new product ID? (Y/N): ";
            cin >> ans;

            if (ans == 'y' || ans == 'Y') {
                cerr << "Enter the new product ID: ";
                cin >> prodID;
                prodIDCheck(prodID);
            }
        }
        else
            exists = false;
    } while ((ans == 'y' || ans == 'Y') && exists);
    // while there was a dupe found and they decided to input a new ID

    if (exists)         // there is an uncorrected dupe, return true
        return true;
    else {                // there are no dupes, or it was corrected, push it to the vector & return false
        prodIDVect.push_back(prodID);
        return false;
    }
}

void prodIDCheck(string &prodID)
{
    while (
        !(isalpha(prodID[0]) && isalpha(prodID[1])) ||   // is it a letter?
        !(isdigit(prodID[2]) && isdigit(prodID[3])) ||   // is a number?
        !(prodID.length() == 4)                          // is it 4 chars long?
    ) {
        cerr << "Please enter 4 characters in the format AA00: ";
        cin >> prodID;  // re-enter in correct format
        }
    return;
}

void deleteItem(vector<string> &prodIDVect, vector<string> &nameVect, vector<double> &priceVect, vector<int> &QOHVect)
{
    int deleteLoc;
    string deleteID;

    cerr << "What is the product ID: ";
    cin >> deleteID;
    deleteLoc = findID(prodIDVect, deleteID);

    if (deleteLoc == -1) {
        cerr << "Product ID not found.\n\n";
        return;
    }
    else {  // iterate to the correct location & delete it
        prodIDVect.erase(prodIDVect.begin() + deleteLoc);
        nameVect.erase(nameVect.begin() + deleteLoc);
        priceVect.erase(priceVect.begin() + deleteLoc);
        QOHVect.erase(QOHVect.begin() + deleteLoc);
        cerr << "Item deleted.\n\n";
        return;
    }
}


void queryDB(vector<string> prodIDVect, vector<string> nameVect, vector<double> priceVect, vector<int> QOHVect)
{
    // display menu and get choice
    int choice = queryInstructions(), QOHMin, QOHMax;
    string prodName;
    double priceMin, priceMax;
    bool found;     // was their query found?

    while (choice != 5) { // 5 is to return to previous menu
        switch (choice) {
            case 1:
                displayID(prodIDVect, nameVect, priceVect, QOHVect);
                break;
            case 2:
                cerr << "What is the product name: ";
                cin.ignore();
                getline(cin, prodName);

                printTableHeading();
                found = false;  // it has not been found yet
                for (int i = 0; i < prodIDVect.size(); i++) {
                    if (nameVect[i] == prodName) {
                    found = true;   // ID is a match, print the info
                    printQueryResults(prodIDVect, nameVect, priceVect, QOHVect, i);
                    cerr << endl;
                    }
                }

                if (!found)
                    cerr << "No product with that name was found.\n";

                cerr << endl;
                break;
            case 3:
                cerr << "What is the minimum price: ";
                cin >> priceMin;
                cerr << "What is the maximum price: ";
                cin >> priceMax;

                printTableHeading();
                found = false;  // it has not been found yet
                for (int i = 0; i < prodIDVect.size(); i++) {
                    if ( (priceVect[i] >= priceMin) && (priceVect[i] <= priceMax) ) {
                    found = true;   // ID is a match, print the info
                    printQueryResults(prodIDVect, nameVect, priceVect, QOHVect, i);
                    cerr << endl;
                    }
                }

                if (!found)
                    cerr << "No product within that price range was found.\n";

                cerr << endl;
                break;
            case 4:
                cerr << "What is the minimum quantity: ";
                cin >> QOHMin;
                cerr << "What is the maximum quantity: ";
                cin >> QOHMax;

                printTableHeading();
                found = false;  // it has not been found yet
                for (int i = 0; i < prodIDVect.size(); i++) {
                    if ( (QOHVect[i] >= QOHMin) && (QOHVect[i] <= QOHMax) ) {
                    found = true;   // ID is a match, print the info
                    printQueryResults(prodIDVect, nameVect, priceVect, QOHVect, i);
                    cerr << endl;
                    }
                }

                if (!found)
                    cerr << "No product within that quantity range was found.\n";

                cerr << endl;
                break;
            default:
                cerr << "Please make a valid choice.\n";
        }
        choice = queryInstructions();   // bring up menu again
    }
    return;
}

void printQueryResults(vector<string> prodIDVect, vector<string> nameVect, vector<double> priceVect, vector<int> QOHVect, int i) {
    cerr << setw(11) << prodIDVect[i] << " | " << setw(15)
         << nameVect[i] + " | " << setw(10)
         << setprecision(2) << fixed << priceVect[i] << " | "
         << setw(8) << QOHVect[i];
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
