#include <bits/stdc++.h>
using namespace std;

class ICharacter{
public:
 virtual string getAbility() const = 0;
  virtual ~ICharacter(){}
};

class Mario: public ICharacter{
public:
    string getAbility() const override{
        return "mario";
    }
};

class CharDecorator: public ICharacter{
protected:
ICharacter* ch;
public:
CharDecorator(ICharacter* ch){
    this->ch=ch;
}
};

class HeightUp: public CharDecorator{
public:
HeightUp(ICharacter* ch): CharDecorator(ch){}

string getAbility() const override {
    string s = ch->getAbility();
    for (char &c : s) {
        c = toupper(c);
    }
    return s;
}
};

class GunUp: public CharDecorator{
public:
GunUp(ICharacter* ch): CharDecorator(ch){}

string getAbility() const override{
    string s = ch->getAbility()+" gun";
    return s;
}
};

int main(){
    ICharacter* mario = new Mario();
    string s = mario->getAbility();
    cout<<s<<endl;

    mario = new GunUp(mario);
    s= mario->getAbility();
    cout<<s<<endl;

    mario=new HeightUp(mario);
    s=mario->getAbility();
    cout<<s<<endl;
}