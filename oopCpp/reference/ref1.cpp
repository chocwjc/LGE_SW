#include <iostream>
using namespace std;

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

int main()
{
	int a, b;
	a = 3;
	b = 4;
	
//	swap(a, b); // call by reference

	cout << "a: " << a << "\n";
	cout << "b: " << b << "\n";

	swap(&a, &b); // call by address

	cout << "a: " << a << "\n";
	cout << "b: " << b << "\n";

	return 0;
}
