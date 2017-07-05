// Edgar Perez
// PA 7 - Attendance Tracker

#pragma once
#ifndef _StackNode_H
#define _StackNode_H

template <typename Leaf, class Branch>
class NodeST;

template <typename Leaf, class Branch>
NodeST<Leaf, Branch>* makeNode(Leaf& newData, Branch& newReference)
{
	return new NodeST<Leaf, Branch>(newData, newReference);
}

template <typename Leaf, class Branch>
class NodeST
{
public:
	NodeST(Leaf&, Branch&);
	NodeST(const NodeST& copy);
	~NodeST() { ; }
	Leaf getData() const;
	Branch getReference() const;
	NodeST* getNextPtr();
	void setData(Leaf& newData);
	void setReference(Branch& newReference);
	void setNextPtr(NodeST*& newNext);

private:
	Leaf data;
	Branch reference;
	NodeST<Leaf, Branch>* nextPtr;
};

template <typename Leaf, class Branch>
NodeST<Leaf, Branch>::NodeST(Leaf& data, Branch& reference)
{
	setData(data);
	setReference(reference);
	nextPtr = nullptr;
}

template <typename Leaf, class Branch>
NodeST<Leaf, Branch>::NodeST(const NodeST& copy)
{
	setData(copy.getData());
	setReference(copy.getReference());
	setLeftPtr(copy.getNextPtr());
}

template <typename Leaf, class Branch>
Leaf NodeST<Leaf, Branch>::getData() const
{
	return data;
}

template <typename Leaf, class Branch>
Branch NodeST<Leaf, Branch>::getReference() const
{
	return reference;
}

template <typename Leaf, class Branch>
NodeST<Leaf, Branch>* NodeST<Leaf, Branch>::getNextPtr()
{
	return nextPtr;
}

template <typename Leaf, class Branch>
void NodeST<Leaf, Branch>::setData(Leaf& newData)
{
	data = newData;
}

template <typename Leaf, class Branch>
void NodeST<Leaf, Branch>::setReference(Branch& newReference)
{
	reference = newReference;
}

template <typename Leaf, class Branch>
void NodeST<Leaf, Branch>::setNextPtr(NodeST<Leaf, Branch>*& newNext)
{
	nextPtr = newNext;
}

#endif