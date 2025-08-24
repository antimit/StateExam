#include <iostream>
#include <string>
using namespace std;

class Person {
    string name;
    int age;
public:
    Person(string n, int a) : name(n), age(a) {
        cout << "Konstruktor: " << name << " (" << age << ")\n";
    }
    ~Person() {
        cout << "Destruktor: " << name << "\n";
    }
    void introduce() { cout << "Jsem " << name << ", věk " << age << "\n"; }
};

int main() {
    cout << "=== Stack allocation ===\n";
    Person p1("Alice", 25);  // constructor runs here
    p1.introduce();

    cout << "\n=== Heap allocation ===\n";
    Person* p2 = new Person("Bob", 30); // constructor runs here
    p2->introduce();

    cout << "Uvolňuji p2 pomocí delete...\n";
    delete p2;  // destructor runs here

    cout << "Konec programu\n";
    return 0;   // destructor of p1 runs here (stack cleanup)
}
