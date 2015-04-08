#include <iostream>

using namespace std;

/* Basic namespace */
namespace graphic {
	void init () { cout << "graphic init\n"; }
}
namespace audio {
	void init() { cout << "audio init\n"; }
}

/* Nested namespace */
namespace AAA {
	namespace BBB {
		void foo() {cout << "foo() !!\n";}
	}
}


int main()
{
	graphic::init();
	audio::init();
	AAA::BBB::foo();

	return 0;
}
