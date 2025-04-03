#pragma once

#include <iostream>
#include <cmath>
#include <string>

constexpr size_t TABLE_SIZE = 64;

extern unsigned char pearsonTable[256]; 

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
    size_t capacity;
    size_t count;

    void resize();
    size_t probe(size_t index, size_t i) const;

public:
    HashTable(size_t capacity = TABLE_SIZE);
    HashTable(const HashTable& other);
    ~HashTable();

    size_t multiplicativeHash(T key);
    bool insert(K key, const T &value);
    bool contains(T &value);
    T* search(K key);
    bool erase(K key);
    void insertOrAssign(K key, T &value);
    int countHashMatches(K key);
    int pearsonHash(std::string& str);
    void print();

    HashTable& operator=(const HashTable& other);
};