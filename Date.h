#ifndef DATE_H
#define DATE_H
#include<iostream>
using namespace std;

class Date{
	int day, month, year;
public:
	Date();
	void setDate();
	int getDay();
	int getMonth();
	int getYear();	
};
Date:: Date()
{
	day=month=year=0;
}
void Date:: setDate()
{
	int d, m, y;
	while(1)
	{
		cout<<"\tYear: ";
		cin>>y;
		if(y>=2023)
			break;
		else
			cout<<"\tInvalid Year, Enter again\n\n";		
	}
	while(1)
	{
		cout<<"\tMonth: ";
		cin>>m;
		if(m>=1 && m<=12)
			break;
		else
			cout<<"\tInvalid Month, Enter again\n\n";	
	}
	while(1)
	{
		cout<<"\tDay: ";
		cin>>d;
		if(d>=1 && d<=31)
		{
			if(m==2 && (d>=1 && d<=28))
				break;
			else if((m==4 || m==6 || m==9 || m==11) && (d>=1 && d<=30))
				break;
			else if((m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12) && (d>=1 && d<=31))
				break;
			else
				cout<<"\tInvalid Day, Enter again\n\n";			
		}
		else
			cout<<"\tInvalid Day, Enter again\n\n";
	}
	year=y;
	month=m;
	day=d;
}
int Date:: getDay()
{
	return day;
}
int Date:: getMonth()
{
	return month;
}
int Date:: getYear()
{
	return year;
}

#endif
