#include <iostream>
using namespace std;

// function receives a pointer to int
void byPointer(int *p) {
    *p = *p + 10;  // dereference pointer -> change original variable
    cout << "Inside byPointer, *p = " << *p << "\n";
}

int main() {
    int x = 5;

    cout << "Before byPointer, x = " << x << "\n";
    byPointer(&x);   // pass address of x
    cout << "After byPointer, x = " << x << "\n";

    return 0;
}
