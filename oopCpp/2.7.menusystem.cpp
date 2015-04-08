#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
using namespace std;

class BaseMenu {
	string title;
public:
	BaseMenu(string s) : title(s) {}
	string getTitle() const { return title; }
	virtual void command() = 0;
	virtual ~BaseMenu() {}

};

class MenuItem : public BaseMenu {
public:
	MenuItem(string s) : BaseMenu(s) {}

	void command() {
		cout << getTitle() << " 메뉴가 선택됨" << endl;
		sleep(1);
	}
};

class PopupMenu : public BaseMenu {
	vector<BaseMenu*> v;
public:
	PopupMenu(string s) : BaseMenu(s) {} 
	void addMenu(BaseMenu *p) { v.push_back(p); }

	void command() {
	
		while (1) {

			system("clear");

			int sz = v.size();

			for (int i = 0; i < sz; i++) {
				cout << i+1 << ". " << v[i]->getTitle() << endl;
			}

			cout << sz+1 << ". 상위 메뉴로" << endl;
			
			cout << "메뉴를 선택하세요>> " << endl;

			int cmd;
			cin >> cmd;

			if (cmd == sz+1) break;
			if (cmd <= 0 || cmd > sz) continue;

			v[cmd-1]->command();
		}
	}
};

int main()
{
	PopupMenu* menubar = new PopupMenu("MENUBAR");
	PopupMenu* p1 = new PopupMenu("화면 설정");
	PopupMenu* p2 = new PopupMenu("소리 설정");

	menubar->addMenu(p1);
	menubar->addMenu(p2);
	menubar->addMenu(new MenuItem("버전 정보"));

	p1->addMenu(new MenuItem("해상도 조정"));
	p1->addMenu(new MenuItem("색상 조정"));
	p1->addMenu(new MenuItem("위치 조정"));

	p2->addMenu(new MenuItem("크기 조정"));
	p2->addMenu(new MenuItem("음악 조정"));

	menubar->command();

	return 0;
}

