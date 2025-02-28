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

	TreeElm* copyTree(TreeElm* node) {

		if (!node) return nullptr;

		TreeElm* newNode = new TreeElm(node->key);

		newNode->left = copyTree(node->left);
		newNode->right = copyTree(node->right);

		return newNode;
	}

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

	bool contains(TreeElm* node, int key) {

		if (!node) return false;

		if (key == node->key) return true;

		if (key < node->key) return contains(node->left, key);

		else return contains(node->right, key);
	}

public:

	Set() : root(nullptr) { }

	Set(int key) {
		root = new TreeElm(key);
	}

	Set(const Set& other) {
		root = copyTree(other.root);
	}

	Set& operator=(const Set& other) {
		if (this != &other) {
			clear(root);

			root = copyTree(other.root);
		}

		return *this;
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

	bool contains(int key) {
		return contains(root, key);
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
	
	cout << "1: " << (tree1.insert(1) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl;
	cout << "100: " << (tree1.insert(100) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl;
	cout << "52: " << (tree1.insert(52) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl;
	cout << "51: " << (tree1.insert(51) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl;
	cout << "9: " << (tree1.insert(9) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl;
	cout << "17: " << (tree1.insert(17) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl;
	cout << "36: " << (tree1.insert(36) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl;
	cout << "11: " << (tree1.insert(11) ? "Insertion SUCCESSFUL" : "Key already EXISTS") << endl << endl;

	cout << "Tree after insertion: ";
	tree1.print();
	cout << endl << endl;

	cout << "1: " << (tree1.erase(1) ? "Deletion SUCCESSFUL" : "Key NOT FOUND") << endl;
	cout << "9: " << (tree1.erase(9) ? "Deletion SUCCESSFUL" : "Key NOT FOUND") << endl;
	cout << "36: " << (tree1.erase(36) ? "Deletion SUCCESSFUL" : "Key NOT FOUND") << endl;
	cout << "100: " << (tree1.erase(100) ? "Deletion SUCCESSFUL" : "Key NOT FOUND") << endl << endl;

	cout << "Tree after deletion: ";
	tree1.print();
	cout << endl;
	cout << endl;

	Set tree2(tree1);

	cout << "Copy tree1 (Copy constructor): ";
	tree2.print();
	cout << endl;

	Set tree3 = tree1;
	cout << "Copy tree1 (Assignment operator): ";
	tree3.print();
	cout << endl;

}



