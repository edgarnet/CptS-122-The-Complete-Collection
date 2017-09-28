/*
* =====================================================================================
*
*       Filename:  FitBit.h
*
*    Description:  This is the header file for the program.
*
*        Version:  1.0
*        Created:  1/14/2017 9:16:07 PM
*       Revision:  none
*       Compiler:  msft c
*
*         Author:  Edgar Perez
*   Organization:  Washington State University
*
* =====================================================================================
*/

#ifndef	_FitBit_H
#define	_FitBit_H

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<math.h>

#define		BUFFER	1000
#define		COLUMNS 7
#define		HOURS	1441

typedef enum sleep
{
	NONE, ASLEEP, AWAKE, REALLYAWAKE
} Sleep;

typedef struct fitbit
{
	char minute[9];
	double calories;
	double distance;
	unsigned int floors;
	unsigned int heartRate;
	unsigned int steps;
	Sleep sleepLevel;
} FitbitData;

/*************************************************************
* Function: dataCollect()
* Description: Retrieves data from a .csv that includes
* 	       information from a Fitbit device, which is then
* 	       stored accordingly into an array of structs.
* Input parameters: .csv file and array of FitbitData structs.
* Returns: VOID
* Preconditions: The .csv file must be formatted properly to
* 		 allow the function to store data successfully
* 		 in each struct.
* Postconditions: Each element in the struct array must
* 		  incorporate the file's data accordingly.
*************************************************************/
void dataCollect(FILE* dataset, FitbitData *record[]);

/*Comment*/
char *stringSet(char *string);

/*************************************************************
* Function: totalCalories()
* Description: Determines the total number of calories burned
* 	       in a 24-hour period.
* Input parameters: Array of FitbitData structs.
* Returns: Double - total number of calories burned.
* Preconditions: The array of FitbitData structs must include
* 		 data necessary for analysis.
* Postconditions: The total calories burned should be returned.
*************************************************************/
double totalCalories(FitbitData *record[]);

/*************************************************************
* Function: totalDistance()
* Description: Determies the total distance traveled in a
* 	       24-hour period.
* Input parameters: Array of FitbitData structs.
* Returns: Double - total distance traveled.
* Preconditions: The array of FitbitData structs must include
* 		 data necessary for analysis.
* Postconditions: The total distance traveled should be returned.
*************************************************************/
double totalDistance(FitbitData *record[]);

/*************************************************************
* Function: totalFloors()
* Description: Determines the total floors climed in a 24-hour
* 	       period.
* Input parameters: Array of FirbitData structs.
* Returns: Integer - total floors climed.
* Preconditions: The array of FitbitData structs must include
* 		 data necessary for analysis.
* Postconditions: The total floors climed should be returned.
*************************************************************/
int totalFloors(FitbitData *record[]);

/*************************************************************
* Function: totalSteps()
* Description: Determines the total steps walked in a 24-hour
*              period.
* Input parameters: Array of FitbitData structs.
* Returns: Integer - total steps walked.
* Preconditions: The array of FitbitData structs must include
* 		 data necessary for analysis.
* Postconditions: The total steps walked should be returned.
*************************************************************/
int totalSteps(FitbitData *record[]);

/*************************************************************
* Function: maxSteps()
* Description: Determines the maximum amount of steps walked
* 	       under a minute.
* Input parameters: Array of FitbitData structs.
* Returns: Integer - max steps in one minute.
* Preconditions: The array of FitbitData structs must include
* 		 data necessary for analysis.
* Postconditions: The max steps in one minute should be returned.
*************************************************************/
int maxSteps(FitbitData *record[]);

/*************************************************************
* Function: averageHR()
* Description: Determines the average heart rate over a span
* 	       of 24 hours.
* Input parameters: Array of FitbitData structs.
* Returns: Double - average heart rate throughout one day.
* Preconditions: The array of FitbitData structs must include
* 		 data necessary for analysis.
* Postconditions: The average heart rate in a 24-hour period
* 		  should be returned.
*************************************************************/
double averageHR(FitbitData *record[]);

/*************************************************************
* Function: sleepRange()
* Description: Determines the longest range of poor sleep.
* Input parameters: Char Arrays for start-time and end-time.
* Returns: VOID
* Preconditions: The array of FitbitData structs must include
* 		 data necessary for analysis, as well as the
* 		 char arrays being mutable when passed in.
* Postconditions: The start and end time are stored in their
* 		  respective strings.
*************************************************************/
void sleepRange(char *startTime, char *endTime, FitbitData *record[]);

/*************************************************************
* Function: runApp()
* Description: Performs all necessary tasks for the program
* 	       to execute.
* Input parameters: NONE
* Returns: VOID
* Preconditions: NONE
* Postconditions: NONE
*************************************************************/
void runApp(void);

#endif