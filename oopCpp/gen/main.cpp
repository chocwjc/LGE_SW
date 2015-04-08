#include <iostream>

using namespace std;

class test {
	const int r1;
	const int r2;
public:
	test() : r1(0), r2(0) 
	{
		std::cout << "gen1" << endl;
		std::cout << r1 << endl;
		std::cout << r2 << endl;
		std::cout << "1: Its me: " << this << endl << endl;
	}
	test(int a, int b) : r1(a), r2(b) 
	{
		std::cout << "gen2" << endl;
		std::cout << r1 << endl;
		std::cout << r2 << endl;
		std::cout << "2: Its me: " << this << endl << endl;
	}
	test(const test& a) : r1(a.r1), r2(a.r2)
	{
		std::cout << "gen3" << endl;
		std::cout << r1 << endl;
		std::cout << r2 << endl;
		std::cout << "3: Its me: " << this << endl << endl;
	}
	test operator=(const test &a)
	{
		std::cout << "operator =" << endl;
		std::cout << "4: Its me: " << this << endl << endl;
		return *this;
	}

	int getr1() {return r1;}
	int getr2() {return r2;}
};


int main()
{
	test a(1, 1);
	test b(2, 2);
	test c(3, 3);
	c = a;

	std::cout << b.getr1() << endl;
	std::cout << b.getr1() << endl;

	std::cout << "Its a: " << &a << endl;
	std::cout << "Its b: " << &b << endl;
	std::cout << "Its c: " << &c << endl;

	return 0;
}

	
