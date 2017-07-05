/*
* =====================================================================================
*
*       Filename:  Database.c
*
*    Description:  This file contains function definitions for manipulating the data structure.
*
*        Version:  1.0
*        Created:  2/7/2017 1:47:30 PM
*       Revision:  none
*       Compiler:  msft c
*
*         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
*   Organization:  Washington State University
*
* =====================================================================================
*/

#include	"Header.h"

/* Copyright(C) 1991, 1992  Linus Torvalds */
char *strsep(char **s, const char *ct) {
	char *sbegin = *s;
	char *end;
	if (sbegin == NULL)
		return NULL;
	end = strpbrk(sbegin, ct);
	if (end)
		*end++ = '\0';
	*s = end;
	return sbegin;
}

/*Initializes a new node for the list.*/
Node *makeNode(void) {

	Node *currentPtr = (Node *)(malloc(sizeof(Node)));

	/*Initializes all fields in Node and Record to NULL.*/
	for (int index = 0; index < MAX; index++) {
		currentPtr->data.artist[index] = 0;
		currentPtr->data.album[index] = 0;
		currentPtr->data.song[index] = 0;
		currentPtr->data.genre[index] = 0;
	}

	currentPtr->data.time.minutes = 0;
	currentPtr->data.time.seconds = 0;
	currentPtr->data.plays = 0;
	currentPtr->data.rating = 0;

	currentPtr->next = NULL;
	currentPtr->prev = NULL;

	return currentPtr;
}

/*Returns TRUE if the first node is NULL.*/
Bool isEmpty(Node *playList) {

	if (playList == NULL)
		return TRUE;

	return FALSE;
}

/*Inserts a new node at the front (top) of the list.*/
Bool insertFront(Node **playList) {
	
	/*If no node exists, one is initialized at the front.*/
	if (isEmpty(*playList) == TRUE) {
		*playList = makeNode();
		return TRUE;
	}
	/*Good ol' switcheroo*/
	else {
		(*playList)->prev = makeNode();
		(*playList)->prev->next = *playList;
		*playList = (*playList)->prev;
		return TRUE;
	}

	return FALSE;
}

/*Loads data from the .csv file to the list.
Returns the address of the first node in the list.*/
Node **load(FILE *library) {

	char input[MAX] = { 0 };
	char *track = NULL;
	char *token = NULL;

	/*Initalizes the list in the heap.*/
	Node **playList = (Node**)malloc(sizeof(Node*));
	*playList = NULL;

	/*Checks if the .csv file exists.*/
	if (library == NULL) {
		printf("HEY! THIS IS LIBRARY!");
		return NULL;
	}

	/*Collects data until the end of the file is reached.*/
	while (fgets(input, sizeof(input), library) != NULL) {

		insertFront(playList);
			track = &(input[0]);
			char buffer[MAX] = { 0 };

			/*Separates values from fgets() to their respective field in each node.*/
			/*Artist*/
			token = strsep(&track, ",");
			if (token == NULL)
				strcpy((*playList)->data.artist, "Unknown Artist");
			else if (token[0] == '\"') {
				strcpy(buffer, token);
				buffer[strlen(token)] = ',';
				strcat(buffer, strsep(&track, ","));
				strcpy((*playList)->data.artist, buffer);
			}
			else
				strcpy((*playList)->data.artist, token);

			/*Album*/
			token = strsep(&track, ",");
			if (token == NULL)
				strcpy((*playList)->data.album, "Unknown Album");
			else
				strcpy((*playList)->data.album, token);

			/*Song*/
			token = strsep(&track, ",");
			if (token == NULL)
				strcpy((*playList)->data.song, "Untitled Track");
			else
				strcpy((*playList)->data.song, token);

			/*Genre*/
			token = strsep(&track, ",");
			if (token == NULL)
				strcpy((*playList)->data.genre, "Unknown Genre");
			else
				strcpy((*playList)->data.genre, token);

			/*Minutes*/
			token = strsep(&track, ":");
			if (token == NULL)
				(*playList)->data.time.minutes = 00;
			else
				(*playList)->data.time.minutes = atoi(token);

			/*Seconds*/
			token = strsep(&track, ",");
			if (token == NULL)
				(*playList)->data.time.seconds = 00;
			else
				(*playList)->data.time.seconds = atoi(token);

			/*Plays*/
			token = strsep(&track, ",");
			if (token == NULL)
				(*playList)->data.plays = 0;
			else
				(*playList)->data.plays = atoi(token);

			/*Rating*/
			token = strsep(&track, ",");
			if (token == NULL)
				(*playList)->data.rating = 0;
			else
				(*playList)->data.rating = atoi(token);

	}

	/*Notifies user of load progress.*/
	if (!isEmpty(playList))
		printf("Beez in the trap!\n");
	else
		printf("Load was unsuccessful.\n");

	return playList;
}

/*Stores the data into the file.*/
Bool store(Node **playList, FILE *output, int option) {

	/*Checks if the file is not open.*/
	if (output == NULL) {
		printf("Could not open file!\n");
		return FALSE;
	}

	/*Checks if the music has been loaded.*/
	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	fclose(output);
	output = fopen("PlayList.csv", "w");
	Node *currentPtr = *playList;

	/*Prints the data from list into file.*/
	if (option == EXIT) {
		while (*playList != NULL) {
			fprintf(output, "%s,%s,%s,%s,%d:%d,%d,%d\n", (*playList)->data.artist,
				(*playList)->data.album, (*playList)->data.song, (*playList)->data.genre,
				(*playList)->data.time.minutes, (*playList)->data.time.seconds,
				(*playList)->data.plays, (*playList)->data.rating);
			*playList = (*playList)->next;
			if (*playList)
				free((*playList)->prev);
		}
	}
	else {
		while (currentPtr != NULL) {
			fprintf(output, "%s,%s,%s,%s,%d:%d,%d,%d\n", currentPtr->data.artist,
				currentPtr->data.album, currentPtr->data.song, currentPtr->data.genre,
				currentPtr->data.time.minutes, currentPtr->data.time.seconds,
				currentPtr->data.plays, currentPtr->data.rating);
			currentPtr = currentPtr->next;
		}
	}

	/*Re-opens file for further use.*/
	fclose(output);
	output = fopen("PlayList.csv", "r");

	/*Frees everything.*/
	if (option == EXIT) {
		free(playList);
		fclose(output);
		exit(0);
	}
}

/*Inserts a new node into the list.*/
void insert(Node **playList) {

	insertFront(playList);
	char newAlbum[MAX] = { 0 };
	char newArtist[MAX] = { 0 };
	char newSong[MAX] = { 0 };
	char newGenre[MAX] = { 0 };
	int newMinute = 0;
	int newSecond = 0;
	int plays = 0;
	int rating = 0;

	/*Collects and stores the artist's name.*/
	system("cls");
	printf("Enter the artist's name:\n");
	getchar();
	fgets(newArtist, sizeof(newArtist), stdin);
	strcpy(newArtist, strtok(newArtist, "\n"));
	strcpy((*playList)->data.artist, newArtist);
	system("cls");

	/*Collects and stores the album name.*/
	printf("Enter the album name:\n");
	fgets(newAlbum, sizeof(newAlbum), stdin);
	strcpy(newAlbum, strtok(newAlbum, "\n"));
	strcpy((*playList)->data.album, newAlbum);
	system("cls");

	/*Collects and stores the song title.*/
	printf("Enter the song title:\n");
	fgets(newSong, sizeof(newSong), stdin);
	strcpy(newSong, strtok(newSong, "\n"));
	strcpy((*playList)->data.song, newSong);
	system("cls");

	/*Collects and stores the genre type.*/
	printf("Enter the genre:\n");
	fgets(newGenre, sizeof(newGenre), stdin);
	strcpy(newGenre, strtok(newGenre, "\n"));
	strcpy((*playList)->data.genre, newGenre);
	system("cls");

	/*Collects and stores the song's rating.*/
	do {
		printf("Enter the rating (1-5):\n");
		scanf("%d", &rating);
	} while (rating < 1 || rating > 5);
	(*playList)->data.rating = rating;
	system("cls");

	/*Collects and stores the song's duration.*/
	printf("Enter the duration as 'Minutes:Seconds':\n");
	scanf("%d:%d", &newMinute, &newSecond);
	(*playList)->data.time.minutes = newMinute;
	(*playList)->data.time.seconds = newSecond;
	system("cls");

	/*Collects and stores the song plays.*/
	printf("Enter how many times you've played this song:\n");
	scanf("%d", &plays);
	(*playList)->data.plays = plays;

}

/*Deletes a node from the list.*/
Bool deleteNode(Node **playList) {

	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	char artist[MAX] = { 0 };
	char song[MAX] = { 0 };
	Node *currentPtr = *playList;

	strcpy(artist, printByArtist(playList));
	if (artist == NULL)
		return FALSE;

	else {
		printf("\nType in which song you would like to edit:\n");
		fgets(song, sizeof(song), stdin);
		strcpy(song, strtok(song, "\n"));

		while (currentPtr != NULL) {
			/*Compares the song and artist the user entered to find correct match for deletion.*/
			if (strcmp(currentPtr->data.song, song) == 0
				&& strcmp(currentPtr->data.artist, artist) == 0) {
				if (currentPtr->prev == NULL) {
					*playList = currentPtr->next;
					free(currentPtr);
				}
				else if (currentPtr->next == NULL) {
					currentPtr->prev->next = NULL;
					free(currentPtr);
				}
				else {
					currentPtr->prev->next = currentPtr->next;
					currentPtr->next->prev = currentPtr->prev;
					free(currentPtr);
				}
				return TRUE;
			}
			currentPtr = currentPtr->next;
		}
	}

	return FALSE;
}

/*Executes program.*/
void runApp(void) {

	/*Opens .csv file*/
	FILE *input = fopen("PlayList.csv", "r");
	FILE *start = input;
	if (!input) {
		printf("Unable to open file!\n");
		return;
	}

	Node **playList = NULL;
	char choice[MIN] = { 0 };
	int option = 0;

	/*Menu screen.*/
	do {
		do {
			printf("\n(1) Load (2) Store (3) Display (4) Insert (5) Delete\n");
			printf("(6) Edit (7) Sort (8) Rate (9) Play (10) Shuffle (11) Exit\n");
			printf("Choose an option: ");
			scanf("%s", choice);
			option = atoi(choice);
			system("cls");
		} while (option < 1 || option > 11);

		switch (option) {
		case 1:
			playList = load(input);
			break;
		case 2:
			store(playList, input, option);
			break;
		case 3:
			printList(playList);
			break;
		case 4:
			insert(playList);
			break;
		case 5:
			deleteNode(playList);
			break;
		case 6:
			edit(playList);
			break;
		case 7:
			sortNode(playList);
			break;
		case 8:
			rate(playList);
			break;
		case 9:
			play(playList);
			break;
		case 10:
			shuffle(playList);
			break;
		case 11:
			store(playList, input, option);
			break;
		default:
			break;
		}

	} while (option > 0 || option < 12);
}