#include <iostream>
#include <string>
using namespace std;

int main() {
    cout << "=== CONDITIONAL STATEMENTS ===\n";

    int x = 10;

    // if
    if (x > 0) {
        cout << "x is positive\n";
    }

    // if ... else
    if (x % 2 == 0) {
        cout << "x is even\n";
    } else {
        cout << "x is odd\n";
    }

    // if ... else if ... else
    if (x > 0) {
        cout << "x > 0\n";
    } else if (x < 0) {
        cout << "x < 0\n";
    } else {
        cout << "x == 0\n";
    }

    // switch
    int day = 3;
    switch (day) {
        case 1: cout << "Monday\n"; break;
        case 2: cout << "Tuesday\n"; break;
        case 3: cout << "Wednesday\n"; break;
        default: cout << "Another day\n";
    }

    cout << "\n=== LOOPS ===\n";

    // while
    int i = 0;
    cout << "while loop: ";
    while (i < 5) {
        cout << i << " ";
        i++;
    }
    cout << "\n";

    // do ... while
    int j = 0;
    cout << "do...while loop: ";
    do {
        cout << j << " ";
        j++;
    } while (j < 5);
    cout << "\n";

    // for
    cout << "for loop: ";
    for (int k = 0; k < 5; k++) {
        cout << k << " ";
    }
    cout << "\n";

    // range-based for
    int arr[] = {10, 20, 30};
    cout << "range-based for: ";
    for (int val : arr) {
        cout << val << " ";
    }
    cout << "\n";

    // break & continue
    cout << "for with break & continue: ";
    for (int n = 0; n < 10; n++) {
        if (n == 5) break;        // stop loop completely
        if (n % 2 == 0) continue; // skip even numbers
        cout << n << " ";
    }
    cout << "\n";

    return 0;
}
