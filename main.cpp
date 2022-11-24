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

    Cocktail& operator=(const Cocktail& rhs)
    {
        return *this; // returns the left-hand object
    }

    Cocktail& operator+=(const Cocktail& rhs)
    {
        this->ml += rhs.ml;
        return *this; // returns the left-hand object
    }

    std::string toString(){
        return "Cocktail nr "+ to_string(this->id) +" : "+ to_string(this->ml) + " ml\n";
    }
};

Cocktail::Cocktail(const int& id, const int& ml) :id(id),ml(ml)
    {
        cout<<"Cocktail created"<<endl;
    }
Cocktail::~Cocktail(){ }


class Martini : public Cocktail {
    public:
        Martini(){};
        Martini(const int& id, const int& ml):Cocktail(id,ml){}
        ~Martini(){};

        void listIngredients(){
            cout<<"Martini ingredients: gin, vermouth, orange bitters "<< endl;
        }
};


class Sunrise : public Cocktail{
    public:
        Sunrise(const int& id, const int& ml):Cocktail(id,ml){}
        ~Sunrise(){};
        Sunrise(const Sunrise&) = delete;
        Sunrise& operator= (const Sunrise&) = delete;

        void listIngredients(){
            cout<<"Sunrise ingredients: tequila, orange juice, grenadine "<< endl;
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

    cout<<"-----------------------"<<endl;

    cout<<"Before += : "<< martini2.toString();
    martini2 += martini;
    cout<<"After  += : "<< martini2.toString(); //same martini, but doubled

    martini2 = martini;
    cout<<"After   = : "<< martini2.toString(); //you cannot go back to previous martini, the left value is rturned

    return 0;
}