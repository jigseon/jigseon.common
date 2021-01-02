#pragma once

#include <iostream>
#include <string>
#include "ExceptionClass.h"

using namespace std;

namespace jigseon
{
	template <class T>
	struct HTNode
	{
		char* _key;
		T _value;
		int _count;

		HTNode<T>* _next;

		HTNode(int keysize = 10)
		{
			this->_key = new char[keysize];
			if (this->_key == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
			this->_next = NULL;
			this->_value = 0;
			this->_count = 0;
		}

		HTNode(const char* key, T value, int keysize = 10)
		{
			this->_key = new char[keysize];
			if (this->_key == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
			strcpy_s(this->_key, keysize, key);
			this->_value = value;
			this->_next = NULL;
			this->_count = 0;
		}
		~HTNode()
		{
			delete _key;
		}

	};

	template <class T>
	class HashTable
	{
	private:
		HTNode<T>* _table;
		int _keysize;
		int _tablesize;
		int _count;

	public:
		HashTable<T>(int tablesize = 20, int keysize = 10)
		{
			this->_keysize = keysize;
			this->_tablesize = tablesize;
			this->_count = 0;

			this->_table = new HTNode<T>[tablesize];
			if (this->_table == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
		}
		~HashTable<T>()
		{
			auto it = this->begin();
			for (; it != this->end(); it++)
				this->remove(it->_key);
			delete this->_table;

		}

		int hash(const char* key);
		bool add(string key, T value);
		T get(string key);
		bool remove(string key);

		HTNode<T>& operator[](string key);
		HTNode<T>& operator[](int index);


		class iterator
		{
			HashTable<T>* _ht;
			bool _direction;
			int _current_index;
		public:
			enum directions { forward, backward };
			iterator(HashTable<T>* ht, int current_index, bool dir = forward) { this->_ht = ht; this->_current_index = current_index; this->_direction = dir; }

			void operator++() { _current_index = (_direction == forward) ? _current_index + 1 : _current_index - 1; }
			void operator++(int none) 
			{
				UNREFERENCED_PARAMETER(none);
				_current_index = (_direction == forward) ? _current_index + 1 : _current_index - 1; 
			}
			void operator--() { (_direction == forward) ? _current_index - 1 : _current_index + 1; }
			void operator--(int none) 
			{ 
				UNREFERENCED_PARAMETER(none);
				_current_index = (_direction == forward) ? _current_index - 1 : _current_index + 1; 
			}
			bool operator==(iterator i) { return (_current_index == i._current_index) ? true : false; }  
			bool operator!=(iterator i) 
			{ 
				return (_current_index != i._current_index) ? true : false; 
			}
			HTNode<T>& operator*() { return (*_ht)[_current_index]; }
			HTNode<T>* operator->() { return &(*_ht)[_current_index]; }
		};
		iterator begin() { return iterator(this, 0); }
		iterator end() { return iterator(this, _count); }
		iterator rbegin() { return iterator(this, _count - 1, iterator::backward); }
		iterator rend() { return iterator(this, -1, iterator::backward); }



	};



	template <class T>
	int HashTable<T>::hash(const char* key)
	{
		unsigned hashvalue = 0;
		for (int i = 0; i < _keysize && key[i] != 0; i++)
			hashvalue += key[i];

		hashvalue %= _tablesize;

		return hashvalue;
	}

	template <class T>
	bool HashTable<T>::add(string key, T value)
	{
		int index = hash(key.c_str());
		HTNode<T>* new_node = new HTNode<T>(key.c_str(), value);
		if (new_node == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);


		if (_table[index]._next == NULL)
		{
			this->_table[index]._count += 1;
			this->_count++;
			_table[index]._next = new_node;
		}
		else
		{
			HTNode<T>* vector;

			vector = this->_table[index]._next;
			if (vector->_key == key)
			{
				vector->_value = value;
				delete new_node;
				return true;
			}
			while (vector->_next != NULL)
			{
				if (vector->_next->_key == key)
				{
					vector->_next->_value = value;
					delete new_node;
					return true;
				}
				vector = vector->_next;
			}
			this->_table[index]._count += 1;
			this->_count++;
			vector->_next = new_node;
		}
		return true;
	}

	template <class T>
	T HashTable<T>::get(string key)
	{
		int index = hash(key.c_str());
		HTNode<T>* vector = this->_table[index]._next;
		while (vector->_key != key)
		{
			vector = vector->_next;
			if (vector == NULL)
				throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
		}
		return vector->value;
	}


	template <class T>
	bool HashTable<T>::remove(string key)
	{
		int index = hash(key.c_str());
		HTNode<T>* vector = &_table[index], * temp;

		if (vector->_next == NULL)
			throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);


		while (vector->_next->_key == key)
		{
			vector = vector->_next;
			if (vector == NULL)
				throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
		}



		this->_table[index]._count--;
		this->_count--;

		temp = vector->_next;
		vector->_next = vector->_next->_next;
		delete temp;

		return true;
	}


	template <class T>
	HTNode<T>& HashTable<T>::operator[](string key)
	{
		int index = hash(key.c_str());
		HTNode<T>* vector = this->_table[index]._next;
		while (vector->_key != key)
		{
			vector = vector->_next;
			if (vector == NULL)
				throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
		}
		return *vector;
	}

	template <class T>
	HTNode<T>& HashTable<T>::operator[](int index)
	{
		HTNode<T>* vector;

		if (index > this->_count || -index > this->_count)
		{
			throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
		}

		index = (index >= 0) ? index : this->_count + index;

		for (int i = 0; i < this->_tablesize; i++)
		{
			if (index < this->_table[i]._count )
			{
				vector = this->_table[i]._next;
				for (int j = 0; j < index; j++)
				{
					vector = vector->_next;
					if (vector == NULL) throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
				}
				return *vector;
			}
			else
			{
				index -= this->_table[i]._count;
			}
		}
		throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
	}
}