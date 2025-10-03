#include <iostream>
using namespace std;

class Singleton {
private:
    static Singleton* instance;

    Singleton() {
        cout << "Singleton Constructor called. New Object created." << endl;
    }

public:
    static Singleton* getInstance() {
        if(instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }
};

Singleton* Singleton::instance = nullptr;

int main() {
    Singleton* s1 = Singleton::getInstance();
    s1 = nullptr;
    Singleton* s2 = Singleton::getInstance();
    if(s1==s2){
        cout<<" same objects"<<endl;
    }
    else
    cout<<" Different objects "<<endl;
   
}
