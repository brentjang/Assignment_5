#include <iostream>
#include "Sim.h"
#include <vector>
#include <regex>
#include <cstdlib>
#include <fstream>

using namespace std;

Sim::Sim()
{
    GenTree<Student> masterStudent;
    GenTree<Faculty> masterFaculty;

    GenDDL<GenTree<Student>> studentHistory;
    GenDDL<GenTree<Faculty>> facultyHistory;

    deserialize();
}

void Sim::menu()
{
    cout << '\n';
    cout << "Enter the Number of the Selection to Continue..." << endl;
    cout << "  1.  Print all students and their information" << endl;
    cout << "  2.  Print all faculty and their information" << endl;
    cout << "  3.  Find and display a student's information" << endl;
    cout << "  4.  Find and display a faculty member's information" << endl;
    cout << "  5.  Print the info of a student's faculty advisor" << endl;
    cout << "  6.  Print the info of a faculty member's advisees" << endl;
    cout << "  7.  Add a new student" << endl;
    cout << "  8.  Delete a student" << endl;
    cout << "  9.  Add a new faculty member" << endl;
    cout << "  10. Delete a faculty member" << endl;
    cout << "  11. Change a student’s advisor" << endl;
    cout << "  12. Remove an advisee from a faculty member" << endl;
    cout << "  13. Rollback" << endl;
    cout << "  14. Exit" << endl;
}

int Sim::promptUser()
{
    int temp = 0;
    string a;
    while(true)
    {
        cout << "Please enter a Selection: ";
        cin >> temp;
        if(temp > 0 && temp < 15)
        {
            return temp;
        }
        else
        {
            cout << "Please enter a valid Selection.\n" << endl;
            cin.clear();
            cin.ignore(256,'\n');
        }
    }
}

void Sim::action(int i)
{
    switch(i)
    {
        case 1:
        printStudents();
        break;

        case 2:
        printFaculty();
        break;

        case 3:
        findStudent();
        break;

        case 4:
        findFaculty();
        break;

        case 5:
        printStudentAdvisor();
        break;

        case 6:
        printAdviseeList();
        break;

        case 7:
        addStudent();
        break;

        case 8:
        deleteStudent();
        break;

        case 9:
        addFaculty();
        break;

        case 10:
        deleteFaculty();
        break;

        case 11:
        changeAdvisor();
        break;

        case 12:
        removeAdvisee();
        break;

        case 13:
        undo();
        break;

        case 14:
        done();
        break;
    }
}

void Sim::run()
{
    bool flag = true;
    while(flag)
    {
        menu();
        int temp = promptUser();
        if(temp == 14)
        {
            flag = false;
        }
        else
        {
            action(temp);
        }
    }
}

void Sim::printStudents() //in order
{
    masterStudent.printTree();
}

void Sim::printFaculty() //in order
{
    masterFaculty.printTree();
}

void Sim::findStudent()
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        cout << masterStudent.find(i)->key << endl;
    }
}

void Sim::findFaculty()
{
    int i;
    cout << "Please Enter a FacultyID: ";
    cin >> i;
    if(facultyExists(i))
    {
        cout << masterFaculty.find(i)->key << endl;
    }
}

void Sim::printStudentAdvisor() //given SID
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        cout << "FacultyID: " <<
        masterStudent.find(i)->key.getFID() << endl;
    }
}

void Sim::printAdviseeList() //given FID
{
    int i;
    cout << "Please Enter a FacultyID: ";
    cin >> i;
    if(facultyExists(i))
    {
        string studentList = "|";
        vector<int> studentIDL = masterFaculty.find(i)->key.getSIDL();
        for (int i = 0; i < studentIDL.size(); i++)
        {
            studentList += to_string(studentIDL[i]) + "|";
        }
        cout << "StudentIDs: " << studentList << endl;
    }
}

void Sim::addStudent()
{
    string temp;
    int studentID;
    double GPA;
    int facultyID;
    string name;
    string level;
    string subject;

    bool flag = true;

    regex numbers("[0-9.]+");
    regex text("[A-Za-z.-]+");
    cout << "Adding a New Student..." << endl;

    while(flag)
    {
        studentID = rand() % (49999 - 10000 + 1) + 10000; // random 9 digit number
        Student s(studentID, 0, 0, "", "", "");
        while (masterStudent.contains(studentID) || masterFaculty.contains(studentID)) // duplicate id
        {
            studentID = rand() % (49999 - 10000 + 1) + 10000; // random 9 digit number
            Student s1(studentID, 0, 0, "", "", "");
            s = s1;
        }
        cout << "Enter the Student's Name: ";
        cin >> temp;
        if(regex_match(temp, text))
        {
            name = temp;
            cout << "Enter the Student's Level: ";
            cin >> temp;
            if(regex_match(temp, text))
            {
                level = temp;
                cout << "Enter the Student's Major: ";
                cin >> temp;
                if(regex_match(temp,text))
                {
                    subject = temp;
                    cout << "Enter the Student's GPA: ";
                    cin >> temp;
                    if(regex_match(temp, numbers))
                    {
                        GPA = stod(temp);
                        cout << "Enter the Student's FacultyID: ";
                        cin >> temp;
                        if(regex_match(temp, numbers))
                        {
                            facultyID = stoi(temp);
                            if(facultyExists(facultyID))
                            {
                                masterFaculty.find(facultyID)->key.insertSID(studentID);
                                flag = false;
                                break;
                            }
                            else
                            {
                                cout << "Invalid Faculty ID: Deafult Faculty ID to 0" << endl;

                            }
                        }
                    }
                }
            }
        }
        cout << '\n';
        cout << "Invalid Entry. Restarting..." << endl;
        cout << '\n';
    }
    save();
    Student s(studentID, GPA, facultyID, name, level, subject);
    masterStudent.insert(s);
    cout << "Student Added!" << endl;
    checkIntegrity();
}

void Sim::deleteStudent()
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        save();
        masterStudent.deleter(i);
        checkIntegrity();
    }
}

void Sim::addFaculty()
{
    string temp;
    int facultyID;
    string name;
    string level;
    string subject;

    bool flag = true;

    regex numbers("[0-9.]+");
    regex text("[A-Za-z.-]+");
    cout << "Adding a New Faculty..." << endl;

    while(flag)
    {
        facultyID = rand() % (49999 - 10000 + 1) + 10000; // random 9 digit number
        while (masterFaculty.contains(facultyID) || masterStudent.contains(facultyID)) // duplicate id
        {
            facultyID = rand() % (49999 - 10000 + 1) + 10000; // random 9 digit number
        }
        cout << "Enter the Faculty's Name: ";
        cin >> temp;
        if(regex_match(temp, text))
        {
            name = temp;
            cout << "Enter the Faculty's Level: ";
            cin >> temp;
            if(regex_match(temp, text))
            {
                level = temp;
                cout << "Enter the Faculty's Subject: ";
                cin >> temp;
                if(regex_match(temp,text))
                {
                    subject = temp;
                    flag = false;
                    break;
                }
            }
        }
        cout << '\n';
        cout << "Invalid Entry. Restarting..." << endl;
        cout << '\n';
    }
    save();
    Faculty f(facultyID, name, level, subject);
    masterFaculty.insert(f);
    cout << "Faculty Added!" << endl;
    checkIntegrity();
}

void Sim::deleteFaculty()
{
    int i;
    cout << "Please Enter a FacultyID: ";
    cin >> i;
    if(facultyExists(i))
    {
        save();
        masterFaculty.deleter(i);
        checkIntegrity();
    }
}

void Sim::changeAdvisor()
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        int f;
        cout << "Enter new Advisor ID: ";
        cin >> f;
        if(facultyExists(f))
        {
            save();
            masterStudent.find(i)->key.setFID(f);
            masterFaculty.find(f)->key.insertSID(i);
            return;
        }
    }
    cout << "Invalid Information" << endl;
}

void Sim::removeAdvisee()
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        save();
        masterFaculty.find(masterStudent.find(i)->key.getFID())->key.deleteSID(i);
        checkIntegrity();
    }
}

void Sim::undo()
{
    if (studentHistory.getSize() == 0)
    {
        cout << "Cannot Undo." << endl;
    }
    else
    {
        masterStudent = studentHistory.removeFront();
        masterFaculty = facultyHistory.removeFront();
        cout << "Action Successfullly Undone." << endl;
    }
}

void Sim::done()
{
    ofstream studentFile("studentTable.txt", ios_base::app);
    ofstream facultyFile("facultyTable.txt", ios_base::app);

    return;
}

void Sim::save()
{
    studentHistory.insertFront(masterStudent);
    facultyHistory.insertFront(masterFaculty);
    if(studentHistory.getSize() == 6)
    {
        studentHistory.removeBack();
        facultyHistory.removeBack();
    }
}

void Sim::deserialize()
{
    string line;
    int delimCount = 0;
    string info;
    ifstream studentFile;
    ifstream facultyFile;
    studentFile.open("studentTable.txt");
    facultyFile.open("facultyTable.txt");

    int facultyID = 0;
    string name;
    string level;
    string subject;

    if (facultyFile.peek() != ifstream::traits_type::eof())
    {
        while (getline(facultyFile, line))
        {
            if (line.empty())
            {
                break;
            }
            for (char c : line)
            {
                if (c == '|')
                {
                    switch (delimCount)
                    {
                        case 0:
                        facultyID = stoi(info);
                        break;

                        case 1:
                        name = info;
                        break;

                        case 2:
                        level = info;
                        break;

                        default:
                        subject = info;
                        break;
                    }
                    info = "";
                    ++delimCount;
                }
                else
                {
                    info += c;
                }
            }
            Faculty f(facultyID, name, level, subject);
            //add SID in the file to list
            masterFaculty.insert(f);
            delimCount = 0;
            info = "";
        }
    }

    int studentID = 0;
    double GPA = 0.0;
    facultyID = 0;
    name = "";
    level = "";
    subject = "";

    if (studentFile.peek() != ifstream::traits_type::eof())
    {
        while (getline(studentFile, line))
        {
            if (line.empty())
            {
                break;
            }
            for (char c : line)
            {
                if (c == '|')
                {
                    switch (delimCount)
                    {
                        case 0:
                        studentID = stoi(info);
                        break;

                        case 1:
                        GPA = stod(info);
                        break;

                        case 2:
                        facultyID = stoi(info);
                        break;

                        case 3:
                        name = info;
                        break;

                        case 4:
                        level = info;
                        break;

                        default:
                        subject = info;
                        break;
                    }
                    info = "";
                    ++delimCount;
                }
                else
                {
                    info += c;
                }
            }
            Student s(studentID, GPA, facultyID, name, level, subject);
            masterStudent.insert(s);
            if(masterFaculty.contains(s.getFID()))
            {
                masterFaculty.find(s.getFID())->key.insertSID(s.getSID());
            }
            delimCount = 0;
            info = "";
        }
    }
    checkIntegrity();
}

void Sim::checkIntegrity()
{
    studentIntegrity(masterStudent.getRoot());
    facultyIntegrity(masterFaculty.getRoot());
}

//checks if a students advisor is in the table
//and if not it is set to existing facultyID
void Sim::studentIntegrity(TreeNode<Student>* node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        studentIntegrity(node->left);
        if(masterFaculty.isEmpty())
        {
            node->key.setFID(0);
        }
        else if(!masterFaculty.contains(node->key.getFID()) && !masterFaculty.isEmpty())
        {
            int newFacultyID = rand() % (49999 - 10000 + 1) + 10000;
            while (!masterFaculty.contains(newFacultyID)) // duplicate id
            {
                newFacultyID = rand() % (49999 - 10000 + 1) + 10000; // random 9 digit number
                node->key.setFID(newFacultyID);
            }
            masterFaculty.find(newFacultyID)->key.insertSID(node->key.getSID());
        }
        studentIntegrity(node->right);
    }
}

//checks if a student advisee is in the table
//and if not it is deleted from SIDL
void Sim::facultyIntegrity(TreeNode<Faculty>* node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        facultyIntegrity(node->left);
        for(int i = 0; i < node->key.getNumAdvisees(); i++)
        {
            if(!masterStudent.contains(node->key.getSIDL()[i]))
            {
                node->key.deleteSID(node->key.getSIDL()[i]);
            }
        }
        facultyIntegrity(node->right);
    }
}


bool Sim::studentExists(int i)
{
    if(!masterStudent.contains(i))
    {
        cout << "Student does not exist in the Database." << endl;
        return false;
    }
    return true;
}

bool Sim::facultyExists(int i)
{
    if(!masterFaculty.contains(i))
    {
        cout << "Faculty does not exist in the Database." << endl;
        return false;
    }
    return true;
}
