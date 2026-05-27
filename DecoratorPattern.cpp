#include <bits/stdc++.h>
using namespace std;

class ICharacter{
public:
virtual int getHeight()  = 0;
virtual int getWidth()  = 0;
 virtual string getAbility()  = 0;
  virtual ~ICharacter(){}
};

class Mario: public ICharacter{
int height = 10;
int width = 5;
public:

int getHeight()  override { return height; }
int getWidth()  override { return width; }
void setHeight(int h) { height = h; }
void setWidth(int w) { width = w; }
string getAbility()  override{
        return "mario";
    }
};

class CharDecorator: public Mario{
protected:
Mario* ch;
public:
CharDecorator(Mario* ch){
    this->ch=ch;
}
};

class HeightUp: public CharDecorator { 
    public: HeightUp(Mario* ch): CharDecorator(ch) {} 
    int getHeight() override { return 2 * ch->getHeight(); } 
    int getWidth() override { return 2 * ch->getWidth(); } 
    string getAbility() override { 
        string s = ch->getAbility(); 
        for (char &c : s) { 
            c = toupper(c); 
        }
        return s;
    }
 };

class GunUp: public CharDecorator{
public:
GunUp(Mario* ch): CharDecorator(ch){}

string getAbility()  override{
    string s = ch->getAbility()+" gun";
    return s;
}
};

int main(){
    Mario* mario = new Mario();
    string s = mario->getAbility();
    cout<<s<<endl;
    cout<<mario->getHeight()<<endl;  //-> will print original height only, i,e. 10
    cout<<mario->getWidth()<<endl;   //-> will print original width only, i,e. 5

    mario = new GunUp(mario);
    s= mario->getAbility();
    cout<<s<<endl;

    mario=new HeightUp(mario);
    s=mario->getAbility();
    cout<<s<<endl;
    cout<<mario->getHeight()<<endl;  //-> will print original height only, i,e. 10
    cout<<mario->getWidth()<<endl;  // -> will print original width only, i,e. 5
    // to print 20 and 10, use virtual getHeight and getWidth methods in ICharacter, define them in mario
    // then in the decorator class, declare getHeight( here return getHeight(Mario) * 2 ). similarly define getWidth() fn
// now the present code is after doing the above changes, so ans is coming as expected
}