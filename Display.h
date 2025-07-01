#ifndef DISPLAY_H
#define DISPLAY_H
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<time.h>

int countQuiz=3;
class Display{
public:
	void Menu(Student *students, Teacher *teachers, Course *courses);
	int Login(Student *students, Teacher *teachers, string user);
	void ChangePassword(Student &students, Teacher &teachers, string user);
	void GeneralInformation();
	void setQuiz(Student *students, Teacher *teachers, Course *courses, int index);
	void PendingQuiz(Student *students, Teacher *teachers, Course *courses, int index);
	void GenerateResult(Course *courses, Student *student, int index, string course, string topic, int indexQuiz, string mcqsKey[][5], string tfKey[][5], string *mcqsAns, string *tfAns, string *descriptiveAns);
	void studentMarks(Student &students);
	void QuizAnalytics(Teacher &teacher);
};

void Display:: studentMarks(Student &student)
{
	int numCourses=student.getNumCourse();
	int count=0;
	for(int i=0; i<numCourses; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(student.getCourse(i)->quiz[j].getResult().getCourseName()==" ")		
				count++;
			else
			{
				cout<<"\n\tCourse: "<<student.getCourse(i)->quiz[j].getResult().getCourseName()<<endl;
				cout<<"\tTopic: "<<student.getCourse(i)->quiz[j].getResult().getTopic()<<endl;
				cout<<"\tMarks: "<<student.getCourse(i)->quiz[j].getResult().getMarks(student.getName())<<endl<<endl;
			}	
		}	
	}
	if(count==numCourses*3)
		cout<<"\n\tNo Marks Available\n\n";
}
void Display:: GenerateResult(Course *courses ,Student *student, int index, string course, string topic, int indexQuiz, string mcqsKey[][5], string tfKey[][5], string *mcqsAns, string *tfAns, string *descriptiveAns)
{
	float marks=0;
	bool attendance=1;
	int numQs=0;
	for(int i=0; i<5; i++)
	{
		if(mcqsKey[indexQuiz][i].empty())
			break;
		if(mcqsAns[i]==mcqsKey[indexQuiz][i])
			marks++;
		numQs++;	
	}
	for(int i=0; i<5; i++)
	{
		if(tfKey[indexQuiz][i].empty())
			break;
		if(tfAns[i]==tfKey[indexQuiz][i])
			marks++;
		numQs++;	
	}
	for(int i=0; i<5; i++)
	{
		if(descriptiveAns[i].empty())
			break;
		stringstream ss(descriptiveAns[i]);
    	string word;
    	float count = 0;

		while (ss >> word)
			count+=0.1;
		marks+=count;	
		numQs++;
	}

	string filename = "MarkSheet.csv"; // CSV file to set quiz
	ofstream fout;
	fout.open(filename, ios::app);
    
	srand(time(0));
	if (fout.is_open()) 
	{
		fout<<course<<","<<topic<<endl;
		fout<<"Student Name, Attendance, Marks"<<endl;
		fout<<student[index].getName()<<","<<"1"<<","<<marks<<endl;
		for(int i=0; i<student[index].getNumCourse(); i++)
		{
			if(student[index].getCourse(i)->getName()==course)
			{
				for(int j=0; j<student[index].getCourse(i)->getNumStudentsEnrolled(); j++)
				{
					if(student[index].getCourse(i)->getStudents(j)==student[index].getName())
						continue;
					fout<<student[index].getCourse(i)->getStudents(j)<<",";
					int attendance=rand()%2;
					if(attendance==0)
						fout<<attendance<<","<<"0"<<endl;
					else
					{
						marks=rand()%10;
						fout<<attendance<<","<<marks<<endl;
					}	
				}
				break;
			}
		} 

		fout.close();
		cout << "\tFile updated successfully.\n";	
	}
	else 
	{
		cout << "\tError opening file.\n";
	}
	string courseName[11];
	int numStudentsEnrolled[11];
	for(int i=0; i<11; i++)
	{
		courseName[i]=courses[i].getName();
		numStudentsEnrolled[i]=courses[i].getNumStudentsEnrolled();
	}
	for(int i=0; i<11; i++)
	{
		if(courses[i].getName()==course)
		{
			for(int j=0; j<3; j++)
			{
				if(courses[i].quiz[j].getTopic()==topic)
				{
					courses[i].quiz[j].getResult().setMembers(courseName , course, topic, numStudentsEnrolled);
				}
			}
		}
	}

	filename = "QuizAnalytics.csv"; // CSV file to set quiz
	fout;
	fout.open(filename, ios::app);
    
	srand(time(0));
	if (fout.is_open()) 
	{
		fout<<course<<","<<topic<<","<<numQs<<endl;
		fout<<"Student Name,"<<student[index].getName()<<",";
		for(int i=0; i<student[index].getNumCourse(); i++)
		{
			if(student[index].getCourse(i)->getName()==course)
			{
				for(int j=0; j<student[index].getCourse(i)->getNumStudentsEnrolled(); j++)
				{
					if(student[index].getCourse(i)->getStudents(j)==student[index].getName())
						continue;
					fout<<student[index].getCourse(i)->getStudents(j)<<",";	
				}
				break;
			}
		}
		fout<<endl;
		for(int i=1; i<=numQs; i++) 
		{
			fout<<"Question "<<i<<","<<"1,";
			for(int k=0; k<student[index].getNumCourse(); k++)
			{	
				if(student[index].getCourse(k)->getName()==course)
				{
					for(int j=0; j<student[index].getCourse(k)->getNumStudentsEnrolled(); j++)
					{
						if(student[index].getCourse(k)->getStudents(j)==student[index].getName())
							continue;
						fout<<rand()%2<<",";
					}
					break;
				}
			}
			fout<<endl;
		}

		fout.close();
		cout << "\tFile updated successfully.\n";	
	}
	else 
	{
		cout << "\tError opening file.\n";
	}
}
void Display:: setQuiz(Student *students, Teacher *teachers, Course *courses, int index)
{
	countQuiz++;
	int num[4];//index 0 for quizNum, index 1 for num of MCQs, index 2 for num of T/F, index 3 for num of descriptive ques
	while(1)
	{
		cout<<"\tEnter the topic for Quiz: \n\n";
		cout<<"\t1) "<<courses[index].quiz[0].getTopic()<<endl;
		cout<<"\t2) "<<courses[index].quiz[1].getTopic()<<endl;
		cout<<"\t3) "<<courses[index].quiz[2].getTopic()<<endl;
		cout<<"\tPress a number: ";
		cin>>num[0];
		if(num[0]>=1 && num[0]<=3)
			break;
		else	
			cout<<"\tInvalid Topic number, Enter again\n\n";	
	}
	num[0]--;
	cout<<"\n\tEnter the Date of Quiz\n";
	courses[index].quiz[num[0]].setDate();
	cout<<"\n\n\tEnter the Time of Quiz\n";
	courses[index].quiz[num[0]].setTime();
	courses[index].quiz[num[0]].setDuration();
	courses[index].quiz[num[0]].Interval();
	
	while(1)
	{
		cout<<"\n\tEnter the number of MCQs you want to include (0-5): ";
		cin>>num[1];	
		if(num[1]>=0 && num[1]<=5)
			break;
		else	
			cout<<"\tInvalid input, Enter again\n\n";
	}
	
	while(1)
	{
		cout<<"\n\tEnter the number of True/False Questions you want to include (0-5): ";
		cin>>num[2];
		if(num[2]>=0 && num[2]<=5)
			break;
		else	
			cout<<"\tInvalid input, Enter again\n\n";
	}
	while(1)
	{
		cout<<"\n\tEnter the number of Descriptive Questions you want to include (0-5): ";
		cin>>num[3];
		if(num[3]>=0 && num[3]<=5)
			break;
		else	
			cout<<"\tInvalid input, Enter again\n\n";
	}
	
	srand(time(0));
	int randomValues[5];
	for(int i=0; i<5; i++)//setting values 1-5 in an array
		randomValues[i]=i;	
	for(int i=4 ; i>0; --i)//shuffling the array
	{
		int j=rand()%(i+1);
		swap(randomValues[i], randomValues[j]);
	}
	
	string filename = "Pending Quiz.csv"; // CSV file to set quiz
	ofstream fout;
	fout.open(filename, ios::app);
    
	if (fout.is_open()) 
	{
		fout<<courses[index].getName()<<",";
		fout<<courses[index].quiz[num[0]].getTopic()<<",";
		fout<<courses[index].quiz[num[0]].getTime().examTime<<endl;
		fout<<courses[index].quiz[num[0]].getDate().getYear()<<",";
		fout<<courses[index].quiz[num[0]].getDate().getMonth()<<",";
		fout<<courses[index].quiz[num[0]].getDate().getDay()<<endl;
		fout<<courses[index].quiz[num[0]].getTime().getHour()<<",";
		fout<<courses[index].quiz[num[0]].getTime().getMin()<<",";
		fout<<courses[index].quiz[num[0]].getTime().getSec()<<endl;
		for(int i=0; i<5; i++)
		{
			if(i<num[1])
				fout<<courses[index].quiz[num[0]].getQues(0).getQuestion(i)<<",";//writing MCQs to the csv file
			else
				fout<<",";
				
			if(i<num[2])
				fout<<courses[index].quiz[num[0]].getQues(1).getQuestion(i)<<",";//writing TF to the csv file
			else
				fout<<",";
			
			if(i<num[3])
				fout<<courses[index].quiz[num[0]].getQues(2).getQuestion(i);//writing Descriptive to the csv file
			fout<<endl;
		}
		for(int i=0; i<5; i++)
		{
			if(i<num[1])
				fout<<courses[index].quiz[num[0]].getQues(0).getAnswer(i)<<",";//writing MCQs to the csv file
			else
				fout<<",";
				
			if(i<num[2])
				fout<<courses[index].quiz[num[0]].getQues(1).getAnswer(i)<<",";//writing TF to the csv file
			else
				fout<<",";
			
			if(i<num[3])
				fout<<courses[index].quiz[num[0]].getQues(2).getAnswer(i);//writing Descriptive to the csv file
			fout<<endl;
		}
		fout.close();
		cout << "\tFile updated successfully.\n";	
	}
	else 
	{
		cout << "\tError opening file.\n";
	}
	
	courses[index].quiz[num[0]].getQues(0).displayQuestions(num[1], randomValues);//display mcq questions
	courses[index].quiz[num[0]].getQues(1).displayQuestions(num[2], randomValues);//display t/f questions
	courses[index].quiz[num[0]].getQues(2).displayQuestions(num[3], randomValues);//display  questions
	
}
void Display:: PendingQuiz(Student *students, Teacher *teachers, Course *courses, int index)
{
	int i=0;
	string courseName[countQuiz], topic[countQuiz], examDuration[countQuiz];
	string year[countQuiz], month[countQuiz], day[countQuiz];
	string hr[countQuiz], min[countQuiz], sec[countQuiz];
	string mcqs[countQuiz][5], tf[countQuiz][5], descriptive[countQuiz][5];
	string mcqsKey[countQuiz][5], tfKey[countQuiz][5], descriptiveKey[countQuiz][5];
	string mcqsAns[5]={"\0"}, tfAns[5]={"\0"};
	string descriptiveAns[5]={"\0"};

	ifstream inputFile("Pending Quiz.csv");
	
	if (!inputFile.is_open()) 
	{
		cout << "\tNo Quiz Available\n" << endl;
	}
	string line;
	while (getline(inputFile, line)) 
	{   
		stringstream lineStream(line);

		getline(lineStream, courseName[i], ',');
		getline(lineStream, topic[i], ',');
		getline(lineStream, examDuration[i], ',');

		getline(inputFile, line);//reading date
		stringstream lineStream1(line);

		getline(lineStream1, year[i], ',');
		getline(lineStream1, month[i], ',');
		getline(lineStream1, day[i], ',');

		getline(inputFile, line);//reading time
		stringstream lineStream2(line);

		getline(lineStream2, hr[i], ',');
		getline(lineStream2, min[i], ',');
		getline(lineStream2, sec[i], ',');

		int j=0;
		while(j<5)//reading questions
		{	
			getline(inputFile,line); 
			stringstream lineStream3(line);
			getline(lineStream3, mcqs[i][j], ',');
			getline(lineStream3, tf[i][j], ',');
			getline(lineStream3, descriptive[i][j], ',');
			j++;
		}
		j=0;
		while(j<5)//reading questions
		{	
			getline(inputFile,line); 
			stringstream lineStream4(line);
			getline(lineStream4, mcqsKey[i][j], ',');
			getline(lineStream4, tfKey[i][j], ',');
			getline(lineStream4, descriptiveKey[i][j], ',');
			j++;
		}
		i++;
	}
	inputFile.close();

	int count=0;
	int numCourses=students[index].getNumCourse();
	for(int j=0; j<countQuiz; j++)
	{
		for(int k=0; k<numCourses; k++)
		{
			if(courseName[j]==students[index].getCourse(k)->getName())
			{
				count++;
				cout<<"\t"<<count<<") Course: "<<courseName[j];
				cout<<"\t\tTopic: "<<topic[j]<<endl;
			}
		}	
	}
	string course, topicName;
	cout<<endl;
	cout<<"\tSelect the course: ";
	cin.ignore();
	getline(cin, course);
	cin.ignore();
	cout<<"\tSelect the topic: ";
	getline(cin, topicName);
	int indexQuiz;

	for(int i=0; i<countQuiz; i++)
	{
		if(course==courseName[i] && topic[i]==topicName)
		{
			indexQuiz=i;
			cout<<"\n\tCourse: "<<courseName[i]<<"\tTopic: "<<topic[i]<<endl;
			cout<<"\tDate: "<<day[i]<<" / "<<month[i]<<" / "<<year[i];
			cout<<"\tStart Time: "<<hr[i]<<" : "<<min[i]<<" : "<<sec[i];
			cout<<"\tDuration: "<<stoi(examDuration[i])/60<<" mins\n\n";
			if(mcqs[i][0].empty()==0)
			{
				cout<<"\tMCQs: Write only a,b,c,d\n\n";
				for(int j=0; j<5; j++)
				{
					if(mcqs[i][j].empty())
						break;
					cout<<"\t"<<j+1<<") "<<mcqs[i][j]<<endl;
					while(1)
					{
						cout<<"\tAnswer: ";
						cin>>mcqsAns[j];
						if(mcqsAns[j]=="a" || mcqsAns[j]=="b" || mcqsAns[j]=="c" || mcqsAns[j]=="d")
							break;
						else
							cout<<"\tWrite only a,b,c,d\n\n";	
					}
				}
			}
			if(tf[i][0].empty()==0)
			{	
				cout<<"\n\tTrue/False Questions: Write only t,f\n\n";
				for(int j=0; j<5; j++)
				{
					if(tf[i][j].empty())
						break;
					cout<<"\t"<<j+1<<") "<<tf[i][j]<<endl;
					while(1)
					{
						cout<<"\tAnswer: ";
						cin>>tfAns[j];
						if(tfAns[j]=="t" || tfAns[j]=="f" || tfAns[j]=="T" || tfAns[j]=="F")
							break;
						else
							cout<<"\tWrite only t,f\n\n";	
					}
				}
			}
			if(descriptive[i][0].empty()==0)
			{	
				cout<<"\n\tDescrive Questions:\n\n";
				for(int j=0; j<5; j++)
				{
					if(descriptive[i][j].empty())
						break;
					cout<<"\t"<<j+1<<") "<<descriptive[i][j]<<endl;
					cout<<"\tAnswer: ";
					cin.ignore();
					getline(cin,descriptiveAns[j]);
				}
			}
			cout<<endl;
			GenerateResult(courses, students, index, course, topicName, indexQuiz, mcqsKey, tfKey, mcqsAns, tfAns, descriptiveAns);
		}
	}
}
void Display:: GeneralInformation()
{
	cout<<"~~~~~~~~~~~~~~~ABOUT PAGE~~~~~~~~~~~~~~~\n\n";
	cout<<"Welcome to the university examination system!\nOur platform is an essential part of the academic process and is designed to evaluate the knowledge, skills, and abilities of our students.\nOur mission is to create a fair and transparent testing process that enables our students to demonstrate their understanding and mastery of the subject matter.\nOur team is dedicated to ensuring that our examination system is comprehensive, accurate, and reflective of the curriculum.\nWe strive to provide a range of testing formats and schedules to accommodate the needs of our diverse student body.\nOur goal is to promote academic excellence and to prepare our students for success in their future careers.\n\n";
	cout<<"~~~~~~~~~~~~~~~PAGE PAGE~~~~~~~~~~~~~~~\n\n";
}	
void Display:: QuizAnalytics(Teacher &teacher)
{
	string courseName, topic, qs, marks;
	int numQs, numStudents=0, count=0;
	ifstream inputFile("QuizAnalytics.csv");
	
	if (!inputFile.is_open()) 
	{
		cout << "\tNo Quizzes conducted\n" << endl;
        return;
	}
    string line;   
    while(getline(inputFile, line))
    {
	    stringstream lineStream(line);
        getline(lineStream, courseName, ',');
		getline(lineStream, topic, ',');
		getline(lineStream, qs, ',');
		stringstream ss(qs);
		ss>>numQs;
		getline(inputFile, line);
		if(courseName==teacher.getCourseName())
		{
			cout<<"\n\tThe horizontal lines shows the number of students to score full marks";
			cout<<"\n\tCourse: "<<courseName<<"\tTopic: "<<topic<<endl<<endl;
			cout<<"\tNumber of Questions\n\t|\n";
			for(int i=1; i<=numQs; i++)
			{
				numStudents=0;
				getline(inputFile, line);
				stringstream lineStream1(line);
				getline(lineStream1, qs, ',');
				if(i<10)
					cout<<"   Qs"<<i<<"  |";
				else
					cout<<"   Qs"<<i<<" |";	
				while(1)
				{
					getline(lineStream1, marks, ',');
					if(numStudents==teacher.NumStudentsIncourse())
					{
						cout<<"  "<<count<<endl;
						count=0;
						break;
					}
					if(marks=="1")
					{
						count++;
						cout<<"-";
					}
					numStudents++;
				}
			}
			cout<<"\t|";
			for(int j=1; j<numStudents; j++)
				cout<<"_";
			cout<<"\n\t\t\t\t\t\tNum Students ("<<numStudents<<")\n\n\n";	
		}
		else
		{
			for(int i=0; i<numQs; i++)
				getline(inputFile, line);
		}
    }        
	inputFile.close();
}
void Display:: Menu(Student *students, Teacher *teachers, Course *courses)
{
	int index=-1;
	int page;
	string user="General";
	while(1)
	{
		cout<<"~~~~~~~~~~~~~~~MENU PAGE~~~~~~~~~~~~~~~\n\n";
		if(user=="General")
		{
			cout<<"\t1) About\n";
			cout<<"\t2) Courses\n";
			cout<<"\t3) Student Login\n";
			cout<<"\t4) Teacher Login\n";
			cout<<"\t5) EXIT\n";
			
			while(1)
			{
				cout<<"\tPress a number: ";
				cin>>page;
		
				if(page<1 || page>5)
					cout<<"\tInvalid number, Enter again\n";
				else
					break;	
			}
		}
		else if(user=="student")
		{
			cout<<"\t1) About\n";
			cout<<"\t2) My Courses\n";
			cout<<"\t3) Pending Quizzes\n";
			cout<<"\t4) Marks\n";
			cout<<"\t5) Change Password\n";
			cout<<"\t6) Logout\n";
			cout<<"\t7) EXIT\n";
			
			while(1)
			{
				cout<<"\tPress a number: ";
				cin>>page;
		
				if(page<1 || page>7)
					cout<<"\tInvalid number, Enter again\n";
				else
					break;	
			}
		}
		else if(user=="teacher")
		{
			cout<<"\t1) About\n";
			cout<<"\t2) My Course\n";
			cout<<"\t3) Change Password\n";
			cout<<"\t4) Logout\n";
			cout<<"\t5) EXIT\n";
			
			while(1)
			{
				cout<<"\tPress a number: ";
				cin>>page;
		
				if(page<1 || page>5)
					cout<<"\tInvalid number, Enter again\n";
				else
					break;	
			}
		}
		else if(user=="course")
		{
			cout<<"\t1) Course Details\n";
			cout<<"\t2) Students\n";
			cout<<"\t3) Set Quiz\n";
			cout<<"\t4) Quiz Analytics\n";
			cout<<"\t5) Go Back\n";
			
			while(1)
			{
				cout<<"\tPress a number: ";
				cin>>page;
		
				if(page<1 || page>5)
					cout<<"\tInvalid number, Enter again\n";
				else
					break;	
			}
		}
		
		cout<<endl<<endl;
	
		cout<<"\n~~~~~~~~~~~~~~~MENU PAGE~~~~~~~~~~~~~~~\n\n\n";
		
		if(user=="General")
		{
			switch(page)
			{
				case 1: {
					GeneralInformation();//about
					break;
				}
				case 2: {//Courses
					for(int i=0; i<11; i++)
					{
						cout<<"\t"<<teachers[i].getCourseName()<<"\t"<<teachers[i].getCourseCode()<<endl;
					}
					cout<<endl;
					break;
				}
				case 3: {//student login
					user="student";
					index=Login(students, teachers, user);//teacher login
					break;
				}
				case 4: {//teacher login
					user="teacher";
					index=Login(students, teachers, user);//teacher login
					break;
				}
				case 5: {//exit
					cout<<"\tGOODBYE :)\n\n";//exit
					return;
				}
			}
		}
		else if(user=="student")
		{
			switch(page)
			{
				case 1: {//about
					GeneralInformation();
					break;
				}
				case 2: {//courses of student
					students[index].CoursesDisplay();
					break;
				}
				case 3: {//pending quizzes
					PendingQuiz(students, teachers, courses, index);
					break;		
				}
				case 4: {//marks
					studentMarks(students[index]);
					break;
				}
				case 5: {//change account password
					ChangePassword(students[index], teachers[index], user);
					break;		
				}
				case 6: {//logout
					cout<<"Logout successful\n";
					user="General";
					break;
				}
				case 7: {//exit
					cout<<"\tGOODBYE :)\n\n";
					return;
				}
			}
		}
		else if(user=="teacher")
		{
			switch(page)
			{
				case 1: {//about
					GeneralInformation();
					break;
				}
				case 2: {//courses of teacher
					user="course";
					break;
				}
				case 3: {//change account password
					ChangePassword(students[index], teachers[index], user);
					break;		
				}
				case 4: {//logout teacher account
					cout<<"Logout successful\n";
					user="General";
					break;
				}
				case 5: {//exit
					cout<<"\tGOODBYE :)\n\n";
					return;
				}
			}
		}
		else if(user=="course")
		{
			switch(page)
			{
				case 1: {//course details, name and code, instructor
					cout<<"\tCourse Name: "<<teachers[index].getCourseName()<<endl;
					cout<<"\tCourse Code: "<<teachers[index].getCourseCode()<<endl;
					cout<<"\tCourse Instructor: "<<teachers[index].getName()<<endl;
					break;
				}
				case 2: {//students in the course
					teachers[index].studentsInCourse();
					break;		
				}
				case 3: {//setQuiz
					setQuiz(students, teachers, courses, index);
					break;		
				}

				case 4: {//Quiz Analytics
					QuizAnalytics(teachers[index]);
					break;		
				}
				case 5: {//go back
					user="teacher";
					break;		
				}
			}
		}
	}
}
int Display:: Login(Student *students, Teacher *teachers, string user)
{
	int index=-1;
	string ID, password;
	cout<<"~~~~~~~~~~~~~~~LOGIN PAGE~~~~~~~~~~~~~~~\n\n";
	
	while(1)
	{
		cout<<"\tID: ";
		cin>>ID;
		cout<<"\tPASSWORD: ";
		cin>>password;
		
		if(user=="student")
		{
			for(int i=0; i<216; i++)
			{
				if(students[i].getPassword()==password && students[i].getID()==ID)
					index=i;
			}
		}
		if(user=="teacher")
		{
			for(int i=0; i<11; i++)
			{
				if(teachers[i].getPassword()==password && teachers[i].getID()==ID)
					index=i;
			}
		}
		
		if(index>-1)
			break;
		else
			cout<<"\tInvalid ID or Password.\nEnter again\n";		
	}
	
	cout<<"\n~~~~~~~~~~~~~~~LOGIN PAGE~~~~~~~~~~~~~~~\n\n";
	
	cout<<"\n\tReturning to MAIN MENU.........\n\n";
	return index;
}
void Display:: ChangePassword(Student &students, Teacher &teachers, string user)
{
	bool verify;
	string passNew, passOld;
	cout<<"~~~~~~~~~~~~~~~CHANGE PASSWORD~~~~~~~~~~~~~~~\n\n";
	
	if(user=="student")
	{
		passOld=students.getPassword();
		passNew=students.changePassword();
		
		string filename = "Course Registration Data - Sheet1.csv"; // CSV file to be updated
		string newfilename="Updated Course Registration Data - Sheet1.csv";
		
		string oldword = passOld; // Word to be replaced
		string newword = passNew; // New word
    
		ifstream fin(filename);
		ofstream fout (newfilename);
    
		if (fin.is_open() && fout.is_open()) 
		{
			string line;
			while (getline(fin, line)) 
			{
				stringstream ss(line);
				string cell;
				bool firstcell = true;
				int cellnum=0;
				string firsttwo;
				while (getline(ss, cell, ',')) 
				{
					cellnum++;
					if(cellnum==1 || cellnum==2)
					{
						if(!firstcell)
							fout << ",";
					}
					else
					{
						if (!firstcell) 
						{
							if (cell == oldword) 
							{
								cell = newword;
							}
							fout << ",";
						}
					}	
					firstcell = false;
					fout << cell;
				}
				fout << endl;
			}
			fin.close();
			fout.close();
			cout << "\tFile updated successfully.\n";
			
			// Replace old file with updated file
			if (remove(filename.c_str()) != 0) {
				cout << "\tError deleting file.\n";
			}
			else if (std::rename(newfilename.c_str(), filename.c_str()) != 0) {
				cout << "\tError renaming file.\n";
			}
			else {
				cout << "\tFile updated successfully.\n";
			}
		}
		else 
		{
			cout << "\tError opening file.\n";
		}
		
	}
	if(user=="teacher")
	{
		passOld=teachers.getPassword();
		passNew=teachers.changePassword();
		
		string filename = "Teachers.csv"; // CSV file to be updated
		string newfilename="Updated Teachers.csv";
		
		string oldword = passOld; // Word to be replaced
		string newword = passNew; // New word
    
		ifstream fin(filename);
		ofstream fout (newfilename);
    
		if (fin.is_open() && fout.is_open()) 
		{
			string line;
			while (getline(fin, line)) 
			{
				stringstream ss(line);
				string cell;
				bool firstcell = true;
				while (getline(ss, cell, ',')) 
				{
					if (!firstcell) 
					{
						if (cell == oldword) 
						{
							cell = newword;
						}
						fout << ",";
					}
					firstcell = false;
					fout << cell;
				}
				fout << endl;
			}
			fin.close();
			fout.close();
			cout << "\tFile updated successfully.\n";
			
			// Replace old file with updated file
			if (remove(filename.c_str()) != 0) {
				cout << "Error deleting file.\n";
			}
			else if (std::rename(newfilename.c_str(), filename.c_str()) != 0) {
				cout << "Error renaming file.\n";
			}
			else {
				cout << "File updated successfully.\n";
			}
		}
		else 
		{
			cout << "\tError opening file.\n";
		}
	}
	
	cout<<"~~~~~~~~~~~~~~~CHANGE PASSWORD~~~~~~~~~~~~~~~\n\n";
	cout<<"\n\tReturning to MAIN MENU.........\n\n";
}

#endif
