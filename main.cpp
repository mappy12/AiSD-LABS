#include <iostream>
#include <string>

#include "HashTable.cpp"

int main() {
	
	HashTable<int, int> hTable(64);

	hTable.insert(10, 10);
	hTable.insert(632, 256);
	hTable.insert(932, 72);

	hTable.print();

}