#pragma once
#include <iostream>
#include <iterator>
#include "llist.h"
#include "ExceptionClass.h"
#include <queue>
using namespace std;

enum node_color {red, black, double_black};

template <class S, class T> class RBTree;

template <class S, class T>
class RBTreeNode
{
protected:
	S _key;
	T _data;
	int _color;
	int _depth;
	RBTreeNode * _leftchild, * _rightchild, * _parent;

public:
	RBTreeNode() { _key = S(); _data = T(); _color = red; _leftchild = _rightchild = _parent = NULL; }
	RBTreeNode(S k, T d) { _key = k; _data = d; _color = red; _leftchild = _rightchild = _parent = NULL; }
	RBTreeNode(const RBTreeNode &t) { this->_key = t._key; this->_data = t._data; this->_color = red; this->_leftchild = t._leftchild; this->_rightchild = t._rightchild; this->_parent = t._parent; }

	RBTreeNode *get_left_child() { return _leftchild; }
	RBTreeNode *get_right_child() { return _rightchild; }
	void delete_left_child() { delete _leftchild; _leftchild = NULL; }
	void delete_right_child() { delete _rightchild; _rightchild = NULL; }
	RBTreeNode *get_parent() { return _parent; }
	RBTreeNode *set_left_child(S k, T d);
	RBTreeNode *set_right_child(S k, T d);
	S get_key() { return _key; }
	T get_data() { return _data; }
	void set_key(S k) { _key = k; }
	void set_data(T d) { _data = d; }
	
	friend class RBTree<S, T>;
};

template <class S, class T>
class RBTree
{
protected:
	RBTreeNode<S, T> *root;
	RBTreeNode<S, T> *current;

	bool rb_insert_process(RBTreeNode <S, T> *);
	bool rb_delete_process( RBTreeNode <S, T> *, RBTreeNode <S, T> *);
public:
	RBTree() { root = NULL; current = NULL; }
	RBTree(S k, T d) { root = new RBTreeNode(k, d); current = root; }
	//RBTree(const RBTree &);
	~RBTree();

	RBTreeNode<S,T> * set_root(S k, T d) { root = new RBTreeNode<S, T>(k, d); root->color = black; current = root; return root; }
	void set_current_as_root() { current = root; }
	RBTreeNode <S, T> *get_root() { return this->root; }
	RBTreeNode <S, T> *get_current_node() { return this->current; }
	RBTreeNode <S, T> *find(S);
	void move_to_left() { current = current->get_left_child(); }
	void move_to_right() { current = current->get_right_child(); }
	void move_to_parent() { current = current->parent; }

	void remove_left_child();
	void remove_right_child();

	llist<RBTreeNode<S, T>*> preorder_traverse();
	llist<RBTreeNode<S, T>*> inorder_traverse();
	llist<RBTreeNode<S, T>*> postorder_traverse();
	void levelorder_print();

	bool insert_node(S, T);
	void delete_node(RBTreeNode<S, T> *);
	int active_delete_node(RBTreeNode<S, T> *, RBTreeNode<S, T> **, RBTreeNode<S, T> **);

	bool LLr_coloring(RBTreeNode<S, T> *);
	bool LLb_rotate(RBTreeNode<S, T> *);
	bool LRr_coloring(RBTreeNode<S, T> *);
	bool LRb_rotate(RBTreeNode<S, T> *);

	bool RLr_coloring(RBTreeNode<S, T> *);
	bool RLb_rotate(RBTreeNode<S, T> *);
	bool RRr_coloring(RBTreeNode<S, T> *);
	bool RRb_rotate(RBTreeNode<S, T> *);


	friend void active_destructor(RBTreeNode<S, T> *);
	friend bool active_preorder_traverse(RBTreeNode<S, T> *, llist<RBTreeNode<S, T> *> &);
	friend bool active_inorder_traverse(RBTreeNode<S, T> *, llist<RBTreeNode<S, T> *> &);
	friend bool active_postorder_traverse(RBTreeNode<S, T> *, llist<RBTreeNode<S, T> *> &);
};

template <class S, class T>
RBTreeNode<S, T>* RBTreeNode<S, T>::set_left_child(S k, T d)
{
	leftchild = new RBTreeNode(k, d);
	leftchild->parent = this;
	return leftchild;
}

template <class S, class T>
RBTreeNode<S, T>* RBTreeNode<S, T>::set_right_child(S k, T d)
{
	rightchild = new RBTreeNode(k, d);
	rightchild->parent = this;
	return rightchild;
}


template <class S, class T>
RBTree<S, T>::~RBTree()
{
	active_destructor(root);
	delete(this->root);
	this->root = NULL;
}

template<class S, class T>
inline RBTreeNode<S, T>* RBTree<S, T>::find(S key)
{
	RBTreeNode<S, T>* vector = this->get_root();

	while (vector)
	{
		if (vector->key == key)
			break;
		else if (vector->key > key)
		{
			vector = vector->leftchild;
		}
		else
		{
			vector = vector->rightchild;
		}
	}
	return vector;
}

template <class S, class T>
void RBTree<S, T>::remove_left_child()
{
	delete current->rightchild;
	current->rightchild = NULL;
}

template <class S, class T>
void RBTree<S, T>::remove_right_child()
{
	delete current->leftchild;
	current->leftchild = NULL;
}

template <class S, class T>
llist<RBTreeNode<S,T> *> RBTree<S, T>::preorder_traverse()
{
	llist<RBTreeNode<S, T>*> res;
	active_preorder_traverse(this->root, res);

	return res;
}

template <class S, class T>
bool active_preorder_traverse(RBTreeNode<S, T> *vector, llist<RBTreeNode<S, T>*> &l)
{
	l.InsertTail(vector);
	if (vector->get_left_child() != NULL)
		active_preorder_traverse(vector->get_left_child(), l);
	if (vector->get_right_child() != NULL)
		active_preorder_traverse(vector->get_right_child(), l);

	return true;
}

template <class S, class T>
llist<RBTreeNode<S, T>* > RBTree<S, T>::inorder_traverse()
{
	llist<RBTreeNode<S, T>*> res;
	active_inorder_traverse(this->root, res);

	return res;
}

template <class S, class T>
bool active_inorder_traverse(RBTreeNode<S, T> *vector, llist<RBTreeNode<S, T>*> &l)
{
	if (vector->get_left_child() != NULL)
		active_inorder_traverse(vector->get_left_child(), l);
	l.InsertTail(vector);
	if (vector->get_right_child() != NULL)
		active_inorder_traverse(vector->get_right_child(), l);

	return true;
}

template <class S, class T>
llist<RBTreeNode<S, T>* > RBTree<S, T>::postorder_traverse()
{
	llist<RBTreeNode<S, T>*> res;
	active_postorder_traverse(this->root, res);

	return res;
}

template <class S, class T>
bool active_postorder_traverse(RBTreeNode<S, T> *vector, llist<RBTreeNode<S, T>* > &l)
{
	if (vector->get_left_child() != NULL)
		active_postorder_traverse(vector->get_left_child(), l);
	if (vector->get_right_child() != NULL)
		active_postorder_traverse(vector->get_right_child(), l);
	l.InsertTail(vector);

	return true;
}




template <class S, class T>
int RBTree<S,T>::active_delete_node(RBTreeNode<S, T> *target, RBTreeNode<S, T> **vparent, RBTreeNode<S, T> **sibling)
{
	RBTreeNode<S, T> *vector = target, *parent = target->parent;
	int old_color;


	if (vector->get_left_child() != NULL)
	{
		vector = vector->get_left_child();
		while (vector->get_right_child())
			vector = vector->get_right_child();
		target->key = vector->key;
		target->data = vector->data;
		return active_delete_node(vector, vparent, sibling);

	}
	else if (vector->get_right_child() != NULL)
	{
		vector = vector->get_right_child();
		while (vector->get_left_child())
			vector = vector->get_left_child();
		target->key = vector->key;
		target->data = vector->data;
		return active_delete_node(vector, vparent, sibling);
	}
	else
	{
		old_color = vector->color;
		*vparent = vector->parent;
		if (vector->get_parent()->get_left_child() == vector)
		{
			vector->parent->leftchild = NULL;
			*sibling = vector->parent->rightchild;
		}
		else
		{
			vector->parent->rightchild = NULL;
			*sibling = vector->parent->leftchild;
		}
		delete vector;
		target = NULL;
		vector = NULL;

		return old_color;
	}
}


template <class S, class T>
void active_destructor(RBTreeNode<S, T> *vector)
{
	if (vector->get_left_child() != NULL)
		active_destructor(vector->get_left_child());
	if (vector->get_right_child() != NULL)
		active_destructor(vector->get_right_child());

	if (vector->get_left_child() != NULL)
		vector->delete_left_child();
	if (vector->get_right_child() != NULL)
		vector->delete_right_child();
}

template <class S, class T>
bool RBTree<S, T>::insert_node(S key, T data)
{
	RBTreeNode<S, T> *vector = root;

	while (vector != NULL)
	{
		if (vector->get_key() > key)
		{
			if (vector->leftchild == NULL)
				return rb_insert_process(vector->set_left_child(key, data));
			vector = vector->leftchild;
		}
		else
		{
			if (vector->rightchild == NULL)
				return rb_insert_process(vector->set_right_child(key, data));
			vector = vector->rightchild;
		}
	}

	return (this->set_root(key, data) != NULL)?true:false;
}


template <class S, class T>
void RBTree<S, T>::levelorder_print()
{
	RBTreeNode <S, T> *vector;
	queue<RBTreeNode <S, T> *> q;
	int current_depth;

	vector = get_root();
	current_depth = vector->depth = 1;
	q.push(vector);

	while (1)
	{
		if (q.empty() || vector == NULL)
			break;

		vector = q.front();
		q.pop();

		if (current_depth != vector->depth)
		{
			current_depth = vector->depth;
			cout << endl;
		}
		cout << vector->key << "("<< vector->color<<")" << " : " << vector->data << "  ";

		if (vector->leftchild != NULL)
		{
			vector->leftchild->depth = vector->depth + 1;
			q.push(vector->leftchild);
		}
		if (vector->rightchild != NULL)
		{
			vector->rightchild->depth = vector->depth + 1;
			q.push(vector->rightchild);
		}
	}
}


template <class S, class T>
bool RBTree<S, T>::rb_insert_process(RBTreeNode <S, T> *current)
{
	RBTreeNode <S, T> *parent,*gparent,*uncle;
	
	if (current == root)
		current->color = black;
	if (current->parent == root)
		return true;
	if (current->parent->color == black)
		return true;

	while(current!= root)
	{
		if (current->parent == root)
			return true;
		parent = current->parent;
		gparent = parent->parent;
		if (gparent->leftchild == parent)
		{
			uncle = gparent->rightchild;
			if (parent->leftchild == current)
			{
				if (uncle == NULL)
				{
					LLb_rotate(current);
					return true;
				}
				else if (uncle->color == red)
				{
					LLr_coloring(current);
				}
				else
				{
					LLb_rotate(current);
					return true;
				}
			}
			else
			{
				if (uncle == NULL)
				{
					LRb_rotate(current);
					return true;
				}
				else if (uncle->color == red)
				{
					LRr_coloring(current);
				}
				else
				{
					LRb_rotate(current);
					return true;
				}
			}
		}
		else
		{
			uncle = gparent->leftchild;
			if (parent->leftchild == current)
			{
				if (uncle == NULL)
				{
					RLb_rotate(current);
					return true;
				}
				else if (uncle->color == red)
				{
					RLr_coloring(current);
				}
				else
				{
					RLb_rotate(current);
					return true;
				}
			}
			else
			{
				if (uncle == NULL)
				{
					RRb_rotate(current);
					return true;
				}
				else if (uncle->color == red)
				{
					RRr_coloring(current);
				}
				else
				{
					RLb_rotate(current);
					return true;
				}
			}
		}
		current = gparent;
	}
	current->color = black;
}

template <class S, class T>
void RBTree<S, T>::delete_node(RBTreeNode<S, T> *target)
{
	RBTreeNode<S, T> *parent = target->parent, *successor, *sibling;
	int old_color = target->color;

	if (active_delete_node(target, &parent, &sibling) == black)
		rb_delete_process(parent, sibling);
	root->color = black;
}

template<class S, class T>
inline bool RBTree<S, T>::LLr_coloring(RBTreeNode<S, T>* current)
{
	current->parent->parent->color = red;
	current->parent->parent->leftchild->color = black;
	current->parent->parent->rightchild->color = black;

	return true;
}

template<class S, class T>
inline bool RBTree<S, T>::LLb_rotate(RBTreeNode<S, T>* current)
{
	RBTreeNode<S, T> *parent, *gparent, *uncle;
	parent = current->parent;
	gparent = parent->parent;
	uncle = gparent->rightchild;

	gparent->set_right_child(gparent->key, gparent->data);
	if (uncle != NULL)
	{
		gparent->rightchild->rightchild = uncle;
		uncle->parent = gparent->rightchild;
	}
	gparent->rightchild->leftchild = parent->rightchild;
	parent->rightchild = NULL;
	if (gparent->rightchild->leftchild != NULL)
		gparent->rightchild->leftchild->parent = gparent->rightchild;


	gparent->key = parent->key;
	gparent->data = parent->data;

	gparent->leftchild = parent->leftchild;
	if(parent->leftchild != NULL)
		parent->leftchild->parent = gparent;
	delete parent;

	return true;
}

template<class S, class T>
inline bool RBTree<S, T>::LRr_coloring(RBTreeNode<S, T>* current)
{
	current->parent->parent->color = red;
	current->parent->parent->leftchild->color = black;
	current->parent->parent->rightchild->color = black;
	return true;
}

template<class S, class T>
inline bool RBTree<S, T>::LRb_rotate(RBTreeNode<S, T>* current)
{
	RBTreeNode<S, T> *parent, *gparent, *uncle;
	parent = current->parent;
	gparent = parent->parent;
	uncle = gparent->rightchild;

	gparent->set_right_child(gparent->key,gparent->data);
	if (uncle != NULL)
	{
		gparent->rightchild->rightchild = uncle;
		uncle->parent = gparent->rightchild;
	}
	gparent->rightchild->leftchild = current->rightchild;
	current->rightchild = NULL;
	if (gparent->rightchild->leftchild != NULL)
	{
		gparent->rightchild->leftchild->parent = gparent->rightchild;
	}

	gparent->key = current->key;
	gparent->data = current->data;

	parent->rightchild = current->leftchild;
	if(current->leftchild != NULL)
		current->leftchild->parent = parent;
	delete current;

	return true;
}


template<class S, class T>
inline bool RBTree<S, T>::RLr_coloring(RBTreeNode<S, T>* current)
{
	current->parent->parent->color = red;
	current->parent->parent->leftchild->color = black;
	current->parent->parent->rightchild->color = black;
	return true;
}

template<class S, class T>
inline bool RBTree<S, T>::RLb_rotate(RBTreeNode<S, T>* current)
{
	RBTreeNode<S, T> *parent, *gparent, *uncle;
	parent = current->parent;
	gparent = parent->parent;
	uncle = gparent->leftchild;

	gparent->set_left_child(gparent->key, gparent->data);
	if (uncle != NULL)
	{
		gparent->leftchild->leftchild = uncle;
		uncle->parent = gparent->leftchild;
	}
	gparent->leftchild->rightchild = current->leftchild;
	current->leftchild = NULL;
	if (gparent->leftchild->rightchild != NULL)
	{
		gparent->leftchild->rightchild->parent = gparent->leftchild;
	}

	gparent->key = current->key;
	gparent->data = current->data;

	parent->leftchild = current->rightchild;
	if(current->rightchild != NULL)
		current->rightchild->parent = parent;
	delete current;

	return true;
}


template<class S, class T>
inline bool RBTree<S, T>::RRr_coloring(RBTreeNode<S, T>* current)
{
	current->parent->parent->color = red;
	current->parent->parent->leftchild->color = black;
	current->parent->parent->rightchild->color = black;
	return true;
}

template<class S, class T>
inline bool RBTree<S, T>::RRb_rotate(RBTreeNode<S, T>* current)
{
	RBTreeNode<S, T> *parent, *gparent, *uncle;
	parent = current->parent;
	gparent = parent->parent;
	uncle = gparent->leftchild;

	gparent->set_left_child(gparent->key, gparent->data);
	if (uncle != NULL)
	{
		gparent->leftchild->leftchild = uncle;
		uncle->parent = gparent->leftchild;
	}
	gparent->leftchild->rightchild = parent->leftchild;
	parent->leftchild = NULL;
	if (gparent->leftchild->rightchild != NULL)
		gparent->leftchild->rightchild->parent = gparent->leftchild;


	gparent->key = parent->key;
	gparent->data = parent->data;


	gparent->rightchild = parent->rightchild;
	if(parent->rightchild != NULL)
		parent->rightchild->parent = gparent;
	delete parent;

	return true;
}

template<class S, class T>
inline bool RBTree<S, T>::rb_delete_process(RBTreeNode<S, T> *parent, RBTreeNode<S, T> *sibling)
{
	RBTreeNode<S, T> *temp;
	if (parent == NULL)
	{
		root->color = black;
		return true;
	}


	if (sibling->color == red)
	{

		if (parent->rightchild == sibling)
		{
			parent->rightchild = sibling->leftchild;
			if (sibling->leftchild != NULL)
				sibling->leftchild->parent = parent;

			sibling->parent = parent->parent;
			parent->parent = sibling;
			sibling->leftchild = parent;
		}
		else
		{
			parent->leftchild = sibling->rightchild;
			if (sibling->rightchild != NULL)
				sibling->rightchild->parent = parent;

			sibling->parent = parent->parent;
			parent->parent = sibling;
			sibling->rightchild = parent;
		}
	}
	else // black
	{
		if (parent->rightchild == sibling)
		{
			if (sibling->rightchild != NULL)
				if (sibling->rightchild->color == red)
				{
					// right right
					sibling->rightchild->color = black;
					if (parent->leftchild != NULL)
						parent->leftchild->color = black;


					parent->set_left_child(parent->key, parent->data);
					parent->leftchild->rightchild = sibling->leftchild;
					if (sibling->leftchild != NULL)
						sibling->leftchild->parent = parent->leftchild;

					parent->key = sibling->key;
					parent->data = sibling->data;

					parent->rightchild = sibling->rightchild;
					if (sibling->rightchild != NULL)
						sibling->rightchild->parent = parent;
					delete sibling;
					return true;

				}
			if (sibling->leftchild != NULL)
				if (sibling->leftchild->color == red)
				{

					// right left
					sibling->rightchild->color = black;
					if (parent->leftchild != NULL)
						parent->leftchild->color = black;

					parent->set_left_child(parent->key, parent->data);
					parent->leftchild->rightchild = sibling->leftchild->leftchild;
					if (sibling->leftchild->leftchild != NULL)
					{
						sibling->leftchild->leftchild = parent->leftchild;
						sibling->leftchild->leftchild = NULL;
					}

					parent->key = sibling->leftchild->key;
					parent->data = sibling->leftchild->data;

					temp = sibling->leftchild;
					sibling->leftchild = sibling->leftchild->rightchild;
					sibling->leftchild->rightchild->parent = sibling;
					delete temp;
					return true;
				}
			if (parent->color == red)
			{
				parent->color = black;
				sibling->color = red;
			}
			else
			{
				parent->color = double_black;
				sibling->color = red;

				sibling = (parent->parent->leftchild == parent) ? parent->parent->rightchild : parent->parent->rightchild;
				parent = parent->parent;
			}

		}
		else
		{
			if (sibling->leftchild != NULL)
				if (sibling->leftchild->color == red)
				{
					// left right
					sibling->leftchild->color = black;
					if (parent->rightchild != NULL)
						parent->rightchild->color = black;

					parent->set_right_child(parent->key, parent->data);
					parent->rightchild->leftchild = sibling->rightchild->rightchild;
					if (sibling->rightchild->rightchild != NULL)
					{
						sibling->rightchild->rightchild = parent->rightchild;
						sibling->rightchild->rightchild = NULL;
					}

					parent->key = sibling->rightchild->key;
					parent->data = sibling->rightchild->data;

					temp = sibling->rightchild;
					sibling->rightchild = sibling->rightchild->leftchild;
					sibling->rightchild->leftchild->parent = sibling;
					delete temp;
					return true;
				}
			if (sibling->leftchild != NULL)
				if (sibling->leftchild->color == red)
				{
					// left left
					sibling->leftchild->color = black;
					if (parent->rightchild != NULL)
						parent->rightchild->color = black;


					parent->set_right_child(parent->key, parent->data);
					parent->rightchild->leftchild = sibling->rightchild;
					if (sibling->rightchild != NULL)
						sibling->rightchild->parent = parent->rightchild;

					parent->key = sibling->key;
					parent->data = sibling->data;

					parent->leftchild = sibling->leftchild;
					if (sibling->leftchild != NULL)
						sibling->leftchild->parent = parent;
					delete sibling;
					return true;


				}
			if (parent->color == red)
			{
				parent->color = black;
				sibling->color = red;
			}
			else
			{
				parent->color = double_black;
				sibling->color = red;

				sibling = (parent->parent->leftchild == parent) ? parent->parent->rightchild : parent->parent->rightchild;
				parent = parent->parent;
			}
		}
	}

}
