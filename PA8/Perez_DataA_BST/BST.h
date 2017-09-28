// Edgar Perez
// PA 8 - Data Analysis via BST
// Comments in source file.
#pragma once
#include "TransactionNode.h"

class BST
{
public:
	BST() { mpRoot = nullptr; }
	~BST() { destroyTree(mpRoot); }

	void setRoot(TransactionNode*& newRoot) { mpRoot = newRoot; }
	NodeBST*& getRoot() { return mpRoot; }

	void insert(std::string newData, int newUnits) { secretInsert(mpRoot, newData, newUnits); }
	void inOrderTraversal() { secretTraversal(mpRoot); }
	TransactionNode*& findSmallest() { TransactionNode* smallest = dynamic_cast<TransactionNode*>(findMin(mpRoot)); return smallest; }
	TransactionNode*& findLargest() { TransactionNode* largest = dynamic_cast<TransactionNode*>(findMax(mpRoot)); return largest; }
private:
	NodeBST* mpRoot;
	void destroyTree(NodeBST*& free);
	void secretInsert(NodeBST*& copy, std::string newData, int newUnits);
	void secretTraversal(NodeBST*&);
	NodeBST*& findMin(NodeBST*& copy);
	NodeBST*& findMax(NodeBST*& copy);
};

