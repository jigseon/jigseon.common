#pragma once
#include <iostream>
#include <iterator>
#include "llist.h"
#include "ExceptionClass.h"
#include <queue>

enum node_color {red, black, double_black};

template <class S, class T> class RBTree;
namespace jigseon
{
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
		RBTreeNode() { _depth = 0; _key = S(); _data = T(); _color = red; _leftchild = _rightchild = _parent = NULL; }
		RBTreeNode(S k, T d) { _depth = 1; _key = k; _data = d; _color = red; _leftchild = _rightchild = _parent = NULL; }
		RBTreeNode(const RBTreeNode& t) { _depth = t._depth; this->_key = t._key; this->_data = t._data; this->_color = red; this->_leftchild = t._leftchild; this->_rightchild = t._rightchild; this->_parent = t._parent; }

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
		RBTreeNode<S, T> *_root;
		RBTreeNode<S, T> *_current;

		bool rb_insert_process(RBTreeNode <S, T> *);
		bool rb_delete_process( RBTreeNode <S, T> *, RBTreeNode <S, T> *);
	public:
		RBTree() { _root = NULL; _current = NULL; }
		RBTree(S k, T d) { _root = new RBTreeNode(k, d); _current = _root; }
		//RBTree(const RBTree &);
		~RBTree();

		RBTreeNode<S,T> * set_root(S k, T d) { _root = new RBTreeNode<S, T>(k, d); _root->_color = black; _current = _root; return _root; }
		void set_current_as_root() { _current = _root; }
		RBTreeNode <S, T> *get_root() { return this->_root; }
		RBTreeNode <S, T> *get_current_node() { return this->_current; }
		RBTreeNode <S, T> *find(S);
		void move_to_left() { _current = _current->get_left_child(); }
		void move_to_right() { _current = _current->get_right_child(); }
		void move_to_parent() { _current = _current->_parent; }

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
		_leftchild = new RBTreeNode(k, d);
		_leftchild->_parent = this;
		return _leftchild;
	}

	template <class S, class T>
	RBTreeNode<S, T>* RBTreeNode<S, T>::set_right_child(S k, T d)
	{
		_rightchild = new RBTreeNode(k, d);
		_rightchild->_parent = this;
		return _rightchild;
	}


	template <class S, class T>
	RBTree<S, T>::~RBTree()
	{
		active_destructor(_root);
		delete(this->_root);
		this->_root = NULL;
	}

	template<class S, class T>
	inline RBTreeNode<S, T>* RBTree<S, T>::find(S key)
	{
		RBTreeNode<S, T>* vector = this->get_root();

		while (vector)
		{
			if (vector->_key == key)
				break;
			else if (vector->_key > key)
			{
				vector = vector->_leftchild;
			}
			else
			{
				vector = vector->_rightchild;
			}
		}
		return vector;
	}

	template <class S, class T>
	void RBTree<S, T>::remove_left_child()
	{
		delete _current->_rightchild;
		_current->_rightchild = NULL;
	}

	template <class S, class T>
	void RBTree<S, T>::remove_right_child()
	{
		delete _current->_leftchild;
		_current->_leftchild = NULL;
	}

	template <class S,class T>
	llist< RBTreeNode<S,T> *> RBTree<S, T>::preorder_traverse()
	{
		llist<RBTreeNode<S, T>*> res;
		active_preorder_traverse(this->_root, res);

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
		active_inorder_traverse(this->_root, res);

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
		active_postorder_traverse(this->_root, res);

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
		RBTreeNode<S, T> *vector = target;
		int old_color;


		if (vector->get_left_child() != NULL)
		{
			vector = vector->get_left_child();
			while (vector->get_right_child())
				vector = vector->get_right_child();
			target->_key = vector->_key;
			target->_data = vector->_data;
			return active_delete_node(vector, vparent, sibling);

		}
		else if (vector->get_right_child() != NULL)
		{
			vector = vector->get_right_child();
			while (vector->get_left_child())
				vector = vector->get_left_child();
			target->_key = vector->_key;
			target->_data = vector->_data;
			return active_delete_node(vector, vparent, sibling);
		}
		else
		{
			old_color = vector->_color;
			*vparent = vector->_parent;
			if (vector->get_parent()->get_left_child() == vector)
			{
				vector->_parent->_leftchild = NULL;
				*sibling = vector->_parent->_rightchild;
			}
			else
			{
				vector->_parent->_rightchild = NULL;
				*sibling = vector->_parent->_leftchild;
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
		RBTreeNode<S, T> *vector = _root;

		while (vector != NULL)
		{
			if (vector->get_key() > key)
			{
				if (vector->_leftchild == NULL)
					return rb_insert_process(vector->set_left_child(key, data));
				vector = vector->_leftchild;
			}
			else
			{
				if (vector->_rightchild == NULL)
					return rb_insert_process(vector->set_right_child(key, data));
				vector = vector->_rightchild;
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
		current_depth = vector->_depth = 1;
		q.push(vector);

		while (1)
		{
			if (q.empty() || vector == NULL)
				break;

			vector = q.front();
			q.pop();

			if (current_depth != vector->_depth)
			{
				current_depth = vector->_depth;
				std::cout << endl;
			}
			std::cout << vector->_key << "("<< vector->_color<<")" << " : " << vector->_data << "  ";

			if (vector->_leftchild != NULL)
			{
				vector->_leftchild->_depth = vector->_depth + 1;
				q.push(vector->_leftchild);
			}
			if (vector->_rightchild != NULL)
			{
				vector->_rightchild->_depth = vector->_depth + 1;
				q.push(vector->_rightchild);
			}
		}
	}


	template <class S, class T>
	bool RBTree<S, T>::rb_insert_process(RBTreeNode <S, T> *current)
	{
		RBTreeNode <S, T> *parent,*gparent,*uncle;
	
		if (current == _root)
			current->_color = black;
		if (current->_parent == _root)
			return true;
		if (current->_parent->_color == black)
			return true;

		while(current!= _root)
		{
			if (current->_parent == _root)
				return true;
			parent = current->_parent;
			gparent = parent->_parent;
			if (gparent->_leftchild == parent)
			{
				uncle = gparent->_rightchild;
				if (parent->_leftchild == current)
				{
					if (uncle == NULL)
					{
						LLb_rotate(current);
						return true;
					}
					else if (uncle->_color == red)
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
					else if (uncle->_color == red)
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
				uncle = gparent->_leftchild;
				if (parent->_leftchild == current)
				{
					if (uncle == NULL)
					{
						RLb_rotate(current);
						return true;
					}
					else if (uncle->_color == red)
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
					else if (uncle->_color == red)
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
		current->_color = black;
		return true;
	}

	template <class S, class T>
	void RBTree<S, T>::delete_node(RBTreeNode<S, T> *target)
	{
		RBTreeNode<S, T> *parent = target->_parent, *sibling;

		if (active_delete_node(target, &parent, &sibling) == black)
			rb_delete_process(parent, sibling);
		_root->_color = black;
	}

	template<class S, class T>
	inline bool RBTree<S, T>::LLr_coloring(RBTreeNode<S, T>* current)
	{
		current->_parent->_parent->_color = red;
		current->_parent->_parent->_leftchild->_color = black;
		current->_parent->_parent->_rightchild->_color = black;

		return true;
	}

	template<class S, class T>
	inline bool RBTree<S, T>::LLb_rotate(RBTreeNode<S, T>* current)
	{
		RBTreeNode<S, T> *parent, *gparent, *uncle;
		parent = current->_parent;
		gparent = parent->_parent;
		uncle = gparent->_rightchild;

		gparent->set_right_child(gparent->_key, gparent->_data);
		if (uncle != NULL)
		{
			gparent->_rightchild->_rightchild = uncle;
			uncle->_parent = gparent->_rightchild;
		}
		gparent->_rightchild->_leftchild = parent->_rightchild;
		parent->_rightchild = NULL;
		if (gparent->_rightchild->_leftchild != NULL)
			gparent->_rightchild->_leftchild->_parent = gparent->_rightchild;


		gparent->_key = parent->_key;
		gparent->_data = parent->_data;

		gparent->_leftchild = parent->_leftchild;
		if(parent->_leftchild != NULL)
			parent->_leftchild->_parent = gparent;
		delete parent;

		return true;
	}

	template<class S, class T>
	inline bool RBTree<S, T>::LRr_coloring(RBTreeNode<S, T>* current)
	{
		current->_parent->_parent->_color = red;
		current->_parent->_parent->_leftchild->_color = black;
		current->_parent->_parent->_rightchild->_color = black;
		return true;
	}

	template<class S, class T>
	inline bool RBTree<S, T>::LRb_rotate(RBTreeNode<S, T>* current)
	{
		RBTreeNode<S, T> *parent, *gparent, *uncle;
		parent = current->_parent;
		gparent = parent->_parent;
		uncle = gparent->_rightchild;

		gparent->set_right_child(gparent->_key,gparent->_data);
		if (uncle != NULL)
		{
			gparent->_rightchild->_rightchild = uncle;
			uncle->_parent = gparent->_rightchild;
		}
		gparent->_rightchild->_leftchild = current->_rightchild;
		current->_rightchild = NULL;
		if (gparent->_rightchild->_leftchild != NULL)
		{
			gparent->_rightchild->_leftchild->_parent = gparent->_rightchild;
		}

		gparent->_key = current->_key;
		gparent->_data = current->_data;

		parent->_rightchild = current->_leftchild;
		if(current->_leftchild != NULL)
			current->_leftchild->_parent = parent;
		delete current;

		return true;
	}


	template<class S, class T>
	inline bool RBTree<S, T>::RLr_coloring(RBTreeNode<S, T>* current)
	{
		current->_parent->_parent->_color = red;
		current->_parent->_parent->_leftchild->_color = black;
		current->_parent->_parent->_rightchild->_color = black;
		return true;
	}

	template<class S, class T>
	inline bool RBTree<S, T>::RLb_rotate(RBTreeNode<S, T>* current)
	{
		RBTreeNode<S, T> *parent, *gparent, *uncle;
		parent = current->_parent;
		gparent = parent->_parent;
		uncle = gparent->_leftchild;

		gparent->set_left_child(gparent->_key, gparent->_data);
		if (uncle != NULL)
		{
			gparent->_leftchild->_leftchild = uncle;
			uncle->_parent = gparent->_leftchild;
		}
		gparent->_leftchild->_rightchild = current->_leftchild;
		current->_leftchild = NULL;
		if (gparent->_leftchild->_rightchild != NULL)
		{
			gparent->_leftchild->_rightchild->_parent = gparent->_leftchild;
		}

		gparent->_key = current->_key;
		gparent->_data = current->_data;

		parent->_leftchild = current->_rightchild;
		if(current->_rightchild != NULL)
			current->_rightchild->_parent = parent;
		delete current;

		return true;
	}


	template<class S, class T>
	inline bool RBTree<S, T>::RRr_coloring(RBTreeNode<S, T>* current)
	{
		current->_parent->_parent->_color = red;
		current->_parent->_parent->_leftchild->_color = black;
		current->_parent->_parent->_rightchild->_color = black;
		return true;
	}

	template<class S, class T>
	inline bool RBTree<S, T>::RRb_rotate(RBTreeNode<S, T>* current)
	{
		RBTreeNode<S, T> *parent, *gparent, *uncle;
		parent = current->_parent;
		gparent = parent->_parent;
		uncle = gparent->_leftchild;

		gparent->set_left_child(gparent->_key, gparent->_data);
		if (uncle != NULL)
		{
			gparent->_leftchild->_leftchild = uncle;
			uncle->_parent = gparent->_leftchild;
		}
		gparent->_leftchild->_rightchild = parent->_leftchild;
		parent->_leftchild = NULL;
		if (gparent->_leftchild->_rightchild != NULL)
			gparent->_leftchild->_rightchild->_parent = gparent->_leftchild;


		gparent->_key = parent->_key;
		gparent->_data = parent->_data;


		gparent->_rightchild = parent->_rightchild;
		if(parent->_rightchild != NULL)
			parent->_rightchild->_parent = gparent;
		delete parent;

		return true;
	}

	template<class S, class T>
	inline bool RBTree<S, T>::rb_delete_process(RBTreeNode<S, T> *parent, RBTreeNode<S, T> *sibling)
	{
		RBTreeNode<S, T> *temp;
		if (parent == NULL)
		{
			_root->_color = black;
			return true;
		}


		if (sibling->_color == red)
		{

			if (parent->_rightchild == sibling)
			{
				parent->_rightchild = sibling->_leftchild;
				if (sibling->_leftchild != NULL)
					sibling->_leftchild->_parent = parent;

				sibling->_parent = parent->_parent;
				parent->_parent = sibling;
				sibling->_leftchild = parent;
			}
			else
			{
				parent->_leftchild = sibling->_rightchild;
				if (sibling->_rightchild != NULL)
					sibling->_rightchild->_parent = parent;

				sibling->_parent = parent->_parent;
				parent->_parent = sibling;
				sibling->_rightchild = parent;
			}
		}
		else // black
		{
			if (parent->_rightchild == sibling)
			{
				if (sibling->_rightchild != NULL)
					if (sibling->_rightchild->_color == red)
					{
						// right right
						sibling->_rightchild->_color = black;
						if (parent->_leftchild != NULL)
							parent->_leftchild->_color = black;


						parent->set_left_child(parent->_key, parent->_data);
						parent->_leftchild->_rightchild = sibling->_leftchild;
						if (sibling->_leftchild != NULL)
							sibling->_leftchild->_parent = parent->_leftchild;

						parent->_key = sibling->_key;
						parent->_data = sibling->_data;

						parent->_rightchild = sibling->_rightchild;
						if (sibling->_rightchild != NULL)
							sibling->_rightchild->_parent = parent;
						delete sibling;
						return true;

					}
				if (sibling->_leftchild != NULL)
					if (sibling->_leftchild->_color == red)
					{

						// right left
						sibling->_rightchild->_color = black;
						if (parent->_leftchild != NULL)
							parent->_leftchild->_color = black;

						parent->set_left_child(parent->_key, parent->_data);
						parent->_leftchild->_rightchild = sibling->_leftchild->_leftchild;
						if (sibling->_leftchild->_leftchild != NULL)
						{
							sibling->_leftchild->_leftchild = parent->_leftchild;
							sibling->_leftchild->_leftchild = NULL;
						}

						parent->_key = sibling->_leftchild->_key;
						parent->_data = sibling->_leftchild->_data;

						temp = sibling->_leftchild;
						sibling->_leftchild = sibling->_leftchild->_rightchild;
						sibling->_leftchild->_rightchild->_parent = sibling;
						delete temp;
						return true;
					}
				if (parent->_color == red)
				{
					parent->_color = black;
					sibling->_color = red;
				}
				else
				{
					parent->_color = double_black;
					sibling->_color = red;

					sibling = (parent->_parent->_leftchild == parent) ? parent->_parent->_rightchild : parent->_parent->_rightchild;
					parent = parent->_parent;
				}

			}
			else
			{
				if (sibling->_leftchild != NULL)
					if (sibling->_leftchild->_color == red)
					{
						// left right
						sibling->_leftchild->_color = black;
						if (parent->_rightchild != NULL)
							parent->_rightchild->_color = black;

						parent->set_right_child(parent->_key, parent->_data);
						parent->_rightchild->_leftchild = sibling->_rightchild->_rightchild;
						if (sibling->_rightchild->_rightchild != NULL)
						{
							sibling->_rightchild->_rightchild = parent->_rightchild;
							sibling->_rightchild->_rightchild = NULL;
						}

						parent->_key = sibling->_rightchild->_key;
						parent->_data = sibling->_rightchild->_data;

						temp = sibling->_rightchild;
						sibling->_rightchild = sibling->_rightchild->_leftchild;
						sibling->_rightchild->_leftchild->_parent = sibling;
						delete temp;
						return true;
					}
				if (sibling->_leftchild != NULL)
					if (sibling->_leftchild->_color == red)
					{
						// left left
						sibling->_leftchild->_color = black;
						if (parent->_rightchild != NULL)
							parent->_rightchild->_color = black;


						parent->set_right_child(parent->_key, parent->_data);
						parent->_rightchild->_leftchild = sibling->_rightchild;
						if (sibling->_rightchild != NULL)
							sibling->_rightchild->_parent = parent->_rightchild;

						parent->_key = sibling->_key;
						parent->_data = sibling->_data;

						parent->_leftchild = sibling->_leftchild;
						if (sibling->_leftchild != NULL)
							sibling->_leftchild->_parent = parent;
						delete sibling;
						return true;


					}
				if (parent->_color == red)
				{
					parent->_color = black;
					sibling->_color = red;
				}
				else
				{
					parent->_color = double_black;
					sibling->_color = red;

					sibling = (parent->_parent->_leftchild == parent) ? parent->_parent->_rightchild : parent->_parent->_rightchild;
					parent = parent->_parent;
				}
			}
		}
		return true;
	}

}