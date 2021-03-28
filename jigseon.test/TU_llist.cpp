#include "TU_llist.h"


TU_llist::TU_llist()
{
	TU_llist_1();
	TU_llist_2();
	TU_llist_3();
	TU_llist_4();
}

void TU_llist::TU_llist_1()
{
	llist<int> a;
	llist<string> b("test");
	llist<double> c(15, 10);
	llist<double> d = c;


	if (a.count() != 0)
		throw TEST("TU_llist_1_1");

	if (b.count() != 1 || b[0] != "test")
		throw TEST("TU_llist_1_2");

	if (c.count() != 10)
		throw TEST("TU_llist_1_3");


	double TU_llist_1_3_res = 0;
	for (int i = 0; i < 10; i++)
		TU_llist_1_3_res += c[i];

	if (TU_llist_1_3_res != 150)
		throw TEST("TU_llist_1_3");

	if (d.count() != 10 || &d[0] == &c[0])
		throw TEST("TU_llist_1_4");

	double TU_list_01_4_res = 0;
	for (int i = 0; i < 10; i++)
		TU_list_01_4_res += d[i];

	if (TU_list_01_4_res != 150)
		throw TEST("TU_llist_1_4");

}
void TU_llist::TU_llist_2()
{
	llist<int> TU_llist_2;
	int TU_llist_2_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_llist_2.append(i);
	}

	if (TU_llist_2.count() != 73)
		throw TEST("TU_llist_2");
	for (int i = 0; i < TU_llist_2.count(); i++)
	{
		TU_llist_2_sum += TU_llist_2[i];
	}
	if (TU_llist_2_sum != 2701)
		throw TEST("TU_llist_2");

	TU_llist_2.remove(10);
	TU_llist_2.remove(20);
	TU_llist_2.remove(30);
	TU_llist_2.remove(40);
	TU_llist_2.remove(50);

	TU_llist_2.append(10);
	TU_llist_2.append(-10);
	TU_llist_2.append(10);
	TU_llist_2.append(-10);
	TU_llist_2.append(10);
	TU_llist_2.append(-10);
	TU_llist_2.append(10);
	TU_llist_2.append(-10);
	TU_llist_2.append(10);
	TU_llist_2.append(-10);
	TU_llist_2.append(50);
	TU_llist_2.append(40);
	TU_llist_2.append(30);
	TU_llist_2.append(20);
	TU_llist_2.append(10);
	TU_llist_2.append(10);

	TU_llist_2_sum = 0;

	if (TU_llist_2.count() != 84)
		throw TEST("TU_llist_2");
	for (int i = 0; i < TU_llist_2.count(); i++)
	{
		TU_llist_2_sum += TU_llist_2[i];
	}
	if (TU_llist_2_sum != 2711)
		throw TEST("TU_llist_2");
}
void TU_llist::TU_llist_3()
{
	llist<int> TU_llist_3;
	int TU_llist_3_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_llist_3.insert(i, 0);
	}


	if (TU_llist_3.count() != 73)
		throw TEST("TU_llist_3");
	if (TU_llist_3[0] != 73 || TU_llist_3[72] != 1)
		throw TEST("TU_llist_3");
	for (int i = 0; i < TU_llist_3.count(); i++)
	{
		TU_llist_3_sum += TU_llist_3[i];
	}
	if (TU_llist_3_sum != 2701)
		throw TEST("TU_llist_3");


	TU_llist_3.remove(10); //87,72
	TU_llist_3.remove(20); //86,71
	TU_llist_3.remove(30); //85,70
	TU_llist_3.remove(40); //84,69
	TU_llist_3.remove(50); //83,68

	TU_llist_3.insert(10, 0); //83,69
	TU_llist_3.insert(-10, 0); //83,70
	TU_llist_3.insert(10, 0); //83,71
	TU_llist_3.insert(-10, 0); //83,72
	TU_llist_3.insert(10, 0); //83,73
	TU_llist_3.insert(-10, 0); //83,74
	TU_llist_3.insert(10, 0); //83,75
	TU_llist_3.insert(-10, 0); //83,76
	TU_llist_3.insert(10, 0); //83,77
	TU_llist_3.insert(-10, 0); //83,78
	TU_llist_3.insert(50, 0); //83,79
	TU_llist_3.insert(40, 0); //83,80
	TU_llist_3.insert(30, 0); //83,81
	TU_llist_3.insert(20, 0); //83,82
	TU_llist_3.insert(10, 0); //83,83
	TU_llist_3.insert(10, 0); //100,84

	TU_llist_3_sum = 0;
	if (TU_llist_3.count() != 84)
		throw TEST("TU_llist_3");
	for (int i = 0; i < TU_llist_3.count(); i++)
	{
		TU_llist_3_sum += TU_llist_3[i];
	}
	if (TU_llist_3_sum != 2711)
		throw TEST("TU_llist_3");
}

void TU_llist::TU_llist_4()
{

	llist<int> TU_llist_4;
	int TU_llist_4_sum = 0;

	for (int i = 0; i < 100; i++)
	{
		TU_llist_4.append(i + 1);
	}

	if (TU_llist_4[-1] != TU_llist_4[99] || TU_llist_4[-100] != TU_llist_4[0])
		throw TEST("TU_llist_4");

	for (int i = -1; i >= -100; i--)
	{
		TU_llist_4_sum += TU_llist_4[i];
	}

	if (TU_llist_4_sum != 5050)
		throw TEST("TU_llist_4");


	TU_llist_4.insert(101, -100);
	TU_llist_4.insert(102, -50);
	TU_llist_4.insert(103, -1);

	if (TU_llist_4[0] != 101 || TU_llist_4[51] != 102 || TU_llist_4[101] != 103)
		throw TEST("TU_llist_4");


	TU_llist_4_sum = 0;
	for (int i = -1; i >= -103; i--)
	{
		TU_llist_4_sum += TU_llist_4[i];
	}

	if (TU_llist_4_sum != 5356)
		throw TEST("TU_llist_4");

}