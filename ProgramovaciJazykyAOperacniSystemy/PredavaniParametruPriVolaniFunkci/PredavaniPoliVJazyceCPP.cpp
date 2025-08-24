#include <iostream>
using namespace std;

// Function that modifies an array
void modifyArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] *= 2;   // modifies the original array
    }
}

// Function that only prints array
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
}

int main() {
    int numbers[5] = {1, 2, 3, 4, 5};

    cout << "Before modify: ";
    printArray(numbers, 5);

    modifyArray(numbers, 5);   // array passed to function

    cout << "After modify:  ";
    printArray(numbers, 5);

    return 0;
}
