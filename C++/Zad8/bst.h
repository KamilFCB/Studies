#pragma once

#include <iostream>

template <class T>
class bst
{
private:
	class node
	{
	public:
		node(T v);
		~node();
		T val;
		node *left;
		node *right;
	};
	node *root;
public:
	bst();
	bst(T v);
	bst(std::initializer_list<T> k);
	bst(const bst<T> &w);
	bst(bst<T> &&w);
	bst& operator = (const bst<T> &w);
	bst& operator = (bst<T> &&w);
	~bst();
	bool isEmpty();
	void insert(T v);
	void remove(T v);
	bool search(T v);
	void print();
	void print_root(node *r);
	template<class T> friend std::ostream& operator<< (std::ostream &wyj, bst<T> &w);
	

};

//template <class T>


