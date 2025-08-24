#include <iostream>

// Dvě obyčejné funkce
int add(int a, int b) {
    return a + b;
}
int multiply(int a, int b) {
    return a * b;
}

int main() {
    // Deklarace ukazatele na funkci
    int (*operation)(int, int);

    // Přiřazení adresy funkce
    operation = &add;
    std::cout << "Sum: " << operation(3, 4) << "\n";  // 7

    operation = &multiply;
    std::cout << "Product: " << operation(3, 4) << "\n";  // 12

    return 0;
}
