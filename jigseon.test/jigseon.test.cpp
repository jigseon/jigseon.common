#include "../jigseon.common/list.h"
#include "../jigseon.common/llist.h"
#include "../jigseon.common/HashTable.h"
#include "../jigseon.common/Tree.h"
#include "../jigseon.common/RBTree.h"
using namespace jigseon;

void test_list();
void test_llist();
void test_HashTable();
void test_tree();
void test_RBTree();

int main()
{
//	test_list();
	test_tree();
}

void test_RBTree()
{
	RBTree<int,int> tree;
}
void test_tree()
{
	Tree<int, int> tree;
	tree.set_root(1,1);
	tree.set_current_as_root();
	tree.get_current_node()->set_left_child(3,3);
	tree.get_current_node()->set_right_child(2, 2);
	tree.move_to_left();
	tree.get_current_node()->set_left_child(5, 5);
	tree.get_current_node()->set_right_child(7, 7);
	tree.move_to_right();
	tree.get_current_node()->set_left_child(6, 6);
	tree.get_current_node()->set_right_child(8, 8);

	llist<TreeNode<int,int> *> l = tree.inorder_traverse();
	for (auto it = l.begin(); it != l.end(); it++)
	{
		cout << it->_data->get_key()<< " , " << it->_data->get_data()  << endl;
	}
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
		a.append(52351);
		a.append(123412);
		a.append(124124);
		a.append(4);
		a.append(124);
		a.append(41234);
		a.append(3);
		a.append(124);
		a.append(134);
		a.append(1);
		a.append(7);
		a.append(5);
		a.append(1243);
		a.append(7);
	}
	catch (BadAllocException e)
	{
		e.print();
		exit(1);
	}
	auto it = a.begin();
	for (int i =0 ; it != a.end();i++, it++)
	{
		cout <<i<<". "<< *it << endl;
	}
	cout << "------------------------------" << endl;
	a.sort();
	it = a.begin();
	for (int i = 0; it != a.end(); i++, it++)
	{
		cout << i << ". " << *it << endl;
	}
	cout << "------------------------------" << endl;
	a.reverse();
	it = a.begin();
	for (int i = 0; it != a.end(); i++, it++)
	{
		cout << i << ". " << *it << endl;
	}


}
void test_llist()
{
	llist<int> a;

	try
	{
		a.append(52351);
		a.append(123412);
		a.append(124124);
		a.append(4);
		a.append(124);
		a.append(41234);
		a.append(3);
		a.append(124);
		a.append(134);
		a.append(1);
		a.append(7);
		a.append(5);
		a.append(1243);
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

