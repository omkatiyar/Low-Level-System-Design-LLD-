#include <bits/stdc++.h>
using namespace std;
class Region{
    public:
    virtual double calculatePrice(double productPrice, bool customerType)=0;
    virtual ~Region(){}
};

class India : public Region{
string region;
public:
India(){}
India(string r):region(r){}
double calculatePrice(double productPrice, bool customerType) override{
    double price = productPrice;
    if(customerType==true){
        price = 1.25*price;
    }
    else
    price = 1.3*price;
    return price;
}
};

class USA: public Region{
public:
double calculatePrice(double productPrice, bool customerType) override{
    double price = productPrice;
    if(customerType==true){
        price = 1.4 * price;
    }
    else
    price = 1.5 * price;
    return price;
}
};

class Dubai: public Region{
public:
double calculatePrice(double productPrice, bool customerType) override{
    return productPrice;
    // if(customerType==true){
    //     price = 1.4 * price;
    // }
    // else
    // price = 1.5 * price;
    // return price;
}
};

class Product{
    public:
    virtual double getPrice() = 0;
    virtual string getName() = 0;
    virtual string getDescription(string productName="") = 0;
    virtual ~Product(){}
};

class WashingMachine: public Product{
private:
string name;
double price;
public:
string description;
WashingMachine(string name, double price, string description=""): name(name),price(price), description(description){}
double getPrice() override {
    return price;
}
string getName() override{
    return name;
}
string getDescription(string productName="") override {
    return description;
}
};

class Machis: public Product{
private:
string name;
double price;
public:
string description;
Machis(string name, double price, string description=""): name(name),price(price), description(description){}
double getPrice() override {
    return price;
}
string getName() override {
    return name;
}
string getDescription(string productName="") override {
    return description;
}
};

class CustomerType{
public:
virtual bool customerType(string rating="")=0; // rating is from 0 to 5
virtual ~CustomerType(){}
};

class GoodCustomer: public CustomerType{// good customer will have rating >=4.0
    public:
    bool customerType(string rating="") override {
        return true;
    }
};

class BadCustomer: public CustomerType{ // bad customer will have rating < 4
    public:
    bool customerType(string rating="") override {
        return false;
    }
};

class Amazon{
    Region* region;
    Product* product;
    CustomerType* ct;
    public:
    Amazon(Region* reg, Product* prod, CustomerType* ct):region(reg), product(prod), ct(ct){}
    double calculateTotalPrice(){
        double productPrice = product->getPrice();
        string name = product->getName();
        bool isGood = ct->customerType();
        double total = region->calculatePrice(productPrice,isGood);
        cout<<" Total product price for "<<name<<" is "<<total<<" as customer is "<<isGood<<endl;
        return total;
    }
};

int main(){
    Region* r = new India();
    Product* washingMachine = new WashingMachine("LG", 9999.99);
    Product* fire = new Machis("FIRE", 10);
    CustomerType* ct = new BadCustomer();
    // bool customerGood = ct->customerType();
    Amazon* am = new Amazon(r, washingMachine, ct);
    double total = am->calculateTotalPrice();
    cout<<" TTTTOOOOOTTTAAAAALLLLL ::::: "<<total<<endl;
    am= new Amazon(r,fire,ct);
    double t2 = am->calculateTotalPrice();
}