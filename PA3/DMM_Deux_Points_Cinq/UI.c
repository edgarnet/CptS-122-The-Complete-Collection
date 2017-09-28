/*
* =====================================================================================
*
*       Filename:  UI.c
*
*    Description:  This file contains function definitions for the user interface.
*
*        Version:  1.0
*        Created:  2/7/2017 1:48:42 PM
*       Revision:  none
*       Compiler:  msft c
*
*         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
*   Organization:  Washington State University
*
* =====================================================================================
*/

#include	"Header.h"

/*Prints all nodes to the user.*/
Bool printList(Node **playList) {
	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	system("cls");
	char rating[MIN] = { 0 };
	char choice[MIN] = { 0 };
	int option = 0;

	/*User determines what to print to the screen.*/
	do {
		printf("Would you like to display all records or those by an artist?\n");
		printf("Enter '1' for All or '2' for Artist\n");
		scanf("%s", choice);
		option = atoi(choice);
	} while (option != 1 && option != 2);

	if (option == 2) {
		return (Bool)printByArtist(playList);
	}

	/*Prints every record.*/
	printf("Artist                    |Album                    |Song                     |Genre     |Duration  |Plays    |Rating    \n");
	int count = 0;
	Node *currentPtr = *playList;
	while (currentPtr != NULL) {
		for (count = 0; count < currentPtr->data.rating; count++)
			rating[count] = '*';
		count = 0;
		printf("|%-25s|%-25s|%-25s|%-10s| %d:%d     |%-9d|%s \n",
			currentPtr->data.artist, currentPtr->data.album, currentPtr->data.song,
			currentPtr->data.genre, currentPtr->data.time.minutes, currentPtr->data.time.seconds,
			currentPtr->data.plays, rating);
		currentPtr = currentPtr->next;
		while (rating[count]) {
			rating[count] = 0;
			count++;
		}
	}

	return TRUE;
}

/*Coupled with printList()*/
char *printByArtist(Node **playList) {

	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return NULL;
	}

	/*Asks the user for which artist to print.*/
	system("cls");
	int track = 0;
	char artist[MAX] = { 0 };
	char *artistReturn = (char *)malloc(sizeof(char) * MAX);
	char rating[MAX] = { 0 };
	Node *currentPtr = *playList;
	printf("Please type below the artist you're looking for:\nIf the artist has two names, enter as: \"Last, First\"\n");
	getchar();
	fgets(artist, sizeof(artist), stdin);
	strcpy(artist, strtok(artist, "\n"));
	strcpy(artistReturn, artist);

	/*Prints artist records*/
	system("cls");
	printf("%s's Records:\n", artist);
	printf("Album                    |Song                     |Genre     |Duration  |Plays    |Rating    \n");
	int count = 0;
	while (currentPtr != NULL) {
		if (strcmp(currentPtr->data.artist, artistReturn) == 0) {
			for (count = 0; count < currentPtr->data.rating; count++)
				rating[count] = '*';
			printf("%-25s|%-25s|%-10s| %d:%d     |%-9d|%s \n",
				currentPtr->data.album, currentPtr->data.song,
				currentPtr->data.genre, currentPtr->data.time.minutes, currentPtr->data.time.seconds,
				currentPtr->data.plays, rating);
			track++;
			count = 0;
			while (rating[count]) {
				rating[count] = 0;
				count++;
			}
		}
		currentPtr = currentPtr->next;
	}

	/*Returns NULL if no records were found for that artist.*/
	if (track < 1) {
		system("cls");
		printf("We could not find records for %s in your library\n", artist);
		return NULL;
	}

	return artistReturn;
}

/*Allows user to edit information for a song.*/
Bool edit(Node **playList) {

	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	char song[MAX] = { 0 };
	char artist[MAX] = { 0 };
	char newAlbum[MAX] = { 0 };
	char newArtist[MAX] = { 0 };
	char newSong[MAX] = { 0 };
	char newGenre[MAX] = { 0 };
	Node *currentPtr = *playList;
	int choice = MIN;

	/*Returns false if an artist could not be found. Prints songs if successful.*/
	strcpy(artist, printByArtist(playList));
	if (artist == NULL)
		return FALSE;
	else {
		printf("\nType in which song you would like to edit:\n");
		fgets(song, sizeof(song), stdin);
		strcpy(song, strtok(song, "\n"));

		while (currentPtr != NULL) {
			/*Compares the song and artist the user entered to find correct match.*/
			if (strcmp(currentPtr->data.song, song) == 0
				&& strcmp(currentPtr->data.artist, artist) == 0) {
				do {
					printf("Change: (1) Artist, (2) Album, (3) Song, (4) Genre, (0) Exit\n");
					scanf("%d", &choice);

					switch (choice) {
					case 1:
						printf("Enter the artist's name:\n");
						getchar();
						fgets(newArtist, sizeof(newArtist), stdin);
						strcpy(newArtist, strtok(newArtist, "\n"));
						strcpy(currentPtr->data.artist, newArtist);
						system("cls");
						break;
					case 2:
						printf("Enter the album name:\n");
						getchar();
						fgets(newAlbum, sizeof(newAlbum), stdin);
						strcpy(newAlbum, strtok(newAlbum, "\n"));
						strcpy(currentPtr->data.album, newAlbum);
						system("cls");
						break;
					case 3:
						printf("Enter the song title:\n");
						getchar();
						fgets(newSong, sizeof(newSong), stdin);
						strcpy(newSong, strtok(newSong, "\n"));
						strcpy(currentPtr->data.song, newSong);
						system("cls");
						break;
					case 4:
						printf("Enter the genre:\n");
						getchar();
						fgets(newGenre, sizeof(newGenre), stdin);
						strcpy(newGenre, strtok(newGenre, "\n"));
						strcpy(currentPtr->data.genre, newGenre);
						system("cls");
						break;
						/*Clears screen if option is invalid.*/
					default:
						system("cls");
					}
				} while (choice != 0);
			}

			if (!choice)
				break;

			currentPtr = currentPtr->next;
		}
	}
	system("cls");

	return TRUE;
}

/*Allows the user to rate a song.*/
Bool rate(Node **playList) {
	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	char rateSong[MAX] = { 0 };
	int rating = 0;

	/*Asks the User which song they would like to rate.*/
	if (printByArtist(playList) == NULL)
		return FALSE;

	Node *currentPtr = *playList;
	printf("\nType in which song you would like to edit:\n");
	fgets(rateSong, sizeof(rateSong), stdin);
	strcpy(rateSong, strtok(rateSong, "\n"));

	/*Finds the song and allows the user to change its rating.*/
	while (currentPtr != NULL) {
		if (strcmp(currentPtr->data.song, rateSong) == 0) {
			do {
				printf("Enter the rating (1-5):\n");
				scanf("%d", &rating);
			} while (rating < 1 || rating > 5);
			currentPtr->data.rating = rating;
			system("cls");
			return TRUE;
		}
		currentPtr = currentPtr->next;
	}

	return FALSE;
}

/*Prints each song for a short period of time.*/
void play(Node **playList) {

	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return;
	}

	/*Prints the first song.*/
	system("cls");
	Node *currentPtr = *playList;
	printf("Song: %s\n", currentPtr->data.song);
	printf("Artist: %s\n", currentPtr->data.artist);
	printf("Album: %d\n", currentPtr->data.plays);
	printf("Length: %d:%d\n", currentPtr->data.time.minutes, currentPtr->data.time.seconds);
	currentPtr->data.plays++;
	currentPtr = currentPtr->next;

	/*Prints the remaining songs for ~4 seconds each.*/
	while (currentPtr->next != NULL) {
		time_t change = time(NULL) + 4;
		while (change >= time(NULL));
		system("cls");
		printf("Song: %s\n", currentPtr->data.song);
		printf("Artist: %s\n", currentPtr->data.artist);
		printf("Album: %d\n", currentPtr->data.plays);
		printf("Length: %d:%d\n", currentPtr->data.time.minutes, currentPtr->data.time.seconds);
		currentPtr->data.plays++;
		fflush(stdout);
		currentPtr = currentPtr->next;
	}

	printf("\n");
}

/*Sorts the list based on artist, album, rating, or plays.*/
void sortNode(Node **playList) {

	if (playList == NULL) {
		printf("Your music has not been loaded.\n");
		return;
	}

	//Make sure to set these NULL after use.
	char parseArtist[MAX] = { 0 };
	char parseNextArtist[MAX] = { 0 };
	int parseNull = 0;
	int parseNullNext = 0;
	int count = 0;
	int countNext = 0;
	int choice = 0;
	int listLength = 0;

	do {
		printf("Sort by: (1) Artist, (2) Album, (3) Rating, (4) Plays\n");
		scanf("%d", &choice);
	} while (choice < 1 || choice > 4);

	Node *nextPtr = NULL;
	Node *pCur = *playList;
	while (pCur != NULL) {
		pCur = pCur->next;
		listLength++;
	}

	/*Array of pointers to structs for sorting.*/
	Node **excuse = malloc(sizeof(Node *) * listLength);
	pCur = *playList;
	int iterate = 0;
	while (pCur != NULL) {
		excuse[iterate] = pCur;
		iterate++;
		pCur = pCur->next;
	}

	Node *temp = NULL;

	switch (choice) {
	case 1:
		/*Sorts by artist*/
		for (int i = 0; i < listLength; i++) {
			for (int j = 0; j < listLength - i - 1; j++) {
				if (compareString(excuse[j]->data.artist, excuse[j + 1]->data.artist) == 1) {
					temp = excuse[j];
					excuse[j] = excuse[j + 1];
					excuse[j + 1] = temp;
				}
			}
		}
		break;
	case 2:
		/*Sort by album.*/
		for (int i = 0; i < listLength; i++) {
			for (int j = 0; j < listLength - i - 1; j++) {
				if (compareString(excuse[j]->data.album, excuse[j + 1]->data.album) == 1) {
					temp = excuse[j];
					excuse[j] = excuse[j + 1];
					excuse[j + 1] = temp;
				}
			}
		}
		break;
	case 3:
		/*Sort by rating.*/
		for (int i = 0; i < listLength; i++) {
			for (int j = 0; j < listLength - i - 1; j++) {
				if (excuse[j]->data.rating > excuse[j + 1]->data.rating) {
					temp = excuse[j];
					excuse[j] = excuse[j + 1];
					excuse[j + 1] = temp;
				}
			}
		}
		break;
	case 4:
		/*Sort by plays.*/
		for (int i = 0; i < listLength; i++) {
			for (int j = 0; j < listLength - i - 1; j++) {
				if (excuse[j]->data.plays > excuse[j + 1]->data.plays) {
					temp = excuse[j];
					excuse[j] = excuse[j + 1];
					excuse[j + 1] = temp;
				}
			}
		}
		break;
	}
	excuse[0]->prev = NULL;
	excuse[0]->next = excuse[1];
	*playList = excuse[0];
	int link = 0;

	/*Sets the pointers in the array to their respective node in the list.*/
	for (link = 1; link < listLength - 1; link++) {
		excuse[link]->prev = excuse[link - 1];
		excuse[link]->next = excuse[link + 1];
		printf("%s <- %s\n", excuse[link - 1]->data.artist, excuse[link]->data.artist);
		printf("%s -> %s\n", excuse[link]->data.artist, excuse[link + 1]->data.artist);
	}
	excuse[link]->prev = excuse[link];
	excuse[link]->next = NULL;

	printList(playList);
	free(excuse);
	printf("\n");
}

/*Used for bubble sorting strings in sortNode()*/
int compareString(char *cur, char *next) {
	char newCur[MAX] = { 0 };
	char newNext[MAX] = { 0 };
	if (cur[0] == '\"' && next[0] == '\"') {
		return strcmp(cur, next);
	}
	else if (cur[0] == '\"') {
		for (int index = 1; cur[index] != '\"'; index++) 
			newCur[index - 1] = cur[index];

		return strcmp(newCur, next);
	}
	else if (next[0] == '\"') {
		for (int index = 1; next[index] != '\"'; index++)
				newNext[index - 1] = next[index];

		return strcmp(cur, newNext);
	}
	else {
		return strcmp(cur, next);
	}
}

/*Shuffles the songs in the node.*/
void shuffle(Node **playList) {

	int size = 0;
	int count = 0;
	int iterate = 0;
	int success = 0;
	int index = 0;
	Node *currentPtr = *playList;

	while (currentPtr != NULL) {
		size++;
		currentPtr = currentPtr->next;
	}

	/*Stores previous plays into integer array.*/
	int *tally = malloc(sizeof(int) * size);

	/*Determines which song to play based on previous listens.*/
	while (count < size) {
		currentPtr = *playList;
		while (TRUE) {
			success = 0;
			iterate = rand() % size;
			for (index = 0; index <= count; index++) {
				if (iterate == tally[index]) {
					success = 0;
					break;
				}
				success = 1;
			}
			if (success = 1)
				break;
		}
		index = 0;

		/*Plays the song.*/
		while (currentPtr != NULL) {
			if (index == iterate) {
				system("cls");
				printf("Song: %s\n", currentPtr->data.song);
				printf("Artist: %s\n", currentPtr->data.artist);
				printf("Album: %d\n", currentPtr->data.plays);
				printf("Length: %d:%d\n", currentPtr->data.time.minutes, currentPtr->data.time.seconds);
				currentPtr->data.plays++;
				time_t change = time(NULL) + 4;
				while (change >= time(NULL));
				fflush(stdout);
				index++;
				break;
			}
			currentPtr = currentPtr->next;
			index++;
		}
		count++;
	}
	/*Frees int array.*/
	free(tally);
}

