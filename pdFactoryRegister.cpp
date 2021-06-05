#include <iostream>
using namespace std;

class Shoes{
public:
    virtual ~Shoes() {}
    virtual void Show() = 0;
};

class LiNingShoes : public Shoes{
public:
    void Show() { cout << "LiNing" << endl; }
};

class AdidasShoes : public Shoes{
public:
    void Show() { cout << "Adidas" << endl; }
};

class ShoesFactory{
public:
    virtual Shoes* CreateShoes() = 0;
    virtual ~ShoesFactory() {}
};

class LiNingProducer : public ShoesFactory{
public:
    Shoes *CreateShoes() { return new LiNingShoes(); }
};

class AdidasProducer : public ShoesFactory{
public:
    Shoes *CreateShoes() { return new AdidasShoes(); }
};

int main() {
    ShoesFactory *pLiNingProducer = new LiNingProducer();
    Shoes* pLiNingShoes = pLiNingProducer->CreateShoes();
    pLiNingShoes->Show();
    delete pLiNingShoes;
    delete pLiNingProducer;
    
    ShoesFactory *pAdidasProducer = new AdidasProducer();
    Shoes* pAdidasShoes = pAdidasProducer->CreateShoes();
    pAdidasShoes->Show();
    delete pAdidasShoes;
    delete pAdidasProducer;
}