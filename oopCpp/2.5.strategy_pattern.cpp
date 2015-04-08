#include <iostream>

using namespace std;
#define interface struct

// 전략 Pattern

interface BarkString {
	virtual ~BarkString() {}
public:
	virtual string getString() = 0;
};

class dogBarkString : public BarkString {
public:
	string getString() { return "dog dog dog"; }
};

class catBarkString : public BarkString {
public:
	string getString() { return "cat cat cat"; }
};

class Animal {
	BarkString* interface_callback;
public:
	Animal() { interface_callback = NULL; }
	void setBarkString(BarkString *bs) {
		interface_callback = bs;
	}
	void bark() {
		cout << interface_callback->getString() << endl;
	}
};

int main()
{
	dogBarkString dbs;
	catBarkString cbs;
	Animal A;

	A.setBarkString(&dbs);
	A.bark();

	A.setBarkString(&cbs);
	A.bark();

	return 0;
}



