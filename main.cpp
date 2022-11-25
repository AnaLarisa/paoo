#include <iostream>
#include <string>
using namespace std;

class Cocktail {
    protected:
        int id;
        int ml;
        const char* topping;

    public:
    Cocktail(){};
    Cocktail(const int& id, const int& ml, const char* topping);
    ~Cocktail();

    int getMl(){
        return ml;
    }

    Cocktail& operator=(const Cocktail& rhs)
    {
        if(this == &rhs)
        {
            cout<<"self assignation:"<<endl;
            return *this; // returns the left-hand object
        }
            
         id = rhs.id;
         ml = rhs.ml;
         //delete topping;
         //const char *temp = rhs.topping;
         topping = rhs.topping;
         //delete temp;
        
         return *this;
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

Cocktail::Cocktail(const int& id, const int& ml, const char* topping) :id(id),ml(ml),topping(topping)
    {
        cout<<"Cocktail created"<<endl;
    }
Cocktail::~Cocktail(){ }


class Martini : public Cocktail {
    public:
        Martini(){};
        Martini(const int& id, const int& ml, const char* topping):Cocktail(id,ml,topping){
            //specialIngredient = "no";
            //cout<<"Special ingredient: "<<specialIngredient<<endl;
        }
        ~Martini(){};

        void listIngredients(){
            cout<<"Martini ingredients: gin, vermouth, orange bitters "<< endl;
        }


    // private:
    //     const char* specialIngredient;
};


class Sunrise : public Cocktail{
    public:
        Sunrise(const int& id, const int& ml, const char* topping):Cocktail(id,ml,topping){}
        ~Sunrise(){};
        Sunrise(const Sunrise&) = delete;
        Sunrise& operator= (const Sunrise&) = delete;

        void listIngredients(){
            cout<<"Sunrise ingredients: tequila, orange juice, grenadine "<< endl;
        }
};


class SpecialMartini: public Martini{
    public:
        SpecialMartini(){};
        SpecialMartini(const int& id, const int& ml, const char* topping):Martini(id,ml,topping){
            specialIngredient = "cinamon";
        }
        ~SpecialMartini(){};

        SpecialMartini& operator=(const SpecialMartini& rhs)
        {
            Cocktail::operator=(rhs);
            specialIngredient = rhs.specialIngredient; //if we comment this, the private parameter will not change
            return *this;
        }
        
        void changeSpecialIngredient()
        {
            this->specialIngredient = "chili";
        }

        std::string toString(){
        return "Cocktail nr "+ to_string(this->id) +" : "+ to_string(this->ml) + " ml," + "topping = " + this->topping +", \tspecial ingredient: " +this->specialIngredient +"\n";
    }
        
    private:
        const char* specialIngredient;
};


int main() {

    Martini martini(1, 200, "cherry");
    Sunrise sunrise(2, 300, "orange peel");
    cout<<endl;

    cout<< martini.toString();
    martini.listIngredients();

    cout<< sunrise.toString();
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

    martini = martini;
    cout<<"After   = : "<< martini.toString();

    SpecialMartini specialMartini1(3, 250, "mint");
    SpecialMartini specialMartini2(4, 150, "lemon peel");
    specialMartini2.changeSpecialIngredient();

    cout<<"Before:\n";
    cout<< specialMartini1.toString();
    cout<< specialMartini2.toString();
    specialMartini1 = specialMartini2;

    cout<<"After:\n";
    cout<< specialMartini1.toString();
    cout<< specialMartini2.toString();


    return 0;
}