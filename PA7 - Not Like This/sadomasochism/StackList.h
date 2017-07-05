// Edgar Perez
// PA 7 - Attendance Tracker

#pragma once
#ifndef _StackList_H
#define _StackList_H
#include "StackNode.h"

template <typename Leaf, class Branch>
class ListST
{
public:
	ListST();
	// Destroy list
	~ListST() { ; }
	NodeST<Leaf, Branch>* getHeadPtr();
	void setHeadPtr(NodeST<Leaf, Branch>* const & newHead);
	void push(Leaf& data, Branch& reference);
	void pop(Leaf& data, Branch& reference);
	void peak(Leaf& data, Branch& reference);
	void popBack(Leaf& data, Branch& reference);
	bool isEmpty() { return headPtr == nullptr ? true : false; }

private:
	NodeST<Leaf, Branch>* findEnd(NodeST<Leaf, Branch>* curPtr);
	NodeST<Leaf, Branch>* headPtr;
};

template <typename Leaf, class Branch>
ListST<Leaf, Branch>::ListST()
{
	headPtr = nullptr;
}

template <typename Leaf, class Branch>
NodeST<Leaf, Branch>* ListST<Leaf, Branch>::getHeadPtr()
{
	return headPtr;
}

template <typename Leaf, class Branch>
void ListST<Leaf, Branch>::setHeadPtr(NodeST<Leaf, Branch>* const & newHead)
{
	headPtr = newHead;
}

template <typename Leaf, class Branch>
void ListST<Leaf, Branch>::push(Leaf& data, Branch& reference)
{
	NodeST<Leaf, Branch>* store = makeNode(data, reference);
	if (!isEmpty()) {
		store->setNextPtr(headPtr);
		headPtr = store;
	}
	else
		setHeadPtr(store);
}

template <typename Leaf, class Branch>
void ListST<Leaf, Branch>::pop(Leaf& data, Branch& reference)
{
	if (!isEmpty()) {
		NodeST<Leaf, Branch>* store = headPtr;
		headPtr = headPtr->getNextPtr();
		data = store->getData();
		reference = store->getReference();
		delete store;
		store = nullptr;
	}
}

template <typename Leaf, class Branch>
void ListST<Leaf, Branch>::peak(Leaf& data, Branch& reference)
{
	data = headPtr->getData();
	reference = headPtr->getReference();
}

template <typename Leaf, class Branch>
void ListST<Leaf, Branch>::popBack(Leaf& data, Branch& reference)
{
	if (headPtr->getNextPtr()) 
	{
		NodeST<Leaf, Branch>* prior = findEnd(headPtr);
		NodeST<Leaf, Branch>* store = prior->getNextPtr();
		data = store->getData();
		reference = store->getReference();
		NodeST<Leaf, Branch>* temp = nullptr;
		prior->setNextPtr(temp);
		delete store;
		store = nullptr;
	}
	else
	{
		NodeST<Leaf, Branch>* store = findEnd(headPtr);
		headPtr = headPtr->getNextPtr();
		data = store->getData();
		reference = store->getReference();
		delete store;
		store = nullptr;
	}
}

template <typename Leaf, class Branch>
NodeST<Leaf, Branch>* ListST<Leaf, Branch>::findEnd(NodeST<Leaf, Branch>* curPtr)
{
	if (curPtr->getNextPtr()) {
		if (curPtr->getNextPtr()->getNextPtr() == nullptr)
			return curPtr;
		else
			return findEnd(curPtr->getNextPtr());
	}
	else
		return curPtr;
}


#endif