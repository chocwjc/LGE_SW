#include <iostream>
#include <vector>
using namespace std;

// 파워포인트 같은 도형 편집기를 만들어 봅시다.
// 1. 모든 도형을 타입화 한다.
//
// 2. 공통의 부모가 있다면 모든 도형을 묶어서 관리할 수 있다.
//
// 3. 모든 도형(자식) 의 공통의 특징은 부모 클래스에도 존재해야 한다.
//    (-> 부모 포인터로 사용해야 하는 자식의 모든 특징들)
//    리스코프의 치환 법칙
//
// 4. 부모의 함수중 자식이 재정의하는 모든 함수는 반드시 가상함수여야 한다.
// 		"가상 함수가 아닌 함수를 재정의 하지 말라"
//
// 5. 기능은 추가될수 있어야 하며, 기존 코드는 수정되지 말아야 한다.
// 		open-close principle
// 		
// 6. typecode 를 다형성으로 교체		
//
// 7. Prototype 디자인 패턴: 기존 객체의 복사본을 통해서 새로운 객체를 만드는 패턴
// 		cloneable(), clone(), copy() ..
//
// 8. 공통성과 가변성의 분리를 설계 방법
// 		변하는 것에서 변하지 않는 것을 분리한다.
// 		
// 		Template mehtod pattern:  전체적인 실행 흐름은 부모가 비 가상 함수로 제공하고, 
// 															자식마다 변해야 하는 부분을	가상함수화 하여 자식이 변경할 수 있도록 한다.
// 															(Draw 내 락을 처리하는것은 부모의 비 가상함수, Draw는 가상함수인 drawimple 호출)
// 															가장 많이 사용하는 패턴

class Shape {
public:
	void draw() {
		cout << "Mutex lock" << endl;
		drawImple();
		cout << "Mutex unlock" << endl;
  }
	virtual void drawImple() {}
	virtual Shape* clone() { return new Shape(*this); }
};

class Rect : public Shape {
public:
	void drawImple() { cout << "Rect draw" << endl; }
	Rect* clone() { return new Rect(*this); }
};

class Circle : public Shape {
	public:
	void drawImple() { cout << "Circle draw" << endl; }
	Circle* clone() { return new Circle(*this); }
};

int main()
{
	vector<Shape*> v;

	while (1) {
		int cmd;
		cin >> cmd;

		if 			(cmd == 1) v.push_back(new Rect);
		else if (cmd == 2) v.push_back(new Circle);
		else if (cmd == 8) {

			cout << "몇번째 도형의 복사본을 만들까요> >> ";
			cin >> cmd;


			v.push_back(v[cmd]->clone());

		} else if (cmd == 9) {

			for (int i = 0; i < v.size(); i++) {

				// 다형성: 동일 함수를 호출하는 모양이지만, 객체에 따라 다른 함수를 호출하는 것
				v[i]->draw();
			}
		}
	}
}
