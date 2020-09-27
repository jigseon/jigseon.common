﻿
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

	public:
		class iterator
		{
			T* _currentP;
			bool _direction;
		public:
			enum directions { forward, backward };
			iterator(T* current, bool dir = forward) { _currentP = current; _direction = dir; }

			void operator++() { _currentP = (_direction == forward) ? _currentP + 1 : _currentP - 1; }
			void operator++(int none) { _currentP = (_direction == forward) ? _currentP + 1 : _currentP - 1; }
			void operator--() { (_direction == forward) ? _currentP - 1 : _currentP + 1; }
			void operator--(int none) { _currentP = (_direction == forward) ? _currentP - 1 : _currentP + 1; }
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
	size_t needsize, currentsize = this->_nr_list_nodes;
	T* tempbuf = this->_consecutive;

	needsize = (nextsize >> 3) + (nextsize < 9 ? 3 : 6);
	this->_consecutive = new T[needsize + nextsize];
	if (this->_allocated_elements > 0)
		copy_n(tempbuf, needsize + nextsize, _consecutive);
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
			copy_n(tempbuf + i + 1, _allocated_elements - i, _consecutive + i);
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
void list<T>::reverse();

///	@brief
template <class T>
void list<T>::sort();

///	@brief
template <class T>
void list<T>::clear()
{
	_nr_list_nodes = 0;
	_allocated_elements = 0;
	delete _consecutive;
	_consecutive = nullptr;
}
}
