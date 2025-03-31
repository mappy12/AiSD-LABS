#include <cmath>
#include <string>

constexpr size_t TABLE_SIZE = 64;


template<typename K, typename T>
class HashTable {

	struct Item {
		K key;
		T value;

		Item() : key(), value() {}
		Item(const K key, const T value) : key(key), value(value) {}
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

		return fractPart * capacity;

	}



};
