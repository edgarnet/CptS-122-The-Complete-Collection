/*Name: Edgar Perez*/
/*PA 5: FitnessApp*/
/*Collaborators: Elliott Villars, Shusanta Bhatari*/
#include "Wrapper.h"

// Constructor for wrapper.
Wrapper::Wrapper(void)
{
	cout << "FitApp" << endl;
}

// Destructor for wrapper.
Wrapper::~Wrapper()
{
	cout << "It's all over folks!" << endl;
}

// Executes the program.
void Wrapper::runApp()
{
	// Main menu.
	int choice = 0;
	do
	{
		system("cls");
		cout << "Choose an option below" << endl << endl;
		cout << "Press (1) to load weekly diet plan." << endl;
		cout << "Press (2) to load weekly exercise plan" << endl;
		cout << "Press (3) to store weekly diet plan" << endl;
		cout << "Press (4) to store weekly exercise plan" << endl;
		cout << "Press (5) to display weekly diet plan" << endl;
		cout << "Press (6) to display weekly exercise plan" << endl;
		cout << "Press (7) to edit a daily diet plan" << endl;
		cout << "Press (8) to edit a daily exercise plan" << endl;
		cout << "Press (9) to exit" << endl;
		cin >> choice;
		// Switch statement which calls the functions of the Wrapper class.
		features(choice);
	} while (choice != 9);

	// So like I had way too many errors when I declared my streams as private members,
	// which is the reasoning behind the hard coding of of/ifstreams:
	ofstream out;
	out.open("dietPlans.txt");
	if (out.fail())
		cout << "Could Not Open File!" << endl;
	else
		storeWeeklyPlan(out, diet);
	out.close();
	out.open("exercisePlans.txt");
	if (out.fail())
		cout << "Could Not Open File!" << endl;
	else
		storeWeeklyPlan(out, exercise);
	out.close();
}

// Loads one DietPlanner object from a file.
void Wrapper::loadDailyPlan(ifstream& fileStream, DietPlanner& plan)
{
	fileStream >> plan;
}

// Loads one ExercisePlanner object from a file.
void Wrapper::loadDailyPlan(ifstream& fileStream, ExercisePlanner& plan)
{
	fileStream >> plan;
}

// Loads a weeks worth of DietPlanners from a file.
void Wrapper::loadWeeklyPlan(ifstream& fileStream, List<DietPlanner>& list)
{
	DietPlanner storage;
	list.setHeadPtr(storage);
	loadDailyPlan(fileStream, list.getHeadPtr()->getData());
	while(fileStream)
	{
		loadDailyPlan(fileStream, storage);
		if (!storage.getName().empty() && !storage.getName().empty())
			list.insertAtEnd(storage);
	}
}

// Loads a weeks worth of ExercisePlanners from a file.
void Wrapper::loadWeeklyPlan(ifstream& fileStream, List<ExercisePlanner>& list)
{
	ExercisePlanner storage;
	list.setHeadPtr(storage);
	loadDailyPlan(fileStream, list.getHeadPtr()->getData());
	while (fileStream)
	{
		loadDailyPlan(fileStream, storage);
		if (!storage.getName().empty() && !storage.getName().empty())
			list.insertAtEnd(storage);
	}
}

// Displays one DietPlanner object from a list.
void Wrapper::displayDailyPlan(ostream& consoleStream, const DietPlanner& plan)
{
	consoleStream << plan;
}

// Displays one ExercisePlanner object from a list.
void Wrapper::displayDailyPlan(ostream& consoleStream, const ExercisePlanner& plan)
{
	consoleStream << plan;
}

// Displays a weeks worth of DietPlanners from a list.
void Wrapper::displayWeeklyPlan(ostream& consoleStream, const List<DietPlanner>& list)
{
	system("cls");
	for (auto current = list.getHeadPtr(); current != nullptr; current = current->getNextPtr()) {
		displayDailyPlan(consoleStream, current->getData());
		cout << endl;
	}
	system("pause");
}

// Display a weeks worth of ExercisePlanners from a list.
void Wrapper::displayWeeklyPlan(ostream& consoleStream, const List<ExercisePlanner>& list)
{
	system("cls");
	for (auto current = list.getHeadPtr(); current != nullptr; current = current->getNextPtr()) {
		displayDailyPlan(consoleStream, current->getData());
		cout << endl;
	}
	system("pause");
}

// Stores one DietPlanner object into a file.
void Wrapper::storeDailyPlan(ofstream& fileStream, DietPlanner& plan)
{
	fileStream << plan;
}

// Stores one ExercisePlanner object into a file.
void Wrapper::storeDailyPlan(ofstream& fileStream, ExercisePlanner& plan)
{
	fileStream << plan;
}

// Stores a weeks worth of DietPlanners into a file.
void Wrapper::storeWeeklyPlan(ofstream& fileStream, List<DietPlanner>& list)
{
	for (auto current = list.getHeadPtr(); current != nullptr; current = current->getNextPtr())
		storeDailyPlan(fileStream, current->getData());
}

// Stores a weeks worth of ExercisePlanners into a file.
void Wrapper::storeWeeklyPlan(ofstream& fileStream, List<ExercisePlanner>& list)
{
	for (auto current = list.getHeadPtr(); current != nullptr; current = current->getNextPtr())
		storeDailyPlan(fileStream, current->getData());
}

// Allows the user to edit a DietPlanner object.
void Wrapper::editDailyPlan(ostream& consoleStream, List<DietPlanner>& list)
{
	string evaluate;
	cout << "Enter the name of the diet plan you would like to edit:" << endl;
	cin >> evaluate;
	auto current = list.getHeadPtr();
	// Determines which node to edit based on the plan name given by the user.
	for (; current != nullptr && evaluate != current->getData().getName(); current = current->getNextPtr());
	if (current == nullptr)
	{
		cout << "We could not find that plan!" << endl;
		return;
	}
	else
	{
		current->getData().editGoal();
	}
}

// Allows the user to edit an ExercisePlanner object.
void Wrapper::editDailyPlan(ostream& consoleStream, List<ExercisePlanner>& list)
{
	string evaluate;
	cout << "Enter the name of the diet plan you would like to edit." << endl;
	cin >> evaluate;
	auto current = list.getHeadPtr();
	// Determines which node to edit based on the plan name given by the user.
	for (; current != nullptr && evaluate != current->getData().getName(); current = current->getNextPtr());
	if (current == nullptr)
	{
		cout << "We could not find that plan!" << endl;
		return;
	}
	else
	{
		current->getData().editGoal();
	}
}

// Switch statement that determines which function from Wrapper to call.
void Wrapper::features(int choice)
{
	ifstream in;
	ofstream out;
	switch (choice)
	{
	case 1:
		in.open("dietPlans.txt");
		if (in.fail()) {
			cout << "Could Not Open File!" << endl;
			break;
		}
		loadWeeklyPlan(in, diet);
		in.close();
		break;
	case 2:
		in.open("exercisePlans.txt");
		if (in.fail()) {
			cout << "Could Not Open File!" << endl;
			break;
		}
		loadWeeklyPlan(in, exercise);
		in.close();
		break;
	case 3:
		out.open("dietPlans.txt");
		if (out.fail()) {
			cout << "Could Not Open File!" << endl;
			break;
		}
		storeWeeklyPlan(out, diet);
		out.close();
		break;
	case 4:
		out.open("exercisePlans.txt");
		if (out.fail()) {
			cout << "Could Not Open File!" << endl;
			break;
		}
		storeWeeklyPlan(out, exercise);
		out.close();
		break;
	case 5:
		displayWeeklyPlan(cout, diet);
		break;
	case 6:
		displayWeeklyPlan(cout, exercise);
		break;
	case 7:
		editDailyPlan(cout, diet);
		break;
	case 8:
		editDailyPlan(cout, exercise);
		break;
	default:
		break;
	}
}