#ifndef TEACHER_H
#define TEACHER_H
#include"User.h"
#include"Course.h"
#include<iostream>
using namespace std;

class Course;

class Teacher:public User{
	Course *course;
public:
	Teacher();
	void setCourse(Course& c);
	string getCourseName();
	string getCourseCode();
	void studentsInCourse();
	int  NumStudentsIncourse();
};
Teacher:: Teacher()
{
	course=NULL;
}
void Teacher:: setCourse(Course& c)
{
	course=&c;
	course->setInstructor(name);
}
string Teacher:: getCourseName()
{
	return course->getName();
}
string Teacher:: getCourseCode()
{
	return course->getCode();
}
void Teacher:: studentsInCourse()
{
	course->studentsInCourse();
}
int Teacher::  NumStudentsIncourse()
{
	return course->getNumStudentsEnrolled();
}


#endif
