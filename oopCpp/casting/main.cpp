#include <stdlib.h>

using namespace std;

int main()
{
	int *p2 = reinterpret_cast<int*>(malloc(100));

	auto const int c = 10;

	int *p3 = const_cast<int*>(&c);
	*p3 = 20;

	<< *p3  << endl;
	cout << c    << endl;

	return 0;
}

