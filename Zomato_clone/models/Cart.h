#ifndef CART_H
#define CART_H

#include <bits/stdc++.h>
using namespace std;

#include "Restaurant.h"
#include "Menu.h"

class Cart {
private:
    vector<Menu*> items;   // ✅ keep items inside Cart
    Restaurant* restaurant;

public:
    Cart(vector<Menu*> items = {}, Restaurant* r = nullptr) {
        this->items = items;
        this->restaurant = r;
    }

    void setRestaurant(Restaurant* r) { restaurant = r; }
    Restaurant* getRestaurant() { return restaurant; }

    void addToCart(Menu* m) { items.push_back(m); }
    vector<Menu*> getItems() { return items; }

    double calculateTotal() {
        double total = 0;
        for (auto m : items) total += m->getPrice();
        return total;
    }

    bool isEmpty() { return items.empty(); }
    void clear() { items.clear(); }
};

#endif
