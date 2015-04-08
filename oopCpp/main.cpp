#include <iostream>

using namespace std;

class A {
	int x;
public:
	void foo()  { cout <<  "A foo" << endl; }
};

class B {
	int y;
public:
	virtual void goo() { cout << "B foo" << endl; }
};

int main()
{
	int b = 4096;
	char c;

	b = static_cast<char>(c);

	cout << b << endl;

	return 0;
}
