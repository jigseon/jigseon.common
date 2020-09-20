#include "../jigseon.common/list.h"


using namespace jigseon;



int main()
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
		a.remove(1);
		a.remove(2);
		a.remove(5);
		a.remove(3);
		a.remove(4);
		a.remove(6);
		a.remove(7);
	}
	catch (BadAllocException e)
	{
		e.print();
		exit(1);
	}


}


/*
int main()
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
}*/