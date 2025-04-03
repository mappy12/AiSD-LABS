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

	int val1 = 76;

	cout << hTable.contains(val1) << endl;

	cout << hTable.search(932) << endl;

	cout << hTable.erase(632) << endl;
	hTable.print();

	int val2 = 20;

	hTable.insertOrAssign(932, val2);

	hTable.print();

	cout << hTable.countHashMatches(932);

	cout << endl;
}