#ifndef TIME_H
#define TIME_H
#include<iostream>
using namespace std;

class Time{
	int hour, min, sec;
public:
	Time();
	void setTime();
	int getHour();
	int getMin();
	int getSec();	
	int ExamTime();
	int examTime;
};
Time:: Time()
{
	hour=min=sec=0;
}
void Time:: setTime()
{
	int h, m, s;
	while(1)
	{
		cout<<"\tHour: ";
		cin>>h;
		if(h>=0 && h<=23)
			break;
		else
			cout<<"\tInvalid Hour, Enter again\n\n";		
	}
	while(1)
	{
		cout<<"\tMinute: ";
		cin>>m;
		if(m>=0 && m<=59)
			break;
		else
			cout<<"\tInvalid Minutes, Enter again\n\n";	
	}
	while(1)
	{
		cout<<"\tSecond: ";
		cin>>s;
		if(s>=0 && s<=59)
			break;
		else
			cout<<"\tInvalid Seconds, Enter again\n\n";
	}
	hour=h;
	min=m;
	sec=s;
}
int Time:: getHour()
{
	return hour;
}
int Time:: getMin()
{
	return min;
}
int Time:: getSec()
{
	return sec;
}
int Time:: ExamTime()
{
	int startTime=hour*3600 + min*60 + sec;//converting time to seconds
	int endTime=0;
	while(1)
	{
		Time end;
		cout<<"\tEnter End time\n";
		end.setTime();
		endTime=end.getHour()*3600 + end.getMin()*60 + end.getSec();//converting time to seconds
		if(startTime<endTime)
			break;
		else 
			cout<<"\tThe end time should be after the start time\n\n";	
	}
	examTime=endTime-startTime;	
	return examTime;
}


#endif
