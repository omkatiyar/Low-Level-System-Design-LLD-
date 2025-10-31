#include <bits/stdc++.h>
using namespace std;

class Formatter{
public:
virtual string format()=0;
virtual ~Formatter(){}
};

class PlainText: public Formatter{
public:
    string format() override{
        string msg = " Plain Text Formatting done ";
        return msg;
    }
};

class HTML: public Formatter{
public:
    string format() override{
        string msg = " HTML Formatting done ";
        return msg;
    }
};

class Notification{
public:
virtual void notify(const string& msg) =0;
virtual ~Notification(){}
};

class NotificationFactory{
    private:
    static unordered_map<string, function<Notification*()>>& registry(){
        static unordered_map<string, function<Notification*()>> map ={
            {"Email", []() { return new Email(); }},
            {"SMS", []() { return new SMS(); }},
            {"Slack", []() { return new Slack(); }},
        };
        return map;
    }
    public:
    static Notification* getNotification(string type){
        auto& mp = registry();
        auto it=mp.find(type);
        if(it!=mp.end()){
            return mp[type]();
        }
        else{
            return new Email();
        }
    }
    static void addNotificationPlatform(string type, function<Notification*()> n){
        registry()[type] = n;
    }
};

struct NotificationRegistrar {
    NotificationRegistrar(const string& name, function<Notification*()> creator) {
        NotificationFactory::addNotificationPlatform(name, creator);
    }
};

class Email: public Notification{
    private:
    static NotificationRegistrar reg;
public:
void notify(const string& msg) override{
    cout<<msg<<" via email sent "<<endl;
}
};
/// //// reg function is used althouth it is never defined in the struct
NotificationRegistrar Email::reg("Email", []() { return new Email(); }); // no code change required in existing codebase 
// due to NotificationRegistrar struct


class SMS: public Notification{
    private:
    static NotificationRegistrar reg;
public:
void notify(const string& msg) override{
    cout<<msg<<" via sms sent "<<endl;
}
};
NotificationRegistrar SMS::reg("SMS", []() { return new SMS(); }); // no code change required in existing codebase 
// due to NotificationRegistrar struct


class Slack: public Notification{
    private:
    static NotificationRegistrar reg;
public:
void notify(const string& msg) override{
    cout<<msg<<" via slack sent "<<endl;
}
};
NotificationRegistrar Slack::reg("Slack", []() { return new Slack(); }); // no code change required in existing codebase 
// due to NotificationRegistrar struct


class Discord : public Notification {
public:
    void notify(const string& msg) override {
        cout << msg << " via Discord sent" << endl;
    }
private:
    static NotificationRegistrar reg;
};
/// //// reg function is used althouth it is never defined in the struct
NotificationRegistrar Discord::reg("Discord", []() { return new Discord(); }); // no code change required in existing codebase 
// due to NotificationRegistrar struct

class NotificationSender{
private:
    Formatter* f;
    Notification* n;
public:
    NotificationSender(Formatter* fr, Notification* nf): f(fr), n(nf){}
    void sendNotification(){
        cout<<" Sending notification "<<endl;
        string msg=f->format();
        n->notify(msg);
        return ;
    } 
};

// int main(){
//     Formatter* f = new HTML();
//     NotificationFactory* nf = new NotificationFactory();
//     Notification* n = nf->getNotification("Slack");
//     NotificationSender* ns = new NotificationSender(f,n);
//     ns->sendNotification();
// }
int main(){
    auto f = make_unique<HTML>();
    auto n = unique_ptr<Notification>(NotificationFactory::getNotification("Slack"));
    NotificationSender ns(f.get(), n.get());
    ns.sendNotification();

    auto fp=make_unique<PlainText>();
    n=unique_ptr<Notification>(NotificationFactory::getNotification("Discord"));
    NotificationSender nss(fp.get(),n.get());
    nss.sendNotification();

}