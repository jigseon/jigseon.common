#include "../jigseon.common/list.h"
#include "../jigseon.common/llist.h"
#include "../jigseon.common/HashTable.h"
#include "../jigseon.common/Tree.h"
#include "../jigseon.common/RBTree.h"
#include "../jigseon.common/Graph.h"
#include "../jigseon.common/BigNumber.h"
using namespace jigseon;

void test_list();
void test_llist();
void test_HashTable();
void test_tree();
void test_RBTree();
void test_graph();
void test_BigInteger();


int main()
{

	test_BigInteger();
}

void test_BigInteger()
{
	BigInteger b(1000000);
	cout << b << endl;
	b = b + 1000000000;
	cout << b << endl;
	b = b - "1000000000";
	cout << b << endl;
	b = b - "1000000000";
	cout << b << endl;
	b = b + "100000000000";
	cout << b << endl;
	b = b * 10;
	cout << b << endl;
	b = b * "10";
	cout << b << endl;
	b = b / "1000000000";
	cout << b << endl;

}


void test_graph()
{
	Graph<int,int> gr(5);
	gr.add_vertex(1,1);
	gr.add_vertex(2, 2);
	gr.add_vertex(3, 3);
	gr.add_vertex(4, 4);
	gr.add_vertex(5, 5);
	gr.add_edge(1,2,3);
	gr.add_edge(1, 3, 4);
	gr.add_edge(2, 5, 4);
	gr.add_edge(3, 4, 2);
	gr.add_edge(4, 5, 10);

	llist<Vertex<int,int>*> l = gr.DFS();
	for (auto it = l.begin(); it != l.end();it++) {
		cout << it->_data->_data <<","<< it->_data->_data << endl;
	}

	cout << endl << endl << endl;

	llist<Vertex<int, int>*> l2 = gr.WFS();
	for (auto it2 = l2.begin(); it2 != l.end(); it2++) {
		cout << it2->_data->_data << "," << it2->_data->_data << endl;
	}

	gr.dijkstra();
}
void test_RBTree()
{

	jigseon::RBTree<int,int> tree;
	tree.insert_node(5, 5);
	tree.insert_node(6, 6);
	tree.insert_node(7, 7);
	tree.insert_node(1,1);
	tree.insert_node(2, 2);
	tree.insert_node(3, 3);

	llist<RBTreeNode<int, int>*> l = tree.preorder_traverse();
	tree.levelorder_print();
	tree.delete_node(l[0]);
	cout <<endl<<endl;
	tree.levelorder_print();
	tree.inorder_traverse();
	tree.postorder_traverse();
	cout << endl << tree.find(2)->get_data();
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

