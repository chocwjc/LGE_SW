#include <iostream>

using namespace std;

class Animal {
public:
	virtual void cry() { cout << "Animal cry" << endl; }
};

class Dog  : public Animal {
public:
	void cry() { cout << "Dog cry" << endl; }
};

class Cat : public Animal {
public:
	void cry() { cout << "Cat cry" << endl; }
};

void foo(Animal *d) 
{
	d->cry();
}

int main()
{
	Animal a;
	Dog b;
	Cat c;

	foo(&a);
	foo(&b);
	foo(&c);

	return 0;
}

