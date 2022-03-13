#include "TU_Heap.h"
#include "../jigseon.common/Heap.h"

#include <string>
#include <iostream>

TU_Heap::TU_Heap()
{
	TU_Heap_1();
}

void TU_Heap::TU_Heap_1()
{
	Heap<int> TU_Heap_1_1;
	Heap<double> TU_Heap_1_2(50, minimum);
	Heap<string> TU_Heap_1_3(50, maximum);

	if(TU_Heap_1_1.count() != 0)
		throw TEST("TU_Heap_1_1");
	if (TU_Heap_1_1.capacity() != 100)
		throw TEST("TU_Heap_1_1");
	if(TU_Heap_1_1.heap_mode() != "minimum")
		throw TEST("TU_Heap_1_1");


	if (TU_Heap_1_2.count() != 0)
		throw TEST("TU_Heap_1_2");
	if (TU_Heap_1_2.capacity() != 50)
		throw TEST("TU_Heap_1_2");
	if (TU_Heap_1_2.heap_mode() != "minimum")
		throw TEST("TU_Heap_1_2");


	if (TU_Heap_1_3.count() != 0)
		throw TEST("TU_Heap_1_3");
	if (TU_Heap_1_3.capacity() != 50)
		throw TEST("TU_Heap_1_3");
	if (TU_Heap_1_3.heap_mode() != "maximum")
		throw TEST("TU_Heap_1_3");

	return;
}