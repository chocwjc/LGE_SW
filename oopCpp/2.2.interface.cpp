#include <iostream>
using namespace std;

typedef interface struct;

interface Icamera {
	virtual void take() = 0;
	virtual ~Icamera() {};
}
