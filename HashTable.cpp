constexpr size_t TABLE_SIZE = 32;


template<typename T, typename K>
class HashTable {

	struct Item {
		K key;
		T value;

		Item() : key(), value() {}
		Item(const key, const value) : key(key), value(value) {}
	};

	Item* elements;
	size_t capacity = TABLE_SIZE;
	size_t count = 0;

	HashTable(size_t capacity) : capacity(capacity) {
		elements = new Item[capacity];
	}

	~HashTable() {
		delete[] elements;
	}
}; 