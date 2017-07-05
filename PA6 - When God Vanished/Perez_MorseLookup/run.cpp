// Name: Edgar Perez
// Collaborators: Shusanta Bhatter, Nick Vasicek
// Runapp source file

#include "Run.h"

void runapp()
{
	char firstChar = 0;
	string firstString;
	ifstream input;
	ifstream convert;
	// Opens both files
	input.open("MorseTable.txt");
	convert.open("Convert.txt");
	if (input)
	{
		// Collects first data and reference for the tree.
		input.get(firstChar);
		getline(input, firstString);
		getline(input, firstString);
		ListBT<char, string> morseTable(firstChar, firstString);
		// Stores the rest of the MorseTable into the tree.
		collectTable(morseTable, input);
		morseTable.printTree();
		// Prints the convert.txt as morse.
		printMorse(morseTable, convert);
	}
	else
		cout << "Could not access files." << endl;
	cout << endl;
	input.close();
	convert.close();
}

void collectTable(ListBT<char, string>& morseTree, ifstream& input)
{
	char tempChar = 0;
	string tempString;
	while(input)
	{
		// Collects and stores the morse into the tree.
		input.get(tempChar);
		getline(input, tempString);
		getline(input, tempString);
		if (tempChar != 'C') //Omits first character.
			morseTree.insertNode(tempChar, tempString);
	}
}

void printMorse(ListBT<char, string>& morseTree, ifstream& convert)
{
	char tempChar = 0;
	string tempString;
	while(convert)
	{
		// Converts each character from Convert.txt and prints the corresponding morse code.
		convert.get(tempChar);
		// Converts lowercase to uppercase.
		if (tempChar >= 'a' && tempChar <= 'z')
			tempChar -= 32;
		auto node = morseTree.search(tempChar);
		if (node)
			cout << node->getReference();
		else
			cout << tempChar;
	}
}