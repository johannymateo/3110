#ifndef PHONE_H
#define PHONE_H

#include <string>
using namespace std;

class Phone {

private:
    string prodID;
    string name;
    double price;
    int QOH;
public:
    // constructors
    Phone();
    Phone(string, string, double, int);
    // setters
    void setPrice(double price)
        { this->price = price; }
    void setQOH(int QOH)
        { this->QOH = QOH; };
    bool prodIDCheck(string);    // check if the format is valid


    // getters
    string getID() const
        { return prodID; }
    string getName() const
        { return name; }
    double getPrice() const
        { return price; }
    int getQOH() const
        { return QOH; }
};

#endif
