#include <iostream>
using namespace std;

struct Base {
    virtual ~Base() = default;  // nutné pro RTTI
};

struct Derived : Base {
    void hello() { cout << "Hello from Derived\n"; }
};

int main() {
    Base* b1 = new Derived();
    Base* b2 = new Base();

    // Bezpečný downcast
    if (Derived* d = dynamic_cast<Derived*>(b1)) {
        d->hello();  // OK, protože b1 skutečně ukazuje na Derived
    }

    // Neplatný downcast
    if (Derived* d = dynamic_cast<Derived*>(b2)) {
        d->hello();
    } else {
        cout << "b2 není Derived!\n";
    }

    delete b1;
    delete b2;
}

