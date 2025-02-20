#include <iostream>

using namespace std;

class Set {

	struct TreeElm {
		int data;
		TreeElm* left;
		TreeElm* right;

		TreeElm() : data(0), left(nullptr), right(nullptr) { }

		TreeElm(int data) : data(data), left(nullptr), right(nullptr) { }
	};

	TreeElm* root;

public:

	Set() : root(nullptr) { }

	Set(int data) {
		root = new TreeElm(data);
	}

	~Set() {
		clear(root);
	}

	void clear(TreeElm* node) {
		if (!node) return;

		clear(node->left);
		clear(node->right);

		delete node;
	}

};


int main() {
	cout << "lab1";
}



