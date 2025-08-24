#include <iostream>
#include <string>
using namespace std;

class Person {
private:
    string name;
    int age;

public:
    // --- Konstruktor ---
    Person(string n, int a) : name(n), age(a) {
        cout << "Konstruktor: Vytvořen " << name << " (" << age << ")\n";
    }

    // --- Destruktor ---
    ~Person() {
        cout << "Destruktor: Mazán " << name << "\n";
    }

    // --- Deklarace a implementace členských funkcí ---
    void introduce() {
        cout << "Jmenuji se " << name << " a je mi " << age << " let.\n";
    }

    void setAge(int a) {
        age = a;
    }

    int getAge() {
        return age;
    }
};

int main() {
    cout << "Začátek programu\n";

    Person p1("Alice", 25);   // volá se konstruktor
    p1.introduce();

    p1.setAge(26);            // volání členské funkce
    cout << "Nový věk: " << p1.getAge() << "\n";

    {   // nový blok
        Person p2("Bob", 30); // konstruktor
        p2.introduce();
    }   // p2 zde zaniká → zavolá se destruktor

    cout << "Konec programu\n";
    return 0;  // tady se zničí i p1 → destruktor
}
