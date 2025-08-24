#include <iostream>
using namespace std;

int main()
{
    int arr[5] = {10, 20, 30, 40, 50};

    // arr je ukazatel na první prvek
    cout << "arr (address of first element): " << arr << "\n";
    cout << "&arr[0]: " << &arr[0] << "\n";

    // Přístup přes index
    cout << "arr[2] = " << arr[2] << "\n";

    // Přístup přes ukazatelovou aritmetiku
    cout << "*(arr + 2) = " << *(arr + 2) << "\n";

    ///////////////////////////////////////////////
    for (int i = 0; i < 5; i++)
    {
        cout << arr[i] << " "; // klasický index
    }
    cout << "\n";
    for (int *p = arr; p < arr + 5; p++)
    {
        cout << *p << " "<<endl; // ukazatelová aritmetika
    }
    

    //ROZDIL
    //arr (pole) není totéž co int* (ukazatel).

    //sizeof(arr) = velikost celého pole (např. 5×4 = 20 bajtů).

    //sizeof(&arr[0]) nebo sizeof(int*) = velikost ukazatele (např. 8 bajtů na 64bit systému).

    cout <<"pole „zná“ svou délku v bajtech, ukazatel ne" <<endl;
    int arr1[5] = {1,2,3,4,5};
    cout << sizeof(arr) << "\n";


    int* p = arr;
    cout << sizeof(p) << "\n";


    return 0;
}
