#include "TU_list.h"


TU_list::TU_list()
{
	TU_list_1();
	TU_list_2();
	TU_list_3();
	TU_list_4();
	TU_list_5();
	TU_list_6();
	TU_list_7();
	TU_list_8();
	TU_list_9();
	TU_list_10();
	TU_list_11();
	TU_list_12();
}

void TU_list::TU_list_1()
{
	list<int> a;
	list<string> b("test");
	list<double> c(15, 10);
	list<double> d = c;

	if (a.count() != 0)
		throw TEST("TU_list_1_1");

	if (b.count() != 1 || b[0] != "test")
		throw TEST("TU_list_1_2");

	if (c.count() != 10)
		throw TEST("TU_list_1_3");


	double TU_list_1_3_res = 0;
	for (int i = 0; i < 10; i++)
		TU_list_1_3_res += c[i];

	if (TU_list_1_3_res != 150)
		throw TEST("TU_list_1_3");

	if (d.count() != 10 || &d[0] == &c[0])
		throw TEST("TU_list_1_4");

	double TU_list_1_4_res = 0;
	for (int i = 0; i < 10; i++)
		TU_list_1_4_res += d[i];

	if (TU_list_1_4_res != 150)
		throw TEST("TU_list_1_4");

}


void TU_list::TU_list_2()
{
	list<int> TU_list_2;
	int TU_list_2_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_list_2.append(i);
	}

	if (TU_list_2.allocated_elements() != 88)
		throw TEST("TU_list_2");
	if (TU_list_2.nr_list_nodes() != 73)
		throw TEST("TU_list_2");
	for (int i = 0; i < TU_list_2.nr_list_nodes(); i++)
	{
		TU_list_2_sum += TU_list_2[i];
	}
	if (TU_list_2_sum != 2701)
		throw TEST("TU_list_2");

	TU_list_2.remove(10); //87,72
	TU_list_2.remove(20); //86,71
	TU_list_2.remove(30); //85,70
	TU_list_2.remove(40); //84,69
	TU_list_2.remove(50); //83,68

	TU_list_2.append(10); //83,69
	TU_list_2.append(-10); //83,70
	TU_list_2.append(10); //83,71
	TU_list_2.append(-10); //83,72
	TU_list_2.append(10); //83,73
	TU_list_2.append(-10); //83,74
	TU_list_2.append(10); //83,75
	TU_list_2.append(-10); //83,76
	TU_list_2.append(10); //83,77
	TU_list_2.append(-10); //83,78
	TU_list_2.append(50); //83,79
	TU_list_2.append(40); //83,80
	TU_list_2.append(30); //83,81
	TU_list_2.append(20); //83,82
	TU_list_2.append(10); //83,83
	TU_list_2.append(10); //100,84

	TU_list_2_sum = 0;
	if (TU_list_2.allocated_elements() != 100)
		throw TEST("TU_list_2");
	if (TU_list_2.nr_list_nodes() != 84)
		throw TEST("TU_list_2");
	for (int i = 0; i < TU_list_2.nr_list_nodes(); i++)
	{
		TU_list_2_sum += TU_list_2[i];
	}
	if (TU_list_2_sum != 2711)
		throw TEST("TU_list_2");

}


void TU_list::TU_list_3()
{
	list<int> TU_list_3;
	int TU_list_3_sum = 0;
	for (int i = 1; i <= 73; i++)
	{
		TU_list_3.insert(i, 0);
	}

	if (TU_list_3.allocated_elements() != 88)
		throw TEST("TU_list_3");
	if (TU_list_3.nr_list_nodes() != 73)
		throw TEST("TU_list_3");
	if (TU_list_3[0] != 73 || TU_list_3[72] != 1)
		throw TEST("TU_list_3");
	for (int i = 0; i < TU_list_3.nr_list_nodes(); i++)
	{
		TU_list_3_sum += TU_list_3[i];
	}
	if (TU_list_3_sum != 2701)
		throw TEST("TU_list_3");


	TU_list_3.remove(10); 
	TU_list_3.remove(20); 
	TU_list_3.remove(30); 
	TU_list_3.remove(40);
	TU_list_3.remove(50);

	TU_list_3.insert(10, 0); 
	TU_list_3.insert(-10, 0);
	TU_list_3.insert(10, 0); 
	TU_list_3.insert(-10, 0); 
	TU_list_3.insert(10, 0); 
	TU_list_3.insert(-10, 0);
	TU_list_3.insert(10, 0); 
	TU_list_3.insert(-10, 0);
	TU_list_3.insert(10, 0); 
	TU_list_3.insert(-10, 0);
	TU_list_3.insert(50, 0); 
	TU_list_3.insert(40, 0); 
	TU_list_3.insert(30, 0); 
	TU_list_3.insert(20, 0); 
	TU_list_3.insert(10, 0); 
	TU_list_3.insert(10, 0); 

	TU_list_3_sum = 0;
	if (TU_list_3.allocated_elements() != 100)
		throw TEST("TU_list_3");
	if (TU_list_3.nr_list_nodes() != 84)
		throw TEST("TU_list_3");
	for (int i = 0; i < TU_list_3.nr_list_nodes(); i++)
	{
		TU_list_3_sum += TU_list_3[i];
	}
	if (TU_list_3_sum != 2711)
		throw TEST("TU_list_3");

}


void TU_list::TU_list_4()
{
	list<int> TU_list_4;
	int TU_list_4_sum=0;

	for (int i = 0; i < 100;i++)
	{
		TU_list_4.append(i + 1);
	}

	if(TU_list_4[-1] != TU_list_4[99] || TU_list_4[-100] != TU_list_4[0])
		throw TEST("TU_list_4");

	for (int i = -1;i>=-100;i--)
	{
		TU_list_4_sum += TU_list_4[i];
	}

	if(TU_list_4_sum != 5050)
		throw TEST("TU_list_4");


	TU_list_4.insert(101, -100);
	TU_list_4.insert(102, -50);
	TU_list_4.insert(103,-1);

	if(TU_list_4[0] != 101 || TU_list_4[51] != 102 || TU_list_4[101] != 103)
		throw TEST("TU_list_4");


	TU_list_4_sum = 0;
	for (int i = -1; i >= -103; i--)
	{
		TU_list_4_sum += TU_list_4[i];
	}

	if (TU_list_4_sum != 5356)
		throw TEST("TU_list_4");
}

void TU_list::TU_list_5() 
{
	list<int> TU_list_5(10,50);
	int sum = 0;

	list<int>::iterator it = TU_list_5.begin();
	TU_list_5.append(10);

	for (; it != TU_list_5.end(); it++)
	{
		sum += *it;
	}

	if(TU_list_5.count() != 51)
		throw TEST("TU_list_5");
	if(sum != 510)
		throw TEST("TU_list_5");
}

void TU_list::TU_list_6()
{
	list<int> TU_list_6(10, 50);
	int inserts,removes;
	size_t initial_count_value;

	

	srand(time(NULL));
	for (int i = 0;i<10;i++)
	{
		initial_count_value = TU_list_6.count();
		inserts = rand() % 100 + 1;
		removes = rand() % inserts + 1;
		
		for (int cv_insert = 0; cv_insert < inserts; cv_insert++)
		{
			TU_list_6.append(10);
		}

		for (int cv_remove=0; cv_remove < removes; cv_remove++)
		{
			TU_list_6.remove(10);
		}

		if (TU_list_6.count() != initial_count_value + inserts - removes)
			throw TEST("TU_list_6");
	}



}

void TU_list::TU_list_7()
{
	list<int> TU_list_7_1;

	for (int i =1;i<=10;i++)
	{
		TU_list_7_1.append(i);
	}

	list<int> TU_list_7_2 = TU_list_7_1.copy();

	if (TU_list_7_1.allocated_elements() != TU_list_7_2.allocated_elements())
		throw TEST("TU_list_7");
	if (TU_list_7_1.nr_list_nodes() != TU_list_7_2.nr_list_nodes())
		throw TEST("TU_list_7");
	for (int i = 0; i < 10; i++)
	{
		if (TU_list_7_1[i] != TU_list_7_2[i])
			throw TEST("TU_list_7");
	}
	
	if(&TU_list_7_1[0] == &TU_list_7_2[0])
		throw TEST("TU_list_7");
}

void TU_list::TU_list_8()
{
	list<int> TU_list_8_1(5,5), TU_list_8_2(10,10);
	int sum=0;

	TU_list_8_1.extend(TU_list_8_2);
	if (TU_list_8_1.count() != 15)
		throw TEST("TU_list_8");

	auto it = TU_list_8_1.begin();
	for (;it!=TU_list_8_1.end();it++)
	{
		sum += *it;
	}

	if (sum != 25+100)
		throw TEST("TU_list_8");

}
void TU_list::TU_list_9()
{
	list<int> TU_list_9(5, 10);

	if (TU_list_9.count() != 10)
		throw TEST("TU_list_9");

	TU_list_9.clear();

	if (TU_list_9.count() != 0)
		throw TEST("TU_list_9");
	if (TU_list_9.allocated_elements() != 0)
		throw TEST("TU_list_9");

	TU_list_9.append(10);
	TU_list_9.append(11);
	if (TU_list_9.count() != 2)
		throw TEST("TU_list_9");

}



void TU_list::TU_list_10() 
{
	list<int> TU_list_10_1;
	int test_elements = 100;
	int test_executions = 100;

	srand(time(NULL));
	for (int i = 1; i <= test_elements; i++)
	{
		TU_list_10_1.append(rand() % 1000 - 499);
	}

	list<int> TU_list_10_2(TU_list_10_1);
	TU_list_10_1.sort();

	for (int test=1;test<= test_executions;test++)
	{
		for (int i = 0; i < test_elements-1; i++)
		{
			int a= TU_list_10_1[i],b= TU_list_10_1[i + 1];
			if (a >b )
			{
				cout << "Error"<<test<<" case : ";
				for (int j = 0; j < test_elements; j++)
				{
					cout << TU_list_10_2[j] << ", ";
				}
				cout << endl << "Current Result : " << endl;
				for (int j = 0; j < test_elements; j++)
				{
					cout << "\t" << TU_list_10_1[j] << endl;
				}
				throw TEST("TU_list_10");
			}
		}
	}
}


void TU_list::TU_list_11()
{
	list<int> TU_list_11_1;
	int test_elements = 100;
	int test_executions = 100;

	srand(time(NULL));
	for (int i = 1; i <= test_elements; i++)
	{
		TU_list_11_1.append(rand() % 1000 - 499);
	}

	list<int> TU_list_11_2(TU_list_11_1);
	TU_list_11_1.reverse();

	for (int test = 1; test <= test_executions; test++)
	{
		for (int i = 0; i > test_elements - 1; i++)
		{
			int a = TU_list_11_1[i], b = TU_list_11_1[i + 1];
			if (a > b)
			{
				cout << "Error" << test << " case : ";
				for (int j = 0; j < test_elements; j++)
				{
					cout << TU_list_11_2[j] << ", ";
				}
				cout << endl << "Current Result : " << endl;
				for (int j = 0; j < test_elements; j++)
				{
					cout << "\t" << TU_list_11_1[j] << endl;
				}
				throw TEST("TU_list_11");
			}
		}
	}
}

void TU_list::TU_list_12()
{
	list<int> TU_list_12;
	int previous_value = -1;
	
	for (int i = 0; i < 20; i++)
	{
		TU_list_12.append(i + 1);
	}

	auto it = TU_list_12.begin();
	for (; it != TU_list_12.end(); it++)
	{
		if(previous_value >= *it)
			throw TEST("TU_list_12");
		previous_value = *it;
		
	}
}