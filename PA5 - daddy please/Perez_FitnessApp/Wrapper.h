/*Late but with COMMENTS!!!*/
/*Name: Edgar Perez*/
/*PA 5: FitnessApp*/
/*Collaborators: Elliott Villars, Shusanta Bhatari*/
#pragma once
#ifndef _Wrapper_H
#define _Wrapper_H
#include "DietPlanner.h"
#include "ExercisePlanner.h"
#include "List.h"

class Wrapper
{
public:
	// Constructor for wrapper.
	Wrapper();
	// Destructor for wrapper.
	~Wrapper();

	// Executes the program.
	void runApp();

private:
	// Loads one DietPlanner object from a file.
	void loadDailyPlan(ifstream& fileStream, DietPlanner& plan);

	// Loads one ExercisePlanner object from a file.
	void loadDailyPlan(ifstream& fileStream, ExercisePlanner& plan);

	// Loads a weeks worth of DietPlanners from a file.
	void loadWeeklyPlan(ifstream& fileStream, List<DietPlanner>& list);

	// Loads a weeks worth of ExercisePlanners from a file.
	void loadWeeklyPlan(ifstream& fileStream, List<ExercisePlanner>& list);

	// Displays one DietPlanner object from a list.
	void displayDailyPlan(ostream& consoleStream, const DietPlanner& plan);

	// Displays one ExercisePlanner object from a list.
	void displayDailyPlan(ostream& consoleStream, const ExercisePlanner& plan);

	// Displays a weeks worth of DietPlanners from a list.
	void displayWeeklyPlan(ostream& consoleStream, const List<DietPlanner>& list);

	// Display a weeks worth of ExercisePlanners from a list.
	void displayWeeklyPlan(ostream& consoleStream, const List<ExercisePlanner>& list);

	// Stores one DietPlanner object into a file.
	void storeDailyPlan(ofstream& fileStream, DietPlanner& plan);

	// Stores one ExercisePlanner object into a file.
	void storeDailyPlan(ofstream& fileStream, ExercisePlanner& plan);

	// Stores a weeks worth of DietPlanners into a file.
	void storeWeeklyPlan(ofstream& fileStream, List<DietPlanner>& list);

	// Stores a weeks worth of ExercisePlanners into a file.
	void storeWeeklyPlan(ofstream& fileStream, List<ExercisePlanner>& list);

	// Allows the user to edit a DietPlanner object.
	void editDailyPlan(ostream& consoleStream, List<DietPlanner>& list);

	// Allows the user to edit an ExercisePlanner object.
	void editDailyPlan(ostream& consoleStream, List<ExercisePlanner>& list);

	// Switch statement that determines which function from Wrapper to call.
	void features(int choice);

	// Lists of DietPlanner and ExercisePlanner objects.
	List<DietPlanner> diet;
	List<ExercisePlanner> exercise;
};

#endif