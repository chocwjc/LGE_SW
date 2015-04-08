#include <iostream>

using namespace std;

template<typename T> T Max(T a, T b)
{
	return a > b ? a : b;
}

int main()
{
	int temp1;
	int temp2;

	temp1 = Max<int>(3, 4);
	cout  << temp1 << "\n";

//temp2 = Max(65, 65.5);; 불가능

	temp2 = Max<int>(65, 78.5);
	cout << temp2 << "\n";

	return 0;
}
