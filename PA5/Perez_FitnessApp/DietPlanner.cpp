/*Name: Edgar Perez*/
/*PA 5: FitnessApp*/
/*Collaborators: Elliott Villars, Shusanta Bhatari*/
#include "DietPlanner.h"

// Constructor for DietPlanner object.
DietPlanner::DietPlanner()
{
	goal = 0;
	name = "NULL";
	date = "NULL";
}

// Constructor for DietPlanner object with parameters.
DietPlanner::DietPlanner(int calories, string label, string time)
{
	goal = calories;
	name = label;
	date = time;
}

// Copy constructor for DietPlanner object.
DietPlanner::DietPlanner(DietPlanner &rightDietPlanner)
{
	goal = rightDietPlanner.getGoal();
	name = rightDietPlanner.getName();
	date = rightDietPlanner.getDate();
}

// Deconstructor for DietPlanner.
DietPlanner::~DietPlanner()
{
	cout << "This DietPlanner is gone." << endl;
}

// DietPlanner copy constructor via overloaded operator.
DietPlanner & DietPlanner::operator= (const DietPlanner &rightDietPlanner) 
{
	if (this != &rightDietPlanner)
	{
		goal = rightDietPlanner.getGoal();
		name = rightDietPlanner.getName();
		date = rightDietPlanner.getDate();
	}
	return *this;
}

// DietPlanner getter for int goal.
int DietPlanner::getGoal() const
{
	return goal;
}

// DietPlanner getter for string name.
string DietPlanner::getName() const
{
	return name;
}

// DietPlanner getter for string date.
string DietPlanner::getDate() const
{
	return date;
}

// DietPlanner setter for goal.
bool DietPlanner::setGoal(int calories)
{
	return (goal = calories) == calories ? true : false;
}

// DietPlanner setter for name.
bool DietPlanner::setName(string label)
{
	return (name = label) == label ? true : false;
}

// DietPlanner setter for date.
bool DietPlanner::setDate(string time)
{
	return (date = time) == time ? true : false;
}

// Edits the goal of a DietPlanner object.
bool DietPlanner::editGoal() 
{
	int newGoal = 0;
	cout << "Enter a new goal:" << endl;
	cin >> newGoal;
	return setGoal(abs(newGoal)) && goal >= 0 ? true : false;
}

// Non-member function that displays DietPlanner object contents to the console.
ostream & operator<<(ostream & out, const DietPlanner & objDietPlan)
{
	return out << "Name: " << objDietPlan.getName() << endl << "Goal: " << objDietPlan.getGoal() << endl << "Date: " << objDietPlan.getDate() << endl;
}

// Non-member function that writes DietPlanner object contents to a file.
ofstream & operator<<(ofstream & outF, const DietPlanner & objDietPlan)
{
	outF << objDietPlan.getName() << endl << objDietPlan.getGoal() << endl << objDietPlan.getDate() << endl << endl;
	return outF;
}

// Non-member function that reads and stores data from a file into a DietPlanner object.
ifstream & operator>>(ifstream & inF, DietPlanner & objDietPlan)
{
	string temp;
	getline(inF, temp);
	objDietPlan.setName(temp);
	int goal = 0;
	inF >> goal;
	objDietPlan.setGoal(goal);
	getline(inF, temp);
	getline(inF, temp);
	objDietPlan.setDate(temp);
	getline(inF, temp);
	return inF;
}