#include <bits/stdc++.h>
using namespace std;

class Product{
public:
    string name;
    int price;
    Product(string naam, int daam){
        name = naam;
        price = daam; 
    }
};
class ShoppingCart{
private:
    // ShoppingCart* shoppingCart;
    vector<Product* >products;
public:

    void addProducts(Product* p){
        products.push_back(p);
    }

    vector<Product*> getProducts(){
        return products;
    }

    int calculateTotalPrice(){
        int total=0;
        for(auto it:products){
            total= total + it->price;
        }
        return total;
    }
};

class CartPrintInvoice{
private: 
    ShoppingCart* cart;
public:
    CartPrintInvoice(ShoppingCart* cart){
        this->cart = cart;
    }
    void printInvoice(){
        for(auto p: cart->getProducts()){
            cout<<" product is "<<p->name<<" and price is "<<p->price<<endl;
        }
        cout<<" Total is "<<cart->calculateTotalPrice()<<endl;
    }
};
class SaveToDB{
private: 
    ShoppingCart* cart;
public:
    SaveToDB(){}
    SaveToDB(ShoppingCart* cart){
        this->cart = cart;
    }
    virtual void save()=0;
};
class SaveToSQL: public SaveToDB{
private:
    ShoppingCart* cart;
public:
    SaveToSQL(ShoppingCart* cart){
        this->cart = cart;
    }
    
    void save(){
        cout<<" saved to DB "<<endl;
        for(auto p: cart->getProducts()){
            cout<<" saved "<<p->name<<" and price : "<<p->price<<endl;
        }
        cout<<" SQL saving ended"<<endl;
    }
};

class SaveToMongo: public SaveToDB{
private:
    ShoppingCart* cart;
public:
    SaveToMongo(ShoppingCart* cart){
        this->cart = cart;
    }
    
    void save(){
        cout<<"------- saving to Mongo --------"<<endl;
        for(auto p: cart->getProducts()){
            cout<<" saved "<<p->name<<" and price : "<<p->price<<endl;
        }
        cout<<" Mongo saving ended"<<endl;
    }
};

int main(){
    Product* al=new Product("alexa",1000);
    Product* ov=new Product("para",23000);
    Product* tr=new Product("philips",1450);
    ShoppingCart* sc = new ShoppingCart();
    // vector<Product*> pv = sc->getProducts();
    // pv.push_back(al);
    // pv.push_back(ov);
    // pv.push_back(tr);
    /// if we use above method then products are not added in the shopping_cart, we should use:
    sc->addProducts(al);
    sc->addProducts(ov);
    sc->addProducts(tr);
    cout<<" total value of the cart is "<<sc->calculateTotalPrice()<<endl;

    CartPrintInvoice* cpi = new CartPrintInvoice(sc);
    cpi->printInvoice();

    SaveToDB* sv = new SaveToSQL(sc);
    sv->save();
    SaveToDB* sv2 = new SaveToMongo(sc);
    sv2->save();
}
