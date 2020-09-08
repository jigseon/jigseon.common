#include "stdafx.h"

#include "llist.h"

using namespace jigseon;

///	@brief
template <class T>
llist_node<T>::llist_node() :
	_next(nullptr),
	_prev(nullptr),
	_data(nullptr)
{
}

///	@brief
template <class T>
llist_node<T>::llist_node(_In_ const T& cls) :
	_next(nullptr),
	_prev(nullptr),
	_data(cls)
{
}

///	@brief
template <class T>
llist_node<T>::~llist_node()
{
}

///	@brief
template <class T>
llist<T>::llist() :
	_nr_llist_nodes(0),
	_tail(nullptr),
	_head(nullptr)
{
}

///	@brief
template <class T>
llist<T>::llist(_In_ T data)
{
	_head = new llist_node<T>(data);
	if (nullptr == _head)
		throw BADALLOC

		_nr_llist_nodes = 1;
	_head->_next = nullptr;
	_head->_prev = nullptr;
	_tail = _head;

	return;
}

///	@brief
template <class T>
llist<T>::llist(_In_ const llist<T>& cls) // 복사 생성자
{
	llist_node<T>* temp = cls.GetHead();

	_nr_llist_nodes = 0;
	_tail = nullptr;
	_head = nullptr;

	while (nullptr != temp)
	{
		this->InsertTail(temp->_data);
		temp = temp->_next;
	}

	this->_nr_llist_nodes = cls._nr_llist_nodes;
}

///	@brief
template <class T>
llist<T>::~llist()
{
	this->clear();
}

///	@brief
template <class T>
bool
llist<T>::InsertHead(_In_ const T& data)
{
	if (nullptr == _head)
	{
		_head = new llist_node<T>(data);
		if (nullptr == _head) throw BADALLOC

		_head->_next = nullptr;
		_head->_prev = nullptr;
		_tail = _head;
	}
	else
	{
		llist_node<T>* temp = _head;
		_head = new llist_node<T>(data);
		if (nullptr == _head) throw BADALLOC
		_head->_next = temp;
		temp->_prev = _head;
		_head->_prev = nullptr;
	}

	_nr_llist_nodes++;
	return true;
}

///	@brief
template <class T>
bool
llist<T>::InsertTail(_In_ const T& data)
{
	if (nullptr == _tail)
	{
		_tail = new llist_node<T>(data);
		if (nullptr == _tail) throw BADALLOC
		_tail->_next = nullptr;
		_tail->_prev = nullptr;
		_head = _tail;
	}
	else
	{
		llist_node<T>* temp = _tail;
		_tail = new llist_node<T>(data);
		if (nullptr == _tail) throw BADALLOC
		_tail->_prev = temp;
		temp->_next = _tail;
		_tail->_next = nullptr;
	}

	_nr_llist_nodes++;
	return true;
}

///	@brief
template <class T>
bool
llist<T>::InsertAt(_In_ uint32_t index, _In_ const T& data)
{
	_nr_llist_nodes++;
	llist_node<T>* temp = _head;

	if (index < 0)
	{
		throw INVALIDINPUT
	}

	if (nullptr == _head || 0 == index)
	{
		InsertHead(data);
		return true;
	}
	else
	{
		for (uint32_t i = 0; i <= index - 1; ++i)
		{
			if (nullptr == temp->_next) // 목표에 도달하지 못하였는데 널이라면..
			{
				InsertTail(data);
				return true;
			}
			temp = temp->_next;
		}

		llist_node<T>* newllist_node = new llist_node<T>(data);
		if (nullptr == _head) throw BADALLOC
		newllist_node->_next = temp->_next;
		newllist_node->_next->_prev = newllist_node;
		temp->_next = newllist_node;
		newllist_node->_prev = temp;
		return true;
	}
}

///	@brief
template <class T>
bool
llist<T>::Delete(_In_ llist_node<T>* node)
{
	if (_nr_llist_nodes == 0)
		return false;

	_nr_llist_nodes--;

	if (nullptr == node->_prev)
		_head = node->_next;
	else
		node->_prev->_next = node->_next;

	if (nullptr == node->_next)
		_tail = node->_prev;
	else
		node->_next->_prev = node->_prev;

	delete node;

	return true;
}

///	@brief
template <class T>
bool
llist<T>::DeleteHead()
{
	if (_nr_llist_nodes == 0)
		return false;
	_nr_llist_nodes--;
	llist_node<T>* temp = _head;

	if (nullptr == _head)
		return false;

	_head = _head->_next;
	if (nullptr == _head)
		_tail = nullptr;

	delete temp;

	return true;
}

///	@brief
template <class T>
bool
llist<T>::DeleteTail()
{
	if (_nr_llist_nodes == 0)
		return false;
	_nr_llist_nodes--;
	llist_node<T>* temp = _tail;

	if (nullptr == _tail)
		return false;

	if (_tail == _head)
	{
		_tail = nullptr;
		_head = nullptr;

		delete _tail; // <-- ???
		return true;
	}

	_tail = _tail->_prev;
	if (nullptr == _tail)
		_head = nullptr;
	else
		_tail->_next = nullptr;

	delete temp;

	return true;
}


///	@brief
template <class T>
bool
llist<T>::DeleteAt(_In_ uint32_t index)
{
	if (_nr_llist_nodes == 0)
		return false;
	if (index < 0)
		return false;


	_nr_llist_nodes--; // <-- ???
	llist_node<T>* temp = _head;

	if (index == 0)
	{
		DeleteHead();
		return true;
	}
	else
	{
		for (uint32_t i = 1; i <= index; ++i)
		{
			temp = temp->_next;
			if (nullptr == temp->_next)
			{
				DeleteTail();
				return true;
			}
		}

		temp->_next->_prev = temp->_prev;
		temp->_prev->_next = temp->_next;
		delete temp;

		return true;
	}
}

///	@brief
template <class T>
llist_node<T>*
llist<T>::GetHead() const
{
	return _head;
}

///	@brief
template <class T>
llist_node<T>*
llist<T>::GetTail() const
{
	return _tail;
}

///	@brief
template <class T>
T&
llist<T>::operator[](int index)
{
	if (index >= this->_nr_llist_nodes || -index > (int)this->_nr_llist_nodes) // <-- ???
	{
		throw INVALIDINPUT
	}

	auto it = (index >= 0) ? this->begin() : this->rbegin();

	for (int i = 0; i < index; ++i)
		it++;

	return it->_data;
}

///	@brief
template <class T>
llist<T>&
llist<T>::copy()
{
	return new llist<T>(*this);
}

///	@brief
template <class T>
void
llist<T>::extend(const llist<T> l)
{
	llist<T>* temp = new llist<T>(l);
	this->_tail->_next = temp->_head;
	temp->_head->_prev = this->_tail;
	this->_nr_llist_nodes += temp->_nr_llist_nodes;
	this->_tail = temp->_tail;
}

///	@brief
template <class T>
void
llist<T>::remove(T value)
{
	for (llist<T>::iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it->_data == value)
		{
			this->Delete(&*it);
			return;
		}
	}
}

///	@brief
template <class T>
void llist<T>::reverse()
{
    Heap<T> maxheap(this->_nr_llist_nodes, maximum);
    for (auto it = this->begin(); it != this->end(); it++)
    {
        maxheap.enqueue(it->_data, it->_data);
    }
    for (auto it = this->begin(); it != this->end(); it++)
    {
        it->_data = maxheap.dequeue().data;
    }
}

///	@brief
template <class T>
void llist<T>::sort()
{
    Heap<T> minheap(this->_nr_llist_nodes, minimum);
    for (auto it = this->begin(); it != this->end(); it++)
    {
        minheap.enqueue(it->_data, it->_data);
    }
    for (auto it = this->begin(); it != this->end(); it++)
    {
        it->_data = minheap.dequeue().data;
    }
}
