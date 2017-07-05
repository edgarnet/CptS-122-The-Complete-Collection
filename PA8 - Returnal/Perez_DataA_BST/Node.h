#pragma once
// Edgar Perez
// PA 8 - Data Analysis via BST
#include <string>

class NodeBST
{
public:
	NodeBST() { mpLeft = nullptr; mpRight = nullptr; }
	NodeBST(std::string& newString) { mData = newString; mpLeft = nullptr; mpRight = nullptr; }
	// Useless copy constructor.
	NodeBST& operator=(NodeBST& copyNode)
	{ this->mData = copyNode.mData; this->mpLeft = copyNode.mpLeft; this->mpRight = copyNode.mpLeft; return *this; }

	// Accessors
	std::string getData() const { return mData; }
	NodeBST*& getLeftPtr() { return mpLeft; }
	NodeBST*& getRightPtr() { return mpRight; }

	// Mutators
	void setData(std::string& newString) { mData = newString; }
	void setLeftPtr(NodeBST*& newLeft) { mpLeft = newLeft; }
	void setRightPtr(NodeBST*& newRight) { mpRight = newRight; }

	virtual void printData() = 0;

	virtual ~NodeBST() { ; }

protected:
	std::string mData;
	NodeBST* mpLeft;
	NodeBST* mpRight;
};

