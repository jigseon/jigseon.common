#pragma once

#include <cstdlib>
#include <queue>
#include <iostream>
#include <string>
#include "llist.h"

using namespace jigseon;

namespace jigseon
{
#define VERTEX_HEADER 0
#define VERTEX_NORMAL 1
#define VERTEX_ADJACET 2
#define VERTEX_VISITED 4
#define EDGE_UNKNOWN -1;
#define EDGE_HEADER 0
#define EDGE_NORMAL 0
#define EDGE_VISITED 1
#define MAX_WEIGHT 2147483647

	template <class S, class T>struct Vertex;

	template <class S, class T>
	struct Edge
	{
		struct Vertex<S, T>* _from, * _to;
		int _weight;
		struct Edge* _next;
		int _flag;

		Edge()
		{
			this->_flag = EDGE_UNKNOWN;
			_to = _from = NULL;
			_weight = 0;
			_next = NULL;
		}
	};

	template <class S, class T>
	struct AdjacentVertex
	{
		S _key;
		struct Vertex<S, T>* _from, * _to;
		int _flag;

		struct AdjacentVertex* _nextAdV;

		AdjacentVertex()
		{
			_flag = VERTEX_HEADER;
			_key = 0;
			_from = NULL;
			_to = NULL;
			_nextAdV = NULL;
		}

	};

	template <class S, class T>
	struct Vertex
	{
		S _key;
		T _data;
		int _flag;
		int _weightsumfromtarget;

		struct AdjacentVertex<S, T> _adheader;
		struct Edge<S, T> _edheader;
		Vertex()
		{
			_key = 0;
			_data = 0;
			_flag = VERTEX_NORMAL;
			_adheader._flag = VERTEX_ADJACET;
			_adheader._from = NULL;
			_adheader._to = NULL;
			_adheader._key = 0;
			_adheader._nextAdV = NULL;
			_edheader._flag = EDGE_HEADER;
			_edheader._to = 0;
			_edheader._from = 0;
			_edheader._weight = 0;
			_edheader._next = 0;
			_weightsumfromtarget = MAX_WEIGHT;
		}
	};

	template <class S, class T>
	class Graph
	{
	private:
		Vertex<S, T>* _vertices;
		int _nr_vertices, _capacity;
	public:
		Graph(int n);
		void add_vertex(S key, T data);
		void add_edge(S fromkey, S tokey, int weight);
		llist<Vertex<S, T>*> DFS();
		llist<Vertex<S, T>*> WFS();
		void dijkstra();
		friend int active_dfs(Vertex<S, T>* Node, llist<Vertex<S, T>*>& l);
		friend int active_wfs(Vertex<S, T>* Node, llist<Vertex<S, T>*>& l);
		friend int active_dijkstra(Vertex<S, T>* Node);

		T& operator[](S key);
	};

	template <class S, class T>
	Graph<S, T>::Graph(int n)
	{
		_vertices = new Vertex<S, T>[n];
		_nr_vertices = 0;
		_capacity = n;
	}

	template <class S, class T>
	void Graph<S, T>::add_vertex(S key, T data)
	{
		if (this->_nr_vertices + 1 > this->_capacity)
		{
			std::cout << "Can not create vertex any more." << endl;
			return;
		}
		this->_vertices[_nr_vertices]._key = key;
		this->_vertices[_nr_vertices]._data = data;
		_nr_vertices++;

		return;
	}

	template <class S, class T>
	void Graph<S, T>::add_edge(S fromkey, S tokey, int weight)
	{
		AdjacentVertex<S, T>* vector = NULL;
		Edge<S, T>* evector = NULL;
		Vertex<S, T>* from = NULL, * to = NULL;

		for (int i = 0; i < this->_nr_vertices; i++)
			if (_vertices[i]._key == fromkey)
			{
				vector = &_vertices[i]._adheader;
				from = _vertices + i;
				break;
			}

		for (int i = 0; i < this->_nr_vertices; i++)
			if (_vertices[i]._key == tokey)
			{
				to = _vertices + i;

				break;
			}


		if (vector == NULL || to == NULL)
		{
			std::cout << "there is no such a vertex.." << endl;
			return;
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

	}

	template <class S, class T>
	llist<Vertex<S, T>*> Graph<S, T>::DFS()
	{
		llist<Vertex<S, T>*> temp;

		for (int i = 0; i < this->_capacity; i++)
		{
			_vertices[i]._flag = VERTEX_NORMAL;
		}
		active_dfs(_vertices, temp);
		return temp;
	}

	template <class S, class T>
	int active_dfs(Vertex<S, T>* Node, llist<Vertex<S, T>*>& l)
	{
		AdjacentVertex<S, T>* vector = &Node->_adheader;

		Node->_flag |= VERTEX_VISITED;
		l.InsertTail(Node);

		while (vector->_nextAdV != NULL)
		{
			if (!(vector->_nextAdV->_to->_flag & VERTEX_VISITED))
				active_dfs(vector->_nextAdV->_to, l);
			vector = vector->_nextAdV;
		}

		return 0;
	}

	template <class S, class T>
	llist<Vertex<S, T>*>  Graph<S, T>::WFS()
	{
		llist<Vertex<S, T>*> temp;

		for (int i = 0; i < this->_capacity; i++)
		{
			_vertices[i]._flag = VERTEX_NORMAL;
		}
		active_wfs(_vertices, temp);
		return temp;
	}

	template <class S, class T>
	int active_wfs(Vertex<S, T>* Node, llist<Vertex<S, T>*>& l)
	{
		queue<Vertex<S, T>*> q;
		AdjacentVertex<S, T>* vector;

		Node->_flag |= VERTEX_VISITED;
		q.push(Node);

		while (!q.empty())
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
	void Graph<S, T>::dijkstra()
	{
		Vertex<S, T>* target = _vertices;

		for (int i = 0; i < this->_capacity; i++)
		{
			_vertices[i]._flag = VERTEX_NORMAL;
		}
		target->_weightsumfromtarget = 0;
		active_dijkstra(target);
		return ;
	}


	template <class S, class T>
	int active_dijkstra(Vertex<S, T>* Node)
	{
		AdjacentVertex<S, T>* vector;
		Edge<S, T>* evector;
		queue<Vertex<S, T>*> q;

		Node->_flag |= VERTEX_VISITED;
		q.push(Node);

		while (!q.empty())
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


	template <class S, class T>
	T& Graph<S, T>::operator[](S key)
	{
		auto l = this->WFS();
		for (auto it = l.begin(); it != l.end(); it++)
		{
			if (it->_data->_key == key)
				return it->_data->_data;
		}
		throw InvalidIndexException(__LINE__, __FUNCTION__, __FILE__);
	}

}