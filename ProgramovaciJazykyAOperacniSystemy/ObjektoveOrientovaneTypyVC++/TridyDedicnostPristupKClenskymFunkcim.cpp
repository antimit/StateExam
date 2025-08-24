// Třídy, dědičnost, přístup k členským funkcím (C++)
#include <iostream>
#include <string>
#include <utility>
using namespace std;

class Person {
private:
    string name;        // private: zvenku nepřístupné (jen přes metody)
protected:
    int age;            // protected: přístupné v potomcích
public:
    Person(string n, int a) : name(move(n)), age(a) { ++count; }
    virtual ~Person() { --count; }

    // --- veřejné členské funkce (přístup přes . nebo ->) ---
    const string& getName() const { return name; }   // const metoda (nemění objekt)
    int getAge() const { return age; }
    void setAge(int a) { age = a; }

    // virtual → umožní polymorfní volání přes ukazatel/reference na základní třídu
    virtual string role() const { return "Person"; }
    virtual void introduce() const {
        cout << "Ahoj, jsem " << name << " a je mi " << age << ".\n";
    }

    // statická členská funkce (patří třídě, ne instanci)
    static int instances() { return count; }

private:
    static int count;   // statický datový člen (společný pro všechny instance)
};
int Person::count = 0;

class Student : public Person {              // public dědičnost = Personova public zůstává public
private:
    string school;
public:
    Student(string n, int a, string s) : Person(move(n), a), school(move(s)) {}

    // ukázka přístupu k protected členu 'age' z potomka
    void birthday() { ++age; }

    string role() const override { return "Student"; }
    void introduce() const override {
        Person::introduce();                 // volání verze z předka
        cout << "Studuji na " << school << ".\n";
    }
};

class Teacher : public Person {
private:
    string subject;
public:
    Teacher(string n, int a, string sub) : Person(move(n), a), subject(move(sub)) {}
    string role() const override { return "Teacher"; }
    void introduce() const override {
        cout << "Jsem " << getName() << ", vyučuji " << subject << ", věk " << getAge() << ".\n";
    }
};

int main() {
    cout << "== Vytváření objektů ==\n";
    Person p("Alice", 30);
    Student s("Bob", 20, "CVUT");
    Teacher t("Carol", 45, "Matematika");
    cout << "Počet instancí (Person::instances): " << Person::instances() << "\n\n";

    cout << "== Přístup k členským funkcím přes objekt (.) ==\n";
    p.introduce();
    s.introduce();
    t.introduce();

    cout << "\nZměna dat přes veřejné metody:\n";
    s.setAge(21);                     // veřejná metoda → OK
    cout << s.getName() << " má nyní " << s.getAge() << " let.\n";
    // s.age = 99;                   // ❌ ERROR: 'age' je protected (nelze zvenku)
    // p.name = "X";                 // ❌ ERROR: 'name' je private

    cout << "\n== Dědičnost + protected v potomkovi ==\n";
    s.birthday();                      // Student umí měnit 'age' díky protected
    cout << "Po narozeninách: " << s.getAge() << " let.\n";

    cout << "\n== Polymorfismus a přístup přes ukazatel/reference ==\n";
    Person* bp = &s;                   // ukazatel na předka ukazuje na potomka
    cout << "role přes base pointer: " << bp->role() << "\n"; // volá Student::role()
    bp->introduce();                   // volá Student::introduce() (díky virtual)

    Person& br = t;                    // reference na předka
    cout << "role přes base ref: " << br.role() << "\n";       // Teacher::role()
    br.introduce();                    // Teacher::introduce()

    cout << "\n== Ukazatel na dynamicky alokovaný objekt (->) ==\n";
    Student* dyn = new Student("Dana", 19, "FIT");
    cout << "role(dyn): " << dyn->role() << "\n";
    dyn->introduce();
    delete dyn;                        // uvolnění heapu

    cout << "\nPočet instancí na konci: " << Person::instances() << "\n";
    return 0;
}
