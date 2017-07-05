// Name: Edgar Perez
// Collaborators: Shusanta Bhatter, Nick Vasicek
// Binary Tree List Template

#ifndef _ListBT_H
#define _ListBT_H

#include "NodeBT.h"
#include <iostream>

using namespace std;

template <typename Leaf, typename Branch>
class ListBT
{
public:
	ListBT(Leaf, Branch);
	// List Deconstructor
	~ListBT() { freeTree(); }

	void insertNode(Leaf newData, Branch newReference);
	void printTree();
	NodeBT<Leaf, Branch>* search(Leaf data);
	void freeTree();

private:
	NodeBT<Leaf, Branch>* treeRoot;
	void setRoot(Leaf data, Branch reference);
	NodeBT<Leaf, Branch>* getRoot() const;
	bool isEmpty();

	//Add utility functions.
	void insertNodeUltility(NodeBT<Leaf, Branch>*& copy, Leaf newData, Branch newReference);
	void printTreeUtility(NodeBT<Leaf, Branch>* copy);
	NodeBT<Leaf, Branch>* searchUtility(NodeBT<Leaf, Branch>* copy, Leaf data);
	void freeTreeUtility(NodeBT<Leaf, Branch>*& node);
};

// Constructor given first data and reference.
template <typename Leaf, class Branch>
ListBT<Leaf, Branch>::ListBT(Leaf data, Branch reference)
{
	setRoot(data, reference);
}

// Mutator and Accessor for treeRoot

template <typename Leaf, class Branch>
void ListBT<Leaf, Branch>::setRoot(Leaf data, Branch reference)
{
	treeRoot = makeNode(data, reference);
}

template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>* ListBT<Leaf, Branch>::getRoot() const
{
	return treeRoot;
}

// Inserts a new node into the tree via insertNodeUtility()
template <typename Leaf, class Branch>
void ListBT<Leaf, Branch>::insertNode(Leaf newData, Branch newReference)
{
	insertNodeUltility(treeRoot, newData, newReference);
}

template <typename Leaf, class Branch>
void ListBT<Leaf, Branch>::insertNodeUltility(NodeBT<Leaf, Branch>*& copy, Leaf newData, Branch newReference)
{
	if (copy == nullptr)
		copy = makeNode(newData, newReference);
	else if (newData > copy->getData()) {
		insertNodeUltility(copy->getRightPtr(), newData, newReference);
	}
	else if (newData < copy->getData()) {
		insertNodeUltility(copy->getLeftPtr(), newData, newReference);
	}
	else
		cout << newData << " has already been processed!" << endl;
}

// Prints the tree via printTreeUtility()
template <typename Leaf, class Branch>
void ListBT<Leaf, Branch>::printTree()
{
	NodeBT<Leaf, Branch>* copy = getRoot();
	printTreeUtility(copy);
}

template <typename Leaf, class Branch>
void ListBT<Leaf, Branch>::printTreeUtility(NodeBT<Leaf, Branch>* copy)
{
	if (copy != nullptr)
	{
		printTreeUtility(copy->getLeftPtr());
		cout << "Data: " << copy->getData() << endl << "Reference: " << copy->getReference() << endl;
		printTreeUtility(copy->getRightPtr());
	}
}

// Searches for a particular key via searchUtility()
template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>* ListBT<Leaf, Branch>::search(Leaf data)
{
	NodeBT<Leaf, Branch>* copy = getRoot();
	return searchUtility(copy, data);
}

template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>* ListBT<Leaf, Branch>::searchUtility(NodeBT<Leaf, Branch>* copy, Leaf data)
{
	if (copy != nullptr)
	{
		if (copy->getData() == data)
			return copy;
		if (data > copy->getData())
			return searchUtility(copy->getRightPtr(), data);
		if (data < copy->getData())
			return searchUtility(copy->getLeftPtr(), data);
	}
	else
		return nullptr;
}

// Frees the nodes in the tree via freeTreeUtility()
template <typename Leaf, class Branch>
void ListBT<Leaf, Branch>::freeTree()
{
	freeTreeUtility(treeRoot);
}

template <typename Leaf, class Branch>
void ListBT<Leaf, Branch>::freeTreeUtility(NodeBT<Leaf, Branch>*& node)
{
	if (node != nullptr)
	{
		freeTreeUtility(node->getLeftPtr());
		freeTreeUtility(node->getRightPtr());
		delete node;
	}
}

// Returns true if the tree is empty
template <typename Leaf, class Branch>
bool ListBT<Leaf, Branch>::isEmpty()
{
	return (getRoot() == nullptr) ? true : false;
}

#endif