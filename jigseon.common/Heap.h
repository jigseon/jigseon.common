#pragma once

#include <iostream>
#include <cstdlib>

namespace jigseon
{
	enum mode { minimum, maximum };
	enum status { absent, present  };

	template <class T>
	struct HeapNode
	{
		int _key;
		T _data;
		int _status;

		HeapNode(int key = -1, T data = 0)
		{
			this->_key = key;
			this->_data = data;
			this->_status = absent;
		}
	};

	template <class T>
	class Heap
	{
	private:
		HeapNode<T>* _heap;
		size_t _count, _capacity;
		int _mode;

	public:
		Heap(size_t n = 100, int mode = minimum);
		void swap(HeapNode<T>*, HeapNode<T>*);
		bool enqueue(int key, T data);
		HeapNode<T> dequeue();

		class iterator
		{
			HeapNode<T>* _currentP;
			bool _direction;
		public:
			enum directions { forward, backward };
			iterator(HeapNode<T>* current, bool dir = forward) { _currentP = current; _direction = dir; }

			void operator++() { _currentP = (_direction == forward) ? _currentP + 1 : _currentP - 1; }
			void operator++(int none) { _currentP = (_direction == forward) ? _currentP + 1 : _currentP - 1; }
			void operator--() { (_direction == forward) ? _currentP - 1 : _currentP + 1; }
			void operator--(int none) { _currentP = (_direction == forward) ? _currentP - 1 : _currentP + 1; }
			bool operator==(iterator i) { return (this->_currentP == i._currentP) ? true : false; } // iterator &i ·Î ¹ÞÀ» °æ¿ì begin()¿¡¼­ ³ª¿Â iterator°¡  
			bool operator!=(iterator i) { return (this->_currentP != i._currentP) ? true : false; }
			HeapNode<T>& operator*() { return *_currentP; }
			HeapNode<T>* operator->() { return _currentP; }
		};
		iterator begin() { return iterator(this->_heap); }
		iterator end() { return iterator(this->_heap + _count); }
		iterator rbegin() { return iterator(this->_heap + _count - 1, iterator::backward); }
		iterator rend() { return iterator(this->_heap - 1, iterator::backward); }

		HeapNode<T>& operator[](int index);

	};
	template <class T>
	Heap<T>::Heap(size_t n, int mode)
	{
		this->_heap = new HeapNode<T>[n];
		if (this->_heap == NULL) throw BADALLOC;
		this->_capacity = n;
		this->_count = 0;
		this->_mode = mode;
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
		if (_capacity <= _count)
			return false;

		size_t current = _count;

		_heap[current]._key = key;
		_heap[current]._data = data;
		_heap[current]._status = present;

		_count++;

		while (_heap[current]._status != absent && current > 0 && _count>1)
		{

			if (this->_mode == minimum)
			{
				if (_heap[current]._key >= _heap[(current - 1) / 2]._key)
					return true;

				swap(_heap + current, _heap + (current - 1) / 2);
				current = (current - 1) / 2;
			}
			else
			{
				if (_heap[current]._key <= _heap[(current - 1) / 2]._key)
					return true;

				swap(_heap + current, _heap + (current - 1) / 2);
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

		if (_count <= 0)
			return HeapNode<T>();

		swap(_heap, _heap + (_count - (unsigned long long)1));

		res = _heap[_count - 1];
		_heap[_count - 1]._status = absent;
		_count--;
		current = 0;

		while (current <= _count - 1)
		{
			if (this->_mode == minimum)
			{
				successor = (_heap[current * 2 + 1]._key < _heap[current * 2 + 2]._key || _heap[current * 2 + 2]._status == absent) ? current * 2 + 1 : current * 2 + 2;

				if (_heap[current]._key >= _heap[successor]._key && _heap[successor]._status != absent)
				{
					if (successor >= _count)
						return res;
					swap(_heap + current, _heap + successor);
					current = successor;

				}
				else
					return res;
			}
			else
			{
				successor = (_heap[current * 2 + 1]._key > _heap[current * 2 + 2]._key || _heap[current * 2 + 2]._status == absent) ? current * 2 + 1 : current * 2 + 2;

				if (_heap[current]._key <= _heap[successor]._key && _heap[successor]._status != absent)
				{
					if (successor >= _count)
						return res;
					swap(_heap + current, _heap + successor);
					current = successor;
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
			throw INVALIDINDEX;
		}

		index = (index > 0) ? index : this->_count + index;

		return this->_heap[index];
	}
}