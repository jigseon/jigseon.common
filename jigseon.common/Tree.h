#pragma once
#include <iostream>
#include <string>
#include "ExceptionClass.h"
#include "llist.h"

template <class S, class T> class Tree;

template <class S, class T>
class TreeNode
{
protected:
	S _key;
	T _data;
	TreeNode* _leftchild, * _rightchild, * _parent;
public:
	TreeNode() { key = S(); data = T(); leftchild = rightchild = parent = NULL; }
	TreeNode(S k, T d) { key = k; data = d; leftchild = rightchild = parent = NULL; }
	TreeNode(const TreeNode& t) { this->key = t.key; this->data = t.data; this->leftchild = t.leftchild; this->rightchild = t.rightchild; this->parent = t.parent; }

	TreeNode* get_left_child() { return leftchild; }
	TreeNode* get_right_child() { return rightchild; }
	void delete_left_child() { delete leftchild; leftchild = NULL; }
	void delete_right_child() { delete rightchild; rightchild = NULL; }
	TreeNode* get_parent() { return parent; }
	bool set_left_child(S k, T d);
	bool set_right_child(S k, T d);
	S get_key() { return key; }
	T get_data() { return data; }
	void set_key(S k) { key = k; }
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
	Tree() { root = NULL; current = NULL; }
	Tree(S k, T d) { root = new TreeNode(k, d); current = root; }
	//Tree(const Tree &);
	~Tree();

	bool set_root(S k, T d) { root = new TreeNode<S, T>(k, d); current = root; return (root != NULL) ? true : false; }
	void set_current_as_root() { current = root; }
	TreeNode <S, T>* get_root() { return this->root; }
	TreeNode <S, T>* get_current_node() { return this->current; }
	void move_to_left() { current = current->get_left_child(); }
	void move_to_right() { current = current->get_right_child(); }
	void move_to_parent() { current = current->parent; }

	void remove_left_child();
	void remove_right_child();

	LinkedList<TreeNode<S, T>*> preorder_traverse();
	LinkedList<TreeNode<S, T>*> inorder_traverse();
	LinkedList<TreeNode<S, T>*> postorder_traverse();

	bool insert_node(S, T);
	void delete_node(S);


	friend void active_destructor(TreeNode<S, T>*);
	friend bool active_preorder(TreeNode<S, T>*, LinkedList<TreeNode<S, T>*>&);
	friend bool active_inorder(TreeNode<S, T>*, LinkedList<TreeNode<S, T>*>&);
	friend bool active_postorder(TreeNode<S, T>*, LinkedList<TreeNode<S, T>*>&);
};

template <class S, class T>
bool TreeNode<S, T>::set_left_child(S k, T d)
{
	leftchild = new TreeNode(k, d);
	leftchild->parent = this;
	return leftchild != NULL ? true : false;
}

template <class S, class T>
bool TreeNode<S, T>::set_right_child(S k, T d)
{
	rightchild = new TreeNode(k, d);
	rightchild->parent = this;
	return rightchild != NULL ? true : false;
}


template <class S, class T>
Tree<S, T>::~Tree()
{
	active_destructor(root);
	delete(this->root);
	this->root = NULL;
}

template <class S, class T>
void Tree<S, T>::remove_left_child()
{
	delete current->rightchild;
	current->rightchild = NULL;
}

template <class S, class T>
void Tree<S, T>::remove_right_child()
{
	delete current->leftchild;
	current->leftchild = NULL;
}

template <class S, class T>
LinkedList< TreeNode<S, T>*> Tree<S, T>::preorder_traverse()
{
	LinkedList<TreeNode<S, T>*> res;
	active_preorder(this->root, res);

	return res;
}

template <class S, class T>
bool active_preorder(TreeNode<S, T>* vector, LinkedList<TreeNode<S, T>*>& l)
{
	l.InsertTail(vector);
	if (vector->get_left_child() != NULL)
		active_preorder(vector->get_left_child(), l);
	if (vector->get_right_child() != NULL)
		active_preorder(vector->get_right_child(), l);

	return true;
}

template <class S, class T>
LinkedList<TreeNode<S, T>*> Tree<S, T>::inorder_traverse()
{
	LinkedList<TreeNode<S, T>> res;
	active_inorder(this->root, res);

	return res;
}

template <class S, class T>
bool active_inorder(TreeNode<S, T>* vector, LinkedList<TreeNode<S, T>*>& l)
{
	if (vector->get_left_child() != NULL)
		active_inorder(vector->get_left_child(), l);
	l.InsertTail(vector);
	if (vector->get_right_child() != NULL)
		active_inorder(vector->get_right_child(), l);

	return true;
}

template <class S, class T>
LinkedList<TreeNode<S, T>*> Tree<S, T>::postorder_traverse()
{
	LinkedList<TreeNode<S, T>*> res;
	active_postorder(this->root, res);

	return res;
}

template <class S, class T>
bool active_postorder(TreeNode<S, T>* vector, LinkedList<TreeNode<S, T>*>& l)
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