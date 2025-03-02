#include <iostream>
#include <chrono>

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



size_t lcg() {

	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;

}


double insertionTime(Set& tree, int elementsCount) {

	auto start = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < elementsCount; ++i) {
		tree.insert(lcg());
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> diff = end - start;

	return diff.count();

}

double searchTime(Set& tree, int attempts) {

	auto start = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < attempts; ++i) {

		tree.contains(lcg());

	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> diff = end - start;

	return diff.count();

}

double  deletionTime(Set& tree, int attempts) {

	auto start = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < attempts; ++i) {

		tree.erase(lcg());

	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> diff = end - start;

	return diff.count();

}

double insertionTime(vector<int> vector, int elementsCount) {

	auto start = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < elementsCount; ++i) {
		vector.push_back(lcg());
	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> diff = end - start;

	return diff.count();

}

double searchTime(vector<int> vector, int attempts) {

	auto start = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < attempts; ++i) {

		auto item = find(vector.begin(), vector.end(), lcg());

	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> diff = end - start;

	return diff.count();

}

double  deletionTime(vector<int> vector, int attempts) {

	auto start = chrono::high_resolution_clock::now();

	for (size_t i = 0; i < attempts; ++i) {

		int key = lcg();
		auto item = find(vector.begin(), vector.end(), key);
		if (item != vector.end()) {
			vector.erase(item);
		}

	}

	auto end = chrono::high_resolution_clock::now();

	chrono::duration<double, milli> diff = end - start;

	return diff.count();

}

void getAvgTime(Set& btree) {

	cout << "------------------------------------------------------------------------------" << endl << endl;
	cout << "/////////////////////////////" << "Getting average time (binary tree)" << "/////////////////////////////" << endl;

	const size_t insertionAttempts = 100;
	const size_t searchAttempts = 1000;
	const size_t deletionAttempts = 1000;

	vector<size_t> sizes = { 1000, 10000, 100000 };

	for (size_t size : sizes) {

		double totalInsertionTime = 0.0;
		double totalSearchTime = 0.0;
		double totalDeletionTime = 0.0;

		for (size_t i = 0; i < insertionAttempts; ++i) {

			Set tree;
			totalInsertionTime += insertionTime(tree, size);

		}

		for (size_t i = 0; i < size; ++i) {

			btree.insert(lcg());

		}

		for (size_t i = 0; i < deletionAttempts; ++i) {

			totalSearchTime += searchTime(btree, 1);

		}

		for (size_t i = 0; i < searchAttempts; ++i) {

			totalDeletionTime += deletionTime(btree, 1);

		}

		double avgInsertionTime = totalInsertionTime / insertionAttempts;
		double avgSearchTime = totalSearchTime / searchAttempts;
		double avgDeletionTime = totalDeletionTime / deletionAttempts;

		cout << endl << endl << "Size: " << size << endl << endl;

		cout << "Avg insertion time: " << avgInsertionTime << " milliseconds" << endl;
		cout << "Avg search time: " << avgSearchTime << " milliseconds" << endl;
		cout << "Avg deletion time: " << avgDeletionTime << " milliseconds" << endl;
	}
}


void getAvgTime(vector<int> vec) {

	cout << "------------------------------------------------------------------------------" << endl << endl;
	cout << "/////////////////////////////" << "Getting average time (vector)" << "/////////////////////////////" << endl;

	const size_t insertionAttempts = 100;
	const size_t searchAttempts = 1000;
	const size_t deletionAttempts = 1000;

	vector<size_t> sizes = { 1000, 10000, 100000 };

	for (size_t size : sizes) {

		double totalInsertionTime = 0.0;
		double totalSearchTime = 0.0;
		double totalDeletionTime = 0.0;

		for (size_t i = 0; i < insertionAttempts; ++i) {

			vector<int> vec1;
			totalInsertionTime += insertionTime(vec1, size);

		}

		for (size_t i = 0; i < size; ++i) {

			vec.push_back(lcg());

		}

		for (size_t i = 0; i < deletionAttempts; ++i) {

			totalSearchTime += searchTime(vec, 1);

		}

		for (size_t i = 0; i < searchAttempts; ++i) {

			totalDeletionTime += deletionTime(vec, 1);

		}

		double avgInsertionTime = totalInsertionTime / insertionAttempts;
		double avgSearchTime = totalSearchTime / searchAttempts;
		double avgDeletionTime = totalDeletionTime / deletionAttempts;

		cout << endl << endl << "Size: " << size << endl << endl;

		cout << "Avg insertion time: " << avgInsertionTime << " milliseconds" << endl;
		cout << "Avg search time: " << avgSearchTime << " milliseconds" << endl;
		cout << "Avg deletion time: " << avgDeletionTime << " milliseconds" << endl;
	}
}


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
	cout << endl << endl << endl;
	
	Set tree;
	getAvgTime(tree);

	vector<int> vec;
	getAvgTime(vec);

	return 0;
}
