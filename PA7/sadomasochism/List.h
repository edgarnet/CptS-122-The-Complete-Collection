// Edgar Perez
// PA 7 - Attendance Tracker

#pragma once
#ifndef _List_H
#define _List_H

#include "Node.h"

// Warning: Contains actual witchcraft.

// Template List class definition.
template <class T>
class List
{
public:
	// Constructor for List object.
	List();
	// Copy Constructor for List object.
	List(const List &copyList);
	// Destructor for List object.
	~List();
	// List copy constructor via overloaded operator.
	List & operator=(const List &rhs);
	// Getter for List object's head pointer.
	Node<T>* getHeadPtr() const;
	// Setter for List object's head pointer.
	void setHeadPtr(T newData);
	// Inserts T object at end of list.
	void insertAtEnd(T newData);
	// Deletes a Node object at front of list.
	T deleteAtFront();
	// Deletes Node object at end of list.
	T deleteAtEnd();

private:
	// Head pointer of type T*.
	Node<T>* mpHead;
	// Recursively gets the last pointer in the list.
	Node<T>* getLastPtr(Node <T> *copy) const;
	// Recursively builds the list.
	void builder(Node<T>* copy);
	// Calls lilDestroy.
	void destroyer();
	// Recursively deallocates the list.
	void lilDestroy(Node<T>* gone);
	// Determines if the list is empty.
	bool isEmpty();
};

//Non-member class specific functions.
//void printList(List<Wrapper> & job);

// Constructor for List object.
template <class T>
List<T>::List()
{
	mpHead = nullptr;
}

// Copy Constructor for List object.
template <class T>
List<T>::List(const List& copyList)
{
	setHeadPtr(makeNode<T>(copyList.getHeadPtr()->getData()));
	builder(copyList->getHeadPtr()->getNextPtr());
}

// Destructor for List object.
template<class T>
List<T>::~List()
{
	cout << "All is lost." << endl;
	destroyer();
}

// List copy constructor via overloaded operator.
template <class T>
List<T>& List<T>::operator=(const List& rhs)
{
	List(rhs);
	return (*this);
}

// Getter for List object's head pointer.
template<class T>
Node<T>* List<T>::getHeadPtr() const
{
	return mpHead;
}

// Recursively gets the last pointer in the list.
template<class T>
Node<T>* List<T>::getLastPtr(Node<T>* copy) const
{
	return (copy->getNextPtr() != nullptr) ? getLastPtr(copy->getNextPtr()) : copy;
}

// Setter for List object's head pointer.
template<class T>
void List<T>::setHeadPtr(T newData)
{
	if (isEmpty())
		mpHead = makeNode<T>(newData);
}

// Inserts T object at end of list.
template <class T>
void List<T>::insertAtEnd(T newData)
{
	if (!isEmpty())
		(getLastPtr(mpHead))->setNextPtr(makeNode<T>(newData));
	else
		setHeadPtr(newData);
}

// Deletes a Node object at front of list.
template<class T>
inline T List<T>::deleteAtFront()
{
	T save = nullptr;
	Node<T>* gone = nullptr;
	if (!isEmpty())
	{
		gone = getHeadPtr();
		mpHead = gone->getNextPtr();
		save = gone->getData();
		delete gone;
	}
	return save;
}

// Deletes Node object at end of list.
template<class T>
T List<T>::deleteAtEnd()
{
	T save;
	Node<T>* gone = getHeadPtr();
	if (!isEmpty() && gone->getNextPtr() != nullptr) {
		while (gone->getNextPtr()->getNextPtr() != nullptr)
			gone = gone->getNextPtr();
		save = gone->getNextPtr()->getData();
		delete gone->getNextPtr();
		gone->setNextPtr(nullptr);
	}
	return save;
}

// Recursively builds the list.
template<class T>
void List<T>::builder(Node<T>* head)
{
	if (head != nullptr)
	{
		insertAtEnd(head->getData());
		builder(head->getNextPtr());
	}
}

// Recursively deallocates the list.
template <class T>
void List<T>::lilDestroy(Node<T>* gone)
{
	if (gone != nullptr)
	{
		lilDestroy(gone->getNextPtr());
		delete gone;
	}
}

// Calls lilDestroy.
template <class T>
void List<T>::destroyer()
{
	lilDestroy(mpHead);
}

// Determines if the list is empty.
template<class T>
bool List<T>::isEmpty()
{
	return mpHead == nullptr ? true : false;
}

#endif