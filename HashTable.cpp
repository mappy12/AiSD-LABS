#include <iostream>
#include <cmath>
#include <string>

constexpr size_t TABLE_SIZE = 64;

using namespace std;

template<typename K, typename T>
class HashTable {

	struct Item {
		K key;
		T value;
		bool isEmpty = true;

		Item() : key(), value() {}
		Item(const K key, const T value) : key(key), value(value), isEmpty(false) {}
	};


	Item* elements;
	size_t capacity = TABLE_SIZE;
	size_t count = 0;


	size_t stringToInt(const std::string key) {

		size_t hash = 0;

		const size_t mod = 1e9 + 7;

		for (char c : key) {

			hash = (hash * 31 + c) % mod;

		}

		return hash;
	}


	void resize() {

		Item* newElements = new Item[capacity * 2]();

		for (size_t i = 0; i < capacity; ++i) {
			if (!elements[i].isEmpty) {

				size_t newIdx = multiplicativeHash(elements[i].key);
				size_t j = 0;

				while (!newElements[newIdx].isEmpty && j < capacity * 2) {
					++j;
					newIdx = probe(newIdx, j);
				}

				newElements[newIdx] = elements[i];

			}
		}

		delete[] elements;

		elements = newElements;

		capacity = capacity * 2;

	}


	size_t probe(size_t index, size_t i) const {
        return (index + i) % capacity;
    }


public:

	HashTable(size_t capacity) : capacity(capacity) {

		elements = new Item[capacity]();

	}


	HashTable(const HashTable& other) :
		capacity(other.capacity),
		count(other.count),
		elements(new Item[other.capacity]) {

		for (size_t i = 0; i < other.capacity; ++i) {
			elements[i] = other.elements[i];
		}

	}


	~HashTable() {

		delete[] elements;

	}


	size_t multiplicativeHash(T key) {

		size_t a = 2654435769u;
		
		double x = (static_cast<double>(a) / 32) * key;
		double fractPart = x - floor(x);

		return static_cast<int>(fractPart * capacity);

	}


	bool insert(K key, const T &value) {

		if (count >= capacity - 5) {
			resize();
		}

		size_t index = multiplicativeHash(key);
		size_t i = 0;

		while (!elements[index].isEmpty && i < capacity) {
			
			if (elements[index].key == key) return false;

			++i;

			index = probe(index, i);  

		}

		elements[index] = Item(key, value);

		++count;

		return true;

	}


	void print() {
		
		for(size_t i = 0; i < capacity; ++i) {

			if (!elements[i].isEmpty) {

				cout << "[" << i << "]: Key = " << elements[i].key << ", Value = " << elements[i].value << endl;

			}

		}

	}


	bool contains(T &value) {

		for (size_t i = 0; i < capacity; ++i) {

			if (!elements[i].isEmpty && elements[i].value == value) {

				return true;

			}

		}

		return false;

	}

};
