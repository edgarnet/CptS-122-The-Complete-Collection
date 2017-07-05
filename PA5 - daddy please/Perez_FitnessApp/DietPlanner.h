/*Name: Edgar Perez*/
/*PA 5: FitnessApp*/
/*Collaborators: Elliott Villars, Shusanta Bhatari*/
#pragma once
#ifndef  _DietPlanner_H
#define _DietPlanner_H
#include <iostream>
#include <fstream>
#include <string>
//Just incase:
#include <stdlib.h>

// Namespaces for input/output.
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::ofstream;
using std::ifstream;
using std::getline;

class DietPlanner
{
public:
	// Constructor for DietPlanner object.
	DietPlanner();
	// Constructor for DietPlanner object with parameters.
	DietPlanner(int calories, string label, string time);
	// Copy constructor for DietPlanner object.
	DietPlanner(DietPlanner &rightDietPlanner);
	// Deconstructor for DietPlanner.
	~DietPlanner();
	// DietPlanner copy constructor via overloaded operator.
	DietPlanner & operator= (const DietPlanner &rightDietPlanner);
	// DietPlanner getter for int goal.
	int getGoal() const;
	// DietPlanner getter for string name.
	string getName() const;
	// DietPlanner getter for string date.
	string getDate() const;
	// DietPlanner setter for goal.
	bool setGoal(int calories);
	// DietPlanner setter for name.
	bool setName(string label);
	// DietPlanner setter for date.
	bool setDate(string time);
	// Edits the goal of a DietPlanner object.
	bool editGoal();

	//Data members of the DietPlanner class.
private:
	int goal;
	string name;
	string date;
};

// Non-member function that displays DietPlanner object contents to the console.
ostream& operator<<(ostream& out, const DietPlanner& objDietPlan);

// Non-member function that writes DietPlanner object contents to a file.
ofstream& operator<<(ofstream& outF, const DietPlanner& objDietPlan);

// Non-member function that reads and stores data from a file into a DietPlanner object.
ifstream& operator>>(ifstream& inF, DietPlanner& objDietPlan);

#endif