#pragma once

#include <iostream>
#include <string>
#include "ExceptionClass.h"

using namespace std;


template <class T>
struct HTNode
{
	char* key;
	T value;
	int count;

	HTNode<T>* next;

	HTNode(int keysize = 10)
	{
		this->key = new char[keysize];
		if (this->key == NULL) throw BadAllocException(__LINE__,__FUNCTION__,__FILE__);
		this->next = NULL;
		this->value = 0;
		this->count = 0;
	}

	HTNode(const char* key, T value, int keysize = 10)
	{
		this->key = new char[keysize];
		if (this->key == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
		strcpy_s(this->key, keysize, key);
		this->value = value;
		this->next = NULL;
		this->count = 0;
	}
	~HTNode()
	{
		delete key;
	}

};

template <class T>
class HashTable
{
private:
	HTNode<T>* table;
	int keysize;
	int tablesize;
	int count;

public:
	HashTable<T>(int tablesize = 20, int keysize = 10)
	{
		this->keysize = keysize;
		this->tablesize = tablesize;
		this->count = 0;

		this->table = new HTNode<T>[tablesize];
		if (this->table == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);
	}
	~HashTable<T>()
	{
	    delete this->table;
	    
	}
	
	int hash(const char* key);
	bool add(string key, T value);
	T get(string key);
	bool remove(string key);

	HTNode<T>& operator[](string key);
	HTNode<T>& operator[](int index);


	class iterator
	{
		HashTable<T> *ht;
		bool direction;
		int current_index;
	public:
		enum directions { forward, backward };
		iterator(HashTable<T> *ht, int current_index, bool dir = forward) { this->ht = ht; this->current_index = current_index; this->direction = dir; }

		void operator++() { current_index = (direction == forward) ? current_index + 1 : current_index - 1; }
		void operator++(int none) { current_index = (direction == forward) ? current_index + 1 : current_index - 1; }
		void operator--() { (direction == forward) ? current_index - 1 : current_index + 1; }
		void operator--(int none) { current_index = (direction == forward) ? current_index - 1 : current_index + 1; }
		bool operator==(iterator i) { return (current_index == i.current_index) ? true : false; } // iterator &i 로 받을 경우 begin()에서 나온 iterator가  
		bool operator!=(iterator i) { return (current_index != i.current_index) ? true : false; }
		HTNode<T>& operator*() { return (*ht)[current_index]; }
		HTNode<T> *operator->() { return &(*ht)[current_index]; }
	};
	iterator begin() {	return iterator(this,0);}
	iterator end() { return iterator(this, count); }
	iterator rbegin() { return iterator(this, count - 1, iterator::backward); }
	iterator rend() { return iterator(this, -1, iterator::backward); }



};



template <class T>
int HashTable<T>::hash(const char* key)
{
	unsigned hashvalue = 0;
	for (int i = 0; i < keysize && key[i] != 0; i++)
		hashvalue += key[i];

	hashvalue %= tablesize;

	return hashvalue;
}

template <class T>
bool HashTable<T>::add(string key, T value)
{
	int index = hash(key.c_str());
	HTNode<T>* new_node = new HTNode<T>(key.c_str(), value);
	if (new_node == NULL) throw BadAllocException(__LINE__, __FUNCTION__, __FILE__);


	this->table[index].count += 1;
	this->count++;

	if (table[index].next == NULL)
		table[index].next = new_node;
	else
	{
		HTNode<T>* vector;

		vector = this->table[index].next;
		while (vector->next != NULL)
		{
 			if (vector->next->key == key)
			{
				vector->next->value = value;
				delete new_node;
			}
			vector = vector->next;
		}

		vector->next = new_node;
	}
	return true;
}

template <class T>
T HashTable<T>::get(string key)
{
	int index = hash(key.c_str());
	HTNode<T>* vector = this->table[index].next;
	while (vector->key != key)
	{
		vector = vector->next;
		if (vector == NULL)
			throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
	}
	return vector->value;
}


template <class T>
bool HashTable<T>::remove(string key)
{
	int index = hash(key.c_str());
	HTNode<T>* vector = &HashTable[index], * temp;

	if (vector->next == NULL)
		throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);


	while (strcmp(vector->next->key, key) != 0)
	{
		vector = vector->next;
		if (vector->next == NULL)
			throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
	}



	this->table[index].count--;
	this->count--;

	temp = vector->next;
	vector->next = vector->next->next;
	delete temp;

	return true;
}


template <class T>
HTNode<T>& HashTable<T>::operator[](string key)
{
	int index = hash(key.c_str());
	HTNode<T>* vector = this->table[index].next;
	while (vector->key != key)
	{
		vector = vector->next;
		if (vector == NULL)
			throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
	}
	return *vector;
}

template <class T>
HTNode<T>& HashTable<T>::operator[](int index)
{
	HTNode<T>* vector;

	if (index > this->count || -index > this->count)
	{
		throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
	}

	index = (index > 0) ? index : this->count + index;

	for (int i = 0; i < this->tablesize; i++)
	{
		if (index < this->table[i].count)
		{
			vector = this->table[i].next;
			for (int j = 0; j < index; j++)
			{
				vector = vector->next;
				if (vector == NULL) throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
			}
			return *vector;
		}
		else
		{
			index -= this->table[i].count;
		}
	}
}