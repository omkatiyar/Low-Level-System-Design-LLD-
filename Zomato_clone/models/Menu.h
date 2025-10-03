#ifndef MENU_H
#define MENU_H

#include <bits/stdc++.h>
using namespace std;

class Menu {
private:
    static int menuId;
    int code;
    string name;
    double price;

public:
    Menu() {}
    Menu(const string& name, double price) {
        this->name = name;
        this->price = price;
        code = ++menuId;
    }

    int getCode() {
        return code;
    }

    void setCode(int c) {
        code = c;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    void updateName(const string& naam) {
        name = naam;
    }

    void updatePrice(double p) {
        price = p;
    }
};

int Menu::menuId = 0;

#endif
