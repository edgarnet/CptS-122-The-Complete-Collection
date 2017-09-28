/*
* =====================================================================================
*
*       Filename:  Groceries.h
*
*    Description:  This contains function declarations for the program.
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

#ifndef _Groceries_H

#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<string.h>

#define		EXPRESS		3

typedef enum bool {
	FALSE, TRUE
}Bool;

//Struct for cart items.
typedef struct groceryNode {
	char *item;
	struct groceryNode * pNext;
}GroceryNode;

typedef struct queueNode
{
	int customerNumber; // Unique identifier; starts at 1; after 24 hours should be reset to 1
	int serviceTime;   // Proportional to the number of items in the customers cart.
	int totalTime;     // totalTime = serviceTime + sum of serviceTimes of customers in line before this customer; units in minutes
	GroceryNode *cart;
	struct queueNode *pNext;
} QueueNode;

typedef struct queue
{
	QueueNode *pHead;
	QueueNode *pTail;
} Queue;

//Randomly returns an item for a cart node.
char *cartItem(void);

//Determines the size of a cart list.
int cartSize(GroceryNode *cart);

//Sets up a cart list.
GroceryNode *setCart(void);

//Returns a new node for the queue.
QueueNode *makeNode();

//Determines if the queue's nodes are empty.
Bool isEmpty(Queue *fifo);

//Stores a new node into the queues.
Bool enqueue(Bool newDay, Queue *express, Queue *normal);

//Frees a cart (item) list.
Bool freeCart(GroceryNode *cart);

//Dequeues a node from any queue.
Bool dequeue(Queue *fifo, QueueNode save);

//Creates both 'express lane' and normal lane' queues based on the amount of consumers.
Bool consumerSet(int consumers, Queue *express, Queue *normal);

//Prints everything from both queues.
void printAll(Queue *express, Queue *normal);

//Prints each item from 'express lane' and 'normal lane' simultaneously.
void printExpress(int minutes, Queue *express, Queue *normal);

//Runs the program.
void runApp(void);

#endif // !_Groceries_cH
