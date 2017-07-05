/*Name: Edgar Perez*/
/*PA 5: FitnessApp*/
/*Collaborators: Elliott Villars, Shusanta Bhatari*/
#pragma once
#include "DietPlanner.h"
#ifndef _ExercisePlanner_H
#define _ExercisePlanner_H

class ExercisePlanner
{
public:
	// Constructor for ExercisePlanner object.
	ExercisePlanner();
	// Constructor for ExercisePlanner object with parameters.
	ExercisePlanner(int calories, string label, string time);
	// Copy constructor for ExercisePlanner object.
	ExercisePlanner(ExercisePlanner &rightExcercisePlanner);
	// Deconstructor for ExercisePlanner.
	~ExercisePlanner();
	// ExercisePlanner copy constructor via overloaded operator.
	ExercisePlanner & operator= (const ExercisePlanner &rightExercisePlanner);
	// ExercisePlanner getter for int goal.
	int getGoal() const;
	// ExercisePlanner getter for string name.
	string getName() const;
	// ExercisePlanner getter for string date.
	string getDate() const;
	// ExercisePlanner setter for goal.
	bool setGoal(int calories);
	// ExercisePlanner setter for name.
	bool setName(string label);
	// ExercisePlanner setter for date.
	bool setDate(string time);
	// Edits the goal of a ExercisePlanner object.
	bool editGoal();

	//Data members of the ExercisePlanner class.
private:
	int goal;
	string name;
	string date;
};

// Non-member function that displays ExercisePlanner object contents to the console.
ostream & operator<<(ostream & out, const ExercisePlanner& objExercisePlan);

// Non-member function that writes ExercisePlanner object contents to a file.
ofstream& operator<<(ofstream& outF, const ExercisePlanner& objExercisePlan);

// Non-member function that reads and stores data from a file into a ExercisePlanner object.
ifstream& operator >> (ifstream& inF, ExercisePlanner& objExercisePlan);

#endif