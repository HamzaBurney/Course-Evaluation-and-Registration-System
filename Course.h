#ifndef COURSE_H
#define COURSE_H
#include<iostream>
#include"Quiz.h"
using namespace std;

class Course{
private:	

	string code;
	string name;
	string *studentsEnrolled;
	string instructor;
	int numStudentsEnrolled;
	
public:
	Quiz quiz[3];
	Course();
	void setCode(string c);
	void setName(string n);
	void setStudents(string n);
	void setInstructor(string instructorName);
	void setNumStudentsEnrolled(int num);
	string getCode();
	string getName();	
	string getStudents(int i);
	string getInstructor();
	int getNumStudentsEnrolled();
	void studentsInCourse();
	~Course();

};
Course:: Course()
{
	code=name=instructor="";
	studentsEnrolled=NULL;
	numStudentsEnrolled=0;
}
void Course:: setCode(string c)
{
	code=c;
}
void Course:: setName(string n)
{
	name=n;
}
void Course:: setStudents(string n)
{
	string temp[numStudentsEnrolled];
	for(int i=0; i<numStudentsEnrolled; i++)
		temp[i]=studentsEnrolled[i];
		
	delete[] studentsEnrolled;
	numStudentsEnrolled++;
	studentsEnrolled=new string[numStudentsEnrolled];
	
	for(int i=0; i<numStudentsEnrolled-1; i++)
		studentsEnrolled[i]=temp[i];
	studentsEnrolled[numStudentsEnrolled-1]=n;
}
void Course:: setInstructor(string instructorName)
{
	instructor=instructorName;
}
string Course:: getCode()
{
	return code;
}
string Course:: getName()
{
	return name;
}
string Course:: getStudents(int i)
{
	return studentsEnrolled[i];
}
string Course:: getInstructor()
{
	return instructor;
}
int Course:: getNumStudentsEnrolled()
{
	return numStudentsEnrolled;
} 
void Course:: studentsInCourse()
{
	for(int i=0; i<numStudentsEnrolled; i++)
	{
		cout<<"\t"<<i+1<<") "<<studentsEnrolled[i]<<endl;
	}
	cout<<endl<<endl;
}
Course:: ~Course()
{
	delete[] studentsEnrolled;
}



#endif
