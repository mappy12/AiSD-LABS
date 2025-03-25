#include <cmath>

constexpr size_t TABLE_SIZE = 32;


template<typename T, typename K>
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

public:

	HashTable(size_t capacity) : capacity(capacity) {

		elements = new Item[capacity];

	}

	~HashTable() {

		delete[] elements;

	}

	int hash(long long key, size_t tableSize) {

		double A = (sqrt(5) - 1) / 2;

		double x = key * A;

		double fract_part = x - static_cast<int>(x);

		return static_cast<int>(tableSize * fract_part);

	}

}; 