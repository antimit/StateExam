#include <iostream>
using namespace std;

// Definice struktury
struct Person
{
    string name;
    int age;
};

int main()
{
    // Normální proměnná typu Person
    Person p1 = {"Alice", 25};

    // Ukazatel na strukturu
    Person *ptr = &p1;

    // Přístup k členům přes ukazatel
    cout << "Name via pointer: " << ptr->name << "\n"; // místo (*ptr).name
    cout << "Age via pointer: " << ptr->age << "\n";

    // Změna hodnoty přes ukazatel
    ptr->age = 30;
    cout << "Modified age: " << p1.age << "\n";

 
    //(*ptr).age je úplně totéž co ptr->age (jen méně přehledné).
    Person *p2 = new Person; // dynamická alokace
    p2->name = "Bob";
    p2->age = 40;

    cout << p2->name << ", " << p2->age << "\n";

    delete p2; // nezapomenout uvolnit paměť

    return 0;
}
