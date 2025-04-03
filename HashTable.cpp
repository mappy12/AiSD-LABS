#include "HashTable.h"

unsigned char pearsonTable[256] = {
    98,  6,  85, 150, 36,  23, 83,  39, 240, 204, 234, 200, 22,  4,   132, 248,
    3,   94,  177, 181, 190, 83, 129, 12,  45,  203, 37,  225, 125, 138, 54,  248,
    5,   42,  197, 91,  219, 196, 95,  74,  21,  5,   98,  151, 215, 127, 141, 41,
    9,   177, 69,  254, 206, 188, 52,  98,  93,  220, 198, 184, 9,   101, 18,  203,
    190, 6,   160, 37,  8,   59,  179, 231, 146, 136, 76,  179, 77,  189, 125, 157,
    211, 55,  185, 210, 145, 191, 129, 65,  96,  83,  17,  16,  255, 190, 37,  187,
    132, 78,  3,   40,  185, 241, 106, 191, 11,  224, 232, 183, 200, 166, 98,  67,
    157, 4,   99,  71,  133, 180, 95,  66,  62,  89,  254, 211, 114, 51,  1,   166,
    192, 99,  185, 161, 248, 61,  22,  78,  44,  157, 65,  50,  30,  53,  61,  74,
    181, 230, 47,  167, 54,  98,  56,  142, 59,  45,  67,  51,  250, 131, 143, 190,
    141, 40,  128, 137, 56,  220, 153, 11,  239, 95,  98,  192, 99,  50,  100, 220,
    43,  115, 50,  87,  127, 56,  96,  4,   42,  161, 10,  41,  53,  49,  206, 163,
    33,  14,  26,  98,  198, 150, 181, 207, 127, 123, 232, 110, 226, 71,  213, 44,
    247, 54,  101, 33,  121, 42,  168, 39,  153, 52,  92,  55,  232, 193, 35,  251,
    232, 29,  142, 252, 192, 90,  64,  8,   177, 43,  111, 49,  15,  58,  3,   69,
    139, 85,  2,   200, 132, 26,  53,  128, 97,  126, 47,  63,  234, 19,  192, 3
};


template<typename K, typename T>
void HashTable<K, T>::resize() {

	Item* newElements = new Item[capacity * 2]();

	for (size_t i = 0; i < capacity; ++i) {
		if (!elements[i].isEmpty) {

			size_t newIdx;

			if constexpr (is_same<K, string>::value) {

				newIdx = pearsonHash(elements[i].key) % (capacity * 2);
				
			} else {

				newIdx = multiplicativeHash(elements[i].key);

			}

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


template<typename K, typename T>
size_t HashTable<K,T>::probe(size_t index, size_t i) const {
	return (index + i) % capacity;
}


template<typename K, typename T>
HashTable<K,T>::HashTable(size_t capacity) : capacity(capacity) {

	elements = new Item[capacity]();

}


template<typename K, typename T>
HashTable<K,T>::HashTable(const HashTable& other) :
	capacity(other.capacity),
	count(other.count),
	elements(new Item[other.capacity]) {

	for (size_t i = 0; i < other.capacity; ++i) {
		elements[i] = other.elements[i];
	}

}


template<typename K, typename T>
HashTable<K,T>::~HashTable() {

	delete[] elements;

}


template<>
size_t HashTable<int, int>::hash(int key) {

    return multiplicativeHash(key); 
	
}


template<>
size_t HashTable<std::string, int>::hash(std::string key) {

    return pearsonHash(key);  

}

template<typename K, typename T>
size_t HashTable<K,T>::multiplicativeHash(int key) {

	size_t a = 2654435769u;
	
	double x = (static_cast<double>(a) / 32) * key;
	double fractPart = x - floor(x);

	return static_cast<int>(fractPart * capacity);

}


template<typename K, typename T>
bool HashTable<K,T>::insert(K key, const T &value) {

	if (count >= capacity - 20) {
		resize();
	}

	size_t index = hash(key);
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


template<typename K, typename T>
void HashTable<K,T>::print() {
	
	for(size_t i = 0; i < capacity; ++i) {

		if (!elements[i].isEmpty) {

			cout << "[" << i << "]: Key = " << elements[i].key << ", Value = " << elements[i].value << endl;

		}

	}

	cout << endl;

}


template<typename K, typename T>
bool HashTable<K,T>::contains(T &value) {

	for (size_t i = 0; i < capacity; ++i) {

		if (!elements[i].isEmpty && elements[i].value == value) {

			return true;

		}

	}

	return false;

}


template<typename K, typename T>
T* HashTable<K,T>::search(K key) {

	size_t index = hash(key);
	size_t i = 0;

	while (!elements[index].isEmpty && i < capacity) {

		if (elements[index].key == key) {
			return &elements[i].value;
		}

		++i;

		index = probe(index, i);

	}

	return nullptr;

}


template<typename K, typename T>
bool HashTable<K,T>::erase(K key) {

	size_t index = hash(key);
	size_t i = 0;

	while (!elements[index].isEmpty && i < capacity) {

		if (elements[index].key == key) {

			elements[index].isEmpty = true;
			--count;
			return true;

		}

		++i;

		index = probe(index, i);

	}

	return false;

}


template<typename K, typename T>
void HashTable<K,T>::insertOrAssign(K key, T &value) {

	size_t index = hash(key);
	size_t i = 0;

	while(!elements[index].isEmpty && i < capacity) {

		if (elements[index].key == key) {

			elements[index].value = value;
			return;

		}

		++i;

		index = probe(index, i);

	}

	elements[index] = Item(key, value);
	++count;

}


template<typename K, typename T>
int HashTable<K,T>::countHashMatches(K key) {

	size_t hashVal = hash(key);
	size_t countElm = 0;

	for (size_t i = 0; i < capacity; ++i) {

		if(!elements[i].isEmpty && hash(elements[i].key) == hashVal) {
			
			++countElm;

		}

	}

	return countElm;

}


template<typename K, typename T>
size_t HashTable<K,T>::pearsonHash(const string& str) {
	unsigned char hash = 0;

	for (char c : str) {

		hash = pearsonTable[hash ^ static_cast<unsigned char>(c)];
		
	}

	return static_cast<size_t>(hash);
}


template<typename K, typename T>
bool HashTable<K, T>::compareHashes(std::string& str1, std::string& str2) {
    return pearsonHash(str1) == pearsonHash(str2);
}


template<typename K, typename T>
HashTable<K,T>& HashTable<K,T>::operator=(const HashTable& other) {

	if(this != &other) {

		delete[] elements;

		capacity = other.capacity;
		count = other.count;

		elements = new Item[capacity]();

		for (size_t i = 0; i < capacity; ++i) {

			elements[i] = other.elements[i];

		}

	}

	return *this;
}


template class HashTable<int, int>;
template class HashTable<string,int>;