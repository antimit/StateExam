#include <iostream>
#include <stdexcept>   // for runtime_error
using namespace std;

// Function that can throw an exception
int safeDivide(int a, int b) {
    if (b == 0) {
        throw runtime_error("Division by zero!");  // throw exception
    }
    return a / b;
}

int main() {
    cout << "=== EXCEPTIONS (try...catch) ===\n";

    try {
        cout << "Dividing 10 / 2 = " << safeDivide(10, 2) << "\n";
        cout << "Dividing 10 / 0 = " << safeDivide(10, 0) << "\n"; // this throws
    }
    catch (runtime_error &e) {   // catch the thrown exception
        cout << "Caught exception: " << e.what() << "\n";
    }

    return 0;
}
