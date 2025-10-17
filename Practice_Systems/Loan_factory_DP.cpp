#include <bits/stdc++.h>
using namespace std;

class Loan{
public:
virtual void getLoan(double amount )=0;
virtual ~Loan(){}
};

class HomeLoan: public Loan{
    private:
    double amount;
    public:
    HomeLoan(){}
    HomeLoan(double a){
    amount = a;
    }
    void getLoan(double amount) override{
        cout<<" Amount : "<<amount<<" has been issued for home loan "<<endl;
        return;
    }
};

class PersonalLoan: public Loan{
    public:
    void getLoan(double amount) override{
        cout<<" Amount : "<<amount<<" has been issued for Personal loan "<<endl;
        return;
    }
};

class Mortgage: public Loan{
    public:
    void getLoan(double amount) override{
        cout<<" Amount : "<<amount<<" has been issued as Mortgage "<<endl;
        return;
    }
};

class LoanFactory{
    public:
    Loan* getLoan(string type){
        static unordered_map<string, function<Loan* ()>>ln = {
            {"HomeLoan",[](){return new HomeLoan();}},
            {"PersonalLoan", [](){return new PersonalLoan();}},
            {"Mortgage", [](){return new Mortgage();}}
        };
        auto it=ln.find(type);
        if(it!=ln.end())
        return it->second();
        else{
            return new PersonalLoan();
        }
    }
};

int main(){
    LoanFactory* lf = new LoanFactory();
    Loan* loanType = lf->getLoan("HomeLoan");
    loanType->getLoan(24000);
}