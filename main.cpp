#include <iostream>
#include <string>

#include "HashTable.cpp"

int main() {
	
	HashTable<int, int> hTable(64);

	hTable.insert(10, 10);
	hTable.insert(632, 256);
	hTable.insert(932, 72);

	hTable.print();

	cout << endl;

	int val = 76;

	cout << hTable.contains(val) << endl;

	cout << hTable.search(932) << endl;

	cout << hTable.erase(632) << endl;
	hTable.print();

	cout << endl;

}