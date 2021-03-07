#include "TU_llist.h"


TU_llist::TU_llist()
{
	TU_llist_01();
	TU_llist_02();
	TU_llist_03();

}

void TU_llist::TU_llist_01()
{
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

}
void TU_llist::TU_llist_02()
{
	llist<int> TU_llist_02;
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
		throw TEST("TU_llist_02");
}
void TU_llist::TU_llist_03()
{
	llist<int> TU_llist_03;
	int TU_llist_03_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_llist_03.insert(i, 0);
	}


	if (TU_llist_03.count() != 73)
		throw TEST("TU_llist_03");
	if (TU_llist_03[0] != 73 || TU_llist_03[72] != 1)
		throw TEST("TU_llist_03");
	for (int i = 0; i < TU_llist_03.count(); i++)
	{
		TU_llist_03_sum += TU_llist_03[i];
	}
	if (TU_llist_03_sum != 2701)
		throw TEST("TU_llist_03");


	TU_llist_03.remove(10); //87,72
	TU_llist_03.remove(20); //86,71
	TU_llist_03.remove(30); //85,70
	TU_llist_03.remove(40); //84,69
	TU_llist_03.remove(50); //83,68

	TU_llist_03.insert(10, 0); //83,69
	TU_llist_03.insert(-10, 0); //83,70
	TU_llist_03.insert(10, 0); //83,71
	TU_llist_03.insert(-10, 0); //83,72
	TU_llist_03.insert(10, 0); //83,73
	TU_llist_03.insert(-10, 0); //83,74
	TU_llist_03.insert(10, 0); //83,75
	TU_llist_03.insert(-10, 0); //83,76
	TU_llist_03.insert(10, 0); //83,77
	TU_llist_03.insert(-10, 0); //83,78
	TU_llist_03.insert(50, 0); //83,79
	TU_llist_03.insert(40, 0); //83,80
	TU_llist_03.insert(30, 0); //83,81
	TU_llist_03.insert(20, 0); //83,82
	TU_llist_03.insert(10, 0); //83,83
	TU_llist_03.insert(10, 0); //100,84

	TU_llist_03_sum = 0;
	if (TU_llist_03.count() != 84)
		throw TEST("TU_llist_03");
	for (int i = 0; i < TU_llist_03.count(); i++)
	{
		TU_llist_03_sum += TU_llist_03[i];
	}
	if (TU_llist_03_sum != 2711)
		throw TEST("TU_llist_03");
}
