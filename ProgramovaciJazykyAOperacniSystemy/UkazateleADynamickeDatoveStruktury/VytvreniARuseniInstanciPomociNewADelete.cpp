#include <iostream>
using namespace std;

struct Person {
    string name;
    int age;
};

int main() {
    // Vytvoření instance na heapu
    Person* p = new Person;

    // Použití
    p->name = "Alice";
    p->age = 25;
    cout << p->name << ", " << p->age << endl;

    // Uvolnění paměti
    delete p;



    /////////////////////////////////////////////////////////////



    // Dynamické pole 3 osob
    Person* people = new Person[3];

    people[0].name = "Alice";  people[0].age = 25;
    people[1].name = "Bob";    people[1].age = 30;
    people[2].name = "Charlie";people[2].age = 35;

    for (int i = 0; i < 3; i++) {
        cout << people[i].name << " (" << people[i].age << ")\n";
    }

    // Uvolnění paměti pole
    delete[] people;


    
    return 0;
}
