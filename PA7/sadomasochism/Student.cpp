// Edgar Perez
// PA 7 - Attendance Tracker

#include "Student.h"

// Constuctor for Student class and mutator for dates' stack.

Student::Student()
{
	record = 0;
	idNumber = 0;
}

void Student::setDates(bool absent, struct tm& newTime)
{
	dates.push(absent, newTime);
}