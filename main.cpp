#include <iostream>

using namespace std;

class Set {

	struct TreeElm {
		int key;
		TreeElm* left;
		TreeElm* right;

		TreeElm() : key(0), left(nullptr), right(nullptr) { }

		TreeElm(int key) : key(key), left(nullptr), right(nullptr) { }
	};

	TreeElm* root;

	bool insert(TreeElm*& node, int key) {

		if (!node) {

			node = new TreeElm(key);
			return true;

		}

		if (key < node->key) {

			if (!node->left) {

				node->left = new TreeElm(key);
				return true;

			}
			else {

				return insert(node->left, key);

			}


		}
		else if (key > node->key) {

			if (!node->right) {

				node->right = new TreeElm(key);
				return true;

			}
			else {

				return insert(node->right, key);

			}
		}

		return false;
	}

	bool erase(TreeElm*& node, int key) {

		if (!node) {
			return false;
		}

		if (key < node->key) {

			return erase(node->left, key);

		}

		else if (key > node->key) {

			return erase(node->right, key);

		}

		else {

			if (!node->left && !node->right) {

				delete node;
				node = nullptr;
				return true;

			}

			else if (!node->left) {

				TreeElm* temp = node;
				node = node->right;
				delete temp;
				
				return true;

			}

			else if (!node->right) {
				
				TreeElm* temp = node;
				node = node->left;
				delete temp;

				return true;

			} 

			else {
				TreeElm* minRight = findMin(node->right);

				node->key = minRight->key;
				return erase(node->right, minRight->key);
			}

		}

	}

	TreeElm* findMin(TreeElm* node) {

		while (node->left) node = node->left;
		return node;

	}

public:

	Set() : root(nullptr) { }

	Set(int key) {
		root = new TreeElm(key);
	}

	Set(const Set& other) {

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

	bool insert(int key) {
		return insert(root, key);
	}

	bool erase(int key) {
		return erase(root, key);
	}

	void inOrder(TreeElm* node) {
		if (!node) return;
		inOrder(node->left);

		cout << node->key << " ";

		inOrder(node->right);
	}

	void print() {
		inOrder(root);
	}

};


int main() {
	Set tree1(10);
	
	tree1.insert(1);
	tree1.insert(100);
	tree1.insert(52);
	tree1.insert(51);
	tree1.insert(9);
	tree1.insert(17);
	tree1.insert(36);
	tree1.insert(11);

	tree1.print();
	cout << endl << endl;

	tree1.erase(1);
	tree1.erase(100);
	tree1.erase(52);
	tree1.erase(51);

	tree1.print();
	cout << endl;
}



