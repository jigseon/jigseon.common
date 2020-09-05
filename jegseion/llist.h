#pragma once

#include <sal.h>

#include "jegseion/Src/ExceptionClass.h"

template <class T>
class llist_node
{
public:
	llist_node();
	llist_node(_In_ const T& cls);
	virtual ~llist_node();

private:
	T _data;
	llist_node<T>* _next;
	llist_node<T>* _prev;
};

template <class T>
class llist
{
public:
	llist();
	llist(T data);
	llist(const llist& cls);
	virtual ~llist();

public:
	bool InsertHead(_In_ const T& data);
	bool InsertTail(_In_ const T& data);
	bool InsertAt(_In_ uint32_t index, _In_ const T& data);
	
	bool Delete(_In_ llist_node<T>* node);
	bool DeleteHead();
	bool DeleteTail();
	bool DeleteAt(_In_ uint32_t index);

	llist_node<T> GetHead();
	llist_node<T> GetTail();

	T& operator[] (int);
	class iterator // llist::iterator ��  static ����
	{
	public:
		enum direction { forward, backward };

		iterator(llist_node<T>* current, bool direction = forward) { _current = current; _direction = direction; }

		void operator++() { _current = (_direction == forward) ? _current->_next : _current->_prev; }
		void operator++(int none) { _current = (_direction == forward) ? _current->_next : _current->_prev; }
		void operator--() { _current = (_direction == forward) ? _current->_next : _current->_prev; }
		void operator--(int none) { _current = (_direction == forward) ? _current->_prev : _current->_next; }
		void operator==(iterator i) { return (this->_current == i._current) ? true : false; }
		void operator!=(iterator i) { return (this->_current != i._current) ? true : false; }
		llist_node<T> &operator*() { return *_current; }
		llist_node<T>* operator->() { return _current; }

		//
		// ->�� �����ε��ϸ� x->f() �� ������ ���� �ؼ��ȴ�.
		// (x.operator->())->f().
		//
	private:
		llist_node<T>* _current;
		bool _direction;
	};

	iterator begin() { return iterator(GetHead()); }
	iterator end() { return iterator(nullptr); }
	iterator rbegin() { return iterator(GetTail(), iterator::backward); }
	iterator rend() { return iterator(nullptr, iterator::backward); }

public:
	void append(T n) { this->InsertTail(n); }
	llist<T>& copy();
	size_t count() const { return this->_nr_llist_nodes; }
	void extend(const llist<T> l);
	void remove(T value);
	void reverse();
	void sort();

private:
	size_t _nr_llist_nodes;
	llist_node<T>* _head;
	llist_node<T>* _tail;

private:
	void clear() { while (this->DeleteHead()); }
};