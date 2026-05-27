#include <iostream>
#include <string>
using namespace std;

// ===== Base Component =====
class Coffee {
public:
    virtual string createCoffee() const = 0;
    virtual ~Coffee() {}
};

// ===== Concrete Components =====
class NormalCoffee : public Coffee {
public:
    string createCoffee() const override {
        return "Normal Coffee";
    }
};

class Latte : public Coffee {
public:
    string createCoffee() const override {
        return "Latte";
    }
};

class BlackCoffee : public Coffee {
public:
    string createCoffee() const override {
        return "Black Coffee";
    }
};

// ===== Abstract Factory =====
class ICoffeeFactory {
public:
    virtual Coffee* getCoffee(const string& type) const = 0;
    virtual ~ICoffeeFactory() {}
};

// ===== Concrete Factory =====
class CoffeeFactory : public ICoffeeFactory {
public:
    Coffee* getCoffee(const string& type) const override {
        if (type == "Normal")
            return new NormalCoffee();
        else if (type == "Latte")
            return new Latte();
        else
            return new BlackCoffee();
    }
};

// ===== Decorator Base =====
class CoffeeDecorator : public Coffee {
protected:
    Coffee* coffee;
public:
    CoffeeDecorator(Coffee* c) : coffee(c) {}
    virtual ~CoffeeDecorator() { delete coffee; }
};

// ===== Concrete Decorators =====
class Milk : public CoffeeDecorator {
public:
    Milk(Coffee* c) : CoffeeDecorator(c) {}
    string createCoffee() const override {
        return coffee->createCoffee() + " + Milk";
    }
};

class Sugar : public CoffeeDecorator {
public:
    Sugar(Coffee* c) : CoffeeDecorator(c) {}
    string createCoffee() const override {
        return coffee->createCoffee() + " + Sugar";
    }
};

class WhippedCream : public CoffeeDecorator {
public:
    WhippedCream(Coffee* c) : CoffeeDecorator(c) {}
    string createCoffee() const override {
        return coffee->createCoffee() + " + Whipped Cream";
    }
};

class CoffeeShop{
    private:
    ICoffeeFactory* cf;
    Coffee* c;
    public:
    Coffee* takeOrder(){
        string coffeeType;
        vector<string>addOns={"Milk","WhippedCream"};
        cin>>coffeeType;
        cf = new CoffeeFactory();
        c = cf->getCoffee(coffeeType);
        for(auto a: addOns){
            if(a=="Milk")
            c = new Milk(c);
            else if(a=="Sugar")
            c = new Sugar(c);
            else if(a == "WhippedCream")
            c = new WhippedCream(c);
            else{}
        }
        return c;
    }
};

// ===== Main =====
int main() {
    // Create factory
    // ICoffeeFactory* factory = new CoffeeFactory();

    // // Step 1: Create a base coffee from factory
    // Coffee* myCoffee = factory->getCoffee("Latte");

    // // Step 2: Add decorators dynamically
    // myCoffee = new Milk(myCoffee);
    // myCoffee = new Sugar(myCoffee);
    // myCoffee = new WhippedCream(myCoffee);

    // // Step 3: Print final decorated coffee
    // cout << "Your Order: " << myCoffee->createCoffee() << endl;

    // // Clean up memory
    // delete myCoffee;
    // delete factory;
    CoffeeShop cs;
    Coffee* c = cs.takeOrder();
    cout<<"Your order: "<<c->createCoffee()<<endl;
    return 0;
}
