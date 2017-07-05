/*
* =====================================================================================
*
*       Filename:  Groceries.c
*
*    Description:  This contains function definitions for QueueNode.
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

//Returns a new node for the queue.
QueueNode *makeNode() {
	QueueNode *newNode = malloc(sizeof(QueueNode));
	newNode->customerNumber = 1;
	newNode->cart = setCart();
	newNode->serviceTime = cartSize(newNode->cart);
	newNode->totalTime = 0;
	newNode->pNext = NULL;

	return newNode;
}

//Determines if the queue's nodes are empty.
Bool isEmpty(Queue *fifo) {
	return fifo->pHead == NULL && fifo->pTail == NULL ? TRUE : FALSE;
}

//Stores a new node into the queues.
Bool enqueue(Bool newDay, Queue *express, Queue *normal) {
	QueueNode *customer = NULL;

	//Sets up an empty 'express lane' node.
	if (isEmpty(express)) {
		while ((customer = makeNode())->serviceTime > 3) {
			freeCart(customer->cart);
			free(customer);
		}
		customer->totalTime = customer->serviceTime;
		express->pHead = customer;
		express->pTail = customer;
	}
	//Sets up an empty 'normal lane' node.
	if (isEmpty(normal)) {
		while ((customer = makeNode())->serviceTime <= 3) {
			freeCart(customer->cart);
			free(customer);
		}
		customer->totalTime = customer->serviceTime;
		normal->pHead = customer;
		normal->pTail = customer;
		return TRUE;
	}
	//Resets the total time for a new day for each queue.
	if (newDay == TRUE) {
		while ((customer = makeNode())->serviceTime > 3) {
			freeCart(customer->cart);
			free(customer);
		}
		customer->totalTime = customer->serviceTime;
		express->pTail->pNext = customer;
		express->pTail = customer;

		while ((customer = makeNode())->serviceTime <= 3) {
			freeCart(customer->cart);
			free(customer);
		}
		customer->totalTime = customer->serviceTime;
		normal->pTail->pNext = customer;
		normal->pTail = customer;
		return TRUE;
	}
	//Stores a new node into both queues.
	else {
		while ((customer = makeNode())->serviceTime > 3) {
			freeCart(customer->cart);
			free(customer);
		}
		customer->customerNumber += express->pTail->customerNumber;
		customer->totalTime = (customer->serviceTime + express->pTail->totalTime);
		express->pTail->pNext = customer;
		express->pTail = customer;

		while ((customer = makeNode())->serviceTime <= 3) {
			freeCart(customer->cart);
			free(customer);
		}
		customer->customerNumber += normal->pTail->customerNumber;
		customer->totalTime = (customer->serviceTime + normal->pTail->totalTime);
		normal->pTail->pNext = customer;
		normal->pTail = customer;
		return TRUE;
	}
	
	//If all else fails.
	return FALSE;
}

//Frees a cart (item) list.
Bool freeCart(GroceryNode *cart) {
	GroceryNode *clear = NULL;

	if (cart == NULL)
		return FALSE;

	while (cart != NULL) {
		clear = cart;
		cart = cart->pNext;
		free(clear);
	}

	return TRUE;
}

//Dequeues a node from any queue.
Bool dequeue(Queue *fifo, QueueNode save) {
	QueueNode *clear = NULL;

	if (isEmpty(fifo)) {
		printf("Your queue is empty!\n");
		return FALSE;
	}
	//Stores the node's data into the output parameter 'save'.
	else {
		save.customerNumber = fifo->pHead->customerNumber;
		save.serviceTime = fifo->pHead->serviceTime;
		save.totalTime = fifo->pHead->totalTime;
		save.cart = fifo->pHead->cart;
		save.pNext = fifo->pHead->pNext;
		clear = fifo->pHead;

		if (clear == fifo->pTail) {
			freeCart(clear->cart);
			free(clear);
			fifo->pHead = NULL;
			fifo->pTail = NULL;
			return TRUE;
		}

		fifo->pHead = fifo->pHead->pNext;
		freeCart(clear->cart);
		free(clear);
		return TRUE;
	}

	return FALSE;
}

//Creates both 'express lane' and normal lane' queues based on the amount of consumers.
Bool consumerSet(int consumers, Queue *express, Queue *normal) {
	enqueue(FALSE, express, normal);

	for (int i = 0; i < consumers / 2; i++) {
		if (express->pTail->totalTime + normal->pTail->totalTime >= 1440)
			enqueue(TRUE, express, normal);
		else
			enqueue(FALSE, express, normal);
	}

	return TRUE;
}

//Prints everything from both queues.
void printAll(Queue *express, Queue *normal) {
	QueueNode *displayExp = express->pHead;
	QueueNode *displayNom = normal->pHead;
	GroceryNode *curCart = NULL;
	int prevLine = 0;

	//Prints until 'express lane' is NULL.
	while (displayExp != NULL) {
		if (displayExp == NULL)
			break;
		printf("\nCustomer Number: %d\n", displayExp->customerNumber);
		prevLine = displayExp->customerNumber;
		curCart = displayExp->cart;
		while (curCart != NULL) {
			printf("Item:            %s\n",curCart->item);
			curCart = curCart->pNext;
		}
		printf("Depart Time:    %d:%d\n", displayExp->totalTime / 60, displayExp->totalTime % 60);
		displayExp = displayExp->pNext;
	}

	//Prints until 'normal lane' is NULL.
	while (displayNom != NULL) {
		printf("\nCustomer Number: %d\n", displayNom->customerNumber + prevLine);
		curCart = displayNom->cart;
		while (curCart != NULL) {
			printf("Item:            %s\n", curCart->item);
			curCart = curCart->pNext;
		}
		printf("Depart Time:    %d:%d\n", displayNom->totalTime / 60, displayNom->totalTime % 60);
		displayNom = displayNom->pNext;
	}
}

//Prints each item from 'express lane' and 'normal lane' simultaneously.
void printExpress(int minutes, Queue *express, Queue *normal) {
	QueueNode *curExp = express->pHead;
	QueueNode *curNom = normal->pHead;

	int totalTime = 0;
	//Prints until 'express lane' is NULL.
	while (curExp != NULL) {
		if (curExp == NULL)
			break;
		int curTime = time(NULL) + 1;
		totalTime++;
		//Prints side by side.
		printf("Express lane                    Normal Lane\n");
		printf("Customer Number: %-10d\tCustomer Number: %d\n", curExp->customerNumber, curNom->customerNumber);
		printf("Item:            %-10s\tItem:            %s\n", curExp->cart->item, curNom->cart->item);
		printf("Arrival Time:    %d:%-10d\tArrival Time     %d:%d\n", (curExp->totalTime - curExp->serviceTime) / 60, 
			(curExp->totalTime - curExp->serviceTime) % 60, (curNom->totalTime - curNom->serviceTime) / 60, 
			(curNom->totalTime - curNom->serviceTime) % 60);
		while (curTime >= time(NULL));
		curExp->cart = curExp->cart->pNext;
		curNom->cart = curNom->cart->pNext;
		if (curExp->cart == NULL)
			curExp = curExp->pNext;
		if (curNom->cart == NULL)
			curNom = curNom->pNext;
		if (totalTime >= minutes)
			break;
		if (totalTime % 10 == 0) {
			printAll(express, normal);
			curTime = time(NULL) + 1;
			while (curTime >= time(NULL));
		}
		//Moves to next node.
		system("cls");
	}

	//Prints until 'normal lane' is NULL.
	while (curNom != NULL) {
		if (totalTime >= minutes)
			break;
		totalTime++;
		printf("Normal Lane\n");
		printf("Customer Number: %d\n", curNom->customerNumber);
		printf("Item:            %s\n", curNom->cart->item);
		printf("Arrival Time:    %d:%d\n", (curNom->totalTime - curNom->serviceTime) / 60, 
			(curNom->totalTime - curNom->serviceTime) % 60);
		int curTime = time(NULL) + 1;
		while (curTime >= time(NULL));
		curNom->cart = curNom->cart->pNext;
		if (curNom->cart == NULL)
			curNom = curNom->pNext;
		if (totalTime % 10 == 0) {
			printAll(express, normal);
			curTime = time(NULL) + 1;
			while (curTime >= time(NULL));
		}
		//Moves to next node.
		system("cls");
	}
}

//Runs the program.
void runApp(void) {
	//UI / how length of time is determined.
	printf("Enter the amount of minutes that will visit the store:\n");
	int minutes = 0;
	scanf("%d", &minutes);
	Queue *express = malloc(sizeof(Queue));
	express->pHead = NULL;
	express->pTail = NULL;
	Queue *normal = malloc(sizeof(Queue));
	normal->pHead = NULL;
	normal->pTail = NULL;

	//Queues are initialized and then set for display.
	int consumers = minutes;
	consumerSet(consumers, express, normal);
	system("cls");
	printExpress(minutes, express, normal);
	QueueNode *proxy = makeNode();
	while (dequeue(express, *proxy) != FALSE);
	while (dequeue(normal, *proxy) != FALSE);
}