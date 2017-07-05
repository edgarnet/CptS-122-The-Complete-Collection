/*
* =====================================================================================
*
*       Filename:  Cart.c
*
*    Description:  This contains function definitions for GroceryNode.
*
*        Version:  1.0
*        Created:  2/16/2017 10:04:34 PM
*       Revision:  none
*       Compiler:  msft c
*
*         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
*   Organization:  Washington State University
*
* =====================================================================================
*/

#include	"Groceries.h"

//Randomly returns an item for a cart node.
char *cartItem(void) {
	int type = rand() % 8 + 1;
	char *item = malloc(sizeof(char));

	switch (type) {
	case 1:
		return item = "Bread";
	case 2:
		return item = "Steak";
	case 3:
		return item = "Rice";
	case 4:
		return item = "Olive Oil";
	case 5:
		return item = "Fruit";
	case 6:
		return item = "Eggs";
	case 7:
		return item = "Fish";
	case 8:
		return item = "Vegetables";
	default:
		return item = "Jelly";
	}

}

//Determines the size of a cart list.
int cartSize(GroceryNode *cart) {
	GroceryNode *curCart = cart;
	int size = 0;
	//Initialize 1 or 0?
	for (size = 0; curCart != NULL; size++)
		curCart = curCart->pNext;
	return size;
}

//Sets up a cart list.
GroceryNode *setCart(void) {

	//1 - express.
	//2 - regular.
	int fate = rand() % 2 + 1;
	int size = 0;
	GroceryNode *newNode = malloc(sizeof(GroceryNode));
	GroceryNode *curNode = newNode;

	//Based on fate-value, this stores the items in the cart list.
	switch (fate) {
	case 1:
		size = rand() % 3 + 1;
		for (int i = 0; i < size; i++) {
			curNode->item = cartItem();
			if (i < size - 1) {
				curNode->pNext = malloc(sizeof(GroceryNode));
				curNode = curNode->pNext;
			}
			else
				curNode->pNext = NULL;
		}
	case 2:
		size = rand() % 5 + 4;
		for (int i = 3; i < size; i++) {
			curNode->item = cartItem();
			if (i < size - 1) {
				curNode->pNext = malloc(sizeof(GroceryNode));
				curNode = curNode->pNext;
			}
			else
				curNode->pNext = NULL;
		}
	}

	return newNode;
} 
