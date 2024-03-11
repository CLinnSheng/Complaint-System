#ifndef USER_H
#define USER_H
#include "complaint.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class PersonalDetails{
	
	private:
		string ID;
		
	public:
		PersonalDetails(string id="") : ID(id) {}
		void setPersonalDetails(string id){ ID = id; }
		string getPersonalDetails() const{ return ID; }
};

class User{

    protected:
        string userName;
        string password;

    public:
        User(string pass, string uN) : password(pass), userName(uN) {}
        
        void setPass(string pass){ password = pass; }
        
		void setUserName(string uN){ userName = uN; }
       
        string getPass() const{ return password; }
        
		string getUserName() const{ return userName; }
		
		virtual void setID(string) = 0;
		
		virtual string getID() const = 0;
		
		virtual void fileComplaint(string a, int b, int c) = 0;
		
		virtual void printDetails() = 0;
		
		virtual void printComplaint() = 0;
		
		virtual string getComplaintD(int i, int j) = 0;
		virtual string getComplaintS(int i, int j) = 0;
		virtual string getComplaintC(int i, int j) = 0;
		
};

class Student : public User{

    private:
        Complaint *complaint[4][5] = {NULL};
        PersonalDetails matricNo;
        
    public:
        Student(string mN="", string pass="", string uN="") : User(pass, uN), matricNo(mN){}
        
        void setID(string mN){ matricNo.setPersonalDetails(mN); }
        
		void fileComplaint(string desc, int cat, int nComplaint){
        	
        	switch(cat){
        		
        		case 0:
        			if(complaint[cat][nComplaint] == NULL)
        				complaint[cat][nComplaint] = new Arcade(desc, "Arcade");
        			break;
        			
        		case 1:
        			if(complaint[cat][nComplaint] == NULL)        		
        				complaint[cat][nComplaint] = new Faculty(desc, "Faculty");
        			break;
        			
        		case 2:
        			if(complaint[cat][nComplaint] == NULL)
        				complaint[cat][nComplaint] = new Hostel(desc, "Hostel");
        			break;
        			
        		case 3:
        			if(complaint[cat][nComplaint] == NULL)
	        			complaint[cat][nComplaint] = new Other(desc, "Other");
        			break;
										        		
			}
			
		}
		
		string getID() const{ return matricNo.getPersonalDetails(); }
		
		void printDetails(){
			cout<<"Username: "<<userName
				<<"\nMatric No: "<<getID()<<endl;
		}
		
		void printComplaint(){
			
			int no=1;

			for(int i=0; i<4; i++)
				for(int j=0; j<5; j++)
					if(complaint[i][j] != NULL)
						cout<<no++<<". "<<left<<setw(40)<<complaint[i][j]->getDescription()<<complaint[i][j]->getCategory()<<endl;
				
	
		}
		
		string getComplaintD(int i, int j){
			if(complaint[i][j] != NULL)
				return complaint[i][j]->getDescription();
			else
				return "";
		}
		string getComplaintC(int i, int j){
			if(complaint[i][j] != NULL)
				return complaint[i][j]->getCategory();
			else
				return "";
		}
		string getComplaintS(int i, int j){
			if(complaint[i][j] != NULL)
				return complaint[i][j]->getStatus();
			else
				return "";
		}
		
};

class Staff : public User{
	
	private:
        PersonalDetails staffID;

    public:
        Staff(string sID="", string pass="", string uN="") : User(pass, uN), staffID(sID) {}
        
        void fileComplaint(string a, int b, int c){}
		
		string getID() const{ return staffID.getPersonalDetails(); }
        
        void setID(string sID){ staffID.setPersonalDetails(sID); }
        
		void printDetails(){
			cout<<"Username: "<<userName
				<<"\nID: "<<getID()<<endl;
		}
		
		void printComplaint(){}
		
		string getComplaintS(int i, int j) { return ""; }
		string getComplaintD(int i, int j) { return ""; }
		string getComplaintC(int i, int j) { return ""; }
		
};

#endif
