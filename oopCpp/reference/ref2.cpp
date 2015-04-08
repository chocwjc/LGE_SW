#include <stdio.h>
#include <iostream>
using namespace std;

int foo() {}

int main()
{
	//int &r1;
	//int &r2 = 10;
	//const int &r3 = 10;


	int arr[3];
	//int (*p)[3] = &arr;
	//int (&p)[3] = arr;

	//void (&f)(void) = foo;

	printf("%p\n", arr);
	printf("%p\n", &arr);
}

