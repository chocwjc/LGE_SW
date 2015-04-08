#include <iostream>

using namespace std;

template<typename T> class node {
	node<T>* next;
	T data;
public:
	node() : data(0), next(NULL) { }
	node(T data) : data(data), next(this) {	}
	node(T data, node<T>& prev) : data(data), next(prev.next) {
		prev.next = this;
	}
	T get_data() { 
		return data;
	}
	node* get_next() const {
		return next;
	}
	void set_nextof(node<T>& pnode) {
		this->next = pnode.next;
		pnode.next = this;
	}
	void remove(node<T>& pnode) {
		pnode.next = next;
	}
	bool is_last() const {
		return next == NULL;
	}
};

template<typename T> class Stack {
	unsigned size;
	node<T> head;

public:
	Stack() : size(0) {}
	~Stack() {
	}
	void push(T data) {
		node<T>* pnode = new node<T>(data, head);
		size++;
	}
	T top() {
		return head.get_next()->get_data();
	}
	T pop() {
		T data;
		node<T>* node;

		node = head.get_next();
		data = node->get_data();

		node->remove(head);
		delete node;

		return data;
	}
	Stack(const Stack<T>& s) {
		size = s.size;
		node<T>* scur = s.head.get_next();
		node<T>* ncur = &head;
		while (scur != NULL) {
			T data = scur->get_data();
			node<T>* nnode = new node<T>(data);
			nnode->set_nextof(*ncur);
			ncur = nnode;
			scur = scur->get_next();
		}
	}
	Stack<T>& operator=(const Stack<T>& s) {
		size = s.size;
		node<T>* scur = s.get_head().get_next();
		node<T>* ncur = &head;
		while (scur != NULL) {
			T data = scur->get_data();
			node<T>* nnode = new node<T>(data);
			nnode->set_nextof(*ncur);
			ncur = nnode;
			scur = scur->get_next();
		}
	}
};


int main()
{
	int n;
	Stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);
	s.push(50);

	Stack<int> s2 = s;
	
	n = s2.top();
	cout << n << endl;

	s2.pop();
	n = s2.pop();
	s2.pop();
	cout << n << endl;
	n = s2.pop();
	cout << n << endl;
	
	return 0;
}
