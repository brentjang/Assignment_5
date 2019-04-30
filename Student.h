#include <iostream>

using namespace std;

class Student
{
public:
    Student();
    Student(int i, double g, int f, string n, string l, string s);
    ~Student() {};
    void setSID(int s);
    void setGPA(double g);
    void setFID(int s);
    void setName(string n);
    void setLevel(string l);
    void setSubject(string s);
    int getSID();
    double getGPA();
    int getFID();
    string getName();
    string getLevel();
    string getSubject();
    string writeStudent();

    friend bool operator < (const Student& a, const Student& b);
    friend bool operator >(const Student& a, const Student& b);
    friend bool operator <=(const Student& a, const Student& b);
    friend bool operator >=(const Student& a, const Student& b);
    friend bool operator !=(const Student& a, const Student& b);
    friend bool operator ==(const Student& a, const Student& b);

    friend bool operator < (const int& a, const Student& b);
    friend bool operator >(const Student& a, const int& b);
    friend bool operator <=(const Student& a, const int& b);
    friend bool operator >=(const Student& a, const int& b);
    friend bool operator !=(const Student& a, const int& b);
    friend bool operator ==(const Student& a, const int& b);

    friend ostream& operator<<(ostream& out, const Student& a);

private:
    int studentID;
    double GPA;
    int facultyID;
    string name;
    string level;
    string subject;
};
