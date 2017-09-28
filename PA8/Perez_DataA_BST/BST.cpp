// Edgar Perez
// PA 8 - Data Analysis via BST
#include "BST.h"

// Frees the BST.
void BST::destroyTree(NodeBST*& free)
{
	if (free != nullptr)
	{
		destroyTree(free->getLeftPtr());
		destroyTree(free->getRightPtr());
		delete free;
	}
}

// Insert helper function.
void BST::secretInsert(NodeBST*& copy, std::string newData, int newUnits)
{
	if (copy == nullptr)
		copy = new TransactionNode(newData, newUnits);
	else if (newUnits > ((TransactionNode*)copy)->getUnits())
		secretInsert(copy->getRightPtr(), newData, newUnits);
	else if (newUnits < ((TransactionNode*)copy)->getUnits())
		secretInsert(copy->getLeftPtr(), newData, newUnits);
	else
		std::cout << newData << " & " << newUnits << " has already been processed!" << std::endl;
}

// Recursive in-order print helper function.
void BST::secretTraversal(NodeBST*& copy)
{
	if (copy == nullptr)
		return;
	secretTraversal(copy->getLeftPtr());
	((TransactionNode*)copy)->printData();
	secretTraversal(copy->getRightPtr());
}

// findSmallest() helper function: recursively finds smallest 'Units' in BST.
NodeBST*& BST::findMin(NodeBST*& copy)
{
	if (copy->getLeftPtr() == nullptr)
		return copy;
	findMin(copy->getLeftPtr());
}

// findLargest() helper function: recursively finds largest 'Units' in BST.
NodeBST*& BST::findMax(NodeBST*& copy)
{
	if (copy->getRightPtr() == nullptr)
		return copy;
	findMax(copy->getRightPtr());
}