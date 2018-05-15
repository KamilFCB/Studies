#include "stdafx.h"
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

template <class T>
bst<T>::bst()
{
	root = nullptr;
}

template <class T>
bst<T>::bst(T v)
{
	root = new node(v);
}

template <class T>
bst<T>::~bst()
{
	delete root;
}

template <class T>
bst<T>::node::node(T v)
{
	val = v;
	left = nullptr;
	right = nullptr;
}

template <class T>
bst<T>::bst(std::initializer_list<T> k)
{
	auto i = k.begin();
	i++;
	for (auto i = k.begin(); i != k.end(); i++)
	{
		insert(*i);
	}
	/*int *tab = new int[k.size()];
	int i = 0;
	for (auto it = k.begin(); i < k.size(); i++)
	{
		tab[i] = *it;
		it++;
	}

	root = new node(tab[0]);

	for (int j = 1; j < i; j++)
	{
		insert(tab[j]);
	}*/
}

template <class T>
bst<T>::bst(const bst<T> &b)
{
	
}

template <class T>
bst<T>::bst(bst<T> &&b)
{
	root = b.root;
	b.root = nullptr;
}

//bst& bst::operator=(const bst &b)
//{
//
//}

template <class T>
bst<T>& bst<T>::operator=(bst<T> &&b)
{
	delete root;
	root = b.root;
	b.root = nullptr;

	return *this;
}

template <class T>
bst<T>::node::~node()
{
	delete left;
	delete right;
}

template <class T>
void bst<T>::insert(T v)
{
	node *tmp = new node(v);
	node *prev;
	if (isEmpty())
		root = tmp;
	else
	{
		node *current = root;
		prev = current;
		while (current)
		{
			prev = current;
			if (v > current->val)
				current = current->right;
			else
				current = current->left;
		}

		if (v > prev->val)
			prev->right = tmp;
		else
			prev->left = tmp;
	}
}

template <class T>
void bst<T>::remove(T v)
{
	if (isEmpty())
		return;

	node *current = root;
	node *prev = root;

	if (!search(v))
	{
		return;
	}

	while (current)
	{
		if (current->val == v)
			break;
		else
		{
			prev = current;
			if (v > current->val)
				current = current->right;
			else
				current = current->left;
		}
	}
	// prawy lisc
	if (current->left == nullptr && current->right != nullptr)
	{
		if (prev->left == current)
		{
			prev->left = current->right;
			delete current;
		}
		else
		{
			prev->right = current->right;
			delete current;
		}
	}
	//lewy lisc
	else if (current->left != nullptr && current->right == nullptr)
	{
		if (prev->left == current)
		{
			prev->left = current->left;
			delete current;
		}
		else
		{
			prev->right = current->left;
			delete current;
		}
	}
	// dwa puste liscie
	else if (current->left == nullptr && current->right == nullptr)
	{
		if (prev == nullptr)
			delete current;
		else
		{
			if (prev->left == current)
				prev->left = nullptr;
			else
				prev->right = nullptr;
			delete current;
		}
	}
	//dwa liscie
	else if (current->left != nullptr && current->right != nullptr)
	{
		node *tmp;
		tmp = current->right;
		if (tmp->left == nullptr && tmp->right == nullptr)
		{
			current = tmp;
			delete tmp;
			current->right = nullptr;
		}
		else
		{	//szukamy najmniejszego elementu
			if (current->right->left != nullptr)
			{
				node *tmp1 = current->right;
				node *tmp2 = current->right->left;
				while (tmp2->left != nullptr)
				{
					tmp1 = tmp2;
					tmp2 = tmp2->left;
				}
				current->val = tmp2->val;
				delete tmp2;
				tmp1->left = nullptr;
			}
			else
			{
				node *tmp1 = current->right;
				current->val = tmp1->val;
				current->right = tmp1->right;
				delete tmp1;
			}
		}
	}
}

template <class T>
bool bst<T>::search(T v)
{
	node *current = root;

	

	while (current != nullptr)
	{
		if (current->val == v)
			return true;

		if (v > current->val)
			current = current->right;
		else
			current = current->left;
	}
	return false;
}

template <class T>
bool bst<T>::isEmpty()
{
	return root == nullptr;
}

template <class T>
void bst<T>::print()
{
	print_root(root);
}

template <class T>
void bst<T>::print_root(node *r)
{
	if (r != nullptr)
	{
		if (r->left != nullptr)
			print_root(r->left);

		std::cout << r->val << " ";

		if (r->right != nullptr)
			print_root(r->right);
	}
}

template <class T>
std::ostream& operator<< (std::ostream &wyj, bst<T> &w)
{
	w.print();
	std::cout << std::endl;
	return wyj;
}