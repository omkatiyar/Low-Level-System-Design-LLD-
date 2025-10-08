#include <bits/stdc++.h>
using namespace std;

// ===== Base Class =====
class Notification {
public:
    virtual void notify() = 0;
    virtual ~Notification() {}
};

// ===== Derived Classes =====
class SMSNotify : public Notification {
    string sms;
public:
    SMSNotify(string sms) : sms(sms) {}
    void notify() override {
        cout << "SMS: " << sms << endl;
    }
};

class EmailNotify : public Notification {
    string mail;
public:
    EmailNotify(string mail) : mail(mail) {}
    void notify() override {
        cout << "Email: " << mail << endl;
    }
};

// ===== Sender Class =====
class SendNot {
    Notification* n;   // polymorphic pointer
public:
    SendNot(Notification* n = nullptr) {
        this->n = n;
    }
    void sendNotification() {
        if (n) n->notify();
        else cout << "No notification set!" << endl;
    }
};

int main() {
    Notification* email = new EmailNotify("Mail sent to om.katiyar");
    Notification* sms   = new SMSNotify("SMS sent to Om");

    SendNot sn1(email);
    sn1.sendNotification();  // Email

    SendNot sn2(sms);
    sn2.sendNotification();  // SMS

    delete email;
    delete sms;
    return 0;
}
