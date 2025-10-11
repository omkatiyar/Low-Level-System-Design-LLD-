// Strategy Pattern project -- its violated but I tried and it worked. SOLID principles are not followed

// This code breaks SRP as Uber class knows all about distance, timeOfHour, ride
/*   This code also breaks Open - close principle because When we want to add a new ride type,
  you’ll have to go inside Uber::calculateFair() and add a new typeid branch. */
/*   The below code also violates DIP as Uber depends directly on concrete logic (typeid(*ride) == typeid(Bike)) instead of 
delegating the pricing logic to the Ride objects   */
#include <bits/stdc++.h>
using namespace std;

class Ride{
public:
virtual string selectRide()=0;
virtual ~Ride(){}
};

class Bike: public Ride{
private:
string ride;
public:
Bike(string r=""):ride(r){}
    string selectRide() override{
        return "Bike";
    }
};

class Car: public Ride{
private:
string ride;
public:
Car(string r=""):ride(r){}
    string selectRide() override{
        return "Car";
    }
};

class XUV: public Ride{
private:
string ride;
public:
XUV(string r=""):ride(r){}
    string selectRide() override{
        return "XUV";
    }
};

class TimeofHour{
public:
virtual bool isPeakHour()=0;
virtual ~TimeofHour(){}
};

class PeakTime: public TimeofHour{
public:
bool isPeakHour() override{
    return true;
}
};

class NonPeakTime: public TimeofHour{
public:
bool isPeakHour() override{
    return false;
}
};

class Distance{
    private:
double km;
public:
Distance(double km):km(km){}
double getDistance(){
    return km;
}
};

class Uber{
    protected:
    Distance* distance;
    TimeofHour* toh;
    Ride* ride;
    public:
    Uber(Distance* distance, TimeofHour* toh,Ride* ride){
        this->distance = distance;
        this->toh = toh;
        this->ride = ride;
    }
    double calculateFair(){
        double fair=0.0;
        double km = distance->getDistance();
        if(toh->isPeakHour()){ // in peakTime, per distance rate will be Rs 12/km for bike, 20 Rs/km for car and 30 Rs/km for XUV
            if (typeid(*ride) == typeid(Bike))
            fair=km*12;
            else if((typeid(*ride) == typeid(Car))){
                fair=km*20;
            }
            else{
                fair = km*30;
            }
        }
        else{ // normal rates apply
            if (typeid(*ride) == typeid(Bike))
            fair=km*10;
            else if((typeid(*ride) == typeid(Car))){
                fair=km*15;
            }
            else{
                fair = km*25;
            }
        }
        cout<<" fair is "<<fair<<" "<<endl;
        return fair;
    }
};
int main(){
    Ride* ride = new XUV();
    TimeofHour* toh = new NonPeakTime();
    Distance* distance = new Distance(8.0);
    Uber* uber = new Uber(distance, toh, ride);
    double fair=uber->calculateFair();
    // cout<<" fair is "<<fair<<endl;
}