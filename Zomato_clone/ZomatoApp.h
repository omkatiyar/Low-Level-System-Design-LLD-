#ifndef ZOMATO_APP_H
#define ZOMATO_APP_H

#include <bits/stdc++.h>
using namespace std;

#include "models/User.h"
#include "models/Restaurant.h"
#include "models/Cart.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "strategies/PaymentStrategy.h"
#include "strategies/UPI.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduleOrderFactory.h"
#include "services/NotificationService.h"

class ZomatoApp {
public:
    ZomatoApp() {
        initializeRestaurants();
    }

    void initializeRestaurants() {
        Restaurant* bikaner = new Restaurant("Bikaner", "Delhi");
        bikaner->addMenuItem(new Menu("Samosa", 20));
        bikaner->addMenuItem(new Menu("Chole Bhature", 120));

        Restaurant* thali = new Restaurant("Thali", "Delhi");
        thali->addMenuItem(new Menu("Normal Thali", 150));
        thali->addMenuItem(new Menu("Paneer Thali", 200));

        Restaurant* vadappa = new Restaurant("Vadappa", "Chennai");
        vadappa->addMenuItem(new Menu("Dosa", 80));
        vadappa->addMenuItem(new Menu("Uttapam", 120));
        vadappa->addMenuItem(new Menu("Idli", 60));

        RestaurantManager* rm = RestaurantManager::getInstance();
        rm->addRestaurant(bikaner);
        rm->addRestaurant(thali);
        rm->addRestaurant(vadappa);
    }

    vector<Restaurant*> searchRestaurants(const string& location) {
        return RestaurantManager::getInstance()->searchByLocation(location);
    }

    void selectRestaurant(User* user, Restaurant* restaurant) {
        user->getCart()->setRestaurant(restaurant);
    }

    void addToCart(User* user, const string& itemCode) {
        Restaurant* res = user->getCart()->getRestaurant();
        if (!res) {
            cout << "Please select a restaurant first!" << endl;
            return;
        }
        int code = stoi(itemCode);
        for (auto m : res->getMenu()) {
            if (m->getCode() == code) {
                user->getCart()->addToCart(m);
                break;
            }
        }
    }

    Order* checkoutNow(User* user, PaymentStrategy* ps, const string& orderType) {
        NowOrderFactory factory;
        return checkout(user, orderType, ps, &factory);
    }

    Order* checkoutSchedule(User* user, PaymentStrategy* ps, const string& orderType, const string& schedTime) {
        ScheduleOrderFactory factory(schedTime);
        return checkout(user, orderType, ps, &factory);
    }

    Order* checkout(User* user, const string& orderType, PaymentStrategy* ps, OrderFactory* factory) {
        if (user->getCart()->isEmpty()) {
            cout << "Cart is empty!" << endl;
            return nullptr;
        }

        Cart* userCart = user->getCart();
        Restaurant* res = userCart->getRestaurant();
        vector<Menu*> items = userCart->getItems();

        Order* order = factory->createOrder(user, res, ps, userCart, items, (string&)orderType);
        order->setOrderId(rand() % 10000 + 1);

        OrderManager::getInstance()->addOrder(order);
        return order;
    }

    void payForOrder(User* user, Order* order) {
        if (!order) return;
        bool isPaid = order->processPayment(order->getTotalAmount());
        if (isPaid) {
            NotificationService::notifyUser(order);
            user->getCart()->clear();
        }
    }

    void printUserCart(User* user) {
        for (auto m : user->getCart()->getItems()) {
            cout << " - " << m->getName() << " : " << m->getPrice() << endl;
        }
    }
};

#endif
