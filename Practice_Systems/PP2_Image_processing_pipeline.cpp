// Decorator pattern project of Image processing pipeline
#include <bits/stdc++.h>
using namespace std;

class IPicture {
public:
    virtual string operateOnImage() const = 0;
    virtual ~IPicture() {}
};

// Base Component
class JPG : public IPicture {
public:
    string operateOnImage() const override {
        return "image.jpg";
    }
};

// Decorator Base
class IDecorator : public IPicture {
protected:
    IPicture* pic;
public:
    IDecorator(IPicture* p) : pic(p) {}
    virtual ~IDecorator() { delete pic; }
};

// Concrete Decorators
class EnhanceExtra : public IDecorator {
public:
    EnhanceExtra(IPicture* p) : IDecorator(p) {}
    string operateOnImage() const override {
        return pic->operateOnImage() + " -> Enhanced";
    }
};

class MoreBlurr : public IDecorator {
public:
    MoreBlurr(IPicture* p) : IDecorator(p) {}
    string operateOnImage() const override {
        return pic->operateOnImage() + " -> Blurred";
    }
};

class WaterMark : public IDecorator {
public:
    WaterMark(IPicture* p) : IDecorator(p) {}
    string operateOnImage() const override {
        return pic->operateOnImage() + " -> Watermarked";
    }
};

int main() {
    IPicture* pic = new JPG();
    cout << pic->operateOnImage() << endl;

    pic = new EnhanceExtra(pic);
    cout << pic->operateOnImage() << endl;

    pic = new WaterMark(pic);
    cout << pic->operateOnImage() << endl;

    pic = new MoreBlurr(pic);
    cout << pic->operateOnImage() << endl;

    delete pic; // deletes the entire chain safely
}
