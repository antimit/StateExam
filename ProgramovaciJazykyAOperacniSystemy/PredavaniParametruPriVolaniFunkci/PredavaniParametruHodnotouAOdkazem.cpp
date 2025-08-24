#include <iostream>
using namespace std;

// Function with parameter passed by value
void byValue(int a) {
    a = a + 10;  // only local copy is changed
    cout << "Inside byValue, a = " << a << "\n";
}

// Function with parameter passed by reference
void byReference(int &b) {
    b = b + 10;  // original variable is changed
    cout << "Inside byReference, b = " << b << "\n";
}

int main() {
    cout << "=== Passing parameters by value vs reference ===\n";

    int x = 5;
    cout << "Before byValue, x = " << x << "\n";
    byValue(x);
    cout << "After byValue, x = " << x << "\n\n";

    int y = 5;
    cout << "Before byReference, y = " << y << "\n";
    byReference(y);
    cout << "After byReference, y = " << y << "\n";

    return 0;
}
