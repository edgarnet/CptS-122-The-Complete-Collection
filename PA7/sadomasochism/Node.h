// Edgar Perez
// PA 7 - Attendance Tracker

#pragma once
#ifndef _Node_H
#define _Node_H

// Template declaration for Node class.
template <class T>
class Node;

// makeNode function accessible for any class which includes "Node.h".
template <class T>
Node<T>* makeNode(T newData) { return new Node<T>(newData); }

// Node class definition.
template <class T> class Node
{
public:
	// Constructor for Node object.
	Node(T);
	// Copy Constructor for Node object.
	Node(const Node &copy);
	// Destructor for Node object.
	~Node();
	// Non-const getter for object 'T' stored in Node object.
	T & getData();
	// Getter for Node object's next pointer.
	Node * getNextPtr() const;
	//Setter for data of object 'T'.
	void setData(const T newData);
	// Setter for Node object's next pointer.
	void setNextPtr(Node * const newNext);

	//Data members for Node class.
private:
	T data;
	Node *nextPtr;
};

// Constructor for Node object.
template <class T>
Node <T>::Node(T newData)
{
	setData(newData);
	setNextPtr(nullptr);
}

// Copy Constructor for Node object.
template <class T>
Node <T>::Node(const Node &copy)
{
	data = copy.getData();
	nextPtr = copy.getNextPtr();
}

// Destructor for Node object.
template <class T>
Node<T>::~Node()
{
	cout << "This node has been deallocated" << endl;
}

// Non-const getter for object 'T' stored in Node object.
template <class T>
T & Node<T>::getData()
{
	return data;
}

// Getter for Node object's next pointer.
template <class T>
Node<T>* Node<T>::getNextPtr() const
{
	return nextPtr;
}

//Setter for data of object 'T'.
template <class T>
void Node<T>::setData(const T input)
{
	data = input;
}

// Setter for Node object's next pointer.
template <class T>
void Node<T>::setNextPtr(Node* const newNext)
{
	nextPtr = newNext;
}

#endif