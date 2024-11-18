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


	void push_head(const LinkedList& other) {
		Node<T>* p = other.tail;

		while (p) {
			push_head(p->data);
			p = p->prev;
		}
	}

	
	void pop_tail() {
		if (!tail) {
			throw underflow_error("List is empty");
		}

		Node<T>* temp = tail;

		tail = tail->prev;

		if (tail) {
			tail->next = nullptr;
		}
		else {
			head = nullptr;
		}

		delete temp;
		--size;
	}


	void pop_head() {
		if (!head) {
			throw underflow_error("List is empty");
		}

		Node<T>* temp = head;

		head = head->next;

		if (head) {
			head->prev = nullptr;
		}
		else {
			tail = nullptr;
		}

		delete temp;
		--size;
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

	cout << "Original list:\n" << endl;
	list.print();

	cout << "\nCopy list:\n" << endl;
	copyList.print();
	cout << endl;

	cout << "Push head elm:\n" << endl;

	list.push_head(10);
	list.print();

	cout << "\nPush head other Node:" << endl;

	list.push_head(copyList);
	cout << endl;
	list.print();

	cout << "\nPop tail:\n" << endl;
	list.pop_tail();
	list.print();

	cout << "\nPop head:\n" << endl;
	list.pop_head();
	list.print();
}