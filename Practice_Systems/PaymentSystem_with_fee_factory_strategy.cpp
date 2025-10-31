#include <bits/stdc++.h>
using namespace std;
class FeeStrategy{
    public:
virtual double getFee()=0;
~FeeStrategy(){}
};

class DomesticFee: public FeeStrategy{
double getFee() override{
    return 0.01;
}
};

class International: public FeeStrategy{
double getFee() override{
    return 0.03;
}
};

class PaymentStrategy{
public:
virtual void pay(double amount)=0;
virtual ~PaymentStrategy(){}
};

class UPI: public PaymentStrategy{
    private:
    double bankBalanace;
public:
    UPI(double bb):bankBalanace(bb){}

    void pay(double amount) override{
        if(amount<=bankBalanace){
            cout<<" Amount Rs: "<<amount<<" paid through UPI, remaining balance: "<<bankBalanace-amount<<endl;   
        }
        else{
            cout<<"Insufficient Balance"<<endl;
        }
    return;
    }
};

class CreditCard: public PaymentStrategy{
    private:
    double bankBalanace;
public:
    CreditCard(double bb):bankBalanace(bb){}

    void pay(double amount) override{
        if(amount<=bankBalanace){
            cout<<" Amount Rs: "<<amount<<" paid through credit Card, remaining balance: "<<bankBalanace-amount<<endl;   
        }
        else{
            cout<<"Insufficient Balance"<<endl;
        }
    return;
    }
};

class NetBanking: public PaymentStrategy{
    private:
    double bankBalanace;
public:
    NetBanking(double bb):bankBalanace(bb){}

    void pay(double amount) override{
        if(amount<=bankBalanace){
            cout<<" Amount Rs: "<<amount<<" paid through Net_Banking, remaining balance: "<<bankBalanace-amount<<endl;   
        }
        else{
            cout<<"Insufficient Balance"<<endl;
        }
    return;
    }
};

class PaymentMethod{  
public:

static unordered_map<string, function<PaymentStrategy*()>>& registry(double bankBalance) {
        static unordered_map<string, function<PaymentStrategy*()>> map = {
            {"UPI", [bankBalance]() { return new UPI(bankBalance); }},
            {"CreditCard", [bankBalance]() { return new CreditCard(bankBalance); }},
            {"Mortgage", [bankBalance]() { return new NetBanking(bankBalance); }}
        };
        return map;
    }

static PaymentStrategy* createMethod(string type,double bankBalance){
    unordered_map<string,function<PaymentStrategy* ()>>mp = registry(bankBalance);
    if(mp.find(type)==mp.end()){
        cout<<" No payment method chosen, defaulting to UPI"<<endl;
        return new UPI(bankBalance);
    }
    else{
        return mp[type]();
    }
}

static void registerNewPaymentMethod(const string& type,double bankBalance, function<PaymentStrategy*()> creator) {
        registry(bankBalance)[type] = creator;
    }
};

int main(){
FeeStrategy* fs = new DomesticFee();
double f = fs->getFee();
PaymentMethod* pm = new PaymentMethod();
PaymentStrategy* ps = pm->createMethod("NetBanking",1008.5);
ps->pay(8.5+f*8.5);
ps->pay(990+f*990);
return 0;
}