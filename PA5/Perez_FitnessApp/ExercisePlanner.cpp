/*Name: Edgar Perez*/
/*PA 5: FitnessApp*/
/*Collaborators: Elliott Villars, Shusanta Bhatari*/
#include "ExercisePlanner.h"

// Constructor for ExercisePlanner object.
ExercisePlanner::ExercisePlanner()
{
	goal = 0;
	name = "NULL";
	date = "NULL";
}

// Constructor for ExercisePlanner object with parameters.
ExercisePlanner::ExercisePlanner(int calories, string label, string time)
{
	goal = calories;
	name = label;
	date = time;
}

// Copy constructor for ExercisePlanner object.
ExercisePlanner::ExercisePlanner(ExercisePlanner & rightExcercisePlanner)
{
	goal = rightExcercisePlanner.getGoal();
	name = rightExcercisePlanner.getName();
	date = rightExcercisePlanner.getDate();
}

// Deconstructor for ExercisePlanner.
ExercisePlanner::~ExercisePlanner()
{
	cout << "This ExercisePlanner is gone." << endl;
}

// ExercisePlanner copy constructor via overloaded operator.
ExercisePlanner & ExercisePlanner::operator=(const ExercisePlanner & rightExercisePlanner)
{
	if (this != &rightExercisePlanner)
	{
		goal = rightExercisePlanner.getGoal();
		name = rightExercisePlanner.getName();
		date = rightExercisePlanner.getDate();
	}
	return *this;
}

// ExercisePlanner getter for int goal.
int ExercisePlanner::getGoal() const
{
	return goal;
}

// ExercisePlanner getter for string name.
string ExercisePlanner::getName() const
{
	return name;
}

// ExercisePlanner getter for string date.
string ExercisePlanner::getDate() const
{
	return date;
}

// ExercisePlanner setter for goal.
bool ExercisePlanner::setGoal(int calories)
{
	return (goal = calories) == calories ? true : false;
}

// ExercisePlanner setter for name.
bool ExercisePlanner::setName(string label)
{
	return (name = label) == label ? true : false;
}

// ExercisePlanner setter for date.
bool ExercisePlanner::setDate(string time)
{
	return (date = time) == time ? true : false;
}

// Edits the goal of a ExercisePlanner object.
bool ExercisePlanner::editGoal()
{
	int newGoal = 0;
	cout << "Enter a new goal:" << endl;
	cin >> newGoal;
	return setGoal(abs(newGoal)) && goal >= 0 ? true : false;
}

// Non-member function that displays ExercisePlanner object contents to the console.
ostream & operator<<(ostream & out, const ExercisePlanner & objExercisePlan)
{
	return out << "Name: " << objExercisePlan.getName() << endl << "Goal: " << objExercisePlan.getGoal() << endl << "Date: " << objExercisePlan.getDate() << endl;
}

// Non-member function that writes ExercisePlanner object contents to a file.
ofstream & operator<<(ofstream & outF, const ExercisePlanner & objExercisePlan)
{
	outF << objExercisePlan.getName() << endl << objExercisePlan.getGoal() << endl << objExercisePlan.getDate() << endl << endl;
	return outF;
}

// Non-member function that reads and stores data from a file into a ExercisePlanner object.
ifstream & operator >> (ifstream & inF, ExercisePlanner & objExercisePlan)
{
	string temp;
	getline(inF, temp);
	objExercisePlan.setName(temp);
	int goal = 0;
	inF >> goal;
	objExercisePlan.setGoal(goal);
	getline(inF, temp);
	getline(inF, temp);
	objExercisePlan.setDate(temp);
	getline(inF, temp);
	return inF;
}
