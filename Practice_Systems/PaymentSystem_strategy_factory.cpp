#include <bits/stdc++.h>
using namespace std;

class PaymentStrategy{
public:
virtual void pay(double amount)=0;
virtual ~PaymentStrategy(){}
};

class UPI: public PaymentStrategy{
public:
void pay(double amount) override{
 cout<<" Amount Rs: "<<amount<<" paid through UPI "<<endl;   
 return;
}
};

class CreditCard: public PaymentStrategy{
public:
void pay(double amount) override{
 cout<<" Amount Rs: "<<amount<<" paid through credit card "<<endl;   
 return;
}
};

class NetBanking: public PaymentStrategy{
public:
void pay(double amount) override{
 cout<<" Amount Rs: "<<amount<<" paid through net banking "<<endl;   
 return;
}
};

class PaymentMethod{
public:
static PaymentStrategy* createMethod(string type){
    // if(type=="UPI")
    // return new UPI();
    // else if(type=="net banking")
    // return new NetBanking();
    // else
    // return new CreditCard();
    unordered_map<string,function<PaymentStrategy* ()>>mp = {
        {"UPI",[](){return new UPI();}},
        {"NetBanking", [](){return new NetBanking();}},
        {"CreditCard", [](){return new CreditCard();}}
    };
    if(mp.find(type)==mp.end()){
        cout<<" No payment method chosen, defaulting to UPI"<<endl;
        return new UPI();
    }
    else{
        return mp[type]();
    }
}
};

int main(){
PaymentMethod* pm = new PaymentMethod();
PaymentStrategy* ps = pm->createMethod("NetBanking");
ps->pay(189.23);
return 0;
}