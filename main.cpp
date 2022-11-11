#include <iostream>
#include <string>
using namespace std;

class Cocktail {
    protected:
        int id;
        int ml;

    public:
    Cocktail(){};
    Cocktail(const int& id, const int& ml);
    ~Cocktail();

    int getMl(){
        return ml;
    }
};

Cocktail::Cocktail(const int& id, const int& ml)
    :id(id),
     ml(ml)
    {
        cout<<"Cocktail created"<<endl;
    }
Cocktail::~Cocktail(){
    
}

class Martini : public Cocktail {
    public:
        Martini(){};
        Martini(const int& id, const int& ml):Cocktail(id,ml){}
        ~Martini(){};

        void listIngredients(){
            cout<<"Martini ingredients "<< endl;
        }
};


class Sunrise : public Cocktail{
    public:
        Sunrise(const int& id, const int& ml):Cocktail(id,ml){}
        ~Sunrise(){};
        Sunrise(const Sunrise&) = delete;
        Sunrise& operator= (const Sunrise&) = delete;

        void listIngredients(){
            cout<<"Sunrise ingredients "<< endl;
        }
};


int main() {

    Martini martini(1, 200);
    Sunrise sunrise(2, 300);

    martini.listIngredients();
    sunrise.listIngredients();

    // calling the copy constructor
    Martini martini2(martini);

    // calling the copy assignment operator
    Martini martini3;
    martini3=martini;

    // will not compile
    // Sunrise sunrise2(sunrise);

    return 0;
}