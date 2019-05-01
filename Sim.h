#include "GenTree.h"
#include "GenDDL.h"
#include "Student.h"
#include "Faculty.h"
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

class Sim
{
public:
    Sim();
    ~Sim() {};
    void menu();
    void action(int i);
    int promptUser();
    void run();
    void printStudents(); //in order
    void printFaculty(); //in order
    void findStudent();
    void findFaculty();
    void printStudentAdvisor(); //given SID
    void printAdviseeList(); //given FID
    void addStudent();
    void deleteStudent();
    void addFaculty();
    void deleteFaculty();
    void changeAdvisor();
    void removeAdvisee();
    void undo();
    void save();
    void done();
    void serialize();
    void deserialize();
    void checkIntegrity();
    void studentIntegrity(TreeNode<Student>* node);
    void facultyIntegrity(TreeNode<Faculty>* node);
    void studentWrite(TreeNode<Student>* node);
    void facultyWrite(TreeNode<Faculty>* node);

    bool studentExists(int i);
    bool facultyExists(int i);
    bool facultyContainsSID(Student s);

private:
    GenTree<Faculty> masterFaculty;
    GenTree<Student> masterStudent;
    GenDDL<GenTree<Student>> studentHistory;
    GenDDL<GenTree<Faculty>> facultyHistory;
};
