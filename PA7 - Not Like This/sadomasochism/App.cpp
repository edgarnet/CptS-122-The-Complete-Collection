// Edgar Perez
// PA 7 - Attendance Tracker

#include "App.h"

App::App()
{
}

App::~App()
{
}

void App::runApp()
{
	// For import course list:
	ifstream courseFile;
	courseFile.open("ImportList.csv");

	// For load master list:
	ifstream masterFile;
	masterFile.open("Master.txt");

	ofstream outMaster;

	List<Student> Master;
	List<Student> UpdateMaster;

	bool import = false;
	bool load = false;
	bool update = false;
	bool mark = false;

	int input = 0;

	// Main menu and respective "crash-proof" checks.

	do {
		cout << "Welcome to Attendance Tracker" << endl
			<< "Press (1) to import a new CourseList" << endl
			<< "Press (2) to load a MasterList" << endl
			<< "Press (3) to store your current progress in your MasterList" << endl
			<< "Press (4) to mark the attendance of your students" << endl
			<< "Press (5) to edit a student's attendance" << endl
			<< "Press (6) to generate an AttendanceReport" << endl
			<< "Press (7) to exit." << endl;
		cin >> input;
		switch (input)
		{
		case 1:
			if (!import && !load) {
				courseImport(courseFile, Master);
				import = true;
				system("cls");
				cout << "Import was successful!" << endl << endl;
			}
			else
				cout << "You currently have a session open." << endl << endl;
			break;
		case 2:
			system("cls");
			if (!import && !load) {
				loadMaster(masterFile, Master);
				load = true;
				system("cls");
				cout << "Load was successful!" << endl << endl;
			}
			else
				cout << "You currently have a session open." << endl << endl;
			break;
		case 3:
			system("cls");
			if (!update && mark)
			{
				masterFile.close();
				outMaster.open("Master.txt");
				outMaster << Master;
				outMaster.close();
				masterFile.open("Master.txt");
				loadMaster(masterFile, UpdateMaster);
				update = true;
				cout << "Update was successful!" << endl << endl;
			}
			else
				cout << "You've already saved your progress or haven't marked attendance." << endl << endl;
			break;
		case 4:
			system("cls");
			if (!mark && !update) {
				markAbsence(Master);
				mark = true;
			}
			else
				cout << "Please import a new courseList or load a previous MasterFile." << endl << endl;
			break;
		case 5:
			system("cls");
			if (update)
				editDates(UpdateMaster);
			else if (load || mark)
				editDates(Master);
			else
				cout << "Please load a previous MasterFile or mark attendance." << endl << endl;
			break;
		case 6:
			system("cls");
			if (update)
				generateReport(UpdateMaster);
			else if (load || mark)
				generateReport(Master);
			else
				cout << "Please load a previous MasterFile or mark attendance." << endl << endl;
			break;
		default:
			if (!update && (load || mark))
			{
				masterFile.close();
				outMaster.open("Master.txt");
				outMaster << Master;
				outMaster.close();
				masterFile.open("Master.txt");
			} 
			else if (update)
			{
				masterFile.close();
				outMaster.open("Master.txt");
				outMaster << UpdateMaster;
				outMaster.close();
				masterFile.open("Master.txt");
			}
			break;
		}
	} while (input != 7);

	courseFile.close();
	masterFile.close();
}

// Parses a string based on a line from either ImportList.csv or Master.txt.
void App::parseString(istringstream& data, Student& store, bool input)
{
	string token = "Null";
	string dubTok;
	short record = 0;
	int id_nums = 0;
	Year level;

	/*Time Trash*/
	struct tm shit;
	struct tm prevShit;
	prevShit = { 0, 0, 0, 1, 0, 0, 110, 0, 0 };
	char tempTime[1024] = { 0 };

	bool absent;

	if (input == true) {
		for (int type = 1; data; type++)
		{
			getline(data, token, ',');
			switch (type)
			{
			case 1:
				std::stringstream(token) >> record;
				store.setRecord(record);
				break;
			case 2:
				std::stringstream(token) >> id_nums;
				store.setIDNum(id_nums);
				break;
			case 3:
				dubTok = token;
				getline(data, token, ',');
				dubTok = dubTok + ',' + token;
				store.setName(dubTok);
				break;
			case 4:
				store.setEmail(token);
				break;
			case 5:
				store.setUnits(token);
				break;
			case 6:
				store.setMajor(token);
				break;
			case 7:
				if (token == "Freshman")
					level = freshman;
				else if (token == "Sophomore")
					level = sophomore;
				else if (token == "Junior")
					level = junior;
				else if (token == "Senior")
					level = senior;
				else if (token == "Graduate")
					level = graduate;
				store.setLevel(level);
				break;
			default:
				cout << "We've went over!" << endl;
				break;
			}
		}
	}
	else {
		for (int type = 1; data; type++)
		{
			getline(data, token, ',');
			switch (type)
			{
			case 1:
				std::stringstream(token) >> record;
				store.setRecord(record);
				break;
			case 2:
				std::stringstream(token) >> id_nums;
				store.setIDNum(id_nums);
				break;
			case 3:
				dubTok = token;
				getline(data, token, ',');
				dubTok = dubTok + ',' + token;
				store.setName(dubTok);
				break;
			case 4:
				store.setEmail(token);
				break;
			case 5:
				store.setUnits(token);
				break;
			case 6:
				store.setMajor(token);
				break;
			case 7:
				if (token == "Freshman")
					level = freshman;
				else if (token == "Sophomore")
					level = sophomore;
				else if (token == "Junior")
					level = junior;
				else if (token == "Senior")
					level = senior;
				else if (token == "Graduate")
					level = graduate;
				store.setLevel(level);
				break;
				// What I spent this past week perfecting.
				// Simulating time itself.
			default:
				std::stringstream(token) >> absent;
				getline(data, token, ',');
				strncpy(tempTime, token.c_str(), sizeof tempTime);
				strptime(tempTime, "%Y-%m-%d %w-%j %H:%M:%S", &shit);
				if (prevShit.tm_year == 110 || shit.tm_yday != prevShit.tm_yday) {
					store.setDates(absent, shit);
					prevShit = shit;
				}
				break;
			}
		}
	}
}

// Imports data from ImportList.csv.
void App::courseImport(ifstream& firstFile, List<Student>& store)
{
	string aNewLine;
	string anOldLine;

	if (!firstFile)
	{
		cout << "Could not stream file!" << endl;
		return;
	}

	getline(firstFile, aNewLine);
	while (firstFile)
	{
		Student temp;
		getline(firstFile, aNewLine);
		istringstream buffer(aNewLine);
		if (anOldLine != aNewLine) {
			parseString(buffer, temp, true);
			store.insertAtEnd(temp);
		}
		anOldLine = aNewLine;
	}
}

// Loads data from Master.txt.
void App::loadMaster(ifstream& masterFile, List<Student>& store)
{
	string aNewLine;
	string anOldLine;

	if (!masterFile)
	{
		cout << "Could not stream file!" << endl;
		return;
	}

	while (masterFile)
	{
		Student temp;
		getline(masterFile, aNewLine);
		istringstream buffer(aNewLine);
		if (!aNewLine.empty() && anOldLine != aNewLine) {
			parseString(buffer, temp, false);
			store.insertAtEnd(temp);
		}
		anOldLine = aNewLine;
	}
}

// Allows the user to mark absences.
void App::markAbsence(List<Student>& store)
{
	Node<Student> *curAbs = store.getHeadPtr();
	time_t signOtheTimez = time(0);
	string choice;

	bool evaluate;
	struct tm* curTimez;
	struct tm oldTimez;
	struct tm newTimez;
	bool start = true;

	// If master.txt is empty:
	while (curAbs != nullptr && curAbs->getData().getDates().isEmpty())
	{
		// The beginning of time.
		if (start)
		{
			curTimez = localtime(&signOtheTimez);
			start = false;
		}
		cout << "Student Name: " << curAbs->getData().getName() << endl;
		cout << "Was this student absent? Enter Yes or No:" << endl;
		cin >> choice;
		if (choice == "Yes" || choice == "yes")
			curAbs->getData().setDates(true, *curTimez);
		else
			curAbs->getData().setDates(false, *curTimez);
		curAbs->getData().getDates().peak(evaluate, newTimez);
		cout << "Current day: " << asctime(&newTimez) << " Absent: " << evaluate << endl;
		curAbs = curAbs->getNextPtr();
		system("pause");
		system("cls");
	}
	system("cls");
	// If master.txt is full:
	while (curAbs != nullptr)
	{
		cout << "Student Name: " << curAbs->getData().getName() << endl;
		cout << "Was this student absent? Enter Yes or No:" << endl;
		cin >> choice;
		curAbs->getData().getDates().peak(evaluate, oldTimez);
		changeTime(oldTimez, newTimez);
		if (choice == "Yes" || choice == "yes")
			evaluate = true;
		else
			evaluate = false;
		// Some weird local shit going on here:
		curAbs->getData().setDates(evaluate, newTimez);
		cout << "Current day: " << asctime(&newTimez) << " Absent: " << evaluate << endl;
		curAbs = curAbs->getNextPtr();
		system("pause");
		system("cls");
	}
	system("cls");
}

// Allows the user to edit dates.
void App::editDates(List<Student>& store)
{
	Node<Student>* oldAbs = store.getHeadPtr();
	cout << "Enter the ID of the student you would like to view:" << endl;
	int id_num = 0;
	bool find = false;
	cin >> id_num;
	while (oldAbs != nullptr)
	{
		if (oldAbs->getData().getIDNum() == id_num)
		{
			find = true;
			NodeST<bool, struct tm>* curDate = oldAbs->getData().getDates().getHeadPtr();
			while (curDate != nullptr)
			{
				string dateChoice;
				cout << asctime(&(curDate->getReference())) << endl << "Would you like to edit this date's information?" << endl;
				cin >> dateChoice;
				if (dateChoice == "Yes" || dateChoice == "yes")
				{
					cout << "Was this student absent? Enter Yes or No:" << endl;
					cin >> dateChoice;
					if (dateChoice == "Yes" || dateChoice == "yes")
					{
						bool absent = true;
						curDate->setData(absent);
					}
					else
					{
						bool present = false;
						curDate->setData(present);
					}
				}
				curDate = curDate->getNextPtr();
			}
			break;
		}
		oldAbs = oldAbs->getNextPtr();
	}
	if (find == false)
		cout << "We could not find a student with that ID!" << endl;
	system("pause");
	system("cls");
}

// Generates either report on the screen and in their repsective files: DailyReport.txt and AbsenceTracker.txt.
void App::generateReport(List<Student>& store)
{
	int choice = 0;
	Node<Student>* curStd = store.getHeadPtr();
	cout << "Press (1) to see the most recent attendance information." << endl;
	cout << "Press (2) to view an AbsenceTracker report." << endl;
	cin >> choice;
	system("cls");
	ofstream regReport;
	regReport.open("DailyReport.txt");
	ofstream absenceTracker;
	absenceTracker.open("AbsenceTracker.txt");
	bool notFound = true;
	// DailyReport
	if (choice == 1)
	{
		while (curStd != nullptr)
		{
			bool absent;
			struct tm shitz;
			curStd->getData().getDates().peak(absent, shitz);
			if (absent) {
				cout << curStd->getData().getName() << endl
					<< "Was absent: " << asctime(&shitz) << endl;
				regReport << curStd->getData().getName() << endl
					<< "Was absent: " << asctime(&shitz) << endl;
			}
			else {
				cout << curStd->getData().getName() << endl
					<< "Was present: " << asctime(&shitz) << endl;
				regReport << curStd->getData().getName() << endl
					<< "Was present: " << asctime(&shitz) << endl;
			}
			curStd = curStd->getNextPtr();
		}
		system("pause");
		system("cls");
	}
	// AbsenceTracker
	else
	{
		cout << "How many absences would you like to track?" << endl;
		cin >> choice;
		while (curStd != nullptr)
		{
			auto shitterz = curStd->getData().getDates().getHeadPtr();
			int count = 0;
			for (; shitterz != nullptr; shitterz = shitterz->getNextPtr())
				if (shitterz->getData())
					count++;
			if (count >= choice)
			{
				cout << curStd->getData().getName() << " was absent " << count << " time(s)." << endl;
				absenceTracker << curStd->getData().getName() << " was absent " << count << " time(s)." << endl;
				notFound = false;
				cout << endl;
			}
			curStd = curStd->getNextPtr();
		}
		if (notFound) {
			cout << "We could not find any students absent for that long." << endl;
			system("pause");
		}
	}
	regReport.close();
	absenceTracker.close();
}

// Overloaded operator for storing data into Master.txt.
ofstream& operator<<(ofstream& outfile, List<Student>& store)
{
	char timeTemp[1024] = { 0 };
	Node<Student>* curPtr = store.getHeadPtr();
	while (curPtr != nullptr)
	{
		outfile << curPtr->getData().getRecord() << ',' << curPtr->getData().getIDNum() << ',' << curPtr->getData().getName() << ',' << curPtr->getData().getEmail() << ',' << curPtr->getData().getUnits() << ',' << curPtr->getData().getMajor() << ',';
		if (curPtr->getData().getLevel() == freshman)
			outfile << "Freshman";
		else if (curPtr->getData().getLevel() == sophomore)
			outfile << "Sophomore";
		else if (curPtr->getData().getLevel() == junior)
			outfile << "Junior";
		else if (curPtr->getData().getLevel() == senior)
			outfile << "Senior";
		else if (curPtr->getData().getLevel() == graduate)
			outfile << "Graduate";
		ListST<bool, struct tm> curAbs = curPtr->getData().getDates();
		while (!curAbs.isEmpty())
		{
			bool absence;
			struct tm curTimez;
			curAbs.popBack(absence, curTimez);
			strftime(timeTemp, sizeof timeTemp, "%F %w-%j %T", &curTimez);
			outfile << ',' << absence << ',' << timeTemp;
		}
		outfile << endl;
		curPtr = curPtr->getNextPtr();
	}
	return outfile;
}

// Source: https://gist.github.com/jeremynealbrown/5694aa3a66714254752179ecf3c95582
extern "C" char* strptime(const char* s, const char* f, struct tm* tm) {
	std::istringstream input(s);
	input.imbue(std::locale(setlocale(LC_ALL, nullptr)));
	input >> std::get_time(tm, f);
	if (input.fail()) {
		return nullptr;
	}
	return (char*)(s + input.tellg());
}

// Increments time based on the struct tm passed for 'pastTime'.
void changeTime(struct tm& pastTime, struct tm& presentTime)
{

	presentTime.tm_sec = pastTime.tm_sec;
	presentTime.tm_min = pastTime.tm_min;
	presentTime.tm_hour = pastTime.tm_hour;
	presentTime.tm_mon = pastTime.tm_mon;
	if (pastTime.tm_mday == 31)
		presentTime.tm_mday = 1;
	else
		presentTime.tm_mday = pastTime.tm_mday + 1;
	if (pastTime.tm_wday == 6)
		presentTime.tm_wday = 0;
	else
		presentTime.tm_wday = pastTime.tm_wday + 1;
	if ((pastTime.tm_yday == 365 && pastTime.tm_isdst > 0) || (pastTime.tm_yday == 364 && pastTime.tm_isdst == 0))
	{
		presentTime.tm_yday = 0;
		presentTime.tm_year = pastTime.tm_year + 1;
	}
	else
	{
		presentTime.tm_yday = pastTime.tm_yday + 1;
		presentTime.tm_year = pastTime.tm_year;
	}
	if (pastTime.tm_isdst > 1 || pastTime.tm_isdst < -1)
		presentTime.tm_isdst = 0;
}