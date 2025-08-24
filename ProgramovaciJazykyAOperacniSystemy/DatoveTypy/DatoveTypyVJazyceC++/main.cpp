#include <iostream>

using namespace std;

int main()
{
	int var = 10;

	
	char c = 'A';
	int x = 0x15;
	bool b = true;
	float f = 35.5;
	
	cout << "Size of int: " << sizeof(int) << " bytes" << endl;
    cout << "Size of char: " << sizeof(char) << " byte" << endl;
    cout << "Size of float: " << sizeof(float) << " bytes" << endl;
    cout << "Size of double: " << sizeof(double) << " bytes";

}
//https://www.geeksforgeeks.org/cpp/cpp-data-types/