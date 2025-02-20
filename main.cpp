#include <iostream>

class Set {

	struct TreeElm {
		int data;
		TreeElm* left;
		TreeElm* right;

		TreeElm() : data(0), left(nullptr), right(nullptr) { }
		TreeElm(int data, TreeElm* left, TreeElm* right) : data(data), left(left), right(right) { }
	};

	TreeElm* root;

};

