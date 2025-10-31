#include <bits/stdc++.h>
using namespace std;

class PaymentStrategy{
public:
virtual void pay(double amount)=0;
virtual ~PaymentStrategy(){}
};

class CreditCard: public PaymentStrategy{
private:
    double bankBalance;
public:
CreditCard(double bb): bankBalance(bb){}
void pay(double amount) override{
    cout<<" amount to be paid is "<<amount<<endl;
    if(amount<=bankBalance){
        cout<<" Amount is paid, "<<" remaaining balance is "<<bankBalance-amount<<" "<<endl;
    }
    else{
        cout<<" Insufficient Balance "<<endl;
    }
}
};

class UPI: public PaymentStrategy{
private:
    double bankBalance;
public:
UPI(double bb): bankBalance(bb){}
void pay(double amount) override{
    cout<<" amount to be paid is "<<amount<<" and bank balance is "<<bankBalance<<" "<<endl;
    if(amount<=bankBalance){
        bankBalance = bankBalance - amount;
        cout<<" Amount is paid, "<<" remaaining balance is "<<bankBalance<<" "<<endl;
    }
    else{
        cout<<" Insufficient Balance "<<endl;
    }
}
};

class NetBanking: public PaymentStrategy{
private:
    double bankBalance;
public:
NetBanking(double bb): bankBalance(bb){}
void pay(double amount) override{
    cout<<" amount to be paid is "<<amount<<" and bank balance is "<<bankBalance<<" "<<endl;
    if(amount<=bankBalance){
        bankBalance = bankBalance - amount;
        cout<<" Amount is paid, "<<" remaaining balance is "<<bankBalance<<" "<<endl;
    }
    else{
        cout<<" Insufficient Balance "<<endl;
    }
}
};

class PaymentFlatform{
private:
PaymentStrategy* ps;
public:
PaymentFlatform(){}
PaymentFlatform(PaymentStrategy* ps){
    this->ps = ps;
}
void payNow(double amount){
    ps->pay(amount);
    return;
}
};

int main(){
PaymentStrategy* ps = new UPI(2018.37);// account balance is initialized to 2018.37
PaymentFlatform* pf = new PaymentFlatform(ps);
pf->payNow(190.2); // paying 190.2
}




