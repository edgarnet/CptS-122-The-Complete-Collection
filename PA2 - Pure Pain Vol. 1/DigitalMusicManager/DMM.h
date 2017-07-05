/*
 * =====================================================================================
 *
 *       Filename:  DMM.h
 *
 *    Description:  This contains the function declarations for DMM.c
 *
 *        Version:  1.0
 *        Created:  1/25/2017 7:30:11 PM
 *       Revision:  none
 *       Compiler:  msft c
 *
 *         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
 *   Organization:  Washington State University
 *
 * =====================================================================================
 */

/*Concerning the lack of implementation of 'struct node' and 'insertFront()':
During the development of the program's underlying framework, my goal was to
prove that 'struct node' was an extra layer of abstraction which did little
to add to the efficiency of accessing data via the linked list. With
this is mind, the pointers which contain each 'node' were implemented within
the 'struct song' or as the rubric calls 'struct record'. This essentially
allows direct access to the linked list and the fields which contain
data from 'newPlayList.csv' all within the same struct. If the lack of 'struct node' 
implementation will reduce my grade I am willing to change the framework to
meet the requirements of the PA, but it's a dangerous task which may do more harm than good.*/

#ifndef _DMM_H
#define _DMM_H

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

#define		MAX		1000
#define		EXIT	11
#define		MIN		10

typedef enum boolean {
	FALSE, TRUE
} Bool;

typedef struct duration {
	int seconds;
	int minutes;
} Duration;

//Record struct
typedef struct song {
	char artist[MAX];
	char album[MAX];
	char song[MAX];
	char genre[MAX];
	Duration time;
	int plays;
	int rating;
	struct song *before;
	struct song *after;
} Song;

//Node struct
/*Not implemented due to inconsistency with established framework.*/
typedef struct node {
	struct song data;
	struct node *prevPtr;
	struct song *nextPtr;
}Node;

/* Copyright(C) 1991, 1992  Linus Torvalds */
char *strsep(char **s, const char *ct);

/*Returns address for a new node.*/
Song *makeNode(void);

/*Inserts new node at the top of the linked list.*/
Bool insertFront(Song **pHead);

/*Prints the contents of the linked list. Used for debug only!*/
void printList(Song **pHead);

/*Postcondition: The linked list contains data from the file.*/
Song **load(FILE *library);

/*Displays all song or those of a certain artist.*/
Bool displayAll(Song **playlist);

/*Coupled with displayAll().*/
Bool displayArtist(Song **playlist);

/*Allows User to edit information for a song.*/
Bool edit(Song **playlist);

/*Allows the user to rate a song.*/
Bool rate(Song **playlist);

/*Prints each song for a short period of time.*/
void play(Song **playlist);

/*Stores the data from the list into the .csv file.*/
Bool store(Song **playlist, FILE *input, int option);

/*Executes program.*/
void runApp(void);

#endif // !_DMM_H