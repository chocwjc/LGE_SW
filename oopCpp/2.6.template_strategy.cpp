#include <iostream>
#include <string>
using namespace std;

//

class dogBark {
public:
	inline string getBarkString() { return "dog dog dog"; }
};

class catBark {
public:
	inline string getBarkString() { return "cat cat cat"; }
};

template <typename animalModel> class Animal : public animalModel {
public:
	void bark() { cout << getBarkString() << endl; }
};

int main()
{
	Animal<dogBark> dog;
	dog.bark();

	Animal<catBark> cat;
	cat.bark();

	return 0;
}

