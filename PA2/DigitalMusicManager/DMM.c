/*
 * =====================================================================================
 *
 *       Filename:  DMM.c
 *
 *    Description:  This contains the function definitions for the DMM program.
 *
 *        Version:  1.0
 *        Created:  1/25/2017 7:31:05 PM
 *       Revision:  none
 *       Compiler:  msft c
 *
 *         Author:  Edgar Perez (eap), edgar.a.perez@wsu.edu
 *   Organization:  Washington State University
 *
 * =====================================================================================
 */

#include	"DMM.h"

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

/*Returns address for a new node.*/
Song *makeNode(void) {
	return (malloc(sizeof(Song)));
}

/*Inserts new node at the top of the linked list.
Not implemented due to inconsistency with established framework.*/
Bool insertFront(Song **pHead) {

	if (!*pHead) {
		*pHead = makeNode();
		(*pHead)->before = NULL;
		return TRUE;
	}
	else {
		(*pHead)->before = makeNode();
		(*pHead)->before->after = *pHead;
		(*pHead)->before->before = NULL;
		return TRUE;
	}
	return FALSE;

}

/*Prints the contents of the linked list. Used for debug only!*/
void printList(Song **pHead) {

	Song *pNow = *pHead;
	int count = 0;
	while (pNow) {
		printf("Node: %d\n%s\n%s\n%s\n%s\n%d\n%d\n%d\n%d\n%d\n%d\n",
			count++, pNow->artist, pNow->album, pNow->song, pNow->genre,
			pNow->time.minutes, pNow->time.seconds, pNow->plays, pNow->rating,
			pNow->before, pNow->after);
		pNow = pNow->after;
	}

}

/*Postcondition: The linked list contains data from the file.*/
Song **load(FILE *library) {

	char input[1000] = { 0 };
	char *track = NULL;
	char *token = NULL;
	/*Node which can be manipulated.*/
	Song *playlist = NULL;
	/*Node which stores the first link.*/
	Song **firstPlaylist = malloc(sizeof(Song *));
	*firstPlaylist = makeNode();
	(*firstPlaylist)->before = NULL;
	playlist = *firstPlaylist;

	/*If the .csv could not be opended.*/
	if (!library) {
		printf("Your music library could not be loaded.");
		return NULL;
	}

	//rewind(library);

	/*Stores the data from .csv into the linked list*/
	while(fgets(input, sizeof(input), library) != NULL) {

		/*Sets all fields of each node to NULL.*/
		for (int index = 0; index < MAX; index++) {
			playlist->artist[index] = 0;
			playlist->album[index] = 0;
			playlist->song[index] = 0;
			playlist->genre[index] = 0;
		}
		playlist->time.minutes = 0;
		playlist->time.seconds = 0;
		playlist->plays = 0;
		playlist->rating = 0;

		track = &(input[0]);
		char buffer[MAX] = { 0 };

		/*Separates values from fgets() to their respective field in each node.*/
		token = strsep(&track, ",");
		if (token == NULL)
			strcpy(playlist->artist, "Unknown Artist");
		else if (token[0] == '\"') {
			strcpy(buffer, token);
			buffer[strlen(token)] = ',';
			strcat(buffer, strsep(&track, ","));
			strcpy(playlist->artist, buffer);
		}
		else
			strcpy(playlist->artist, token);
		token = strsep(&track, ",");
		if (token == NULL)
		 	strcpy(playlist->album, "Unknown Album");
		else
			strcpy(playlist->album, token);
		token = strsep(&track, ",");
		if (token == NULL)
			strcpy(playlist->song, "Untitled");
		else
			strcpy(playlist->song, token);
		token = strsep(&track, ",");
		if (token == NULL)
			strcpy(playlist->genre, "Unknown");
		else
			strcpy(playlist->genre, token);
		token = strsep(&track, ":");
		if (token == NULL)
			playlist->time.minutes = 0;
		else
			playlist->time.minutes = atoi(token);
		token = strsep(&track, ",");
		if (token == NULL)
			playlist->time.seconds = 0;
		else
			playlist->time.seconds = atoi(token);
		token = strsep(&track, ",");
		if (token == NULL)
			playlist->plays = 0;
		else
			playlist->plays = atoi(token);
		token = strsep(&track, ",");
		if (token == NULL)
			playlist->rating = 0;
		else
			playlist->rating = atoi(token);

		playlist->after = makeNode();
		playlist->after->before = playlist;
		playlist = playlist->after;

	}

	/*Frees the last node and returns the head of the list.*/
	playlist->before->after = NULL;
	free(playlist);
	if (playlist)
		printf("Your music has been successfully loaded!\n");
	else
		printf("Load was unsuccessful.\n");
	return firstPlaylist;

}

/*Displays all song or those of a certain artist.*/
Bool displayAll(Song **playlist) {

	/*Checks if list was loaded.*/
	if (!playlist) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	system("cls");
	char rating[MAX] = { 0 };
	char choice[MIN] = { 0 };
	int option = 0;

	/*User determines what to print to the screen.*/
	do {
		printf("Would you like to display all records or those by an artist?\n");
		printf("Enter '1' for All or '2' for Artist\n");
		scanf("%s", choice);
		option = atoi(choice);
	} while (option != 1 && option != 2);
	if (option == 2)
		return displayArtist(playlist);

	/*Prints all records for each song.*/
	printf("Artist                    |Album                    |Song                     |Genre     |Duration  |Plays    |Rating    \n");
	int count = 0;
	Song *currentPlaylist = *playlist;
	while (currentPlaylist != NULL) {
		for (count = 0; count < currentPlaylist->rating; count++)
		       rating[count] = '*';
		count = 0;
		printf("|%-25s|%-25s|%-25s|%-10s| %d:%d     |%-9d|%s \n",
				currentPlaylist->artist, currentPlaylist->album, currentPlaylist->song, currentPlaylist->genre,
				currentPlaylist->time.minutes, currentPlaylist->time.seconds, currentPlaylist->plays, rating);
		currentPlaylist = currentPlaylist->after;
		while (rating[count]) {
			rating[count] = 0;
			count++;
		}
	}
	return TRUE;

}

/*Coupled with displayAll().*/
Bool displayArtist(Song **playlist) {

	if (!playlist) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	/*Asks the User for which artist to print.*/
	system("cls");
	int track = 0;
	char artist[MAX] = { 0 };
	char rating[MAX] = { 0 };
	Song *currentPlaylist = *playlist;
	printf("Please type below the artist you're looking for:\nIf the artist has two names, enter as: \"Last, First\"\n");
	getchar();
	fgets(artist, sizeof(artist), stdin);
	strcpy(artist, strtok(artist, "\n"));

	/*Prints artist info.*/
	system("cls");
	printf("%s's Records:\n", artist);
	printf("Album                    |Song                     |Genre     |Duration  |Plays    |Rating    \n");
	int count = 0;
	while (currentPlaylist != NULL) {
		if (strcmp(currentPlaylist->artist, artist) == 0) {
			for (count = 0; count < currentPlaylist->rating; count++)
				rating[count] = '*';
			printf("%-25s|%-25s|%-10s| %d:%d     |%-9d|%s \n",
				currentPlaylist->album, currentPlaylist->song, currentPlaylist->genre,
				currentPlaylist->time.minutes, currentPlaylist->time.seconds, currentPlaylist->plays, rating);
			track++;
			count = 0;
			while (rating[count]) {
				rating[count] = 0;
				count++;
			}
		}
		currentPlaylist = currentPlaylist->after;
	}

	/*Returns 0 if no records were found for that artist.*/
	if (track < 1) {
		system("cls");
		printf("We could not find records for %s in your library\n", artist);
		return FALSE;
	}
	return TRUE;

}

/*Allows User to edit information for a song.*/
Bool edit(Song **playlist) {

	if (!playlist) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	char song[MAX] = { 0 };
	char newAlbum[MAX] = { 0 };
	char newArtist[MAX] = { 0 };
	char newSong[MAX] = { 0 };
	char newGenre[MAX] = { 0 };
	int rating = 0;
	Song *currentPlaylist = *playlist;
	int choice = MIN;
	
	/*Returns false if an artist could not be found. Prints songs if successful.*/
	if (displayArtist(playlist) == FALSE)
		return FALSE;
	else {
		printf("\nType in which song you would like to edit:\n");
		fgets(song, sizeof(song), stdin);
		strcpy(song, strtok(song, "\n"));
		currentPlaylist = *playlist;
		while (currentPlaylist != NULL) {
			if(strcmp(currentPlaylist->song, song) == 0) {
				do {
					printf("Change: (1) Artist, (2) Album, (3) Song, (4) Genre, (0) Exit\n");
					scanf("%d", &choice);
					switch (choice) {
					/*Edits artist name.*/	
					case 1:
						printf("Enter the artist's name:\n");
						getchar();
						fgets(newArtist, sizeof(newArtist), stdin);
						strcpy(newArtist, strtok(newArtist, "\n"));
						strcpy(currentPlaylist->artist, newArtist);
						system("cls");
						break;
					/*Edits album name.*/
					case 2:
						printf("Enter the album name:\n");
						getchar();
						fgets(newAlbum, sizeof(newAlbum), stdin);
						strcpy(newAlbum, strtok(newAlbum, "\n"));
						strcpy(currentPlaylist->album, newAlbum);
						system("cls");
						break;
					/*Edits song title.*/
					case 3:
						printf("Enter the song title:\n");
						getchar();
						fgets(newSong, sizeof(newSong), stdin);
						strcpy(newSong, strtok(newSong, "\n"));
						strcpy(currentPlaylist->song, newSong);
						system("cls");
						break;
					/*Edits genre title.*/
					case 4:
						printf("Enter the genre:\n");
						getchar();
						fgets(newGenre, sizeof(newGenre), stdin);
						strcpy(newGenre, strtok(newGenre, "\n"));
						strcpy(currentPlaylist->genre, newGenre);
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

			currentPlaylist = currentPlaylist->after;
		}
	}
	return TRUE;

}

/*Allows the user to rate a song.*/
Bool rate(Song **playlist) {

	if (!playlist) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	char rateSong[MAX] = { 0 };
	int rating = 0;

	/*Asks the User which song they would like to rate.*/
	if (displayArtist(playlist) == FALSE)
		return FALSE;
	Song *currentPlaylist = *playlist;
	printf("\nType in which song you would like to edit:\n");
	fgets(rateSong, sizeof(rateSong), stdin);
	strcpy(rateSong, strtok(rateSong, "\n"));
	while (currentPlaylist != NULL) {
		if (strcmp(currentPlaylist->song, rateSong) == 0) {
			do {
				printf("Enter the rating (1-5):\n");
				scanf("%d", &rating);
			} while (rating < 1 || rating > 5);
			currentPlaylist->rating = rating;
			system("cls");
			return TRUE;
		}
		currentPlaylist = currentPlaylist->after;
	}
	return FALSE;

}

/*Prints each song for a short period of time.*/
void play(Song **playlist) {

	if (!playlist) {
		printf("Your music has not been loaded.\n");
		return;
	}

	/*Prints the first song.*/
	system("cls");
	Song *currentPlaylist = *playlist;
	printf("Song: %s\n", currentPlaylist->song);
	printf("Artist: %s\n", currentPlaylist->artist);
	printf("Album: %d\n", currentPlaylist->plays);
	currentPlaylist->plays++;
	printf("Length: %d:%d\n", currentPlaylist->time.minutes, currentPlaylist->time.seconds);
	currentPlaylist = currentPlaylist->after;

	/*Prints the remaining songs for ~4 seconds each.*/
	while (currentPlaylist != NULL) {
		time_t change = time(NULL) + 4;
		while (change >= time(NULL));
		system("cls");
		printf("Song: %s\n", currentPlaylist->song);
		printf("Artist: %s\n", currentPlaylist->artist);
		printf("Album: %s\n", currentPlaylist->album);
		currentPlaylist->plays++;
		printf("Length: %d:%d\n", currentPlaylist->time.minutes, currentPlaylist->time.seconds);
		fflush(stdout);
		currentPlaylist = currentPlaylist->after;
	}
	printf("\n");

}

/*Stores the data from the list into the .csv file.*/
Bool store(Song **playlist, FILE *input, int option) {

	if (!input) {
		printf("Could not open file!\n");
		return FALSE;
	}

	if (!playlist) {
		printf("Your music has not been loaded.\n");
		return FALSE;
	}

	fclose(input);
	input = fopen("newPlayList.csv", "w");

	/*Prints the data from list into file.*/
	if (option == EXIT) {
		while (*playlist != NULL) {
			fprintf(input, "%s,%s,%s,%s,%d:%d,%d,%d\n", (*playlist)->artist, (*playlist)->album,
				(*playlist)->song, (*playlist)->genre, (*playlist)->time.minutes, (*playlist)->time.seconds,
				(*playlist)->plays, (*playlist)->rating);
			*playlist = (*playlist)->after;
			if (*playlist)
				free((*playlist)->before);
		}
	}
	Song *currentPlaylist = *playlist;
	if (option != EXIT) {
		while (currentPlaylist != NULL) {
			fprintf(input, "%s,%s,%s,%s,%d:%d,%d,%d\n", (*playlist)->artist, (*playlist)->album,
				(*playlist)->song, (*playlist)->genre, (*playlist)->time.minutes, (*playlist)->time.seconds,
				(*playlist)->plays, (*playlist)->rating);
			currentPlaylist = currentPlaylist->after;
		}
	}

	fclose(input);
	input = fopen("newPlayList.csv", "r");

	/*Frees everything.*/
	if (option == EXIT) {
		free(*playlist);
		free(playlist);
		fclose(input);
		exit(0);
	}
}

/*Executes program.*/
void runApp(void) {

	/*Opens .csv file*/
	FILE *input = fopen("newPlayList.csv", "r");
	FILE *start = input;
	if (!input) {
		printf("Unable to open file!\n");
		return;
	}
	
	Song **playlist = NULL;
	char choice[MIN] = { 0 };
	int option = 0;

	//printList(playlist);

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
			playlist = load(input);
			break;
		case 2:
			store(playlist, input, option);
			break;
		case 3:
			displayAll(playlist);
			break;
		case 6:
			edit(playlist);
			break;
		case 8:
			rate(playlist);
			break;
		case 9:
			play(playlist);
			break;
		case 11:
			store(playlist, input, option);
			break;
		default:
			break;
		}

	} while (option > 0 || option < 12);
}