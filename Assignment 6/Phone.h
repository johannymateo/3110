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
    Phone();    // default constructor
    bool prodIDCheck(string);    // check if the format is valid
    // setters
    void setName(string name)
        { this->name = name; }
    void setPrice(double price)
        { this->price = price; }
    void setQOH(double QOH)
        { this->QOH = QOH; }

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
