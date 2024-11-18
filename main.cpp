#include <iostream>

using namespace std;

template <typename T>
class LinkedList {

	template <typename T>
	struct Node {
		T data;
		Node* next;
		Node* prev;

		Node(T value, Node* pNext = nullptr, Node* pPrev = nullptr) : data(value), next(pNext), prev(pPrev) {}
	};

	Node<T>* head;
	Node<T>* tail;
	size_t size;

public:

	LinkedList() : head(nullptr), tail(nullptr), size(0) {}


	LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
		Node<T>* p = other.head;

		while (p) {
			push_tail(p->data);
			p = p->next;
		}
	}


	void push_tail(const T value) {
		Node<T>* newNode = new Node<T>(value, nullptr, tail);

		if (!head) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = newNode;
		}

		++size;
	}


	void push_tail(const LinkedList& other) {
		Node<T>* p = other.head;

		while (p) {
			this->push_tail(p->data);
			p = p->next;
		}
	}

	
	void push_head(const T value) {
		Node<T>* newNode = new Node<T>(value, head, nullptr);

		if (!head) {
			head = tail = newNode;
		}
		else {
			head->prev = newNode;
			head = newNode;
		}

		++size;
	}


	void print() const {
		Node<T>* p = head;
		
		while (p) {
			cout << p->data << " ";
			p = p->next;
		}

		cout << endl;
	}


};

int main() {
	LinkedList<int> list;

	list.push_tail(2);
	list.push_tail(3);
	list.push_tail(15);

	LinkedList<int> copyList(list);

	cout << "Original list:" << endl;
	list.print();

	cout << "Copy list:" << endl;
	copyList.print();
	cout << endl;

	list.push_head(10);
	list.print();
}