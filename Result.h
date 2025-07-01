#ifndef RESULT_H
#define RESULT_H
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;


class Result{
    string *studentName;
    string courseName;
    string TopicName;
    string *marks;
    int numStudents;
public:
    Result();
    void setMembers(string *courses, string course, string topic, int *students);
    string getCourseName();
    string getTopic();
    string getMarks(string name);
};
Result:: Result()
{
    studentName=NULL;
    marks=NULL;
    courseName=" ";
    TopicName=" ";
    numStudents=0;
}
string Result:: getTopic()
{
    return TopicName;
}
string Result:: getMarks(string name)
{
    int index=0;
    for(int i=0; i<numStudents; i++)
    {
        if(studentName[i]==name)
        {
            index=i;
            break;
        }
    }
    return marks[index];
}
string Result:: getCourseName()
{
    return courseName;
}
void Result::setMembers(string *courses, string course, string topic, int *students)
{
    string m, attendance;
    ifstream inputFile("MarkSheet.csv");
	
	if (!inputFile.is_open()) 
	{
		cout << "Failed to open file!" << endl;
        return;
	}
    string line;   
    while(getline(inputFile, line))
    {
        int num;
	    stringstream lineStream(line);
        getline(lineStream, courseName, ',');
        getline(lineStream, TopicName, ',');
        getline(inputFile, line);//skip the header line
        if(course==courseName && topic==TopicName)
        {
            for(int i=0; i<11; i++)
            {
                if(courses[i]==courseName)
                {
                    numStudents=students[i];
                    studentName=new string[numStudents];
                    marks=new string[numStudents];
                }
            }
            for(int i=0; i<numStudents; i++)
            {
                getline(inputFile, line);
                stringstream lineStream1(line);
                getline(lineStream1, studentName[i], ',');
                getline(lineStream1, attendance, ',');//skip the attendance column
                getline(lineStream1, marks[i], ',');
            }   
            break;         
        }
        else
        {
            for(int i=0; i<11; i++)
            {
                if(courses[i]==courseName)
                {
                    num=students[i];
                }
            }
            for(int i=0; i<num; i++)
                getline(inputFile, line);
        }
    }        
	inputFile.close();
}

#endif