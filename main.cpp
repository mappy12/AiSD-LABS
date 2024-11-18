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

};

int main() {

}