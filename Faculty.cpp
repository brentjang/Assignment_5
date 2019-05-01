#include <iostream>
#include "Faculty.h"
#include <vector>
#include <cstdlib>
using namespace std;


Faculty::Faculty()
{
    facultyID = 0;
    name = "default";
    level = "default";
    subject = "default";
    numAdvisees = 10;
}

Faculty::Faculty(int i, string n, string l, string s)
{
    facultyID = i;
    name = n;
    level = l;
    subject = s;
    numAdvisees = 0;
}

Faculty::Faculty(int i, string n, string l, string s, vector<int> p)
{
    facultyID = i;
    name = n;
    level = l;
    subject = s;
    numAdvisees = p.size();
    for (int i = 0; i < p.size(); i++)
    {
        studentIDL.push_back(p[i]);
    }
}

void Faculty::setFID(int i)
{
    facultyID = i;
}

void Faculty::setName(string n)
{
    name = n;
}

void Faculty::setLevel(string l)
{
    level = l;
}

void Faculty::setSubject(string s)
{
    subject = s;
}

void Faculty::insertSID(int i)
{
    numAdvisees++;
    studentIDL.push_back(i);
}

void Faculty::deleteSID(int i)
{
    for (int j = 0; j < studentIDL.size(); j++)
    {
        if(studentIDL[j] == i)
        {
            studentIDL.erase(studentIDL.begin()+j);
            numAdvisees--;
            break;
        }
    }
}

int Faculty::getFID()
{
    return facultyID;
}

string Faculty::getName()
{
    return name;
}

string Faculty::getLevel()
{
    return level;
}

string Faculty::getSubject()
{
    return subject;
}

vector<int> Faculty::getSIDL()
{
    return studentIDL;
}

int Faculty::getNumAdvisees()
{
    return numAdvisees;
}

string Faculty::writeFaculty()
{
    string studentList = "";
    for (int i = 0; i < numAdvisees; i++)
    {
        studentList += to_string(studentIDL[i]) + "|";
    }
    string a = to_string(facultyID) + "|" + name + "|" + level + "|" + subject + "|" + studentList;
    return a;
}

bool operator <(const Faculty& a, const Faculty& b)
{
    return (a.facultyID < b.facultyID);
}

bool operator >(const Faculty& a, const Faculty& b)
{
    return (a.facultyID > b.facultyID);
}

bool operator <=(const Faculty& a, const Faculty& b)
{
    return (a.facultyID <= b.facultyID);
}

bool operator >=(const Faculty& a, const Faculty& b)
{
    return (a.facultyID >= b.facultyID);
}

bool operator <(const int& a, const Faculty& b)
{
    return (a < b.facultyID);
}

bool operator >(const Faculty& a, const int& b)
{
    return (a.facultyID > b);
}

bool operator <=(const Faculty& a, const int& b)
{
    return (a.facultyID <= b);
}

bool operator >=(const Faculty& a, const int& b)
{
    return (a.facultyID >= b);
}

bool operator !=(const Faculty& a, const int& b)
{
    return !(a.facultyID == b);
}

bool operator ==(const Faculty& a, const int& b)
{
    return (a.facultyID == b);
}


ostream& operator<<(ostream& out, const Faculty& a)
{
    string studentList = "|";
    for (int i = 0; i < a.numAdvisees; i++)
    {
        studentList += to_string(a.studentIDL[i]) + "|";
    }
    out << "FacultyID: " << a.facultyID << '\n'
    << "Name: " << a.name << '\n'
    << "Level: " << a.level << '\n'
    << "Major: " << a.subject << '\n'
    << "AdviseeIDs: " << studentList << '\n';
    return out;
}
