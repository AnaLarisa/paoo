#define _HAS_AUTO_PTR_ETC 1
#include <functional>
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Cocktail {
    protected:
        int id;
        int ml;
        const char* topping;

    public:
    bool finalSteps = true; 

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
         const char *temp = rhs.topping;
         topping = temp;
         delete temp;
        
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



Cocktail* createCocktailInstance(){
    return (new Cocktail(100, 100, "grapefruit peel"));
}

class Martini : public Cocktail {
    public:
        Martini(){};
        Martini(const int& id, const int& ml, const char* topping):Cocktail(id,ml,topping){}
        ~Martini(){};

        void listIngredients(){
            cout<<"Martini ingredients: gin, vermouth, orange bitters "<< endl;
        }
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
            specialIngredient = "cinnamon";
        }
        ~SpecialMartini(){};

        SpecialMartini& operator=(const SpecialMartini& rhs)
        {
            Cocktail::operator=(rhs);
            specialIngredient = rhs.specialIngredient;
            return *this;
        }

        std::string toString(){
        return "Cocktail nr "+ to_string(this->id) +" : "+ to_string(this->ml) + " ml," + "topping = " + this->topping +", \tspecial ingredient: " +this->specialIngredient +"\n";
    }
        
    private:
        const char* specialIngredient;
};


//item 13
// void mix(Cocktail &cocktail)
// {
//     printf("The bartender mixes the cocktail.\n");
//     cocktail.finalSteps = false;
// }

// void pourOverIce(Cocktail &cocktail)
// {
//     printf("The bartender pours the cocktail over ice.\n");
//     cocktail.finalSteps = false;
// }


//item 13
// class Action{
//     private:
//     Cocktail &cocktailLockPtr;

//     public:
//     Action(Cocktail &ptr):cocktailLockPtr(ptr){
//         mix(cocktailLockPtr);        //aquire resource
//     }
//     ~Action(){
//         pourOverIce(cocktailLockPtr); //release resource
//     }
// };


//item 14 - 1
class Uncopyable{
    protected:
    Uncopyable(){}
    ~Uncopyable(){}

    private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

//item 14 - 1
// class Action: private Uncopyable{
//     private:
//     Cocktail &cocktailLockPtr;

//     public:
//     Action(Cocktail &ptr):cocktailLockPtr(ptr){
//         mix(cocktailLockPtr);        //aquire resource
//     }
//     ~Action(){
//         pourOverIce(cocktailLockPtr); //release resource
//     }
// };



//item 14 - 2
void mix(Cocktail *cocktail)
{
    printf("The bartender mixes the cocktail.\n");
    cocktail->finalSteps = false;
}

void pourOverIce(Cocktail *cocktail)
{
    printf("The bartender pours the cocktail over ice.\n");
    cocktail->finalSteps = false;
}

//item 14 - 2: reference count the underlying resource 
class Action{
    public:
    
    explicit Action(Cocktail *ptr){
        mix(ptr);
        cocktailLockPtr.reset(ptr, pourOverIce); // here we specify the function to call when the ref count goes to 0; it will auto invoke the destructor
    }

    private:
    shared_ptr<Cocktail> cocktailLockPtr;  //for ref counting copying
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

    Martini martini4(4, 300, "olive");
    martini2 = martini = martini4;
    cout<<"After   = : "<< martini2.toString(); //you cannot go back to previous martini, the left value is rturned

    martini = martini;
    cout<<"After   = : "<< martini.toString();

    SpecialMartini specialMartini1(3, 250, "mint");
    SpecialMartini specialMartini2(4, 150, "lemon peel");

    cout<<"Before:\n";
    cout<< specialMartini1.toString();
    cout<< specialMartini2.toString();
    specialMartini1 = specialMartini2;

    cout<<"After:\n";
    cout<< specialMartini1.toString();
    cout<< specialMartini2.toString();
    cout<<"-----------------------"<<endl;


    //manual deletion of pointer

    Sunrise *sunrisePtr = new Sunrise(5, 150, "grapefruit peel");
    cout<<sunrisePtr->toString()<<endl;
    delete sunrisePtr;
    //cout<<sunrisePtr->toString(); //error


    //auto_ptr
    auto_ptr<Cocktail> cocktailPtr1( createCocktailInstance());
    cout<<"Auto Cocktail 1 ml: "<<cocktailPtr1->getMl()<<endl;
    auto_ptr<Cocktail> cocktailPtr2(cocktailPtr1);
    cout<<"Auto Cocktail 2 ml: "<<cocktailPtr2->getMl()<<endl;

    //cout<<"Auto Cocktail 1 ml: "<<cocktailPtr1->getMl(); //error - copy does not work
    cout<<endl;

    //shared
    shared_ptr<Cocktail> cocktailPtrShared1(createCocktailInstance());
    cout<<"Shared Cocktail 1 ml: "<<cocktailPtrShared1->getMl()<<endl;
    shared_ptr<Cocktail> cocktailPtrShared2(cocktailPtrShared1);
    cout<<"Shared Cocktail 2 ml: "<<cocktailPtrShared2->getMl()<<endl;

    cout<<"Shared Cocktail 1 ml: "<<cocktailPtrShared1->getMl()<<endl; //copy constructor works as expected 
    cout<<endl;


    //item 14 -1 (make the cocktail uncopyable)
    // Sunrise *sunrisePtr1 = new Sunrise(6, 150, "grapefruit peel");
    // Action action(*sunrisePtr1);

    //Action action2(&action); //- gives an error because it cannot be copied 
    //Action action2(*sunrisePtr1);
    //action2 = action;        //- gives an error because it cannot be assigned


    //item 14 -2 
    Sunrise *sunrisePtr1 = new Sunrise(7, 200, "pomelo peel");
    Sunrise *sunrisePtr2 = new Sunrise(8, 100, "lemon peel");

    Action action(sunrisePtr1);
    cout<<sunrisePtr1->toString()<<endl;

    Action action1(sunrisePtr2);
    action1 = action;


    
    return 0;
}