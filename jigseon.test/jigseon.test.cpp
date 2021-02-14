#include "../jigseon.common/llist.h"
#include "../jigseon.common/HashTable.h"
#include "../jigseon.common/Tree.h"
#include "../jigseon.common/RBTree.h"
#include "../jigseon.common/Graph.h"
#include "../jigseon.common/BigNumber.h"
#include "../jigseon.common/ExceptionClass.h"

#include "TU_list.h"

using namespace jigseon;


void TU_llist();


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

