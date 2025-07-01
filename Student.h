#ifndef STUDENT_H
#define STUDENT_H
#include"User.h"
#include"Course.h"
#include<iostream>
using namespace std;

class Course;

class Student:public User{
	Course *courses[7];
	int numCourses;
public:	
	Student();
	void setCourses(Course &c);
	void enrollStudent();
	void CoursesDisplay();
	void AllocateCourses();
	int getNumCourse();
	Course *getCourse(int i);
};
Student:: Student()
{
	for(int i=0; i<7; i++)
		courses[i]=NULL;
}
void Student:: setCourses(Course &c)
{
	courses[numCourses]=&c;
	numCourses++;
}
void Student:: enrollStudent()
{
	for(int i=0; i<numCourses; i++)
	{
		courses[i]->setStudents(name);
	}	
}
void Student:: CoursesDisplay()
{
	for(int i=0; i<numCourses; i++)
	{
			cout<<"\t"<<courses[i]->getName()<<"\t"<<courses[i]->getCode()<<endl;
	}
	cout<<endl;
}
int Student:: getNumCourse()
{
	return numCourses;
}
Course *Student:: getCourse(int i)
{
	return courses[i];
}

#endif
