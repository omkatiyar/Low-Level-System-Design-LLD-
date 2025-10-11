#include <iostream>
#include <string>
using namespace std;

// ===== Abstract Ride Strategy =====
class Ride {
public:
    virtual string selectRide() = 0;
    virtual double computeFare(double km, bool isPeakHour) = 0;
    virtual ~Ride() {}
};

// ===== Concrete Ride Strategies =====
class Bike : public Ride {
public:
    string selectRide() override {
        return "Bike";
    }
    double computeFare(double km, bool isPeakHour) override {
        return isPeakHour ? km * 12 : km * 10;
    }
};

class Car : public Ride {
public:
    string selectRide() override {
        return "Car";
    }
    double computeFare(double km, bool isPeakHour) override {
        return isPeakHour ? km * 20 : km * 15;
    }
};

class XUV : public Ride {
public:
    string selectRide() override {
        return "XUV";
    }
    double computeFare(double km, bool isPeakHour) override {
        return isPeakHour ? km * 30 : km * 25;
    }
};

// ===== Time Context =====
class TimeOfHour {
public:
    virtual bool isPeakHour() = 0;
    virtual ~TimeOfHour() {}
};

class PeakTime : public TimeOfHour {
public:
    bool isPeakHour() override {
        return true;
    }
};

class NonPeakTime : public TimeOfHour {
public:
    bool isPeakHour() override {
        return false;
    }
};

// ===== Distance Context =====
class Distance {
    double km;
public:
    Distance(double km) : km(km) {}
    double getDistance() const {
        return km;
    }
};

// ===== Uber Context (uses Strategy) =====
class Uber {
    Distance* distance;
    TimeOfHour* toh;
    Ride* ride;
public:
    Uber(Distance* distance, TimeOfHour* toh, Ride* ride)
        : distance(distance), toh(toh), ride(ride) {}

    double calculateFare() {
        double km = distance->getDistance();
        bool peak = toh->isPeakHour();
        double fare = ride->computeFare(km, peak);
        cout << ride->selectRide() << " Fare (km=" << km << ", peak=" << (peak ? "yes" : "no") << "): ₹" << fare << endl;
        return fare;
    }
};

int main() {
    Distance* distance = new Distance(8.0);
    TimeOfHour* time = new PeakTime();
    Ride* ride = new Car();

    Uber* uber = new Uber(distance, time, ride);
    uber->calculateFare();

    // Clean up
    delete distance;
    delete time;
    delete ride;
    delete uber;

    return 0;
}
