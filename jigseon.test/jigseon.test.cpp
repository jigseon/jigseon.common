#include "../jigseon.common/list.h"
#include "../jigseon.common/llist.h"
#include "../jigseon.common/HashTable.h"
#include "../jigseon.common/Tree.h"
#include "../jigseon.common/RBTree.h"
#include "../jigseon.common/Graph.h"
#include "../jigseon.common/BigNumber.h"
#include "../jigseon.common/ExceptionClass.h"
using namespace jigseon;

void TU_list();
void TU_llist();
void test_HashTable();
void test_tree();
void test_RBTree();
void test_graph();
void test_BigInteger();


int main()
{
	try
	{
		TU_list();
		TU_llist();
	}
	catch(TestException e)
	{
		e.print();
		exit(1);
	}

	
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
void TU_list()
{
	//////////////////////////////////////////
	// TU_list_01
	list<int> a;
	list<string> b("test");
	list<double> c(15, 10);
	list<double> d = c;

	if (a.count() != 0)
		throw TEST("TU_list_01_1");

	if(b.count() != 1 ||  b[0] !="test" )
		throw TEST("TU_list_01_2");
	
	if (c.count() != 10)
		throw TEST("TU_list_01_3");


	double TU_list_01_3_res = 0;
	for (int i = 0; i < 10;i++)
		TU_list_01_3_res += c[i];

	if(TU_list_01_3_res != 150)
		throw TEST("TU_list_01_3");

	if (d.count() != 10 || &d[0] == &c[0])
		throw TEST("TU_list_01_4");

	double TU_list_01_4_res = 0;
	for (int i = 0; i < 10; i++)
		TU_list_01_4_res += d[i];

	if (TU_list_01_4_res != 150)
		throw TEST("TU_list_01_4");

	//////////////////////////////////////////
	//////////////////////////////////////////
	// TU_list_02
	list<int> TU_list_02;
	int TU_list_02_sum=0;
	for (int i = 1; i <= 73; i++)
	{
		TU_list_02.append(i);
	}

	if (TU_list_02.allocated_elements() != 88)
		throw TEST("TU_list_02");
	if (TU_list_02.nr_list_nodes() != 73)
		throw TEST("TU_list_02");
	for (int i = 0; i < TU_list_02.nr_list_nodes(); i++)
	{
		TU_list_02_sum += TU_list_02[i];
	}
	if (TU_list_02_sum != 2701)
		throw TEST("TU_list_02");

	TU_list_02.remove(10); //87,72
	TU_list_02.remove(20); //86,71
	TU_list_02.remove(30); //85,70
	TU_list_02.remove(40); //84,69
	TU_list_02.remove(50); //83,68

	TU_list_02.append(10); //83,69
	TU_list_02.append(-10); //83,70
	TU_list_02.append(10); //83,71
	TU_list_02.append(-10); //83,72
	TU_list_02.append(10); //83,73
	TU_list_02.append(-10); //83,74
	TU_list_02.append(10); //83,75
	TU_list_02.append(-10); //83,76
	TU_list_02.append(10); //83,77
	TU_list_02.append(-10); //83,78
	TU_list_02.append(50); //83,79
	TU_list_02.append(40); //83,80
	TU_list_02.append(30); //83,81
	TU_list_02.append(20); //83,82
	TU_list_02.append(10); //83,83
	TU_list_02.append(10); //100,84

	TU_list_02_sum = 0;
	if (TU_list_02.allocated_elements() != 100)
		throw TEST("TU_list_02");
	if (TU_list_02.nr_list_nodes() != 84)
		throw TEST("TU_list_02");
	for (int i = 0; i < TU_list_02.nr_list_nodes(); i++)
	{
		TU_list_02_sum += TU_list_02[i];
	}
	if (TU_list_02_sum != 2711)
		throw TEST("TU_list_02");

	//////////////////////////////////////////
	//////////////////////////////////////////
	// TU_list_03
	list<int> TU_list_03;
	int TU_list_03_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_list_03.insert(i,0);
	}

	if (TU_list_03.allocated_elements() != 88)
		throw TEST("TU_list_03");
	if (TU_list_03.nr_list_nodes() != 73)
		throw TEST("TU_list_03");
	if(TU_list_03[0] != 73 || TU_list_03[72]!=1)
		throw TEST("TU_list_03");
	for (int i = 0; i < TU_list_03.nr_list_nodes(); i++)
	{
		TU_list_03_sum += TU_list_03[i];
	}
	if (TU_list_03_sum != 2701)
		throw TEST("TU_list_03");


	TU_list_03.remove(10); //87,72
	TU_list_03.remove(20); //86,71
	TU_list_03.remove(30); //85,70
	TU_list_03.remove(40); //84,69
	TU_list_03.remove(50); //83,68

	TU_list_03.insert(10, 0); //83,69
	TU_list_03.insert(-10, 0); //83,70
	TU_list_03.insert(10, 0); //83,71
	TU_list_03.insert(-10, 0); //83,72
	TU_list_03.insert(10, 0); //83,73
	TU_list_03.insert(-10, 0); //83,74
	TU_list_03.insert(10, 0); //83,75
	TU_list_03.insert(-10, 0); //83,76
	TU_list_03.insert(10, 0); //83,77
	TU_list_03.insert(-10, 0); //83,78
	TU_list_03.insert(50, 0); //83,79
	TU_list_03.insert(40, 0); //83,80
	TU_list_03.insert(30, 0); //83,81
	TU_list_03.insert(20, 0); //83,82
	TU_list_03.insert(10, 0); //83,83
	TU_list_03.insert(10, 0); //100,84

	TU_list_03_sum = 0;
	if (TU_list_03.allocated_elements() != 100)
		throw TEST("TU_list_03");
	if (TU_list_03.nr_list_nodes() != 84)
		throw TEST("TU_list_03");
	for (int i = 0; i < TU_list_03.nr_list_nodes(); i++)
	{
		TU_list_03_sum += TU_list_03[i];
	}
	if (TU_list_03_sum != 2711)
		throw TEST("TU_list_03");


	//////////////////////////////////////////
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
	cout << a.allocated_elements() << endl;
	cout << a.nr_list_nodes() << endl;
	cout << "===========================" << endl;
	auto it = a.begin();
	for (int i =0 ; it != a.end();i++, it++)
	{
		cout <<i<<". "<< *it << endl;
	}
	a.insert(55555, 5);
	a.insert(66666, 6);
	a.insert(77777, 7);
	auto it2 = a.begin();

	cout << endl << endl << endl;
	cout << a.allocated_elements() << endl;
	cout << a.nr_list_nodes() << endl;
	cout << "===========================" << endl;
	for (int i = 0; it2 != a.end(); i++, it2++)
	{
		cout << i << ". " << *it2 << endl;
	}
	cout << "===========================" << endl;
}
void TU_llist()
{
	//////////////////////////////////////////
	// TU_llist_01
	llist<int> a;
	llist<string> b("test");
	llist<double> c(15, 10);
	llist<double> d = c;


	if (a.count() != 0)
		throw TEST("TU_llist_01_1");

	if (b.count() != 1 || b[0] != "test")
		throw TEST("TU_llist_01_2");

	if (c.count() != 10)
		throw TEST("TU_lliST_01_3");


	double TU_llist_01_3_res = 0;
	for (int i = 0; i < 10; i++)
		TU_llist_01_3_res += c[i];

	if (TU_llist_01_3_res != 150)
		throw TEST("TU_llist_01_3");

	if (d.count() != 10 || &d[0] == &c[0])
		throw TEST("TU_llist_01_4");

	double TU_list_01_4_res = 0;
	for (int i = 0; i < 10; i++)
		TU_list_01_4_res += d[i];

	if (TU_list_01_4_res != 150)
		throw TEST("TU_llist_01_4");

	//////////////////////////////////////////
	//////////////////////////////////////////
	// TU_llist_02

	list<int> TU_llist_02;
	int TU_llist_02_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_llist_02.append(i);
	}

	if (TU_llist_02.count() != 73)
		throw TEST("TU_llist_02");
	for (int i = 0; i < TU_llist_02.count(); i++)
	{
		TU_llist_02_sum += TU_llist_02[i];
	}
	if (TU_llist_02_sum != 2701)
		throw TEST("TU_llist_02");

	TU_llist_02.remove(10);
	TU_llist_02.remove(20); 
	TU_llist_02.remove(30); 
	TU_llist_02.remove(40);
	TU_llist_02.remove(50);

	TU_llist_02.append(10); 
	TU_llist_02.append(-10);
	TU_llist_02.append(10); 
	TU_llist_02.append(-10); 
	TU_llist_02.append(10); 
	TU_llist_02.append(-10); 
	TU_llist_02.append(10); 
	TU_llist_02.append(-10); 
	TU_llist_02.append(10); 
	TU_llist_02.append(-10); 
	TU_llist_02.append(50); 
	TU_llist_02.append(40); 
	TU_llist_02.append(30); 
	TU_llist_02.append(20); 
	TU_llist_02.append(10); 
	TU_llist_02.append(10); 

	TU_llist_02_sum = 0;

	if (TU_llist_02.count() != 84)
		throw TEST("TU_llist_02");
	for (int i = 0; i < TU_llist_02.count(); i++)
	{
		TU_llist_02_sum += TU_llist_02[i];
	}
	if (TU_llist_02_sum != 2711)
		throw TEST("TU_list_02");








	//////////////////////////////////////////
}

