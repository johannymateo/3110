#include "Program.h"
#include "Database.h"
#include "Phone.h"
#include <iostream>

void Program::instructions()
{
    int decision;
    cerr << "1. Add Item" << endl << "2. Update Item Price" << endl
         << "3. Update Item Quantity" << endl << "4. Query Database" << endl
         << "5. Print Database" << endl << "6. Delete Item" << endl
         << "7. Exit Program" << endl
         << "Make a choice: ";
    cin >> decision;
    cerr << endl;

    // call the menu function if the answer isn't exit
    if (decision != 7)
        switchMenu(decision);
}

// what does the user want to do? Calls functions from DB to edit the array
void Program::switchMenu(int action)
{
    switch (action) {
        case 1:
            db.addItem();
            break;
        case 2:
            db.updatePrice();
            break;
        case 3:
            db.updateQOH();
            break;
        case 4:
            db.queryDB();
            break;
        case 5:
            db.printDB();
            break;
        case 6:
            db.deleteItem();
            break;
        default:
            cerr << "Please make a valid choice.\n";
    }

    instructions();    // bring up menu again
}
