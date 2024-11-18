#include <iostream>

using namespace std;

template <typename T>
class LinkedList {

	template <typename T>
	struct Node {
		T data;
		Node* next;
		Node* prev;
	};

	Node<T>* head;
	Node<T>* tail;
	size_t size;

public:

	LinkedList() : head(nullptr), tail(nullptr), size(0) {}

	LinkedList(const LinkedList& other) {

	}

};

int main() {

}