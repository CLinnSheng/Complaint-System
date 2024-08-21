#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <conio.h>
#include <cctype>
#include "user.h"
#include "complaint.h"
#define nUser 15
using namespace std;

int dispMenu();
int studentMenu();
int complaintMenu();
int staffMenu();
void readFileUser(User *[]);
void readData(Complaint *[]);
void writeDatas(Complaint *[], User *);
void writeData(Complaint *[]);
void loginPage(string &, string &);
int verification(string, string, User *[]);
string descComplaint();
string checkPassword(string, string, User *[]);

//for writing and reading purpose
int ncomplaint = 0;

int main() {

	//read userdata from file
	User *allusers[nUser] = {NULL};
    
	//read data(complaint) from file
	Complaint *complaints[100] = {NULL};
	
	//temp store user name and pass
	//ID for forget password
	string userN, pass, ID;
	
	//description for the complaint
	string desc;
	
	bool repeat = true;
	
	//verify and also determine the index of users
	int verify;
	
	int Choice, sChoice, cChoice, SChoice; //Choice - dispMenu(), sChoice - studentMenu, cChoice - complaintMenu(), SChoice - staffMenu
	
	char yes_or_no, studentpage;
	
	//for staff to choose which complaint
	int index;
	char charC;
	
	readFileUser(allusers);
	readData(complaints);

	do{
			
		do{ 
		
			Choice = dispMenu();
		    
			if (Choice < 1 || Choice > 5) {
				
				cout << "Invalid Input!!\n"
			    	     << "Please try again\n";
				system("pause");
				system("cls");
		    	
			}
            
        	}while (Choice < 1 || Choice > 5);
		
		int nArcade = 0, nFaculty = 0, nHostel = 0, nOther = 0;
        
		switch(Choice){

            		case 1:
				
				loginPage(userN, pass);
				
				do{
		
					verify = verification(userN, pass, allusers);
					if (verify == -1) {
						
						cout << "Incorrect password or username!!!\n"
						     <<"Please try again.\n";
						system("pause");
						system("cls");
						loginPage(userN, pass);
						
					}
					
					
				}while (verify == -1);
				 
				cout<<"LOGIN SUCCESSFULLY!!!!\n";
				system("pause");
				system("cls");
				
				
				do{
				
					do{
							
						sChoice = studentMenu();
						if (sChoice < 1 || sChoice > 3) {
								
				            		cout << "Invalid Input!!\n"
				                    	     << "Please try again\n";
				            		system("pause");
				            		system("cls");						
							
						}
							
					} while(sChoice < 1 || sChoice > 3);
					
					if (sChoice == 1) {
						
						do {
														
							do {
								
								cChoice = complaintMenu();
								if (cChoice < 1 || cChoice > 4) {
									
									cout << "Invalid Input!!\n"
									     <<"Please try again\n";
									system("pause");
									system("cls");
									
								}
								
							}while (cChoice < 1 || cChoice > 4);
								
							if (cChoice == 1 && nArcade<5) {
								
								desc = descComplaint();
								allusers[verify]->fileComplaint(desc, cChoice-1, nArcade);
								nArcade++;
								
							}
							
							else if (cChoice == 2 && nFaculty < 5) {
								
								desc = descComplaint();
								allusers[verify]->fileComplaint(desc, cChoice-1, nFaculty);
								nFaculty++;
								
							}
							
							else if (cChoice == 3 && nHostel < 5) {
	
								desc = descComplaint();
								allusers[verify]->fileComplaint(desc, cChoice-1, nHostel);
								nHostel++;
								
							}
							
							else if(cChoice == 4 && nOther < 5) {
	
								desc = descComplaint();
								allusers[verify]->fileComplaint(desc, cChoice-1, nOther);
								nOther++;
								
							}
							
							else
								cout << "The maximum of complaint can be filed for each category is 5 only.\n";
							
							if (nArcade == 5 && nFaculty == 5 && nHostel == 5 && nOther == 5)
								break;
								
							cout << "Do you want to file another complaint?(Y/N) => ";
							cin >> yes_or_no;
							yes_or_no = toupper(yes_or_no);
							cout << "\n\n";
							system("cls");
							
						}while (yes_or_no == 'Y');
						
					}
					
					else if (sChoice == 2) {
						
						allusers[verify]->printDetails();
						
						cout << "\n\n" << left;
						cout << setw(43) << "   Complaint Description"<<"Category\n";
						allusers[verify]->printComplaint();
						
						system("pause");
						system("cls");
					}
					
					else if (sChoice == 3) {
						repeat = true;
						break;
					}
				
					if (sChoice != 3) {
					
						cout << "Do you still wish to stay at student portal? (Y/N) => ";
						cin >> studentpage;
						studentpage = toupper(studentpage);
						system("cls");
					
					}
				
				}while (studentpage == 'Y');
			
				writeDatas(complaints, allusers[verify]);
				
				break;
				
            case 2:
				
				loginPage(userN, pass);
				
				do{
		
					verify = verification(userN, pass, allusers);
					if (verify == -1) {
						
						cout<<"Incorrect password or username!!!\n"
							<<"Please try again.\n";
						system("pause");
						system("cls");
						loginPage(userN, pass);
						
					}

					cout << "LOGIN SUCCESSFULLY!!!!\n";
					system("pause");
					system("cls");					
					
				}while (verify == -1);

					do{
							
						SChoice = staffMenu();
						
						if (SChoice < 1 || SChoice > 2) {
								
					            cout << "Invalid Input!!\n"
					                 << "Please try again\n";
					            system("pause");
					            system("cls");						
							
						}
							
					}while (SChoice < 1 || SChoice > 2);	
					
					if (SChoice == 1) {
					
						do{
					
							allusers[verify]->printDetails();
							cout << "\n\n" << left;
							cout << setw(43) << "   Complaint Description"<<setw(20)<<"Category"<<"Status\n";
							
							for (int i=0; i<ncomplaint; i++)
								cout << i+1 << ". " << setw(40) << complaints[i]->getDescription() << setw(20)<<complaints[i]->getCategory() << complaints[i]->getStatus() << endl;
							
							cout << "\n\nPlease enter the number of complaint's status you would like to change => ";
							cin >> index;
							cout << "Please write down the status for the chosen complaint: ";
							cin.ignore();
							getline(cin, desc);
							
							index--;
							complaints[index]->setStatus(desc);
							writeData(complaints);			
											
							cout << "\n\nDo you want to change the status for another complaint? (Y/N) => ";
							cin >> charC;
							
							charC = toupper(charC);
							cout << endl << endl;
														
							system("cls");					
					
						}while (charC == 'Y');
					
					}
					
					else if (SChoice == 2)
						repeat = true;
					
				break;
            
			case 3:
				
				cout << "\n\nPlease key-in your username and id\n"
				     << "Student - Matric No\n"
				     << "Staff - Staff ID\n";
				cout << "Username: ";
				cin >> userN;
				cout << "ID: ";
				cin >> ID;
				cout << "Your Password: " << checkPassword(userN, ID, allusers)<<endl;
				
				system("pause");
				system("cls");
				
				cout << "Exit the program or else back to the main page? (Y/N) => ";
				cin >> charC;
				charC = toupper(charC);
				
				system("cls");
				
				if(charC == 'Y')
					exit(123);
				else
					repeat = true;
						
        		break;
        		
        	case 4:
        		
        		cout << left;
			cout << setw(43) << "   Complaint Description"<<setw(20)<<"Category"<<"Status\n";
							
			for (int i=0; i<ncomplaint; i++)
				cout << i+1 << ". " << setw(40) << complaints[i]->getDescription() << setw(20)<<complaints[i]->getCategory() << complaints[i]->getStatus() << endl;      
				
			cout << "\n\nExit the program or else back to the main page? (Y/N) => ";
			cin >> charC;
			charC = toupper(charC);
			
			system("cls");
			
			if (charC == 'Y')
				exit(123);
			else
				repeat = true;
	
			break;
											
        	case 5:
        		exit(123);
				break;
        }
    
    }while (repeat == true);

    return 0;

}

int dispMenu() {

	int option;
	
	cout << '\n';
	cout << "\t\t======================================================\n"
	     << "\t\t|                  COMPLAINT SYSTEM                  |\n"
	     << "\t\t======================================================\n"
	     << "\t\t1. Student\n"
	     << "\t\t2. Staff\n"
	     << "\t\t3. Forget Password\n"
	     << "\t\t4. Show All Complaint Status\n"
	     << "\t\t5. Exit\n"
	     << "\t\tEnter your choice(1-4) => ";
	cin >> option;
	cin.ignore();
	
	system("cls");
	
	return option;
}

int studentMenu() {

	int choice;

	cout << "\n\t\t======================================================\n"
             << "\t\t|                   STUDENT PORTAL                   |\n"
             << "\t\t======================================================\n";
	cout << "\t\t1. File a Complaint\n"
	     << "\t\t2. Show Complaint Filed\n"
	     << "\t\t3. Back\n"
	     << "\t\tEnter your choice(1-3) => ";
	cin >> choice;
	
	system("cls");
	
	return choice;

}

int staffMenu() {

	int choice;

	cout << "\n\t\t======================================================\n"
	     << "\t\t|                    STAFF PORTAL                    |\n"
	     << "\t\t======================================================\n";
	cout << "\t\t1. Update Status\n"
	     << "\t\t2. Back\n"
	     << "\t\tEnter your choice(1-2) => ";
	cin >> choice;
	
	system("cls");
	
	return choice;

}

int complaintMenu() {

	int option;
	
	cout << "\n\t\t======================================================\n"
	     << "\t\t|                      CATEGORY                      |\n"
	     << "\t\t======================================================\n";
	cout << "\t\tWhich category you want to complain?"<<endl
	     <<"\t\t1. Arcade\n"
	     <<"\t\t2. Faculty\n"
	     <<"\t\t3. Hostel\n"
	     <<"\t\t4. Other\n"
	     <<"\n\t\tEnter your option(1-4) => ";
	cin >> option;
	
	system("cls");
	
	return option;

}


void readFileUser(User *users[nUser]) {
	
	ifstream inputStudent;
	inputStudent.open("studentlist.txt");
	int cnt=0;
	string uN, pass, ID;
	
	while (getline(inputStudent, uN, ',')) {
		
		getline(inputStudent, pass, ',');
		getline(inputStudent, ID, '\n');
		users[cnt] = new Student(ID, pass, uN);
		cnt++;
		
	}
	
	inputStudent.close();
	
	ifstream inputStaff;
	inputStaff.open("stafflist.txt");
	
	while (!inputStaff.eof()) {
		
		getline(inputStaff, uN, ',');
		getline(inputStaff, pass, ',');
		getline(inputStaff, ID, '\n');
		users[cnt] = new Staff(ID, pass, uN);
		cnt++;
		
	}
	
	inputStaff.close();
	
}

void loginPage(string &userN, string &pass) {
	
	cout << "\n\t\t======================================================"
	     << "\n\t\t|                    LOGIN PAGE                      |\n"
	     << "\t\t======================================================\n";
		
	cout << "\n\t\tUsername: ";
	cin >> userN;
	
	cout << "\t\tPassword: ";
	pass.clear();
	char p;
	int i=0;
	
	do {
		
		p = getch();
		if (p == '\n' || p == 13) {  // Terminate loop if Enter key is pressed
			cout << endl;
			break;
		} 
		
		else if (p == '\b') {  // Handle Backspace key
			
			if (!pass.empty()) {
				cout << "\b \b";
				pass.pop_back();
			}
		
		} 
		
		else {
			cout.put('*');
			pass.push_back(p);
		}
	
	} while (true);	
	
	system("cls");
	
}

int verification(string uN, string pass, User *users[nUser]) {
		
	for (int i=0; i<nUser; i++)
		if (users[i]->getUserName() == uN && users[i]->getPass() == pass)
			return i;
				
	return -1;
	
}

string checkPassword(string uN, string ID, User *users[nUser]) {
	
	for (int i=0; i<nUser; i++)
		if (users[i]->getID() == ID && users[i]->getUserName() == uN)
			return users[i]->getPass();
			
	return "Invalid ID or Username";
	
}

string descComplaint() {
	
	string desc;
	
	cout << "Please describe your complaint: ";
	cin.ignore();
	getline(cin, desc);
	
	return desc;
	
}

void readData(Complaint *complaints[100]) {
	
	ifstream datafile("datas.txt");

	string desc, category, status;

	while (!datafile.eof()) {
		
		getline(datafile, desc, ',');
		getline(datafile, category, ',');
		getline(datafile, status, '\n');
		
		if (desc != "" && category != "" && status != "") {
			complaints[ncomplaint] = new Complaint(desc, category, status);
			ncomplaint++;
		}
	}
	
	datafile.close();

}

void writeDatas(Complaint *complaints[100], User *user) {
	
	ofstream write("datas.txt");
	
	string desc, category, status;
	
	for (int i=0; i<4; i++)
		for (int j=0; j<5; j++) {
			
			desc = user->getComplaintD(i, j);
			category = user->getComplaintC(i, j);
			status = user->getComplaintS(i, j);
			
			if (desc != "" && category != "" && status != "")
				complaints[ncomplaint++] = new Complaint(desc, category, status);
			
		}
		
	for (int i=0; i<ncomplaint; i++)
		write << complaints[i]->getDescription() << ','<<complaints[i]->getCategory() << ','<<complaints[i]->getStatus()<<endl;
	
	write.close();
	
}

void writeData(Complaint *complaints[100]) {
	
	ofstream write("datas.txt");

	for (int i=0; i<ncomplaint; i++)
		write << complaints[i]->getDescription() << ',' << complaints[i]->getCategory() << ',' << complaints[i]->getStatus()<<endl;
	
	write.close();

}
