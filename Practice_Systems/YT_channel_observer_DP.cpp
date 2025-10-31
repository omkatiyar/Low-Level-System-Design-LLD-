#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

class IYtChannel;

class ISubscriber {
public:
    virtual void update(string msg) = 0;
    virtual string getName() = 0;
    virtual ~ISubscriber() = default;
};

class Subscriber : public ISubscriber {
private:
    string name;
public:
    Subscriber(string name) : name(name) {}
    
    string getName() override {
        return this->name;
    }

    void update(string msg) override {
        cout << "[" << name << "] " << msg << endl;
    }
};

class IYtChannel {
public:
    virtual void subscribe(ISubscriber* sub) = 0;
    virtual void unsubscribe(ISubscriber* sub) = 0;
    virtual void notify(string videoName, double videoSize) = 0;
    virtual ~IYtChannel() = default;
};

class YtChannel : public IYtChannel {
private:
    string channelName;
    vector<ISubscriber*> subscribers;
    
public:
    YtChannel(string name) : channelName(name) {}
    
    ~YtChannel() {
        // Clean up subscribers if needed
        subscribers.clear();
    }

    void subscribe(ISubscriber* sub) override {
        // Check if subscriber already exists
        auto it = find(subscribers.begin(), subscribers.end(), sub);
        if (it == subscribers.end()) {
            subscribers.push_back(sub);
            cout << sub->getName() << " subscribed to " << channelName << endl;
        } else {
            cout << sub->getName() << " is already subscribed to " << channelName << endl;
        }
    }

    void unsubscribe(ISubscriber* sub) override {
        auto it = find(subscribers.begin(), subscribers.end(), sub);
        if (it != subscribers.end()) {
            cout << "Unsubscribing " << sub->getName() << " from " << channelName << endl;
            subscribers.erase(it);
        } else {
            cout << "Subscriber " << sub->getName() << " not found in " << channelName << endl;
        }
    }

    void notify(string videoName, double videoSize) override {
        string msg = "New video uploaded to '" + channelName + "': " + 
                    videoName + " (" + to_string(videoSize) + "MB)";
        
        cout << "\n=== Notification from " << channelName << " ===" << endl;
        for (auto sub : subscribers) {
            sub->update(msg);
        }
        cout << "=== End of notifications ===\n" << endl;
    }

    string getChannelName() const {
        return channelName;
    }

    int getSubscriberCount() const {
        return subscribers.size();
    }
};

int main() {
    // Create YouTube channels
    YtChannel* animalsChannel = new YtChannel("Animals Channel");
    YtChannel* cookingChannel = new YtChannel("Cooking Channel");

    // Create subscribers
    ISubscriber* sub1 = new Subscriber("Aron");
    ISubscriber* sub2 = new Subscriber("Shanon");
    ISubscriber* sub3 = new Subscriber("Bawaa");
    ISubscriber* sub4 = new Subscriber("Kaliya");

    // Subscribe subscribers to channels
    cout << "=== Setting up subscriptions ===" << endl;
    animalsChannel->subscribe(sub1);
    animalsChannel->subscribe(sub3);
    cookingChannel->subscribe(sub2);
    cookingChannel->subscribe(sub4);
    
    // Try subscribing same subscriber again
    animalsChannel->subscribe(sub1);

    cout << "\n=== Channel Info ===" << endl;
    cout << animalsChannel->getChannelName() << " has " << animalsChannel->getSubscriberCount() << " subscribers" << endl;
    cout << cookingChannel->getChannelName() << " has " << cookingChannel->getSubscriberCount() << " subscribers" << endl;

    // Notify subscribers about new videos
    cout << "\n=== Uploading new videos ===" << endl;
    animalsChannel->notify("Lion King Documentary", 450.5);
    cookingChannel->notify("Italian Pasta Recipe", 320.7);

    // Unsubscribe someone
    cout << "=== Managing subscriptions ===" << endl;
    animalsChannel->unsubscribe(sub1);
    
    // Notify again after unsubscribe
    animalsChannel->notify("Elephant Migration", 520.3);

    // Test unsubscribing non-existent subscriber
    animalsChannel->unsubscribe(sub2);

    cout << "\n=== Final Channel Info ===" << endl;
    cout << animalsChannel->getChannelName() << " has " << animalsChannel->getSubscriberCount() << " subscribers" << endl;
    cout << cookingChannel->getChannelName() << " has " << cookingChannel->getSubscriberCount() << " subscribers" << endl;

    // Clean up memory
    delete animalsChannel;
    delete cookingChannel;
    delete sub1;
    delete sub2;
    delete sub3;
    delete sub4;

    return 0;
}