// Edgar Perez
// PA 7 - Attendance Tracker

#pragma once
#include "Student.h"
class App
{
public:
	App();
	~App();
	void runApp();
private:
	void parseString(istringstream& data, Student& store, bool input);
	void courseImport(ifstream& firstFile, List<Student>& store);
	void loadMaster(ifstream& masterFile, List<Student>& store);
	void markAbsence(List<Student>& store);
	void editDates(List<Student>& store);
	// Pass in file streams?
	void generateReport(List<Student>& store);
};

ofstream& operator<<(ofstream& outfile, List<Student>& store);

// strptime is not included with <ctime> or <time.h>
// This is an open source replacement for C++.
// Code from https://gist.github.com/jeremynealbrown/5694aa3a66714254752179ecf3c95582
extern "C" char* strptime(const char* s, const char* f, struct tm* tm);

// This increments time based on a local struct tm 'pastTime'.
void changeTime(struct tm& pastTime, struct tm& presentTime);