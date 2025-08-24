#include <iostream>
using namespace std;

int main() {
    cout << "=== Empty and Simple Statements ===\n";

    int x = 5;              // simple statement (declaration + assignment)
    x = x + 1;              // simple statement (assignment)
    cout << "x = " << x << "\n";  // simple statement (function call)

    ;   // empty statement (does nothing)

    // Example: empty statement inside loop
    int i = 0;
    while (i < 5) {
        i++;    // simple statement
        ;       // empty statement inside the loop
    }

    cout << "Loop finished, i = " << i << "\n";

    return 0;
}
