// Edgar Perez
// PA 7 - Attendance Tracker

#pragma once
// Please ignore the amount of included/ "unused" header files.
// There are dependencies for various versions of a given library (C or C++).
#include <time.h>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "StackList.h"
#include "List.h"
#include <locale>

// Student class with appropriate fields based on ImportList.csv.

typedef enum year
{
	freshman, sophomore, junior, senior, graduate
} Year;

using std::string;
using std::istringstream;
using std::ostream;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;

class Student
{
public:
	Student();
	~Student() { ; }
	short getRecord() const
	{
		return record;
	}
	void setRecord(const short copy)
	{
		record = copy;
	}
	int getIDNum() const
	{
		return idNumber;
	}
	void setIDNum(const int copy)
	{
		idNumber = copy;
	}
	string getName() const
	{
		return name;
	}
	void setName(const string copy)
	{
		name = copy;
	}
	string getEmail() const
	{
		return email;
	}
	void setEmail(const string copy)
	{
		email = copy;
	}
	string getUnits() const
	{
		return units;
	}
	void setUnits(const string copy)
	{
		units = copy;
	}
	string getMajor() const
	{
		return major;
	}
	void setMajor(const string copy)
	{
		major = copy;
	}
	Year getLevel() const
	{
		return level;
	}
	void setLevel(const Year copy)
	{
		level = copy;
	}
	ListST<bool, struct tm> getDates() { return dates; }
	void setDates(bool absent, struct tm& newTime);

private:
	short record;
	int idNumber;
	string name;
	string email;
	string units;
	string major;
	Year level;
	//  This is the Student's stack for each attendance/absence.
	ListST<bool, struct tm> dates;
};