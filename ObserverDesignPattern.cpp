#include <bits/stdc++.h>
using namespace std;

class ISubscriber {
public:
    virtual void update() = 0;
    virtual ~ISubscriber() = default;
};

class IYTChannel {
public:
    virtual void add(ISubscriber* sub) = 0;
    virtual void remove(ISubscriber* sub) = 0;
    // virtual void getUpdate(string& msg) = 0;
    virtual void notify() = 0;
    virtual ~IYTChannel() = default;
};

class YTChannel; // forward declaration

class Subscriber : public ISubscriber {
private:
    string name;
    IYTChannel* yt;
public:
    Subscriber(const string& name = "", IYTChannel* yt = nullptr) {
        this->name = name;
        this->yt = yt;
    }

    void update() override {
        // string msg;
        // yt->getUpdate(msg);
        cout << name << " got update: " << endl;
    }
};

class YTChannel : public IYTChannel {
private:
    string name;
    vector<ISubscriber*> subs;
public:
    YTChannel(const string& name) { this->name = name; }

    void add(ISubscriber* sub) override {
        subs.push_back(sub);
    }

    void remove(ISubscriber* sub) override {
        subs.erase(std::remove(subs.begin(), subs.end(), sub), subs.end());
    }

    // void getUpdate(string& msg) override {
    //     msg = "New video uploaded on " + name;
    // }

    void notify() override {
        for (auto s : subs) s->update();
    }
};

int main() {
    YTChannel* yt = new YTChannel("namo namo");

    ISubscriber* sub1 = new Subscriber("Om", yt);
    ISubscriber* sub2 = new Subscriber("Raja", yt);
    ISubscriber* sub3 = new Subscriber("Vola", yt);

    yt->add(sub1);
    yt->add(sub2);
    yt->add(sub3);

    yt->notify();

    yt->remove(sub2);

    yt->notify();

    delete yt;
    delete sub1;
    delete sub2;
    delete sub3;
}
