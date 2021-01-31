
#pragma once
#include "ExceptionClass.h"
#include "Heap.h"

#include <iostream>
#include <sal.h>
#include <Windows.h>
#include <string>

namespace jigseon
{
	template <class T>
	class list
	{
	public:
		list();
		list(T data);
		list(T data,unsigned int elements);
		list(const list& cls);
		virtual ~list();

	public:
		T& operator[] (int);

	public:
		void append(T n);
		list<T>& copy();
		size_t count() const { return this->_nr_list_nodes; }
		void extend(const list<T> l);
		void remove(T);
		void reverse();
		void sort();
		void clear();
		void insert(T,int);

		size_t nr_list_nodes() { return this->_nr_list_nodes; }
		size_t allocated_elements() { return this->_allocated_elements; }

	public:
		class iterator
		{
			T* _currentP;
			bool _direction;
		public:
			enum directions { forward, backward };
			iterator(T* current, bool dir = forward) { _currentP = current; _direction = dir; }

			void operator++() { _currentP = (_direction == forward) ? _currentP + 1 : _currentP - 1; }
			void operator++(int none) 
			{ 
				UNREFERENCED_PARAMETER(none);
				_currentP = (_direction == forward) ? _currentP + 1 : _currentP - 1; 
			}
			void operator--() { (_direction == forward) ? _currentP - 1 : _currentP + 1; }
			void operator--(int none) 
			{ 
				UNREFERENCED_PARAMETER(none);
				_currentP = (_direction == forward) ? _currentP - 1 : _currentP + 1; 
			}
			bool operator==(iterator i) { return (this->_currentP == i._currentP) ? true : false; }
			bool operator!=(iterator i) { return (this->_currentP != i._currentP) ? true : false; }
			T& operator*() { return *_currentP; }
			T* operator->() { return _currentP; }
		};

		iterator begin() { return iterator(_consecutive); }
		iterator end() { return iterator(_consecutive + _nr_list_nodes); }
		iterator rbegin() { return iterator(_consecutive + _nr_list_nodes - 1, iterator::backward); }
		iterator rend() { return iterator(_consecutive - 1, iterator::backward); }

	private:
		size_t resize(size_t);
	private:
		size_t _nr_list_nodes;
		size_t _allocated_elements;
		T* _consecutive;
	};


	///	@brief
	template <class T>
	list<T>::list() :
		_nr_list_nodes(0),
		_allocated_elements(0),
		_consecutive(nullptr)
	{
	}

	///	@brief
	template <class T>
	list<T>::list(_In_ T data)
	{
		_consecutive = new T(data);
		if (nullptr == _consecutive)
			throw BADALLOC;

		_nr_list_nodes = 1;
		_allocated_elements = 1;

		return;
	}

	template <class T>
	list<T>::list(_In_ T data,unsigned int elements)
	{
		_consecutive = new T(data);
		if (nullptr == _consecutive)
			throw BADALLOC;


		_nr_list_nodes = 1;
		_allocated_elements = 1;

		for (unsigned int i = 1; i < elements;i++)
		{
			this->append(data);
		}


		return;
	}


	///	@brief
	template <class T>
	list<T>::list(_In_ const list<T>& cls) // 복사 생성자
	{
		_consecutive = new T[cls._allocated_elements];
		this->_nr_list_nodes = cls._nr_list_nodes;
		this->_allocated_elements = cls._allocated_elements;

		for (int i = 0; i < _nr_list_nodes; i++)
		{
			this->_consecutive[i] = cls._consecutive[i];
		}
	}

	///	@brief
	template <class T>
	list<T>::~list()
	{
		this->clear();
	}

	///	@brief
	template <class T>
	size_t list<T>::resize(size_t nextsize)
	{
		size_t needsize;
		T* tempbuf = this->_consecutive;

		needsize = (nextsize >> 3) + (nextsize < 9 ? 3 : 6);
		this->_consecutive = new T[needsize + nextsize];
		if (this->_allocated_elements > 0)
			std::copy_n(tempbuf, needsize + nextsize, _consecutive);
		delete tempbuf;

		this->_allocated_elements = needsize + nextsize;

		return needsize + nextsize;
	}

	///	@brief
	template <class T>
	void list<T>::append(T data)
	{
		if (_allocated_elements <= _nr_list_nodes)
			resize(_nr_list_nodes + 1);
		this->_consecutive[_nr_list_nodes] = data;
		this->_nr_list_nodes++;
	}

	///	@brief
	template <class T>
	list<T>& list<T>::copy();

	///	@brief
	template <class T>
	void list<T>::extend(const list<T> l);


	///	@brief
	template <class T>
	void list<T>::remove(T data)
	{
		T* tempbuf = _consecutive;
		_consecutive = new T[_allocated_elements - 1];

		for (int i = 0; i < _nr_list_nodes; i++)
		{
			if (tempbuf[i] == data)
			{
				std::copy_n(tempbuf + i + 1, _allocated_elements - i, _consecutive + i);
				--_nr_list_nodes;
				--_allocated_elements;
				return;
			}
			else
			{
				_consecutive[i] = tempbuf[i];
			}
		}
		throw INVALIDINPUT;
	}


	///	@brief
	template <class T>
	void list<T>::reverse() 
	{
		Heap<T> maxheap(this->_nr_list_nodes,maximum);
		for (auto it = this->begin();it != this->end();it++)
		{
			maxheap.enqueue(*it,*it);
		}
		for (auto it = this->begin(); it != this->end(); it++)
		{
			*it = maxheap.dequeue()._data;
		}
	}

	/// @brief
	template <class T>
	void list<T>::sort()
	{
		Heap<T> minheap(this->_nr_list_nodes,minimum);
		for (auto it = this->begin(); it != this->end();it++)
		{
			minheap.enqueue(*it, *it);
		}
		for (auto it = this->begin(); it != this->end(); it++)
		{
			*it = minheap.dequeue()._data;
		}
	}

	///	@brief
	template <class T>
	void list<T>::clear()
	{
		_nr_list_nodes = 0;
		_allocated_elements = 0;
		delete _consecutive;
		_consecutive = nullptr;
	}

	template <class T>
	T& list<T>::operator[](int index)
	{
		return this->_consecutive[index];
	}

	template <class T>
	void list<T>::insert(T data, int index)
	{
		this->append(data);
		for (int i=index;i<this->_nr_list_nodes ;i++)
		{
			T temp = data;
			data = (*this)[i];
			(*this)[i] = temp;
		}
	}

}



