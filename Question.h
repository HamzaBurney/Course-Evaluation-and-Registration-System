#ifndef QUESTION_H
#define QUESTION_H
#include<iostream>
using namespace std;

class Question{

	string type;
	int numQues;
	int numAns;
	string answers[5];
	string question[5];
	bool attendance;
	
public:
	
	Question();
	void setQuestion(string ques);
	void setAnswers(string ans);
	void setType(string t);
	string getType();
	string getAnswer(int i);
	string getQuestion(int i);
	int getNumQues();
	int getNumAns();
	void displayQuestions(int num, int randomValues[]);
	void setAttendance(bool att);
	
};

Question:: Question()
{
	attendance=0;
	numAns=0;
	numQues=0;
	type="";
	for(int i=0; i<5; i++)
	{
		answers[i]=question[i]="";
	}	
}
void Question:: setQuestion(string ques)
{
	question[numQues]=ques;
	numQues++;
}
void Question:: setAnswers(string ans)
{
	answers[numAns]=ans;
	numAns++;
}
void Question:: setType(string t)
{
	type=t;
}
string Question:: getType()
{
	return type;
}
string Question:: getAnswer(int i)
{
	return answers[i];
}
string Question:: getQuestion(int i)
{
	return question[i];
}
int Question:: getNumQues()
{
	return numQues;
}
int Question:: getNumAns()
{
	return numAns;
}
void Question:: displayQuestions(const int num, int randomValues[])
{
	
	if(num>0)
	{	
		cout<<"\n\t"<<type<<": \n";
		for(int i=0; i<num; i++)
		{
			cout<<"\t"<<i+1<<") "<<question[randomValues[i]]<<endl<<endl;	
		}
	}
}
void Question:: setAttendance(bool att)
{
	attendance=att;
}

#endif
