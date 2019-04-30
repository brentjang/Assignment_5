#include <iostream>
#include <vector>
using namespace std;

class Faculty
{
public:
    Faculty();
    Faculty(int i, string n, string l, string s);
    Faculty(int i, string n, string l, string s, vector<int> p);
    ~Faculty() {};
    void setFID(int s);
    void setName(string n);
    void setLevel(string l);
    void setSubject(string s);
    void insertSID(int s);
    void deleteSID(int s);
    int getFID();
    string getName();
    string getLevel();
    string getSubject();
    vector<int> getSIDL();
    int getNumAdvisees();
    string writeFaculty();

    friend bool operator < (const Faculty& a, const Faculty& b);
    friend bool operator >(const Faculty& a, const Faculty& b);
    friend bool operator <=(const Faculty& a, const Faculty& b);
    friend bool operator >=(const Faculty& a, const Faculty& b);

    friend bool operator <(const int& a, const Faculty& b);
    friend bool operator >(const Faculty& a, const int& b);
    friend bool operator <=(const Faculty& a, const int& b);
    friend bool operator >=(const Faculty& a, const int& b);
    friend bool operator !=(const Faculty& a, const int& b);
    friend bool operator ==(const Faculty& a, const int& b);

    friend ostream& operator<<(ostream& out, const Faculty& a);

private:
    int facultyID;
    string name;
    string level;
    string subject;
    vector<int> studentIDL;
    int numAdvisees;
};
