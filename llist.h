#pragma once
#include "ExceptionClass.h"
#include "Heap.h"


#include <iostream>
#include <sal.h>
#include <Windows.h>
#include <string>

namespace igo_library
{
	template <class T>
	class llist_node
	{
	public:
		llist_node();
		llist_node(_In_ const T& cls);
		virtual ~llist_node();

	public:
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
		void clear() { while (this->DeleteHead()); }

		llist_node<T>* GetHead() const;
		llist_node<T>* GetTail() const;

		T& operator[] (int);
		class iterator // llist::iterator 는  static 참조
		{
		public:
			enum direction { forward, backward };

			iterator(llist_node<T>* current, bool direction = forward) { _current = current; _direction = direction; }

			void operator++() { _current = (_direction == forward) ? _current->_next : _current->_prev; }
			void operator++(int none)
			{
				UNREFERENCED_PARAMETER(none);
				_current = (_direction == forward) ? _current->_next : _current->_prev;
			}
			void operator--() { _current = (_direction == forward) ? _current->_next : _current->_prev; }
			void operator--(int none)
			{
				UNREFERENCED_PARAMETER(none);
				_current = (_direction == forward) ? _current->_prev : _current->_next;
			}
			bool operator==(iterator i) { return (this->_current == i._current) ? true : false; }
			bool operator!=(iterator i) { return (this->_current != i._current) ? true : false; }
			llist_node<T>& operator*() { return *_current; }
			llist_node<T>* operator->() { return _current; }

			//
			// ->를 오버로딩하면 x->f() 는 다음과 같이 해석된다.
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
	};

}
