#ifndef NOTIFICATION_SERVICE_H
#define NOTIFICATION_SERVICE_H

#include "../models/Order.h"
#include "../models/Menu.h"
#include <bits/stdc++.h>
using namespace std;

class NotificationService {
public:
    static void notifyUser(Order* order) {
        cout << "\nNotification: " << order->getType() << " order placed." << endl;
        cout << "Order ID: " << order->getOrderId() << endl;
        cout << "User: " << order->getUser()->getName() << endl;
        cout << "Restaurant: " << order->getRestaurant()->getName() << endl;
        cout << "Items:" << endl;
        for (auto m : order->getMenuItems()) {
            cout << " - " << m->getName() << " : " << m->getPrice() << endl;
        }
        cout << "Total: " << order->getTotalAmount() << endl;
        cout << "Scheduled: " << order->getScheduledTime() << endl;
    }
};

#endif
