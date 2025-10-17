// #include <bits/stdc++.h>
// using namespace std;

// class IRestuarant{
// public:
// virtual void setName(string name)=0;
// virtual void showMenu()=0;
// virtual void setMenu(string dishName, double price)=0;
// virtual double getItemPrice(string item)=0;
// virtual ~IRestuarant(){}
// };

// class Restaurant: public IRestuarant {
//     string name;
//     vector<pair<string, double>> menu;   // {"Pizza", 250}, {"Burger", 150}

// public:
//     Restaurant(string n="", vector<pair<string,double>> m={}) : name(n), menu(m) {}

//     void setName(string name)override{
//         this->name = name;
//     }

//     void showMenu() override{
//         for (auto &item : menu)
//             cout << item.first << " - ₹" << item.second << endl;
//     }

//     void setMenu(string dishName, double price) override {
//         pair<string,double>p = make_pair(dishName, price);
//         auto it = find(menu.begin(),menu.end(),p);
//         if(it==menu.end())
//         menu.push_back(p);
//         else{
//             int idx = it-menu.begin();
//             menu[idx].first = dishName;
//             menu[idx].second = price;
//         }
//         return;
//     }

//     double getItemPrice(string item) override{
//         for (auto &p : menu)
//             if (p.first == item) return p.second;
//         return 0.0;
//     }
// };

// class VegRestuarant : public IRestuarant{
//     string name;
//     vector<pair<string, double>> menu;   // {"Pizza", 250}, {"Burger", 150}

// public:
//     VegRestuarant(string n="", vector<pair<string,double>> m={}) : name(n), menu(m) {}
    
//     void setName(string name)override{
//         this->name = name;
//     }
//     void showMenu() override{
//         for (auto &item : menu)
//             cout << item.first << " - ₹" << item.second << endl;
//     }

//     void setMenu(string dishName, double price) override {
//         pair<string,double>p = make_pair(dishName, price);
//         auto it = find(menu.begin(),menu.end(),p);
//         if(it==menu.end())
//         menu.push_back(p);
//         else{
//             int idx = it-menu.begin();
//             menu[idx].first = dishName;
//             menu[idx].second = price;
//         }
//         return;
//     }

//     double getItemPrice(string item) override {
//         for (auto &p : menu)
//             if (p.first == item) return p.second;
//         return 0.0;
//     }
// };

// class NonVegRestaurant : public IRestuarant {
//     string name;
//     vector<pair<string, double>> menu;   // {"Pizza", 250}, {"Burger", 150}

// public:
//     NonVegRestaurant(string n="", vector<pair<string,double>> m={}) : name(n), menu(m) {}
//     void setName(string name)override{
//         this->name = name;
//     }
//     void showMenu() override {
//         for (auto &item : menu)
//             cout << item.first << " - ₹" << item.second << endl;
//     }

//     void setMenu(string dishName, double price)override{
//         pair<string,double>p = make_pair(dishName, price);
//         auto it = find(menu.begin(),menu.end(),p);
//         if(it==menu.end())
//         menu.push_back(p);
//         else{
//             int idx = it-menu.begin();
//             menu[idx].first = dishName;
//             menu[idx].second = price;
//         }
//         return;
//     }

//     double getItemPrice(string item)override {
//         for (auto &p : menu)
//             if (p.first == item) return p.second;
//         return 0.0;
//     }
// };

// class RestuarantFactory{
//     IRestuarant* r;
// public:
// IRestuarant* getRestuarant(string type){
//     if(type=="veg")
//     return new VegRestuarant();
//     else if(type=="non_veg")
//     return new NonVegRestaurant();
//     else
//     return new Restaurant();
// }
// };


#include <bits/stdc++.h>
using namespace std;

// ======================== Strategy Pattern ========================
class PricingStrategy {
public:
    virtual double pay(double total) = 0;     // apply discount or charges
    virtual string getType() = 0;
    virtual ~PricingStrategy() {}
};

class RegularPricing : public PricingStrategy {
public:
    double pay(double total) override { return total; }
    string getType() override { return "Regular User (0% discount)"; }
};

class GoldPricing : public PricingStrategy {
public:
    double pay(double total) override { return total * 0.9; }  // 10% off
    string getType() override { return "Gold User (10% discount)"; }
};

class SuperPricing : public PricingStrategy {
public:
    double pay(double total) override { return total * 0.8; }  // 20% off
    string getType() override { return "Super User (20% discount)"; }
};

// ======================== Factory for User Pricing ========================
class UserFactory {
public:
    static PricingStrategy* getPricingStrategy(const string& userType) {
        if (userType == "regular") return new RegularPricing();
        if (userType == "gold") return new GoldPricing();
        if (userType == "super") return new SuperPricing();
        cout << "Unknown user type, defaulting to Regular.\n";
        return new RegularPricing();
    }
};

// ======================== Restaurant Interface ========================
class IRestaurant {
public:
    virtual void setMenu(const string& dish, double price) = 0;
    virtual void showMenu() = 0;
    virtual double getItemPrice(const string& dish) = 0;
    virtual void order(const vector<string>& items) = 0;
    virtual ~IRestaurant() {}
};

// ======================== Concrete Restaurant ========================
class VegRestaurant : public IRestaurant {
    vector<pair<string, double>> menu;
    PricingStrategy* pricing;

public:
    VegRestaurant(PricingStrategy* p) : pricing(p) {}

    void setMenu(const string& dish, double price) override {
        menu.push_back({dish, price});
    }

    void showMenu() override {
        cout << "\n📋 Veg Restaurant Menu:\n";
        for (auto& item : menu)
            cout << " - " << item.first << " : ₹" << item.second << endl;
    }

    double getItemPrice(const string& dish) override {
        for (auto& i : menu)
            if (i.first == dish) return i.second;
        return 0.0;
    }

    void order(const vector<string>& items) override {
        double total = 0;
        cout << "\n🛍️ Items Ordered:\n";
        for (auto& item : items) {
            double price = getItemPrice(item);
            if (price == 0)
                cout << "❌ " << item << " not found!\n";
            else {
                total += price;
                cout << "✅ " << item << " - ₹" << price << endl;
            }
        }

        cout << "\nSubtotal: ₹" << total << endl;
        double finalAmt = pricing->pay(total);
        cout << "User Type: " << pricing->getType() << endl;
        cout << "💰 Final Amount to Pay: ₹" << finalAmt << endl;
    }
};

// ======================== Factory for Restaurant ========================
class RestaurantFactory {
public:
    static IRestaurant* getRestaurant(const string& type, PricingStrategy* pricing) {
        if (type == "veg") return new VegRestaurant(pricing);
        // You can later add: NonVegRestaurant, PremiumRestaurant, etc.
        cout << "Unknown restaurant type, defaulting to Veg.\n";
        return new VegRestaurant(pricing);
    }
};

// ======================== MAIN FUNCTION ========================
int main() {
    cout << "===== Welcome to Zomato++ =====\n";
    cout << "Enter user type (regular / gold / super): ";
    string userType;
    cin >> userType;

    // Step 1: get pricing strategy
    PricingStrategy* pricing = UserFactory::getPricingStrategy(userType);
    // PricingStrategy* pricing = new GoldPricing(); -- here gold pricing applies for regular user
    // Step 2: create restaurant
    IRestaurant* r = RestaurantFactory::getRestaurant("veg", pricing);

    // Step 3: set menu
    r->setMenu("Paneer Butter Masala", 250);
    r->setMenu("Veg Biryani", 180);
    r->setMenu("Dal Makhani", 150);
    r->setMenu("Butter Naan", 40);

    // Step 4: display menu
    r->showMenu();

    // Step 5: take order (you can modify to take input interactively)
    vector<string> orderList = {"Paneer Butter Masala", "Butter Naan", "Veg Biryani"};
    r->order(orderList);

    delete r;
    delete pricing;
    return 0;
}
