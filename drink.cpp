//Usage examples: The Builder pattern is a well-known pattern in C++ world. It’s especially useful when you need to create an object with lots of possible configuration options.
//Identification: The Builder pattern can be recognized in a class, which has a single creation method and several methods to configure the resulting object. 

#include <iostream>
#include <string>
#include <vector>

class Cocktail{
    public:
    std::vector<std::string> parts_;
    void ListParts()const{
        std::cout << "Cocktail parts: ";
        for (size_t i=0;i<parts_.size();i++){
            if(parts_[i]== parts_.back()){
                std::cout << parts_[i];
            }else{
                std::cout << parts_[i] << ", ";
            }
        }
        std::cout << "\n\n"; 
    }
};



class Builder{
    public:
    virtual ~Builder(){}
    virtual void MakePartA() const = 0; //=0 makes the function purely virtual
    virtual void MakePartB() const = 0;
    virtual void MakePartC() const = 0;
};


class ConcreteBuilder1 : public Builder{
    private:

    Cocktail* cocktail;


    public:

    ConcreteBuilder1(){
        this->Reset();
    }

    ~ConcreteBuilder1(){
        delete cocktail;
    }

    void Reset(){
        this->cocktail= new Cocktail();
    }


    void MakePartA()const override{
        this->cocktail->parts_.push_back("VodKa");
    }

    void MakePartB()const override{
        this->cocktail->parts_.push_back("Espresso");
    }

    void MakePartC()const override{
        this->cocktail->parts_.push_back("Coffee Liqueur");
    }

    /**
     * Usually, after returning the end result to the client, a builder instance
     * is expected to be ready to start producing another cocktail. That's why
     * it's a usual practice to call the reset method at the end of the
     * `GetCocktail` method body. However, this behavior is not mandatory, and
     * you can make your builders wait for an explicit reset call from the
     * client code before disposing of the previous result.
     */

    /**
     * Please be careful here with the memory ownership. Once you call
     * GetCocktail the user of this function is responsable to release this
     * memory. Here could be a better option to use smart pointers to avoid
     * memory leaks
     */

    Cocktail* GetCocktail() {
        Cocktail* result = this->cocktail;
        this->Reset();
        return result;
    }
};

/**
 * The Barman is only responsible for executing the building steps in a
 * particular sequence. It is helpful when producing cocktails according to a
 * specific order or configuration. Strictly speaking, the Barman class is
 * optional, since the client can control builders directly.
 */
class Barman{
    private:

    Builder* builder;

    public:

    void set_builder(Builder* builder){
        this->builder=builder;
    }

    void BuildMinimalCocktail(){
        this->builder->MakePartA();
    }
    
    void BuildFullFeaturedEspressoMartiniCocktail(){
        this->builder->MakePartA();
        this->builder->MakePartB();
        this->builder->MakePartC();
    }
};

/**
 * I used raw pointers for simplicity however you may prefer to use smart
 * pointers here
 */
void ClientCode(Barman& Barman)
{
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    Barman.set_builder(builder);
    std::cout << "Standard basic cocktail:\n"; 
    Barman.BuildMinimalCocktail();
    
    Cocktail* p= builder->GetCocktail();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured cocktail:\n"; 
    Barman.BuildFullFeaturedEspressoMartiniCocktail();

    p= builder->GetCocktail();
    p->ListParts();
    delete p;

    // Remember, the Builder pattern can be used without a Barman class.
    std::cout << "Custom cocktail:\n";
    builder->MakePartA();
    builder->MakePartC();
    p=builder->GetCocktail();
    p->ListParts();
    delete p;

    delete builder;
}

int main(){
    Barman* barman = new Barman();
    ClientCode(*barman);
    delete barman;
    return 0;    
}