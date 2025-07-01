#include"Student.h"
#include"Teacher.h"
#include"Course.h"
#include"Display.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<cstring>
using namespace std;

int main()
{
	Course *courses=new Course[11];
	int numCourses=0;
	Student *students=new Student[216];
	int numStudents=0;
	string sNO, ID, name, coursesName, password, code, course[11];
	
	ifstream inputFile("Course Registration Data - Sheet1.csv");
	
	if (!inputFile.is_open()) 
	{
		cout << "Failed to open file!" << endl;
		return 1;
	}
	string line;
	getline(inputFile, line); // Skip the header line
	getline(inputFile, line); // Skip the header line
	while (getline(inputFile, line) && numStudents<216) 
	{   
		stringstream lineStream(line);
	
		getline(lineStream, sNO, ',');
		getline(lineStream, ID, ',');
		getline(lineStream, name, ',');
		getline(lineStream, course[0], ',');
		getline(lineStream, course[1], ',');
		getline(lineStream, course[2], ',');
		getline(lineStream, course[3], ',');
		getline(lineStream, course[4], ',');
		getline(lineStream, course[5], ',');
		getline(lineStream, course[6], ',');
		getline(lineStream, course[7], ',');
		getline(lineStream, course[8], ',');
		getline(lineStream, course[9], ',');
		getline(lineStream, course[10], ',');
		getline(lineStream, password, ',');
		
		students[numStudents].setName(name);
		students[numStudents].setID(ID);
		if(course[0]=="1")
			students[numStudents].setCourses(courses[0]);
		if(course[1]=="1")
			students[numStudents].setCourses(courses[1]);
		if(course[2]=="1")
			students[numStudents].setCourses(courses[2]);
		if(course[3]=="1")
			students[numStudents].setCourses(courses[3]);
		if(course[4]=="1")
			students[numStudents].setCourses(courses[4]);
		if(course[5]=="1")
			students[numStudents].setCourses(courses[5]);
		if(course[6]=="1")
			students[numStudents].setCourses(courses[6]);
		if(course[7]=="1")
			students[numStudents].setCourses(courses[7]);
		if(course[8]=="1")
			students[numStudents].setCourses(courses[8]);
		if(course[9]=="1")
			students[numStudents].setCourses(courses[9]);
		if(course[10]=="1")
			students[numStudents].setCourses(courses[10]);
		
		students[numStudents].setPassword(password);
		students[numStudents].enrollStudent();
		numStudents++;
	}
	inputFile.close();
	
	Teacher *teachers=new Teacher[11];
	int numTeacher=0;
	ifstream inputFile1("Teachers.csv");
	
	if (!inputFile1.is_open()) 
	{
		cout << "Failed to open file!" << endl;
		return 1;
	}
	getline(inputFile1, line); // Skip the header line
	while (getline(inputFile1, line) && numTeacher<11) 
	{   
		stringstream lineStream(line);
		
		getline(lineStream, ID, ',');
		getline(lineStream, password, ',');
		getline(lineStream, name, ',');
		getline(lineStream, coursesName, ',');
		getline(lineStream, code, ',');
    	
		teachers[numTeacher].setName(name);
		teachers[numTeacher].setID(ID);
		teachers[numTeacher].setPassword(password);
		courses[numCourses].setName(coursesName);
		courses[numCourses].setCode(code);
		
		teachers[numTeacher].setCourse(courses[numCourses]);
    	
		numTeacher++;
		numCourses++;
	}
	inputFile1.close();
	
	int count=1;
	int numTopic=0;
	numCourses=0;
	ifstream inputFile2("Quiz.csv");
	string mcqs, tf, descriptive, topic;
	if (!inputFile2.is_open()) 
	{
		cout << "Failed to open file!" << endl;
		return 1;
	}
	getline(inputFile2, line); // Skip the header line
	getline(inputFile2, line); // Skip the header line 
	while (getline(inputFile2, line) && numCourses<11) 
	{  
		stringstream lineStream(line);
	
		getline(lineStream, topic, ',');
		getline(lineStream, mcqs, ',');
		getline(lineStream, tf, ',');
		getline(lineStream, descriptive, ',');
		
		courses[numCourses].quiz[numTopic].setTopic(topic);
		courses[numCourses].quiz[numTopic].getQues(0).setQuestion(mcqs);
		courses[numCourses].quiz[numTopic].getQues(1).setQuestion(tf);
		courses[numCourses].quiz[numTopic].getQues(2).setQuestion(descriptive);
		courses[numCourses].quiz[numTopic].getQues(0).setType("MCQS Questions");
		courses[numCourses].quiz[numTopic].getQues(1).setType("T/F Questions");
		courses[numCourses].quiz[numTopic].getQues(2).setType("Descriptive Questions");
	
		if(count==5)
		{
			count=0;
			numTopic++;
		}
		if(numTopic==3)
		{	
			getline(inputFile2, line); // Skip the header line
			getline(inputFile2, line); // Skip the header line 
			numTopic=0;
			numCourses++;
		}
		count++;
	}
	inputFile2.close();

	count=1;
	numTopic=0;
	numCourses=0;
	ifstream inputFile3("Answers.csv");
	if (!inputFile3.is_open()) 
	{
		cout << "Failed to open file!" << endl;
		return 1;
	}
	getline(inputFile3, line); // Skip the header line
	getline(inputFile3, line); // Skip the header line 
	while (getline(inputFile3, line) && numCourses<11) 
	{  
		stringstream lineStream(line);
	
		getline(lineStream, topic, ',');
		getline(lineStream, mcqs, ',');
		getline(lineStream, tf, ',');
		getline(lineStream, descriptive, ',');
		courses[numCourses].quiz[numTopic].getQues(0).setAnswers(mcqs);
		courses[numCourses].quiz[numTopic].getQues(1).setAnswers(tf);
		courses[numCourses].quiz[numTopic].getQues(2).setAnswers(descriptive);
		
	
		if(count==5)
		{
			count=0;
			numTopic++;
		}
		if(numTopic==3)
		{	
			getline(inputFile3, line); // Skip the header line
			getline(inputFile3, line); // Skip the header line 
			numTopic=0;
			numCourses++;
		}
		count++;
	}
	inputFile2.close();
	
	Display d;
	d.Menu(students, teachers, courses);
	
	delete[] teachers;
	delete[] students;
	delete[] courses;
	
	return 0;
}
