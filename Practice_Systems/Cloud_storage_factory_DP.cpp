/*
Principle	Status	       Comment
SRP     	❌ Violated	  FileManager + CloudStorage have multiple responsibilities
OCP	        ✅ Mostly_OK	  Easily extendable, minor factory map update
LSP	        ❌ Violated	  File operations forced on subclasses unnecessarily
ISP	        ❌ Violated	  Cloud providers inherit unused file methods
DIP	        ✅ Followed	  High-level code depends on abstraction (CloudStorage)

This was my code
*/

#include <bits/stdc++.h>
using namespace std;

class FileManager{
private:
unordered_map<string,int>mp;
public:
void upload(string name, int size){
    if(mp.find(name)==mp.end()){
        cout<<"Uploading file "<<name<<" of size "<<size<<endl;
        mp[name]=size;
    }
    else{
        cout<<"Modifying file "<<name<<" of size "<<size<<endl;
        mp[name]=size;
    }
    return;
}
void download(string name){
    auto it=mp.find(name);
    if(it!=mp.end()){
        cout<<" File "<<name<<" of size "<<it->second<<" downloaded successfully "<<endl;
    }
    else{
        cout<<" No such file found "<<endl;
    }
    return;
}
void deleteFile(string name){
    auto it=mp.find(name);
    if(it!=mp.end()){
        cout<<" File "<<name<<" of size "<<it->second<<" erased successfully "<<endl;
        mp.erase(it);
    }
    else{
        cout<<" No such file found "<<endl;
    }
}
void ListFiles(){
    for(auto it:mp){
        cout<<it.first<<" has size "<<it.second<<endl;
    }
}
};

class CloudStorage:public FileManager{
    public:
    virtual void setToken(string s)=0;
    virtual string getToken()=0;
    virtual string getSDK()=0;
    virtual bool authenticate(string token)=0;
    virtual ~CloudStorage(){}
};

class AWS: public CloudStorage{
    string token;
public:

    AWS(string t=""){
        this->token = t;
    }

    void setToken(string t) override{
        token = t;
        return;
    }

    string getToken() override{
        return this->token;
    }

    string getSDK() override{
        // this->token = "68eb6eb6-5728-8322-ac2b-14d1d1f5e943;
        return getToken();
    }
    
    bool authenticate(string token) override{
        if(token == this->token){
            cout<<" Successfully authenticated "<<endl;
            return true;
        }
        else{
            cout<<" Authentication failed, Try again "<<endl;
            return false;
        }
    }
};

class GDrive: public CloudStorage{
    string token;
public:
    GDrive(string t=""){
        this->token = t;
    }
    void setToken(string t)override{
        token = t;
        return;
    }
    string getToken()override{
        return this->token;
    }
    string getSDK() override{
        // this->token = "VylXGLyERTmj_zwG4bZrvw";
        return getToken();
    }
    bool authenticate(string token) override{
        if(token == this->token){
            cout<<" Successfully authenticated "<<endl;
            return true;
        }
        else{
            cout<<" Authentication failed, Try again "<<endl;
            return false;
        }
    }
};

class CloudFactory {
public:
    static CloudStorage* getCloud(const string& type) {
        static unordered_map<string,function<CloudStorage*()>> mp = {
            {"AWS", [](){ return new AWS("68eb6eb6-5728-8322-ac2b-14d1d1f5e943"); }},
            {"GDrive", [](){ return new GDrive("VylXGLyERTmj_zwG4bZrvw"); }}
        };
        auto it = mp.find(type);
        if (it != mp.end())
            return it->second();
        else {
            cout << "⚠️ Unknown cloud type. Defaulting to AWS.\n";
            return new AWS();
        }
    }
};

int main(){
    FileManager* fm = new FileManager();
    CloudFactory* cf = new CloudFactory();
    CloudStorage* cs = cf->getCloud("GDrive");
    cs->upload("Kanpur",4);
    cs->upload("Delhi",10);
    cs->upload("Delhi",23);
    cs->ListFiles();
    cs->setToken("Gdrivewaa");
    cout<<"New token is "<<cs->getToken()<<endl;
    cout<<" "<<cs->authenticate("rgdgffjg")<<endl;
}
