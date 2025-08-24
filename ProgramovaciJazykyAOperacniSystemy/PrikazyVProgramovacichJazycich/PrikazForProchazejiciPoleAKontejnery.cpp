#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    cout << "=== RANGE-BASED FOR LOOP ===\n";

    // --- Example 1: Array ---
    int arr[] = {10, 20, 30, 40};
    cout << "Array elements: ";
    for (int val : arr) {      // go through each element in arr
        cout << val << " ";
    }
    cout << "\n";

    // --- Example 2: Vector ---
    vector<string> names = {"Alice", "Bob", "Charlie"};
    cout << "Vector elements: ";
    for (const string &name : names) {   // reference avoids copying
        cout << name << " ";
    }
    cout << "\n";

    // --- Example 3: String ---
    string text = "Hello";
    cout << "Characters in string: ";
    for (char ch : text) {
        cout << ch << " ";
    }
    cout << "\n";

    // --- Example 4: Modifying elements ---
    cout << "Array doubled: ";
    for (int &val : arr) {   // reference allows modification
        val *= 2;
        cout << val << " ";
    }
    cout << "\n";

    return 0;
}
