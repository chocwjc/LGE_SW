#include <algorithm>
#include <iostream>
using namespace std;

#define interface struct

interface getBarkString {
	virtual ~getBarkString() {}
public:
	virtual string getString() = 0;
	void bark() {
		cout << getString() << endl;
	}
};

class dog : public getBarkString {
public:
	string getString() {
		return "dog dog";
	}
};

class cat : public getBarkString {
public:
	string getString()  {
		return "cat cat";
	}
};

int main()
{
	dog a;
	cat b;
	a.bark();
	b.bark();
	return 0;
}


