#include "HashTable.h"


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

	cout << hTable.countHashMatches(932) << endl;

	HashTable<int, int> hTable2(64);
	hTable2.insert(40, 90);
	hTable2.insert(921, 481);
	hTable2.insert(183, 8);

	cout << endl << "hTable2: " << endl;
	hTable2.print();

	cout << "hTable2 after hTable2 = hTable: " << endl;
	hTable2 = hTable;

	hTable2.print();

	string str1 = "h";

	cout << hTable.pearsonHash(str1);

	cout << endl;
}