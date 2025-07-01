#ifndef USER_H
#define USER_H
#include<iostream>
using namespace std;

class User{
protected:
	string name;
	string ID;
	string password;
	bool passwordVerification(string password);
public:	
	User();//default constructor
	void setName(string n);
	void setID(string id);
	void setPassword(string pass);
	string getName();
	string getID();
	string getPassword();
	string changePassword();
};
User:: User()
{
	name=ID=password="";
}
void User:: setName(string n)
{
	name=n;
}
void User:: setID(string id)
{
	ID=id;
}
void User:: setPassword(string pass)
{
	password=pass;
}	
string User:: getName()
{
	return name;
}
string User:: getID()
{
	return ID;
}
string User:: getPassword()
{
	return password;
}
string User:: changePassword()
{
	bool verify=0;
	string passOld, passNew;
	while(1)
	{
		cout<<"\tEnter current password: ";
		cin>>passOld;
		if(passOld==password)
		{
			while(1)
			{
				cout<<"\tEnter new password: ";
				cin>>passNew;
				verify=passwordVerification(passNew);
				if(verify==1)
				{
					password=passNew;
					break;
				}
				else
					cout<<"\tEnter a strong password\n";	
			}
			cout<<"\tPassword Changed Successfully\n";
			break;
		}	
		else
			cout<<"\tInvalid Password.\n\tEnter again\n";
	}
	return passNew;
}
bool User:: passwordVerification(string password) 
{     
	int len=password.length();   
    
	if (len<6)  
		return false;    
   
	bool uppercase = false;    
	bool lowercase = false;   
	bool digit = false;   
	bool special = false;   
    
	for (int i = 0; i < len; i++)    
	{   
		if (isupper(password[i]))  
			uppercase=true;   
		else if (islower(password[i]))  
			lowercase=true;  
		else if (isdigit(password[i]))   
			digit=true;   
		else if (!isspace(password[i]))   
			special=true;  
  }     
     
	return uppercase && lowercase && digit && special;    
}  

#endif
