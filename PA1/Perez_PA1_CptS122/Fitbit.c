/*
* =====================================================================================
*
*       Filename:  FitBit.c
*
*    Description:  This is the source file for the program.
*
*        Version:  1.0
*        Created:  1/14/2017 9:16:54 PM
*       Revision:  none
*       Compiler:  msft c
*
*         Author:  Edgar Perez
*   Organization:  Washington State University
*
* =====================================================================================
*/

#include	"FitBit.h"


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
void dataCollect(FILE* dataset, FitbitData *record[]) {
	char input[BUFFER];
	int firstRow = 0;
	char *datum = NULL;
	while (fgets(input, sizeof(input), dataset) != NULL) {
		if (firstRow < 1) {
			datum = strtok(input, ",");
			datum = strtok(NULL, ",");
			datum = strtok(NULL, ",");
			datum = strtok(NULL, ",");
			datum = strtok(NULL, ",");
			datum = strtok(NULL, ",");
			datum = strtok(NULL, ",");
			firstRow = 7;
		}
		else {
			stringSet(input);
			datum = strtok(input, ",");
			if (datum == NULL)
				strcpy(record[firstRow - COLUMNS]->minute, "<empty>");
			else
				strcpy(record[firstRow - COLUMNS]->minute, datum);
			datum = strtok(NULL, ",");
			if (datum == NULL)
				record[firstRow - COLUMNS]->calories = 0.0;
			else
				record[firstRow - COLUMNS]->calories = atof(datum);
			datum = strtok(NULL, ",");
			if (datum == NULL)
				record[firstRow - COLUMNS]->distance = 0.0;
			else
				record[firstRow - COLUMNS]->distance = atof(datum);
			datum = strtok(NULL, ",");
			if (datum == NULL)
				record[firstRow - COLUMNS]->floors = 0;
			else
				record[firstRow - COLUMNS]->floors = atoi(datum);
			datum = strtok(NULL, ",");
			if (datum == NULL)
				record[firstRow - COLUMNS]->heartRate = 0;
			else
				record[firstRow - COLUMNS]->heartRate = atoi(datum);
			datum = strtok(NULL, ",");
			if (datum == NULL)
				record[firstRow - COLUMNS]->steps = 0;
			else
				record[firstRow - COLUMNS]->steps = atoi(datum);
			datum = strtok(NULL, ",");
			if (datum == NULL)
				record[firstRow - COLUMNS]->sleepLevel = 0;
			else
				record[firstRow - COLUMNS]->sleepLevel = atoi(datum);
		}
		firstRow++;
	}
}


char *stringSet(char *string) {
	char temp[100] = { 0 };
	for (int count = 0; string[count] != 0; count++) {
		if (string[count] == ',' && string[count + 1] == ',') {
			for (int size = 0; string[count + size + 1] != 0; size++)
				temp[size] = string[count + size + 1];
			string[count + 1] = '0';
			for (int length = 0; temp[length] != 0; length++)
				string[count + 2 + length] = temp[length];
		}
	}
	return string;
}


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
double totalCalories(FitbitData *record[]) {
	double sum = 0;
	int index = 0;
	for (; index < HOURS; index++)
		sum += record[index]->calories;
	return sum;
}


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
double totalDistance(FitbitData *record[]) {
	double sum = 0;
	int index = 0;
	for (; index < HOURS; index++)
		sum += record[index]->distance;
	return sum;
}


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
int totalFloors(FitbitData *record[]) {
	int sum = 0;
	int index = 0;
	for (; index < HOURS; index++)
		sum += record[index]->floors;
	return sum;
}


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
int totalSteps(FitbitData *record[]) {
	int sum = 0;
	int index = 0;
	for (; index < HOURS; index++)
		sum += record[index]->steps;
	return sum;
}


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
int maxSteps(FitbitData *record[]) {
	int max = 0;
	int index = 0;
	for (; index < HOURS; index++) {
		if (max <= record[index]->steps)
			max = record[index]->steps;
	}
	return max;
}


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
double averageHR(FitbitData *record[]) {
	int sum = 0;
	int index = 0;
	for (; index < HOURS; index++)
		sum += record[index]->heartRate;
	return ((double)sum / (double)index);
}


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
void sleepRange(char *startTime, char *endTime, FitbitData *record[]) {
	int count = 0;
	int max = 0;
	int previousMax = 0;
	int index = 0;
	for (; index < HOURS; index++) {
		if (record[index]->sleepLevel > ASLEEP && count < 1) {
			count = 1;
			max = record[index]->sleepLevel;
		}
		else if (record[index]->sleepLevel > ASLEEP && count > 0) {
			count++;
			max += record[index]->sleepLevel;
		}
		else if (record[index]->sleepLevel <= ASLEEP && count > 0) {
			if (max >= previousMax) {
				previousMax = max;
				strcpy(startTime, record[index - (count + 1)]->minute);
				strcpy(endTime, record[index - 1]->minute);
			}
			max = 0;
			count = 0;
		}
	}
}


/*************************************************************
* Function: runApp()
* Description: Performs all necessary tasks for the program
* 	       to execute.
* Input parameters: NONE
* Returns: VOID
* Preconditions: NONE
* Postconditions: NONE
*************************************************************/
void runApp(void) {
	FitbitData **record = malloc(HOURS * sizeof(FitbitData*));
	for (int index = 0; index < HOURS; index++) {
		record[index] = malloc(sizeof(struct fitbit));
		record[index]->calories = 0;
		record[index]->distance = 0;
		record[index]->floors = 0;
		record[index]->heartRate = 0;
		record[index]->steps = 0;
		record[index]->sleepLevel = NONE;
	}

	FILE *data = fopen("FitbitData_Local.csv", "r");
	if (data == NULL)
		printf("File could not be opened!\n");

	dataCollect(data, record);
	double valueCalories = totalCalories(record);
	double valueDistance = totalDistance(record);
	int valueFloors = totalFloors(record);
	int valueSteps = totalSteps(record);
	double valueHR = averageHR(record);
	int valueMax = maxSteps(record);

	char valueSleepStart[9] = { 0 };
	char valueSleepEnd[9] = { 0 };

	sleepRange(valueSleepStart, valueSleepEnd, record);

	FILE *output = fopen("Results.csv", "w");
	fprintf(output, "Total Calories, Total Distance, Total Floors, Total Steps, Avg Heartrate, Max Steps, Sleep\n");
	fprintf(output, "%lf, %lf, %d, %d, %lf, %d, %s - %s",
		valueCalories, valueDistance, valueFloors, valueSteps, valueHR, valueMax, valueSleepStart, valueSleepEnd);

	for (int count = 0; count < HOURS; count++)
		free(record[count]);
	free(record);

	fclose(data);
	fclose(output);
}