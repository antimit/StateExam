#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

struct Base {
    // ne-virtual
    void whoAmI_nonvirtual() const { cout << "Base::whoAmI_nonvirtual\n"; }

    // virtual
    virtual void whoAmI() const { cout << "Base::whoAmI (virtual)\n"; }

    virtual ~Base() = default; // virtuální destruktor kvůli polymorfismu
};

struct Derived : Base {
    void whoAmI() const override { cout << "Derived::whoAmI (virtual override)\n"; }
    void onlyInDerived() const { cout << "Derived::onlyInDerived\n"; }
};

int main() {
    cout << boolalpha;

    Derived d;
    Base* bp = &d;     // ukazatel na předka ukazuje na odvozený objekt
    Base& br = d;      // reference na předka na odvozený objekt

    cout << "== Non-virtual call přes base pointer ==\n";
    bp->whoAmI_nonvirtual();   // statická vazba → zavolá Base::whoAmI_nonvirtual

    cout << "== Virtual call přes base pointer ==\n";
    bp->whoAmI();              // dynamická vazba → zavolá Derived::whoAmI

    cout << "== Virtual call přes base reference ==\n";
    br.whoAmI();               // také zavolá Derived::whoAmI

    cout << "\n== Velikosti (orientačně) ==\n";
    cout << "sizeof(Base)    = " << sizeof(Base)    << "\n";
    cout << "sizeof(Derived) = " << sizeof(Derived) << "\n";
    // Obvykle uvidíš, že třída s virtual má alespoň +1 ukazatel navíc (vptr).

    // Pozn.: Následující je jen demonstrace polymorfismu; nelze bezpečně volat onlyInDerived přes Base* bez castu.
    if (Derived* dp = dynamic_cast<Derived*>(bp)) {
        cout << "\nDynamic cast úspěšný → volám onlyInDerived:\n";
        dp->onlyInDerived();
    }

    // Pro úplnost: runtime typy
    cout << "\nRTTI (typeid):\n";
    cout << "typeid(*bp).name() = " << typeid(*bp).name() << "\n"; // ukáže skutečný (odvozený) typ objektu

    return 0;
}
