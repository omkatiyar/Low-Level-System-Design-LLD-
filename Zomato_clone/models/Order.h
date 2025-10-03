#ifndef ORDER_H
#define ORDER_H

#include <bits/stdc++.h>
using namespace std;

#include "Menu.h"
#include "User.h"
#include "Restaurant.h"
#include "../utils/TimeUtils.h"
#include "../strategies/PaymentStrategy.h"

class Order {
private:
    int orderId;
    User* user;
    Restaurant* restaurant;
    vector<Menu*> items;
    PaymentStrategy* ps;
    double totalAmount;
    string scheduledTime;

public:
    Order() {}
    Order(User* user, Restaurant* restaurant, vector<Menu*> items, double totalAmount, PaymentStrategy* ps = nullptr, int orderId = 0) {
        this->orderId = orderId;
        this->user = user;
        this->restaurant = restaurant;
        this->items = items;
        this->ps = ps;
        this->totalAmount = totalAmount;
    }

    virtual string getType() = 0;
    virtual ~Order() {}

    int getOrderId() { return orderId; }
    void setOrderId(int id) { orderId = id; }

    User* getUser() { return user; }
    void setUser(User* u) { user = u; }

    Restaurant* getRestaurant() { return restaurant; }
    void setRestaurant(Restaurant* res) { restaurant = res; }

    vector<Menu*> getMenuItems() { return items; }
    void setMenuItems(const vector<Menu*>& items) { this->items = items; }

    PaymentStrategy* getPaymentStrategy() { return ps; }
    void setPaymentStrategy(PaymentStrategy* p) { ps = p; }

    double getTotalAmount() { return totalAmount; }
    void setTotalAmount(double amount) { totalAmount = amount; }

    string getScheduledTime() { return scheduledTime; }
    void setScheduledTime(const string& scheduledTime) { this->scheduledTime = scheduledTime; }

    bool processPayment(double amount) {
        if (ps) {
            ps->pay(amount);
            cout << "Amount Paid" << endl;
            return true;
        } else {
            cout << "Please select payment mode first" << endl;
            return false;
        }
    }
};

#endif
