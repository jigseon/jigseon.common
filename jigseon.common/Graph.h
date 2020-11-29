#pragma once

#include <cstdlib>
#include <queue>
#include <iostream>
#include <string>
#include "llist.h"

using namespace std;

#define VERTEX_HEADER 0
#define VERTEX_NORMAL 1
#define VERTEX_ADJACET 2
#define VERTEX_VISITED 4
#define EDGE_HEADER 0
#define EDGE_NORMAL 0
#define EDGE_VISITED 1
#define MAX_WEIGHT 2147483647

template <class S, class T>struct Vertex;

template <class S,class T>
struct Edge
{
	struct Vertex<S,T> *_from, *_to;
	int _weight;
	struct Edge * _next;
	int _flag;

	Edge()
	{
		_to = _from = NULL;
		_weight = 0;
		next = NULL;
	}
};

template <class S, class T>
struct AdjacentVertex
{
	S _key;
	struct Vertex<S,T> * _from, * _to;
	int _flag;

	struct AdjacentVertex *nextAdV;

	AdjacentVertex()
	{
		_flag = VERTEX_HEADER;
		_key = 0;
		_from = NULL;
		_to = NULL;
		nextAdV = NULL;
	}

};

template <class S,class T>
struct Vertex
{
	S key;
	T data;
	int flag;
	int weightsumfromtarget;

	struct AdjacentVertex<S,T> adheader;
	struct Edge<S,T> edheader;
	Vertex()
	{
		key = 0;
		data = 0;
		flag = VERTEX_NORMAL;
		adheader._flag = VERTEX_ADJACET;
		adheader._from = NULL;
		adheader._to = NULL;
		adheader._key = 0;
		adheader._nextAdV = NULL;
		edheader._flag = EDGE_HEADER;
		edheader._to = 0;
		edheader._from = 0;
		edheader._weight = 0;
		edheader._next = 0;
		_weightsumfromtarget = MAX_WEIGHT;
	}
};

template <class S,class T>
class Graph
{
private:
	Vertex<S,T> * _vertices;
	int _nr_vertices, _capacity;
public:
	Graph(int n);
	int AddVertex(S key, T data);
	int AddEdge(S fromkey, S tokey, int weight);
	LinkedList<Vertex<S, T>*> DFS();
	LinkedList<Vertex<S, T>*> WFS();
	int dikjstra();
	friend int Active_DFS(Vertex<S,T> *Node, LinkedList<Vertex<S, T>*>&l);
	friend int Active_WFS(Vertex<S,T> *Node, LinkedList<Vertex<S, T>*>& l);
	friend int Active_dikjstra(Vertex<S,T> *Node);

	T& operator[](S key);
};

template <class S,class T>
Graph<S,T>::Graph(int n)
{
	_vertices = new Vertex<S, T>[n];
	_nr_vertices = 0;
	_capacity = n;
}

template <class S, class T>
int Graph<S,T>::AddVertex(S key, T data)
{
	if (this->_nr_vertices + 1 > this->_capacity)
	{
		cout << "Can not create vertex any more." << endl;
		return 0;
	}
	this->_vertices[_nr_vertices]._key = key;
	this->_vertices[_nr_vertices]._data = data;
	_nr_vertices++;

	return 1;
}

template <class S, class T>
int Graph<S,T>::AddEdge(S fromkey, S tokey, int weight)
{
	AdjacentVertex<S, T>*vector = NULL;
	Edge<S, T>* evector = NULL;
	Vertex<S, T> *from = NULL, *to = NULL;

	for (int i = 0; i < this->_nr_vertices; i++)
		if (_vertices[i].key == fromkey)
		{
			vector = &_vertices[i]._adheader;
			from = _vertices + i;
			break;
		}

	for (int i = 0; i < this->_nr_vertices; i++)
		if (_vertices[i].key == tokey)
		{
			to = _vertices + i;

			break;
		}


	if (vector == NULL || to == NULL)
	{
		cout << "there is no such a vertex.." << endl;
		return 0;
	}


	while (vector->_nextAdV != NULL)
		vector = vector->_nextAdV;

	vector->_nextAdV = new AdjacentVertex<S, T>;
	vector->_nextAdV->_from = from;
	vector->_nextAdV->_to = to;
	vector->_nextAdV->_key = tokey;
	vector->_nextAdV->_flag = VERTEX_ADJACET;
	vector->_nextAdV->_nextAdV = NULL;

	evector = &from->_edheader;
	while (evector->_next != NULL)
		evector = evector->_next;
	evector->_next = new Edge<S, T>;
	evector->_next->_from = from;
	evector->_next->_to = to;
	evector->_next->_weight = weight;
	evector->_next->_next = NULL;
	evector->_next->_flag = EDGE_NORMAL;


	return 1;
}

template <class S, class T>
llist<Vertex<S, T> *> Graph<S,T>::DFS()
{
	LinkedList<Vertex<S, T>*> temp;

	for (int i = 0; i < this->_capacity; i++)
	{
		Vertices[i]._flag = VERTEX_NORMAL;
	}
	Active_DFS(_vertices,temp);
	return temp;
}

template <class S, class T>
int Active_DFS(Vertex<S, T> *Node, llist<Vertex<S, T>*> &l)
{
	AdjacentVertex<S, T>* vector = &Node->_adheader;

	Node->_flag |= VERTEX_VISITED;
	l.InsertTail(Node);

	while (vector->_nextAdV != NULL)
	{
		if (!(vector->_nextAdV->_to->_flag & VERTEX_VISITED))
			Active_DFS(vector->_nextAdV->_to,l);
		vector = vector->_nextAdV;
	}

	return 0;
}

template <class S, class T>
llist<Vertex<S, T>*>  Graph<S,T>::WFS()
{
	LinkedList<Vertex<S, T>*> temp;

	for (int i = 0; i < this->_capacity; i++)
	{
		_vertices[i]._flag = VERTEX_NORMAL;
	}
	Active_WFS(_vertices,temp);
	return temp;
}

template <class S, class T>
int Active_WFS(Vertex<S, T>*Node, llist<Vertex<S, T>*> &l)
{
	queue<Vertex<S, T>*> q;
	AdjacentVertex<S,T> *vector;

	Node->_flag |= VERTEX_VISITED;
	q.push(Node);

	while (! q.empty())
	{
		Node = q.front();
		q.pop();

		l.InsertTail(Node);
		vector = &Node->_adheader;
		while (vector->_nextAdV != NULL)
		{
			if (!(vector->_nextAdV->_to->_flag & VERTEX_VISITED))
			{
				vector->_nextAdV->_to->_flag |= VERTEX_VISITED;
				q.push(vector->_nextAdV->_to);
			}
			vector = vector->_nextAdV;
		}
	}
	return 0;
}


template <class S, class T>
int Graph<S,T>::dikjstra()
{
	Vertex<S, T>*target = _vertices;

	for (int i = 0; i < this->_capacity; i++)
	{
		_vertices[i].flag = VERTEX_NORMAL;
	}
	target->_weightsumfromtarget = 0;
	Active_dikjstra(target);
	return 0;
}


template <class S, class T>
int Active_dikjstra(Vertex<S, T>*Node)
{
	AdjacentVertex<S, T>*vector;
	Edge<S, T>*evector;
	queue<Vertex<S, T>*> q;

	Node->flag |= VERTEX_VISITED;
	q.push(Node);

	while (! q.empty())
	{

		Node = q.front();
		q.pop();

		evector = Node->_edheader._next;

		while (evector != NULL)
		{
			if (evector->_to->_weightsumfromtarget > Node->_weightsumfromtarget + evector->_weight)
			{
				evector->_to->_weightsumfromtarget = ((Node->_weightsumfromtarget == MAX_WEIGHT) ? 0 : Node->_weightsumfromtarget) + evector->_weight;
				q.push(evector->_to);
			}
			evector = evector->_next;
		}






		vector = &Node->_adheader;
		while (vector->_nextAdV != NULL)
		{
			if (!(vector->_nextAdV->_to->_flag & VERTEX_VISITED))
			{
				vector->_nextAdV->_to->_flag |= VERTEX_VISITED;
				q.push(vector->_nextAdV->_to);
			}
			vector = vector->_nextAdV;
		}
	}
	return 0;
}


template <class S,class T>
T& Graph<S, T>::operator[](S key)
{
	auto l = this->WFS();
	for (auto it = l.begin();it != l.end();it++)
	{
		if (it->_data->_key == key)
			return it->_data->_data;
	}
	throw InvalidIndexException(__LINE__,__FUNCTION__,__FILE__);
}

