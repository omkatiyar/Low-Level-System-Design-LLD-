#ifndef RESTAURANT_H
#define RESTAURANT_H

#include "Menu.h"
#include <bits/stdc++.h>
using namespace std;

class Restaurant {
private:
    static int nextResId;
    int resId;
    string name;
    string location;
    vector<Menu*> menu;

public:
    Restaurant(string name, string address, vector<Menu*> menu = {}) {
        this->name = name;
        this->location = address;
        this->menu = menu;
        this->resId = ++nextResId;
    }

    string getLocation() { return location; }
    string getName() { return name; }
    vector<Menu*> getMenu() { return menu; }

    void addMenuItem(Menu* m) { menu.push_back(m); }
    void setLocation(const string& loc) { location = loc; }
};

int Restaurant::nextResId = 0;

#endif
