#include "TU_list.h"


TU_list::TU_list()
{
	TU_list_01();
	TU_list_02();
	TU_list_03();
}

void TU_list::TU_list_01()
{
	list<int> a;
	list<string> b("test");
	list<double> c(15, 10);
	list<double> d = c;

	if (a.count() != 0)
		throw TEST("TU_list_01_1");

	if (b.count() != 1 || b[0] != "test")
		throw TEST("TU_list_01_2");

	if (c.count() != 10)
		throw TEST("TU_list_01_3");


	double TU_list_01_3_res = 0;
	for (int i = 0; i < 10; i++)
		TU_list_01_3_res += c[i];

	if (TU_list_01_3_res != 150)
		throw TEST("TU_list_01_3");

	if (d.count() != 10 || &d[0] == &c[0])
		throw TEST("TU_list_01_4");

	double TU_list_01_4_res = 0;
	for (int i = 0; i < 10; i++)
		TU_list_01_4_res += d[i];

	if (TU_list_01_4_res != 150)
		throw TEST("TU_list_01_4");

}


void TU_list::TU_list_02()
{
	list<int> TU_list_02;
	int TU_list_02_sum = 0;
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

}


void TU_list::TU_list_03()
{
	list<int> TU_list_03;
	int TU_list_03_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_list_03.insert(i, 0);
	}

	if (TU_list_03.allocated_elements() != 88)
		throw TEST("TU_list_03");
	if (TU_list_03.nr_list_nodes() != 73)
		throw TEST("TU_list_03");
	if (TU_list_03[0] != 73 || TU_list_03[72] != 1)
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

}