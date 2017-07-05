// Edgar Perez
// PA 8 - Data Analysis via BST
#include "Node.h"
#include <iostream>
class TransactionNode : public NodeBST
{
public:
	TransactionNode() { mUnits = 0; }
	TransactionNode(std::string& newString, int newUnits):NodeBST(newString) { mUnits = newUnits; }
	~TransactionNode() { ; }

	int getUnits() const { return mUnits; }
	void setUnits(int& newUnits) { mUnits = newUnits; }

	// Overloaded virtual printData.
	void printData() { std::cout << "Data: " << getData() << "Units: " << getUnits() << std::endl; }

private:
	int mUnits;
};

