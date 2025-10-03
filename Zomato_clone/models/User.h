#ifndef USER_H
#define USER_H

#include "Cart.h"
#include <bits/stdc++.h>
using namespace std;

class User {
private:
    static int nextUserId;
    int userId;
    string name;
    string location;
    unique_ptr<Cart> cart;   // ✅ smart pointer

public:
    User(string n = "", string loc = "", Cart* c = nullptr, int id = 0) {
        name = n;
        location = loc;
        userId = (id == 0) ? ++nextUserId : id;

        // ✅ take ownership of Cart if provided, else create empty one
        if (c) cart.reset(c);
        else cart = make_unique<Cart>();
    }

    ~User() = default;   // ✅ no need for manual delete

    string getName() const { return name; }
    string getLocation() const { return location; }
    int getUserId() const { return userId; }

    Cart* getCart() { return cart.get(); }   // ✅ expose raw pointer safely

    void setLocation(const string& l) { location = l; }

    void setCart(Cart* c) { cart.reset(c); }  // ✅ safely replaces old cart
};

int User::nextUserId = 0;

#endif
