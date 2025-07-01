#ifndef QUIZ_H
#define QUIZ_H
#include"Time.h"
#include<iostream>
#include"Date.h"
#include"Question.h"
#include"Result.h"
using namespace std;


class Quiz{

	Time time;
	Date date;
	int duration;
	string topic;
	Question question[3];
	Result result;
	
public:

	void setDate();
	void setTime();
	void setTopic(string t);
	string getTopic();
	void setDuration();
	int getDuration();	
	void Interval();
	Question &getQues(int i);
	Date &getDate();
	Time &getTime();
	Result &getResult();
	
};
void Quiz:: setDate()
{
	date.setDate();
}
void Quiz:: setTime()
{
	time.setTime();
}
void Quiz:: setDuration()
{
	duration=time.ExamTime();
}
void Quiz:: setTopic(string t)
{
	topic=t;
}
int Quiz:: getDuration()
{
	return duration;
}
string Quiz:: getTopic()
{
	return topic;
}
void Quiz:: Interval()
{
	int hours, mins, sec;
	hours=duration/3600;
	duration%=3600;
	mins=duration/60;
	sec=duration%60;
	
	cout<<"\n\tExam Duration: \n\t"<<hours<<"hr : "<<mins<<"mins : "<<sec<<"sec\n";
}
Question &Quiz:: getQues(int i)
{
	return question[i];	
}
Date &Quiz:: getDate()
{
	return date;
}
Time &Quiz:: getTime()
{
	return time;
}
Result &Quiz:: getResult()
{
	return result;
}

#endif
