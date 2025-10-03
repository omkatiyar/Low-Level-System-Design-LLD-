#include <bits/stdc++.h>
using namespace std;
// Car is abstract class
class Car{
protected:
    string brand;
    string model;
    bool isEngineOn;
    int currSpeed;

public:
    Car(string b, string m){
        brand = b;
        model = m;
        this->isEngineOn = false;
        this->currSpeed = 0;
    }

    void startEngine(){
        isEngineOn = true;
        cout<<brand<<" "<<model<<" : engine has started "<<endl;
    }
    void stopEngine(){
        isEngineOn = false;
        currSpeed = 0;
        cout<<brand<<" "<<model<<" : engine stopped "<<endl;
    }
    virtual void accelerate()=0;
    virtual void brake() = 0;
    virtual ~Car(){}
};

class ManualCar: public Car{
private:
    int currGear;

public:
    // specialized constructor for ManualCar class
    ManualCar(string brand, string model): Car(brand, model){
        this->currGear=0;
    }
    
    // overriding the accelerate function here according to ManualCar // Dynamic Polymorphism
    void accelerate(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : engine stopped , i.e. cannot accelerate "<<endl;
            return;
        }
        currSpeed+=20;
        currGear++;
        cout<<brand<<" "<<model<<" : currSpeed is "<<currSpeed<<" and currGear is "<<currGear<<endl;
    }

    // overriding the brake function here according to ManualCar //Dynamic Polymorphism
    void brake(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : Engine is already off "<<endl;
            return;
        }
        currGear--;
        currSpeed = currSpeed-20;
        cout<<brand<<" "<<model<<" On brake : currSpeed is "<<currSpeed<<" & currGear is "<<currGear<<endl;
    }
};

class ElectricCar: public Car{
private:
    int batteryLevel;

public:
    // specialized constructor for Electric class
    ElectricCar(string brand, string model): Car(brand, model){
        this->batteryLevel = 100;
    }
    
    // overriding the accelerate function here according to ManualCar // Dynamic Polymorphism
    void accelerate(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : battery=0, i.e. cannot accelerate "<<endl;
            return;
        }
        currSpeed+=15;
        batteryLevel = batteryLevel - 10;
        cout<<brand<<" "<<model<<" : currSpeed is "<<currSpeed<<" and batteryLevel is "<<batteryLevel<<endl;
    }

    // overriding the brake function here according to Electric Car //Dynamic Polymorphism
    void brake(){
        if(!isEngineOn){
            cout<<brand<<" "<<model<<" : Engine is already off "<<endl;
            return;
        }
        batteryLevel = batteryLevel - 10;
        currSpeed = currSpeed-15;
        cout<<brand<<" "<<model<<" On brake : currSpeed is "<<currSpeed<<" & batteryLevel is "<<batteryLevel<<endl;
    }
};

int main(){
    Car* mn = new ManualCar("Ferrai", "Brara");
    mn->startEngine();
    mn->accelerate();
    mn->accelerate();
    mn->brake();
    Car* ec = new ElectricCar("Tesla","R1");
    ec->startEngine();
    ec->accelerate();
    ec->brake();
}