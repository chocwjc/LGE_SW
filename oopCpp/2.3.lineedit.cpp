#include <iostream>
#include <curses.h>
using namespace std;

// 변하는 것을 분리하는 2번째 방법
// 변하는 것을 다른 클래스로 뽑아 낸다. 변해야 하므로 교체 가능해야 한다.
// -> 인터페이스 기반의 다른 클래스로 뽑아 낸다.

struct IValidator {
	public:
	virtual bool validate(string s, char c) = 0;
	virtual vool iscomplete(string s) { return true; }
	virtual ~IValidator() {}
};

class LineEdit {
private:
	string  data;
	IValidator* pValidator;
public:
	LineEdit() : pValidator(0) {}
	void setValidator(IValiator *p) { pValidator = p; }
	//virtual bool validate(char c) { return isdigit(c); }
	string getData() {
		data.clear();

		while (1) {
	
			char c = getchar();

			if (c == 13) break; // enter

			if (pValidator == 0 || pValidator.validate(data, c)) {
				data.push_back(c);
				cout << c;
			}

		}
		cout << endl;
		return data;
	}
};

class AddressLineEdit : public LineEdit {
public:
	bool validate(char c) { return true; }
};

int main()
{
	initscr();
	noecho();

	LineEdit edit;
	AddressLineEdit Aedit;

	while (1) {
		string s = Aedit.getData();
		cout << "input: " << s << endl << "\n\r";
	}

	return 0;
}


