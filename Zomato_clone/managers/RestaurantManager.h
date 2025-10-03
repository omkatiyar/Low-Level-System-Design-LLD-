#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include "../models/Restaurant.h"
#include <bits/stdc++.h>
using namespace std;

class RestaurantManager {
private:
    vector<Restaurant*> restaurants;
    static RestaurantManager* instance;

    RestaurantManager() {}

public:
    static RestaurantManager* getInstance() {
        if (!instance) instance = new RestaurantManager();
        return instance;
    }

    void addRestaurant(Restaurant* r) { restaurants.push_back(r); }

    vector<Restaurant*> searchByLocation(const string& loc) {
        vector<Restaurant*> v;
        for (auto r : restaurants) {
            if (r->getLocation() == loc) v.push_back(r);
        }
        return v;
    }
};

RestaurantManager* RestaurantManager::instance = nullptr;

#endif
