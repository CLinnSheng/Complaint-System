#ifndef COMPLAIN_H
#define COMPLAIN_H
#include <iostream>
using namespace std;

class Complaint{

    protected:
        string description;
        string category;
        string status;

    public:
        Complaint(string desc, string cat, string stat) : description(desc), status(stat), category(cat) {}
        void setDescription(string desc){
            description = desc;
        }
        void setStatus(string stat){
        	status = stat;
		}
        string getDescription() const{
            return description;
        }
        string getStatus() const{
        	return status;
		}
		string getCategory() const{
			return category;
		}

};

class Arcade : public Complaint{
    
    public:
        Arcade(string desc, string cat, string status = "Pending") : Complaint(desc, cat, status) {}

};

class Faculty : public Complaint{

    public:
        Faculty(string desc, string cat, string status = "Pending") : Complaint(desc, cat, status) {}

};

class Hostel : public Complaint{

    public:
        Hostel(string desc, string cat, string status = "Pending") : Complaint(desc, cat, status) {}

};

class Other : public Complaint{

    public:
        Other(string desc, string cat, string status = "Pending") : Complaint(desc, cat, status) {}

};

#endif
