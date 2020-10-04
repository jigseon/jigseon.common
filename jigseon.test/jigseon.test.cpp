#include "../jigseon.common/list.h"
#include "../jigseon.common/llist.h"
#include "../jigseon.common/HashTable.h"

using namespace jigseon;

void test_list();
void test_llist();
void test_HashTable();


int main()
{
	test_HashTable();
}

void test_HashTable()
{
	HashTable<int> ht;
	ht.add("asdf",1);
	ht.add("zxcz",2);
	ht.add("asdf", 3);
	ht.add("r2", 4);
	ht.add("ax", 5);
	ht.add("g3", 6);
	ht.add("asdf", 7);


	auto it = ht.begin();
	for (; it != ht.end(); it++)
	{
		cout << it->_key << it->_value << endl;
	}
}
void test_list()
{
	list<int> a;

	try
	{
		a.append(1);
		a.append(2);
		a.append(3);
		a.append(4);
		a.append(5);
		a.append(6);
		a.append(7);
	}
	catch (BadAllocException e)
	{
		e.print();
		exit(1);
	}

	auto it = a.begin();

	for (; it != a.end(); it++)
	{
		cout << *it;
	}
}
void test_llist()
{
	llist<int> a;

	try
	{
		a.append(1);
		a.append(2);
		a.append(3);
		a.append(4);
		a.append(5);
		a.append(6);
		a.append(7);
	}
	catch (BadAllocException e)
	{
		e.print();
		exit(1);
	}
	//a.Delete((llist_node<int> *)0x41234123424);
	auto it = a.begin();
	for (; it != a.end(); it++)
	{
		cout << it->_data << endl;
	}
	cout << "===============================================" << endl;
	a.remove(5);

	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << endl;
	}
	cout << "===============================================" << endl;
	a[4] = 10000;

	for (int i = 0; i < 6; i++)
	{
		cout << a[i] << endl;
	}
	cout << "===============================================" << endl;
	llist<int> b;
	b.append(-1);
	b.append(-2);
	b.append(-3);
	b.append(-4);

	a.extend(b);
	it = a.begin();
	for (; it != a.end(); it++)
	{
		cout << it->_data << endl;
	}
	cout << "===============================================" << endl;
	a.sort();
	it = a.begin();
	for (; it != a.end(); it++)
	{
		cout << it->_data << endl;
	}
	cout << "===============================================" << endl;
	a.reverse();
	it = a.begin();
	for (; it != a.end(); it++)
	{
		cout << it->_data << endl;
	}
}

