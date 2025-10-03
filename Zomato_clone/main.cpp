#include <bits/stdc++.h>
#include "ZomatoApp.h"
using namespace std;

int main() {
    srand(time(nullptr));

    ZomatoApp app;
    User* user = new User("Om", "Delhi");

    cout << "User " << user->getName() << " is active from " << user->getLocation() << endl;

    vector<Restaurant*> restaurants = app.searchRestaurants(user->getLocation());
    if (restaurants.empty()) {
        cout << "Sorry, we are not present there yet!" << endl;
        return 0;
    }

    cout << "\nFound Restaurants:" << endl;
    for (auto r : restaurants) {
        cout << " - " << r->getName() << endl;
    }

    // pick first restaurant
    app.selectRestaurant(user, restaurants[0]);

    // add items to cart
    app.addToCart(user, "1");
    app.addToCart(user, "2");
    app.addToCart(user, "1");

    cout << "\nUser Cart:" << endl;
    app.printUserCart(user);

    // checkout with UPI
    Order* order = app.checkoutNow(user, new UPI("9876543210"), "Delivery");
    app.payForOrder(user, order);

    delete user;
    return 0;
}
