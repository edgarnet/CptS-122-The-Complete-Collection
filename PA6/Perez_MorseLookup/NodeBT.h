// Name: Edgar Perez
// Collaborators: Shusanta Bhatter, Nick Vasicek
// Binary Tree Node Template

#ifndef _NodeBT_H
#define _NodeBT_H

template <typename Leaf, class Branch>
class NodeBT;

// Returns a new node
template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>* makeNode(Leaf newData, Branch newReference)
{
	return new NodeBT<Leaf, Branch>(newData, newReference);
}

template <typename Leaf, class Branch>
class NodeBT
{
public:
	NodeBT(Leaf, Branch);
	NodeBT(const NodeBT& copy);
	// Node Deconstructor
	~NodeBT() { ; }
	Leaf getData() const;
	Branch getReference() const;
	NodeBT*& getRightPtr();
	NodeBT*& getLeftPtr();
	void setData(Leaf newData);
	void setReference(Branch newReference);
	void setRightPtr(NodeBT* const newRight);
	void setLeftPtr(NodeBT* const newLeft);

private:
	Leaf data;
	Branch reference;
	NodeBT<Leaf, Branch>* leftPtr;
	NodeBT<Leaf, Branch>* rightPtr;
};

// Constructor given first data and reference
template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>::NodeBT(Leaf data, Branch reference)
{
	setData(data);
	setReference(reference);
	setLeftPtr(nullptr);
	setRightPtr(nullptr);
}

// Copy Constructor
template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>::NodeBT(const NodeBT& copy)
{
	setData(copy.getData());
	setReference(copy.getReference());
	setLeftPtr(copy.getLeftPtr());
	setRightPtr(copy.getRightPtr());
}

// Node Accessors...

template <typename Leaf, class Branch>
Leaf NodeBT<Leaf, Branch>::getData() const
{
	return data;
}

template <typename Leaf, class Branch>
Branch NodeBT<Leaf, Branch>::getReference() const
{
	return reference;
}

template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>*& NodeBT<Leaf, Branch>::getLeftPtr()
{
	return leftPtr;
}

template <typename Leaf, class Branch>
NodeBT<Leaf, Branch>*& NodeBT<Leaf, Branch>::getRightPtr()
{
	return rightPtr;
}

// Node Mutators...

template <typename Leaf, class Branch>
void NodeBT<Leaf, Branch>::setData(Leaf newData)
{
	data = newData;
}

template <typename Leaf, class Branch>
void NodeBT<Leaf, Branch>::setReference(Branch newReference)
{
	reference = newReference;
}

template <typename Leaf, class Branch>
void NodeBT<Leaf, Branch>::setLeftPtr(NodeBT<Leaf, Branch>* const newLeft)
{
	leftPtr = newLeft;
}

template <typename Leaf, class Branch>
void NodeBT<Leaf, Branch>::setRightPtr(NodeBT<Leaf, Branch>* const newRight)
{
	rightPtr = newRight;
}

#endif