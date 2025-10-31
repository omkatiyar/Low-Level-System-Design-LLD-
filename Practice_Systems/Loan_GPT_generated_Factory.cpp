#include <bits/stdc++.h>
using namespace std;

class Loan {
public:
    virtual void getLoan(double amount) = 0;
    virtual ~Loan() {}
};

class HomeLoan : public Loan {
public:
    void getLoan(double amount) override {
        cout << "Amount: ₹" << amount << " has been issued as a Home Loan.\n";
    }
};

class PersonalLoan : public Loan {
public:
    void getLoan(double amount) override {
        cout << "Amount: ₹" << amount << " has been issued as a Personal Loan.\n";
    }
};

class Mortgage : public Loan {
public:
    void getLoan(double amount) override {
        cout << "Amount: ₹" << amount << " has been issued as a Mortgage.\n";
    }
};

class LoanFactory {
    // Map of type → constructor function
    static unordered_map<string, function<Loan*()>>& registry() {
        static unordered_map<string, function<Loan*()>> map = {
            {"HomeLoan", []() { return new HomeLoan(); }},
            {"PersonalLoan", []() { return new PersonalLoan(); }},
            {"Mortgage", []() { return new Mortgage(); }}
        };
        return map;
    }

public:
    static Loan* createLoan(const string& type) {
        auto& mp = registry();
        auto it = mp.find(type);

        if (it != mp.end()) {
            return it->second();  // call constructor lambda
        } else {
            cout << "⚠️ Unknown loan type. Defaulting to Personal Loan.\n";
            return new PersonalLoan();
        }
    }

    // Optional: dynamic registration for new loan types at runtime
    static void registerLoan(const string& type, function<Loan*()> creator) {
        registry()[type] = creator;
    }
};

int main() {
    cout << "🏦 Welcome to Loan Portal\n";
    cout << "Enter Loan Type (HomeLoan / PersonalLoan / Mortgage): ";
    string loanType;
    cin >> loanType;

    Loan* loan = LoanFactory::createLoan(loanType);
    loan->getLoan(250000);

    delete loan;
    return 0;
}
