/*
* =====================================================================================
*
*       Filename:  Header.h
*
*    Description:  This file contains all function declarations for the program.
*
*        Version:  1.0
*        Created:  2/7/2017 1:46:43 PM
*       Revision:  none
*       Compiler:  msft c
*
*         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
*   Organization:  Washington State University
*
* =====================================================================================
*/

#ifndef _Header_H
#define _Header_H

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#define		MAX		1000
#define		EXIT	11
#define		MIN		10

typedef enum boolean {
	FALSE, TRUE
}Bool;

typedef struct duration {
	int seconds;
	int minutes;
}Duration;

typedef struct record {
	char artist[MAX];
	char album[MAX];
	char song[MAX];
	char genre[MAX];
	Duration time;
	int plays;
	int rating;
}Record;

typedef struct node {
	Record data;
	struct node *next;
	struct node *prev;
}Node;

/* Copyright(C) 1991, 1992  Linus Torvalds */
char *strsep(char **s, const char *ct);

/*Initializes a new node for the list.*/
Node *makeNode(void);

/*Returns TRUE if the first node is NULL.*/
Bool isEmpty(Node *playList);

/*Inserts a new node at the front (top) of the list.*/
Bool insertFront(Node **playList);

/*Loads data from the .csv file to the list.
Returns the address of the first node in the list.*/
Node **load(FILE *library);

/*Stores the data into the file.*/
Bool store(Node **playList, FILE *output, int option);

/*Prints all nodes to the user.*/
Bool printList(Node **playList);

/*Coupled with printList()*/
char *printByArtist(Node **playList);

/*Allows user to edit information for a song.*/
Bool edit(Node **playList);

/*Allows the user to rate a song.*/
Bool rate(Node **playList);

/*Inserts a new node into the list.*/
void insert(Node **playList);

/*Deletes a node from the list.*/
Bool deleteNode(Node **playList);

/*Prints each song for a short period of time.*/
void play(Node **playList);

/*Sorts the list based on artist, album, rating, or plays.*/
void sortNode(Node **playList);

/*Used for bubble sorting strings in sortNode()*/
int compareString(char *cur, char *next);

/*Shuffles the songs in the node.*/
void shuffle(Node **playList);

/*Executes program.*/
void runApp(void);

#endif //