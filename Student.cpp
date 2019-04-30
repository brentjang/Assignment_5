#include <iostream>
#include "Student.h"
#include <cstdlib>
#include <stdio.h>

using namespace std;


Student::Student()
{
    studentID = 0;
    GPA = 0.0;
    facultyID = 0;
    name = "default";
    level = "default";
    subject = "default";
}

Student::Student(int i, double g, int f, string n, string l, string s)
{
    studentID = i;
    GPA = g;
    facultyID = f;
    name = n;
    level = l;
    subject = s;
}

void Student::setSID(int i)
{
    studentID = i;
}

void Student::setGPA(double g)
{
    GPA = g;
}

void Student::setFID(int f)
{
    facultyID = f;
}

void Student::setName(string n)
{
    name = n;
}

void Student::setLevel(string l)
{
    level = l;
}

void Student::setSubject(string s)
{
    subject = s;
}

int Student::getSID()
{
    return studentID;
}

double Student::getGPA()
{
    return GPA;
}

int Student::getFID()
{
    return facultyID;
}

string Student::getName()
{
    return name;
}

string Student::getLevel()
{
    return level;
}

string Student::getSubject()
{
    return subject;
}

string Student::writeStudent()
{
    string a = to_string(studentID) + "|" + to_string(GPA) + "|" + to_string(facultyID) + "|" + name + "|" + level + "|" + subject;
    return a;
}

bool operator <(const Student& a, const Student& b)
{
    return (a.studentID < b.studentID);
}

bool operator >(const Student& a, const Student& b)
{
    return (a.studentID > b.studentID);
}

bool operator <=(const Student& a, const Student& b)
{
    return (a.studentID <= b.studentID);
}

bool operator >=(const Student& a, const Student& b)
{
    return (a.studentID >= b.studentID);
}

bool operator !=(const Student& a, const Student& b)
{
    return !(a.studentID == b.studentID);
}

bool operator ==(const Student& a, const Student& b)
{
    return (a.studentID == b.studentID);
}

bool operator <(const int& a, const Student& b)
{
    return (a < b.studentID);
}

bool operator >(const Student& a, const int& b)
{
    return (a.studentID > b);
}

bool operator <=(const Student& a, const int& b)
{
    return (a.studentID <= b);
}

bool operator >=(const Student& a, const int& b)
{
    return (a.studentID >= b);
}

bool operator !=(const Student& a, const int& b)
{
    return !(a.studentID == b);
}

bool operator ==(const Student& a, const int& b)
{
    return (a.studentID == b);
}

ostream& operator<<(ostream& out, const Student& a)
{
    out << "StudentID: " << a.studentID << '\n'
    << "Name: " << a.name << '\n'
    << "GPA: " << a.GPA << '\n'
    << "Level: " << a.level << '\n'
    << "Major: " << a.subject << '\n'
    << "FacultyID: " << a.facultyID << '\n';
    return out;
}
