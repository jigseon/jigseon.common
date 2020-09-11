#pragma once

#include <iostream>
#include <cstdlib>

namespace jigseon
{
	enum mode { minimum, maximum };
	enum status { present, absent };

	template <class T>
	struct HeapNode
	{
		int key;
		T data;
		int status;

		HeapNode(int key = -1, T data = 0)
		{
			this->key = key;
			this->data = data;
			this->status = present;
		}
	};

	template <class T>
	class Heap
	{
	private:
		HeapNode<T>* heap;
		int count, capacity;
		int mode;

	public:
		Heap(int n = 100, int mode = minimum);
		void swap(HeapNode<T>*, HeapNode<T>*);
		bool enqueue(int key, T data);
		HeapNode<T> dequeue();

		class iterator
		{
			HeapNode<T>* currentP;
			bool direction;
		public:
			enum directions { forward, backward };
			iterator(HeapNode<T>* current, bool dir = forward) { currentP = current; direction = dir; }

			void operator++() { currentP = (direction == forward) ? currentP + 1 : currentP - 1; }
			void operator++(int none) { currentP = (direction == forward) ? currentP + 1 : currentP - 1; }
			void operator--() { (direction == forward) ? currentP - 1 : currentP + 1; }
			void operator--(int none) { currentP = (direction == forward) ? currentP - 1 : currentP + 1; }
			bool operator==(iterator i) { return (this->currentP == i.currentP) ? true : false; } // iterator &i ·Î ¹ÞÀ» °æ¿ì begin()¿¡¼­ ³ª¿Â iterator°¡  
			bool operator!=(iterator i) { return (this->currentP != i.currentP) ? true : false; }
			HeapNode<T> operator*() { return *currentP; }
			HeapNode<T>* operator->() { return currentP; }
		};
		iterator begin() { return iterator(this->heap); }
		iterator end() { return iterator(this->heap + count); }
		iterator rbegin() { return iterator(this->heap + count - 1, iterator::backward); }
		iterator rend() { return iterator(this->heap - 1, iterator::backward); }

		HeapNode<T>& operator[](int index);

	};
	template <class T>
	Heap<T>::Heap(int n, int mode)
	{
		this->heap = new HeapNode<T>[n];
		if (this->heap == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
		this->capacity = n;
		this->count = 0;
		this->mode = mode;
	}


	template <class T>
	void Heap<T>::swap(HeapNode<T>* a, HeapNode<T>* b)
	{
		HeapNode<T> temp = *a;
		*a = *b;
		*b = temp;
	}



	template <class T>
	bool Heap<T>::enqueue(int key, T data)
	{
		if (capacity <= count)
			return false;

		int current = count;

		heap[current].key = key;
		heap[current].data = data;
		heap[current].status = present;

		count++;

		while (heap[current].status != absent && current >= 0)
		{

			if (this->mode == minimum)
			{
				if (heap[current].key >= heap[(current - 1) / 2].key)
					return true;

				swap(heap + current, heap + (current - 1) / 2);
				current = (current - 1) / 2;
			}
			else
			{
				if (heap[current].key <= heap[(current - 1) / 2].key)
					return true;

				swap(heap + current, heap + (current - 1) / 2);
				current = (current - 1) / 2;
			}
		}

		return true;
	}












	template <class T>
	HeapNode<T> Heap<T>::dequeue()
	{
		int current, successor;
		HeapNode<T> res;

		if (count <= 0)
			return HeapNode<T>();

		swap(heap, heap + (count - 1));

		res = heap[count - 1];
		heap[count - 1].status = absent;
		count--;
		current = 0;

		while (current <= count - 1)
		{
			if (this->mode == minimum)
			{
				successor = (heap[current * 2 + 1].key < heap[current * 2 + 2].key) ? current * 2 + 1 : current * 2 + 2;

				if (heap[current].key >= heap[successor].key && heap[successor].status != absent)
				{
					swap(heap + current, heap + successor);
					current = current * 2 + 1;
				}
				else
					return res;
			}
			else
			{
				successor = (heap[current * 2 + 1].key > heap[current * 2 + 2].key) ? current * 2 + 1 : current * 2 + 2;

				if (heap[current].key <= heap[successor].key && heap[successor].status != absent)
				{
					swap(heap + current, heap + successor);
					current = current * 2 + 1;
				}
				else
					return res;
			}
		}
		return res;
	}



	template<class T>
	HeapNode<T>& Heap<T>::operator[](int index)
	{
		if (index >= this->count || -index > this->count)
		{
			throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
		}

		index = (index > 0) ? index : this->count + index;

		return this->heap[index];
	}
}