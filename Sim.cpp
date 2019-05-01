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
    cout << "====================WELCOME TO THE DATABASE===================" << endl;
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
    cout << "============================================================" << endl;
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
        cout << '\n';
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
        action(temp);
        if(temp == 14)
        {
            flag = false;
        }
    }
}

void Sim::printStudents() //in order
{
    cout << "===============PRINTING ALL STUDENTS===============\n" << endl;
    masterStudent.printTree();
    cout << "===================================================" << endl;
}

void Sim::printFaculty() //in order
{
    cout << "===============PRINTING ALL FACULTY================\n" << endl;
    masterFaculty.printTree();
    cout << "===================================================" << endl;
}

void Sim::findStudent()
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        cout << "==============STUDENT INFO FOR: " << i << "==============\n" << endl;
        cout << masterStudent.find(i)->key << endl;
        cout << "===================================================" << endl;
    }
    cin.clear();
    cin.ignore(256,'\n');
}

void Sim::findFaculty()
{
    int i;
    cout << "Please Enter a FacultyID: ";
    cin >> i;
    if(facultyExists(i))
    {
        cout << "==============FACULTY INFO FOR: " << i << "==============\n" << endl;
        cout << masterFaculty.find(i)->key << endl;
        cout << "===================================================" << endl;
    }
    cin.clear();
    cin.ignore(256,'\n');
}

void Sim::printStudentAdvisor() //given SID
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        cout << "==========FACULTY INFO FOR: STUDENT " << i << "==========\n" << endl;
        cout << masterFaculty.find(masterStudent.find(i)->key.getFID())->key << endl;
        cout << "===================================================" << endl;
    }
    cin.clear();
    cin.ignore(256,'\n');
}

void Sim::printAdviseeList() //given FID
{
    int i;
    cout << "Please Enter a FacultyID: ";
    cin >> i;
    if(facultyExists(i))
    {
        cout << "==========STUDENT INFO FOR: FACULTY " << i << "==========\n" << endl;
        string studentList = "|";
        vector<int> studentIDL = masterFaculty.find(i)->key.getSIDL();
        for (int i = 0; i < studentIDL.size(); i++)
        {
            cout << masterStudent.find(studentIDL[i])->key << endl;
        }
        cout << "===================================================" << endl;
    }
    cin.clear();
    cin.ignore(256,'\n');
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
    regex gpa("[0-4][.][0-9]+");
    regex text("[A-Za-z.-]+");
    cout << "===============Adding a New Student...===============" << endl;

    while(flag)
    {
        //random 5 digit number
        studentID = rand() % (99999 - 10000 + 1) + 10000;
        Student s(studentID, 0, 0, "", "", "");
        while (masterStudent.contains(studentID) || masterFaculty.contains(studentID))
        {
            studentID = rand() % (99999 - 10000 + 1) + 10000;
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
                    if(regex_match(temp, gpa))
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
                                //if facultyID is wrong, randomly assign a correct one
                                facultyID = rand() % (99999 - 10000 + 1) + 10000;
                                while(!masterFaculty.contains(facultyID))
                                {
                                    facultyID = rand() % (99999 - 10000 + 1) + 10000;
                                }
                                masterFaculty.find(masterStudent.find(studentID)->key.getFID())->key.insertSID(studentID);
                                cout << "Invalid Faculty ID: Faculty Automatically set to " << facultyID << endl;
                                flag = false;
                                break;
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
    cout << "===================================================" << endl;
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
        checkIntegrity(); //updates faculty table
        cout << "===================================================" << endl;
        cout << "========STUDENT " << i << " SUCCESSFULLY REMOVED.=======" << endl;
        cout << "===================================================" << endl;
    }
    cin.clear();
    cin.ignore(256,'\n');
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
    cout << "===============Adding a New Faculty...===============" << endl;

    while(flag)
    {
        facultyID = rand() % (99999 - 10000 + 1) + 10000;
        while (masterFaculty.contains(facultyID) || masterStudent.contains(facultyID))
        {
            facultyID = rand() % (99999 - 10000 + 1) + 10000;
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
    cout << "===================================================" << endl;
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
        checkIntegrity(); //updates student table
        cout << "===================================================" << endl;
        cout << "========FACULTY " << i << " SUCCESSFULLY REMOVED.========" << endl;
        cout << "===================================================" << endl;
    }
    cin.clear();
    cin.ignore(256,'\n');
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
            masterFaculty.find(masterStudent.find(i)->key.getFID())->key.deleteSID(i);
            masterStudent.find(i)->key.setFID(f);
            masterFaculty.find(f)->key.insertSID(i);
            cout << "============================================================" << endl;
            cout << "=============SET STUDENT " << i << " FACULTY TO "<< f << "=============" << endl;
            cout << "============================================================" << endl;
            return;
        }
    }
    cout << "Invalid Information" << endl;
    cin.clear();
    cin.ignore(256,'\n');
}

//removes student from advisor and randomly assigns student to new advisor
void Sim::removeAdvisee()
{
    int i;
    cout << "Please Enter a StudentID: ";
    cin >> i;
    if(studentExists(i))
    {
        if(masterFaculty.getMin()->key.getFID() == masterFaculty.getMax()->key.getFID())
        {
            cout << "============================================================" << endl;
            cout << "=======CANNOT REMOVE STUDENT FROM ONLY FACULTY MEMBER=======" << endl;
            cout << "============================================================" << endl;
        }
        else
        {
            save();
            int f = masterStudent.find(i)->key.getFID();
            masterFaculty.find(masterStudent.find(i)->key.getFID())->key.deleteSID(i);
            int newFacultyID = rand() % (99999 - 10000 + 1) + 10000;
            while(!masterFaculty.contains(newFacultyID) || f == newFacultyID)
            {
                newFacultyID = rand() % (99999 - 10000 + 1) + 10000;
            }
            masterStudent.find(i)->key.setFID(newFacultyID);
            masterFaculty.find(newFacultyID)->key.insertSID(i);

            checkIntegrity();
            cout << "============================================================" << endl;
            cout << "========REMOVED STUDENT " << i << " FROM FACULTY "<< f << "============" << endl;
            cout << "============================================================" << endl;
        }
    }
    cin.clear();
    cin.ignore(256,'\n');
}

void Sim::undo()
{
    if (studentHistory.getSize() == 0)
    {
        cout << "============================================================" << endl;
        cout << "========================CANNOT UNDO=========================" << endl;
        cout << "============================================================" << endl;
    }
    else
    {
        masterStudent = studentHistory.removeFront();
        masterFaculty = facultyHistory.removeFront();
        cout << "============================================================" << endl;
        cout << "==================ACTION SUCCESSFULLY UNDONE================" << endl;
        cout << "============================================================" << endl;
    }
}

void Sim::done()
{
    //empties files and then writes over them on exit
    ofstream ofs;
    ofs.open("studentTable.txt", ofstream::out | ofstream::trunc);
    ofs.close();
    studentWrite(masterStudent.getRoot());
    ofs.open("facultyTable.txt", ofstream::out | ofstream::trunc);
    ofs.close();
    facultyWrite(masterFaculty.getRoot());
}

//uses a DDL to hold rollback
void Sim::save()
{
    GenTree<Student> students = copyStudentTree(masterStudent.getRoot());
    studentHistory.insertFront(students);

    GenTree<Faculty> faculty = copyFacultyTree(masterFaculty.getRoot());
    facultyHistory.insertFront(faculty);
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
    vector<int> tempSIDL;

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

                        case 3:
                        subject = info;
                        break;

                        default:
                        tempSIDL.push_back(stoi(info));
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
            Faculty f(facultyID, name, level, subject, tempSIDL);
            masterFaculty.insert(f);
            while(tempSIDL.size() > 0)
            {
                tempSIDL.erase(tempSIDL.begin());
            }
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

//checks if a students advisor is in the table, if not,
//randomly set students advisor to existing facultyID
void Sim::studentIntegrity(TreeNode<Student>* node)
{
    if(node == NULL)
    {
        return;
    }
    else
    {
        studentIntegrity(node->left);
        if(masterFaculty.isEmpty()) //no faculty
        {
            node->key.setFID(0);
        }
        else if(!masterFaculty.contains(node->key.getFID()) && !masterFaculty.isEmpty()) //faculty doesnt exist
        {
            int newFacultyID = rand() % (99999 - 10000 + 1) + 10000;
            while (!masterFaculty.contains(newFacultyID))
            {
                newFacultyID = rand() % (99999 - 10000 + 1) + 10000;
                node->key.setFID(newFacultyID);
            }
            masterFaculty.find(newFacultyID)->key.insertSID(node->key.getSID());
        }
        else if(masterFaculty.contains(node->key.getFID()) && !facultyContainsSID(node->key)) //faculty does exist
        {
            masterFaculty.find(node->key.getFID())->key.insertSID(node->key.getSID());
        }
        studentIntegrity(node->right);
    }
}

//checks if a student advisee is in the table
//and if not it is deleted from faculty list of advisees
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

void Sim::studentWrite(TreeNode<Student>* node)
{
    ofstream studentFile("studentTable.txt", ios_base::app);
    if(node == NULL)
    {
        return;
    }
    else
    {
        studentWrite(node->left);
        studentFile << node->key.writeStudent() << endl;
        studentWrite(node->right);
    }
}

void Sim::facultyWrite(TreeNode<Faculty>* node)
{
    ofstream facultyFile("facultyTable.txt", ios_base::app);
    if(node == NULL)
    {
        return;
    }
    else
    {
        facultyWrite(node->left);
        facultyFile << node->key.writeFaculty() << endl;
        facultyWrite(node->right);
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

bool Sim::facultyContainsSID(Student s)
{
    for(int i = 0; i < masterFaculty.find(s.getFID())->key.getNumAdvisees(); i++)
    {
        if(s.getSID() == masterFaculty.find(s.getFID())->key.getSIDL()[i])
        {
            return true;
        }
    }
    return false;
}

GenTree<Student> Sim::copyStudentTree(TreeNode<Student> *root)
{
    GenTree<Student> a;
    GenStack<TreeNode<Student>*> s;

    while (root != NULL || s.isEmpty() == false)
    {
        while (root !=  NULL)
        {
            s.push(root);
            root = root->left;
        }
        root = s.peek();
        a.insert(s.pop()->key);
        root = root->right;
    }
    return a;
}


GenTree<Faculty> Sim::copyFacultyTree(TreeNode<Faculty> *root)
{
    GenTree<Faculty> q;
    GenStack<TreeNode<Faculty>*> r;

    while (root != NULL || r.isEmpty() == false)
    {
        while (root != NULL)
        {
            r.push(root);
            root = root->left;
        }
        root = r.peek();
        q.insert(r.pop()->key);
        root = root->right;
    }
    return q;
}
