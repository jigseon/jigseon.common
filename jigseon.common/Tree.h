#pragma once
#include <iostream>
#include <string>
#include "ExceptionClass.h"
#include "llist.h"

namespace jigseon
{
	template <class S, class T> class Tree;

	template <class S, class T>
	class TreeNode
	{
	protected:
		S _key;
		T _data;
		TreeNode* _leftchild, * _rightchild, * _parent;
	public:
		TreeNode() { _key = S(); _data = T(); _leftchild = _rightchild = _parent = NULL; }
		TreeNode(S k, T d) { _key = k; _data = d; _leftchild = _rightchild = _parent = NULL; }
		TreeNode(const TreeNode& t) { this->_key = t._key; this->_data = t._data; this->_leftchild = t._leftchild; this->_rightchild = t._rightchild; this->_parent = t._parent; }

		TreeNode* get_left_child() { return _leftchild; }
		TreeNode* get_right_child() { return _rightchild; }
		void delete_left_child() { delete _leftchild; _leftchild = NULL; }
		void delete_right_child() { delete _rightchild; _rightchild = NULL; }
		TreeNode* get_parent() { return _parent; }
		bool set_left_child(S k, T d);
		bool set_right_child(S k, T d);
		S get_key() { return _key; }
		T get_data() { return _data; }
		void set_key(S k) { _key = k; }
		void set_data(T d) { data = d; }


		friend class Tree<S, T>;
	};

	template <class S, class T>
	class Tree
	{
	protected:
		TreeNode<S, T>* _root;
		TreeNode<S, T>* _current;
	public:
		Tree() { _root = NULL; _current = NULL; }
		Tree(S k, T d) { _root = new TreeNode(k, d); _current = _root; }
		//Tree(const Tree &);
		~Tree();

		bool set_root(S k, T d) { _root = new TreeNode<S, T>(k, d); _current = _root; return (_root != NULL) ? true : false; }
		void set_current_as_root() { _current = _root; }
		TreeNode <S, T>* get_root() { return this->_root; }
		TreeNode <S, T>* get_current_node() { return this->_current; }
		void move_to_left() { _current = _current->get_left_child(); }
		void move_to_right() { _current = _current->get_right_child(); }
		void move_to_parent() { _current = _current->_parent; }

		void remove_left_child();
		void remove_right_child();

		llist<TreeNode<S, T>*> preorder_traverse();
		llist<TreeNode<S, T>*> inorder_traverse();
		llist<TreeNode<S, T>*> postorder_traverse();

		bool insert_node(S, T);
		void delete_node(S);


		friend void active_destructor(TreeNode<S, T>*);
		friend bool active_preorder(TreeNode<S, T>*, llist<TreeNode<S, T>*>&);
		friend bool active_inorder(TreeNode<S, T>*, llist<TreeNode<S, T>*>&);
		friend bool active_postorder(TreeNode<S, T>*, llist<TreeNode<S, T>*>&);
	};

	template <class S, class T>
	bool TreeNode<S, T>::set_left_child(S k, T d)
	{
		_leftchild = new TreeNode(k, d);
		_leftchild->_parent = this;
		return _leftchild != NULL ? true : false;
	}

	template <class S, class T>
	bool TreeNode<S, T>::set_right_child(S k, T d)
	{
		_rightchild = new TreeNode(k, d);
		_rightchild->_parent = this;
		return _rightchild != NULL ? true : false;
	}


	template <class S, class T>
	Tree<S, T>::~Tree()
	{
		active_destructor(_root);
		delete(this->_root);
		this->_root = NULL;
	}

	template <class S, class T>
	void Tree<S, T>::remove_left_child()
	{
		delete _current->_rightchild;
		_current->_rightchild = NULL;
	}

	template <class S, class T>
	void Tree<S, T>::remove_right_child()
	{
		delete _current->_leftchild;
		_current->_leftchild = NULL;
	}

	template <class S, class T>
	llist< TreeNode<S, T>*> Tree<S, T>::preorder_traverse()
	{
		llist<TreeNode<S, T>*> res;
		active_preorder(this->root, res);

		return res;
	}

	template <class S, class T>
	bool active_preorder(TreeNode<S, T>* vector, llist<TreeNode<S, T>*>& l)
	{
		l.InsertTail(vector);
		if (vector->get_left_child() != NULL)
			active_preorder(vector->get_left_child(), l);
		if (vector->get_right_child() != NULL)
			active_preorder(vector->get_right_child(), l);

		return true;
	}

	template <class S, class T>
	llist<TreeNode<S, T>*> Tree<S, T>::inorder_traverse()
	{
		llist<TreeNode<S, T> *> res;
		active_inorder(this->_root, res);

		return res;
	}

	template <class S, class T>
	bool active_inorder(TreeNode<S, T>* vector, llist<TreeNode<S, T>*>& l)
	{
		if (vector->get_left_child() != NULL)
			active_inorder(vector->get_left_child(), l);
		l.InsertTail(vector);
		if (vector->get_right_child() != NULL)
			active_inorder(vector->get_right_child(), l);

		return true;
	}

	template <class S, class T>
	llist<TreeNode<S, T>*> Tree<S, T>::postorder_traverse()
	{
		llist<TreeNode<S, T>*> res;
		active_postorder(this->_root, res);

		return res;
	}

	template <class S, class T>
	bool active_postorder(TreeNode<S, T>* vector, llist<TreeNode<S, T>*>& l)
	{
		if (vector->get_left_child() != NULL)
			active_postorder(vector->get_left_child(), l);
		if (vector->get_right_child() != NULL)
			active_postorder(vector->get_right_child(), l);
		l.InsertTail(vector);

		return true;
	}


	template <class S, class T>
	void active_destructor(TreeNode<S, T>* vector)
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
	bool Tree<S, T>::insert_node(S key, T data)
	{

		return this->set_root(key, data);
	}


	template <class S, class T>
	void Tree<S, T>::delete_node(S key)
	{

	}

}