#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include "p3.hpp"

using namespace std;

//Create a new student with the given name
//DO NOT MODIFY THIS CONSTRUCTOR
Student::Student(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open student data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,grade;
  int courseNum;
  while(getline(ifs,line)) {
    //std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> grade;
    grades[courseNum] = grade;
  }
}

//Calls to parent constructor
OutsideClassList::OutsideClassList(string name) : ClassList::ClassList(name) {}
StudentWithTransferCredit::StudentWithTransferCredit(std::string name, std::string schoolName) : Student::Student(name) {}

//DO NOT MODIFY THIS CONSTRUCTOR
ClassList::ClassList(std::string name) {
  std::ifstream ifs(name+".txt");
  if(!ifs.is_open()) {
    std::cout << "ERROR: Unable to open classlist data file " + name + ".txt" << std::endl;
    return;
  }
  this->name = name;
  std::string line,courseName;
  int courseNum,credits;
  while(getline(ifs,line)) {
    //std::cout << "Read line: " << line << std::endl;
    std::stringstream stst;
    stst << line;
    stst >> courseNum >> credits;
    getline(stst,courseName); //Remainder of the line is course name
    courses[courseNum] = {courseName, credits};
  }
}

//prints every course in the classlist
void ClassList::printClassList() {
  for (auto elem : courses) {
    cout << elem.second.first << "  " << elem.first << "  " << elem.second.second << endl;
  }
}

//given a course number, this method return the course name
std::string ClassList::getCourseName(int courseNumber) {
  if (courses.find(courseNumber) != courses.end()) {
    return courses.find(courseNumber)->second.first;
  }
  else {
    //Didn't know what to do here so we just did this lol
    return "not found";
  }
}

//print courses from students classlist
void Student::printStudent(ClassList& cl) {
  for (auto elem : grades) {
    cout << cl.getCourseName(elem.first) << " " << elem.second << endl;
  }
}

//return a student's name
std::string Student::getStudentName() {
  return name;
}

//return school name
std::string StudentWithTransferCredit::getSchoolName() {
  return schoolName;
}

//print equivalent courses from student's old list to the new school's list
void StudentWithTransferCredit::printStudent(OutsideClassList& oldSchool, ClassList& newSchool) {
  for (auto elem : grades) {
    int course_num = elem.first;
    string grade = elem.second;
    if (oldSchool.getCourseEquivalent(course_num) != 0) {
      int new_num = oldSchool.getCourseEquivalent(course_num);
      cout << " " << newSchool.getCourseName(new_num) << ": " << grade << endl;
    }
  }
}

//print all courses from studnet's old school
void OutsideClassList::printClassList() {  
  for (auto elem : courses) {
    cout << elem.second.first << " " << elem.first << endl;
  }
}

//print all courses from old school's list
void OutsideClassList::printClassList(ClassList& cl) {
  for (auto elem : courses) {
    int course_num = elem.first;
    if (getCourseEquivalent(course_num) != 0) {
      int to_search = getCourseEquivalent(course_num);
      cout << getCourseEquivalent(course_num) << "  ";
      string temp = cl.getCourseName(to_search);    
      cout << temp << "    ";  
      cout << elem.second.first << endl;
    }
  }
} 

//get old school's course number and check if the new school has an equivalent course
//and return that course number if so, otherwise return 0
int OutsideClassList::getCourseEquivalent(int courseNumber) {
  int num = 0;
  if (courses.find(courseNumber) != courses.end()) {
    num = courses.find(courseNumber)->second.second;
  }
  return num;
}


int main() {
  //main output and classlist
  cout << "WELCOME TO THE PREREQ-CHECKER" << endl;
  cout << "ClassList: ";
  string input;
  cin >> input;
  cout << input << endl;
  ClassList class_list(input);
  class_list.printClassList();
  
  //print outside classlist
  cout << "ClassList: ";
  string input_list;
  cin >> input_list;
  cout << input_list << endl;
  OutsideClassList outside_list(input_list);
  outside_list.printClassList();
  
  //print overloaded outside classlist
  cout << input_list << endl;
  outside_list.printClassList(class_list);
  
  //print out student info
  cout << "Name of student: ";
  string student_name;
  cin >> student_name;
  cout << "New student's name is: " << student_name << endl;
  
  //print out student with transfer credit info
  string school = "UW-Madison";
  StudentWithTransferCredit transfer_student(student_name, school);
  transfer_student.printStudent(outside_list, class_list);
}
