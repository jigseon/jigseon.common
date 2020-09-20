#pragma once

#include <cstdlib>
#include <queue>
#include <iostream>
#include <string>
#include "LinkedList.h"

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
	struct Vertex<S,T> *from, *to;
	int weight;
	struct Edge *next;
	int flag;

	Edge()
	{
		to = from = NULL;
		weight = 0;
		next = NULL;
	}
};

template <class S, class T>
struct AdjacentVertex
{
	S key;
	struct Vertex<S,T> *from, *to;
	int flag;

	struct AdjacentVertex *nextAdV;

	AdjacentVertex()
	{
		flag = VERTEX_HEADER;
		key = 0;
		from = NULL;
		to = NULL;
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
		adheader.flag = VERTEX_ADJACET;
		adheader.from = NULL;
		adheader.to = NULL;
		adheader.key = 0;
		adheader.nextAdV = NULL;
		edheader.flag = EDGE_HEADER;
		edheader.to = 0;
		edheader.from = 0;
		edheader.weight = 0;
		edheader.next = 0;
		weightsumfromtarget = MAX_WEIGHT;
	}
};

template <class S,class T>
class Graph
{
private:
	Vertex<S,T> *Vertices;
	int nr_vertices, capacity;
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
	Vertices = new Vertex<S, T>[n];
	nr_vertices = 0;
	capacity = n;
}

template <class S, class T>
int Graph<S,T>::AddVertex(S key, T data)
{
	if (this->nr_vertices + 1 > this->capacity)
	{
		cout << "Can not create vertex any more." << endl;
		return 0;
	}
	this->Vertices[nr_vertices].key = key;
	this->Vertices[nr_vertices].data = data;
	nr_vertices++;

	return 1;
}

template <class S, class T>
int Graph<S,T>::AddEdge(S fromkey, S tokey, int weight)
{
	AdjacentVertex<S, T>*vector = NULL;
	Edge<S, T>* evector = NULL;
	Vertex<S, T> *from = NULL, *to = NULL;

	for (int i = 0; i < this->nr_vertices; i++)
		if (Vertices[i].key == fromkey)
		{
			vector = &Vertices[i].adheader;
			from = Vertices + i;
			break;
		}

	for (int i = 0; i < this->nr_vertices; i++)
		if (Vertices[i].key == tokey)
		{
			to = Vertices + i;

			break;
		}


	if (vector == NULL || to == NULL)
	{
		cout << "there is no such a vertex.." << endl;
		return 0;
	}


	while (vector->nextAdV != NULL)
		vector = vector->nextAdV;

	vector->nextAdV = new AdjacentVertex<S, T>;
	vector->nextAdV->from = from;
	vector->nextAdV->to = to;
	vector->nextAdV->key = tokey;
	vector->nextAdV->flag = VERTEX_ADJACET;
	vector->nextAdV->nextAdV = NULL;

	evector = &from->edheader;
	while (evector->next != NULL)
		evector = evector->next;
	evector->next = new Edge<S, T>;
	evector->next->from = from;
	evector->next->to = to;
	evector->next->weight = weight;
	evector->next->next = NULL;
	evector->next->flag = EDGE_NORMAL;


	return 1;
}

template <class S, class T>
LinkedList<Vertex<S, T> *> Graph<S,T>::DFS()
{
	LinkedList<Vertex<S, T>*> temp;

	for (int i = 0; i < this->capacity; i++)
	{
		Vertices[i].flag = VERTEX_NORMAL;
	}
	Active_DFS(Vertices,temp);
	return temp;
}

template <class S, class T>
int Active_DFS(Vertex<S, T> *Node, LinkedList<Vertex<S, T>*> &l)
{
	AdjacentVertex<S, T>* vector = &Node->adheader;

	Node->flag |= VERTEX_VISITED;
	l.InsertTail(Node);

	while (vector->nextAdV != NULL)
	{
		if (!(vector->nextAdV->to->flag & VERTEX_VISITED))
			Active_DFS(vector->nextAdV->to,l);
		vector = vector->nextAdV;
	}

	return 0;
}

template <class S, class T>
LinkedList<Vertex<S, T>*>  Graph<S,T>::WFS()
{
	LinkedList<Vertex<S, T>*> temp;

	for (int i = 0; i < this->capacity; i++)
	{
		Vertices[i].flag = VERTEX_NORMAL;
	}
	Active_WFS(Vertices,temp);
	return temp;
}

template <class S, class T>
int Active_WFS(Vertex<S, T>*Node, LinkedList<Vertex<S, T>*> &l)
{
	queue<Vertex<S, T>*> q;
	AdjacentVertex<S,T> *vector;

	Node->flag |= VERTEX_VISITED;
	q.push(Node);

	while (! q.empty())
	{
		Node = q.front();
		q.pop();

		l.InsertTail(Node);
		vector = &Node->adheader;
		while (vector->nextAdV != NULL)
		{
			if (!(vector->nextAdV->to->flag & VERTEX_VISITED))
			{
				vector->nextAdV->to->flag |= VERTEX_VISITED;
				q.push(vector->nextAdV->to);
			}
			vector = vector->nextAdV;
		}
	}
	return 0;
}


template <class S, class T>
int Graph<S,T>::dikjstra()
{
	Vertex<S, T>*target = Vertices;

	for (int i = 0; i < this->capacity; i++)
	{
		Vertices[i].flag = VERTEX_NORMAL;
	}
	target->weightsumfromtarget = 0;
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

		evector = Node->edheader.next;

		while (evector != NULL)
		{
			if (evector->to->weightsumfromtarget > Node->weightsumfromtarget + evector->weight)
			{
				evector->to->weightsumfromtarget = ((Node->weightsumfromtarget == MAX_WEIGHT) ? 0 : Node->weightsumfromtarget) + evector->weight;
				q.push(evector->to);
			}
			evector = evector->next;
		}






		vector = &Node->adheader;
		while (vector->nextAdV != NULL)
		{
			if (!(vector->nextAdV->to->flag & VERTEX_VISITED))
			{
				vector->nextAdV->to->flag |= VERTEX_VISITED;
				q.push(vector->nextAdV->to);
			}
			vector = vector->nextAdV;
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
		if (it->data->key == key)
			return it->data->data;
	}
	throw InvalidIndexException(__LINE__,__FUNCTION__,__FILE__);
}

