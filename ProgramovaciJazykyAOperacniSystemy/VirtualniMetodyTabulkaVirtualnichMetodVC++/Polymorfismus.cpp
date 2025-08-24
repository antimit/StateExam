#include <iostream>
using namespace std;

//Statický polymorfismus:

//Přetížení funkcí
void print(int x) { cout << "int: " << x << "\n"; }
void print(string s) { cout << "string: " << s << "\n"; }

//Šablony
template <typename T>
T add(T a, T b) { return a + b; }




class Animal {
public:
    virtual void makeSound() { cout << "Some generic animal sound\n"; }
    virtual ~Animal() = default; // virtuální destruktor kvůli polymorfismu
};

class Dog : public Animal {
public:
    void makeSound() override { cout << "Woof!\n"; }
};

class Cat : public Animal {
public:
    void makeSound() override { cout << "Meow!\n"; }
};

int main() {

    //Přetížení funkcí
    print(5);        // volá se verze s int
    print("hello");  // volá se verze s string


    cout << add(2, 3) << "\n";     // int
    cout << add(2.5, 3.1) << "\n"; // double
    
    Animal* a1 = new Dog();
    Animal* a2 = new Cat();

    a1->makeSound(); // zavolá Dog::makeSound
    a2->makeSound(); // zavolá Cat::makeSound

    delete a1;
    delete a2;
}
