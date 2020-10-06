#include<iostream>
#include<iomanip>
#include<string>
#include<cstring> //For string::functions
#include<fstream>

#include <regex> //For regex.replace function

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int idGenerator(string txtfile);
void login();
void profileChoice(int noCustomerType);
void viewProfile(string filename);

class shopper
{
    protected:
        int customerId;
        string customerName;
        string address;
        string customerUserName;
        string customerPassword;
        string cusIdFile = "shopperId.txt"; 
        string cusAccFile = "shopperAccount.txt";

    public:
        //default constructor
        shopper() { customerId=0; }
        virtual void registration() {}
        virtual void displayProfile()=0;
        virtual void updateProfile()=0;
        virtual void deregister() {}
};

class customer : public shopper
{
    private:
        int noCustomerType = 1; 
        string custId;
        string customerType = "Normal Customer";
        string cusFile = "normalCustomer.txt";

    public:
        //default constructor
        customer() { custId=""; }
        void registration()
        {   
            cout << "\n========================================================" << endl;
            cout << "                   Shopper Registration                 " << endl;
            cout << "========================================================" << endl;
            cout << "Welcome, " << customerType << "! Please fill in the information below. " << endl << endl; 
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
			cout << "Enter new user name [max 20 characters]: ";
            getline(cin, customerUserName);
            cout << "Enter new password [max 20 characters]: ";
            getline(cin, customerPassword);

            customerId = idGenerator("shopperId.txt");
            ofstream regCusFile1;
            regCusFile1.open("normalCustomer.txt", ios::app);
            if(regCusFile1)
            {
                regCusFile1 << "|" << setw(10) << customerId;
                regCusFile1 << "|" << setw(30) << customerName;
                regCusFile1 << "|" << setw(100) << address;
                regCusFile1 << "|" << endl;
            }
            regCusFile1.close();
                
            ofstream regCusFile2;
            regCusFile2.open("shopperAccount.txt", ios::app);
            if(regCusFile2)
            {
                regCusFile2 << "|" << setw(10) << customerId << "|" << setw(20) << customerUserName << "|" << setw(20) << customerPassword << "|" << endl;
                cout << "\nYour shopper ID is " << customerId << ".";
                cout << "\nREGISTRATION COMPLETED SUCCESSFULLY!"; 
            }
            regCusFile2.close();
            profileChoice(noCustomerType);
        }
        void displayProfile()
        {
            cout << "\n====================================================================================================" << endl;
            cout << "                                     Normal Customer Shopper Profile                                " << endl;
            cout << "====================================================================================================" << endl;
			viewProfile(cusFile);
        }

        void updateProfile()
        {
            viewProfile(cusFile);
            cout << "\n=========================================" << endl;
            cout << "              Update Profie              " << endl;
            cout << "=========================================" << endl;
            cout << "Please enter your shopper ID: ";
            cin.ignore();
            getline(cin, custId);
            cout << "-----------------------------------------" << endl;
            cout << "Fill in your new information to modify your profile." << endl;
            cout << "If you wish to remain some of the information, please retype the same information as previous." << endl << endl;
            cout << "Enter name: ";
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
			cout << "Enter new user name [max 20 characters]: ";
            getline(cin, customerUserName);
            cout << "Enter new password [max 20 characters]: ";
            getline(cin, customerPassword);

            string line, savedLine;
			size_t pos;
			const char * cnvrFileName = cusFile.c_str();
            const char * cnvrFileName1 = cusAccFile.c_str();

			ifstream readCusFile;
			readCusFile.open(cusFile, ios::in);

			if(readCusFile.is_open())
			{
				while(getline(readCusFile, line))
				{
					pos = line.find(custId);
					if(pos != string::npos)
					{
						if(pos < 11)
						{
							savedLine = line;
						}
						else
						{
							readCusFile.close();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readCusFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getCusFile;
				getCusFile.open(cusFile);

				ofstream temporarily;
				temporarily.open("temporarily.txt");

				while(getline(getCusFile, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temporarily << line << endl;
					}
				}
                temporarily << "|" << setw(10) << custId;
                temporarily << "|" << setw(30) << customerName;
                temporarily << "|" << setw(100) << address;
                temporarily << "|" << endl;

				getCusFile.close();
				temporarily.close();
			}

			if(remove(cnvrFileName)==0)
			{
				cout << "Removed selected item from profile. " << endl;

				if(rename("temporarily.txt", cnvrFileName)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}

            savedLine = "";
            line = "";
            ifstream readAccFile;
			readAccFile.open(cusAccFile, ios::in);

			if(readAccFile.is_open())
			{
				while(getline(readAccFile, line))
				{
					pos = line.find(custId);
					if(pos != string::npos)
					{
						if(pos < 11)
						{
							savedLine = line;
						}
						else
						{
							readAccFile.close();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readAccFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getAccFile;
				getAccFile.open(cusAccFile);

				ofstream temporarilyAcc;
				temporarilyAcc.open("temporarily.txt");

				while(getline(getAccFile, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temporarilyAcc << line << endl;
					}
				}
                temporarilyAcc << "|" << setw(10) << custId;
                temporarilyAcc << "|" << setw(20) << customerUserName;
                temporarilyAcc << "|" << setw(20) << customerPassword;
                temporarilyAcc << "|" << endl;

				getAccFile.close();
				temporarilyAcc.close();
			}

			if(remove(cnvrFileName1)==0)
			{
				cout << "Removed selected item from profile. " << endl;

				if(rename("temporarily.txt", cnvrFileName1)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}
        }
        void deregister()
        {
            string deChoice;

            cout << "\n=========================================" << endl;
            cout << "            Deregister Profie            " << endl;
            cout << "=========================================" << endl;
            cout << "Are you sure want to deregister?" << endl << endl;
            cout << "If yes, your account will no longer exist. " << endl;
            cout << "If no, your account will remain. " << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Enter your choice [Yes or No]: " << endl;
            cin >> deChoice;

            if(deChoice=="Yes")
            {   
                cout << "Please enter your shopper ID: ";
                cin.ignore();
                getline(cin, custId);
                cout << custId;

                string line, savedLine;
                size_t pos;

                //converting string element to cont char * for functions (remove and rename)
                const char * cnvrFileName = cusFile.c_str();
                const char * cnvrFileName1 = cusAccFile.c_str();

                ifstream dltFile;
                dltFile.open(cusFile, ios::in);

                while(getline(dltFile, line))
                {
                    pos = line.find(custId);

                    if(pos != string::npos)
                    {
                        if(pos < 11) {

                            savedLine = line;

                        }else {

                            dltFile.close();

                        }

                    }
                    
                }

                dltFile.close();

                if(savedLine == "")
                {

                    cout << "Item Not Found" << endl;

                }
                else
                {

                    line = "";

                    ifstream inputCusFile;
                    inputCusFile.open(cusFile, ios::in);

                    ofstream temporarily;
                    temporarily.open("temporarily.txt");

                        while(getline(inputCusFile, line)) 
                        {

                            if(line.compare(savedLine) != 0) 
                            {

                                temporarily << line << "\n";

                            }
                        
                        }

                    inputCusFile.close();
                    temporarily.close();

                    if(remove(cnvrFileName) == 0) 
                    {

                    cout << "Removed original file" << endl;

                        if(rename("temporarily.txt", cnvrFileName) == 0) 
                        {

                            cout << "Renamed Temp file to Ori file" << endl;

                        }
                        else
                        {

                            cout << "Renamed Failed";

                        }
                    
                
                    }
                    else
                    {

                        cout << "Removed Failed";

                    }
                }

                line = "";
                savedLine = "";

                ifstream dltAccFile;
                dltAccFile.open(cusAccFile, ios::in);

                while(getline(dltAccFile, line))
                {
                    pos = line.find(custId);
                    if(pos != string::npos)
                    {
                        if(pos < 11) {
                        
                            savedLine = line;

                        }else {

                            dltAccFile.close();

                        }

                    }
                    
                }

                dltAccFile.close();

                if(savedLine == "") 
                {

                    cout << "Item Not Found" << endl;

                }
                else
                {

                    line = "";

                    ifstream inputAccFile;
                    inputAccFile.open(cusAccFile, ios::in);

                    ofstream temporarily;
                    temporarily.open("temporarily.txt");

                        while(getline(inputAccFile, line)) {

                            if(line.compare(savedLine) != 0) {

                                temporarily << line << "\n";

                            }
                        
                        }

                    inputAccFile.close();
                    temporarily.close();

                    if(remove(cnvrFileName1) == 0) {

                    cout << "Removed original file" << endl;

                        if(rename("temporarily.txt", cnvrFileName1) == 0) {

                            cout << "Renamed Temp file to Ori file" << endl;

                        }
                        else
                        {
                            cout << "Renamed Failed";
                        }
                    }
                    else
                    {
                        cout << "Removed Failed";
                    }
                }
            }
            else if(deChoice=="No")
            {
                exit(0);
            }
            else
            {
                cout << "Invalid choice for deregistration!" << endl;
            }
        }
        
};

class mmuStudent : public shopper
{
    private:
        int noCustomerType; 
        string studId;
        string customerType = "MMU Student";
        string mmuCourseName;
        string studFile = "mmuStudent.txt";

    public:
        //default constructor
        mmuStudent() { studId=""; }
        void registration()
        {
            cout << "\n========================================================" << endl;
            cout << "                   Shopper Registration                 " << endl;
            cout << "========================================================" << endl;
            cout << "Welcome, " << customerType << "! Please fill in the information below. " << endl << endl; 
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
            cout << "\nEnter your course name: ";
            getline(cin, mmuCourseName);
			cout << "Enter new user name [max 20 characters]: ";
            getline(cin, customerUserName);
            cout << "Enter new password [max 20 characters]: ";
            getline(cin, customerPassword);

            customerId = idGenerator("shopperId.txt");
            ofstream regStudFile1;
            regStudFile1.open("mmuStudent.txt", ios::app);
            if(regStudFile1)
            {
                regStudFile1 << "|" << setw(10) << customerId;
                regStudFile1 << "|" << setw(30) << customerName;
                regStudFile1 << "|" << setw(100) << address;
                regStudFile1 << "|" << setw(30) << mmuCourseName;
                regStudFile1 << "|" << endl;
            }
            regStudFile1.close();
                
            ofstream regStudFile2;
            regStudFile2.open("shopperAccount.txt", ios::app);
            if(regStudFile2)
            {
                regStudFile2 << "|" << setw(10) << customerId << "|" << setw(20) << customerUserName << "|" << setw(20) << customerPassword << "|" << endl;
                cout << "\nYour shopper ID is " << customerId << ".";
                cout << "\nREGISTRATION COMPLETED SUCCESSFULLY!"; 
            }
            regStudFile2.close();

            profileChoice(noCustomerType);
        }
        void displayProfile()
        {
            cout << "\n====================================================================================================" << endl;
            cout << "                                       MMU Student Shopper Profile                                  " << endl;
            cout << "====================================================================================================" << endl;
			viewProfile(studFile);
        }
        void updateProfile()
        {
            viewProfile(studFile);
            cout << "\n=========================================" << endl;
            cout << "              Update Profie              " << endl;
            cout << "=========================================" << endl;
            cout << "Please enter your shopper ID: ";
            cin.ignore();
            getline(cin, studId);
            cout << "-----------------------------------------" << endl;
            cout << "Fill in your new information to modify your profile." << endl;
            cout << "If you wish to remain some of the information, please retype the same information as previous." << endl << endl;
            cout << "Enter name: ";
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
            cout << "Enter mmu course name: ";
            getline(cin, mmuCourseName);
			cout << "Enter new user name [max 20 characters]: ";
            getline(cin, customerUserName);
            cout << "Enter new password [max 20 characters]: ";
            getline(cin, customerPassword);

            string line, savedLine;
			size_t pos;
			const char * cnvrFileName = studFile.c_str();
            const char * cnvrFileName1 = cusAccFile.c_str();

			ifstream readStudFile;
			readStudFile.open(studFile, ios::in);

			if(readStudFile.is_open())
			{
				while(getline(readStudFile, line))
				{
					pos = line.find(studId);
					if(pos != string::npos)
					{
						if(pos < 11)
						{
							savedLine = line;
						}
						else
						{
							readStudFile.close();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readStudFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getStudFile;
				getStudFile.open(studFile);

				ofstream temporarily;
				temporarily.open("temporarily.txt");

				while(getline(getStudFile, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temporarily << line << endl;
					}
				}
                temporarily << "|" << setw(10) << studId;
                temporarily << "|" << setw(30) << customerName;
                temporarily << "|" << setw(100) << address;
                temporarily << "|" << setw(30) << mmuCourseName;
                temporarily << "|" << endl;

				getStudFile.close();
				temporarily.close();
			}

			if(remove(cnvrFileName)==0)
			{
				cout << "Removed selected item from profile. " << endl;

				if(rename("temporarily.txt", cnvrFileName)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}

            savedLine = "";
            line = "";
            ifstream readAccFile;
			readAccFile.open(cusAccFile, ios::in);

			if(readAccFile.is_open())
			{
				while(getline(readAccFile, line))
				{
					pos = line.find(studId);
					if(pos != string::npos)
					{
						if(pos < 11)
						{
							savedLine = line;
						}
						else
						{
							readAccFile.close();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readAccFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getAccFile;
				getAccFile.open(cusAccFile);

				ofstream temporarilyAcc;
				temporarilyAcc.open("temporarily.txt");

				while(getline(getAccFile, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temporarilyAcc << line << endl;
					}
				}
                temporarilyAcc << "|" << setw(10) << studId;
                temporarilyAcc << "|" << setw(20) << customerUserName;
                temporarilyAcc << "|" << setw(20) << customerPassword;
                temporarilyAcc << "|" << endl;

				getAccFile.close();
				temporarilyAcc.close();
			}

			if(remove(cnvrFileName1)==0)
			{
				cout << "Removed selected item from profile. " << endl;

				if(rename("temporarily.txt", cnvrFileName1)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}
        }
        void deregister()
        {
            string deChoice;

            cout << "\n=========================================" << endl;
            cout << "            Deregister Profie            " << endl;
            cout << "=========================================" << endl;
            cout << "Are you sure want to deregister?" << endl << endl;
            cout << "If yes, your account will no longer exist. " << endl;
            cout << "If no, your account will remain. " << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Enter your choice [Yes or No]: " << endl;
            cin >> deChoice;

            if(deChoice=="Yes")
            {   
                cout << "Please enter your shopper ID: ";
                cin.ignore();
                getline(cin, studId);
                cout << studId;

                string line, savedLine;
                size_t pos;

                //converting string element to cont char * for functions (remove and rename)
                const char * cnvrFileName = studFile.c_str();
                const char * cnvrFileName1 = cusAccFile.c_str();

                ifstream dltFile;
                dltFile.open(studFile, ios::in);

                while(getline(dltFile, line))
                {
                    pos = line.find(studId);

                    if(pos != string::npos)
                    {
                        if(pos < 11) {

                            savedLine = line;

                        }else {

                            dltFile.close();

                        }

                    }
                    
                }

                dltFile.close();

                if(savedLine == "")
                {

                    cout << "Item Not Found" << endl;

                }
                else
                {

                    line = "";

                    ifstream inputStudFile;
                    inputStudFile.open(studFile, ios::in);

                    ofstream temporarily;
                    temporarily.open("temporarily.txt");

                        while(getline(inputStudFile, line)) 
                        {

                            if(line.compare(savedLine) != 0) 
                            {

                                temporarily << line << "\n";

                            }
                        
                        }

                    inputStudFile.close();
                    temporarily.close();

                    if(remove(cnvrFileName) == 0) 
                    {

                    cout << "Removed original file" << endl;

                        if(rename("temporarily.txt", cnvrFileName) == 0) 
                        {

                            cout << "Renamed Temp file to Ori file" << endl;

                        }
                        else
                        {

                            cout << "Renamed Failed";

                        }
                    
                
                    }
                    else
                    {

                        cout << "Removed Failed";

                    }
                }

                line = "";
                savedLine = "";

                ifstream dltAccFile;
                dltAccFile.open(cusAccFile, ios::in);

                while(getline(dltAccFile, line))
                {
                    pos = line.find(studId);
                    if(pos != string::npos)
                    {
                        if(pos < 11) {
                        
                            savedLine = line;

                        }else {

                            dltAccFile.close();

                        }

                    }
                    
                }

                dltAccFile.close();

                if(savedLine == "") 
                {

                    cout << "Item Not Found" << endl;

                }
                else
                {

                    line = "";

                    ifstream inputAccFile;
                    inputAccFile.open(cusAccFile, ios::in);

                    ofstream temporarily;
                    temporarily.open("temporarily.txt");

                        while(getline(inputAccFile, line)) {

                            if(line.compare(savedLine) != 0) {

                                temporarily << line << "\n";

                            }
                        
                        }

                    inputAccFile.close();
                    temporarily.close();

                    if(remove(cnvrFileName1) == 0) {

                    cout << "Removed original file" << endl;

                        if(rename("temporarily.txt", cnvrFileName1) == 0) {

                            cout << "Renamed Temp file to Ori file" << endl;

                        }
                        else
                        {
                            cout << "Renamed Failed";
                        }
                    }
                    else
                    {
                        cout << "Removed Failed";
                    }
                }
            }
            else if(deChoice=="No")
            {
                exit(0);
            }
            else
            {
                cout << "Invalid choice for deregistration!" << endl;
            } 
        }

};

class mmuStaff : public shopper
{
    private:
        int noCustomerType; 
        string staffId;
        string customerType = "MMU Staff";
        string mmuDepartmentName;
        string staffFile = "mmuStaff.txt";

    public:
        //default constructor
        mmuStaff() { staffId=""; }
        void registration()
		{
            cout << "\n========================================================" << endl;
            cout << "                   Shopper Registration                 " << endl;
            cout << "========================================================" << endl;
            cout << "Welcome, " << customerType << "! Please fill in the information below. " << endl; 
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
            cout << "\nEnter the name of department: ";
            getline(cin, mmuDepartmentName);
			cout << "Enter new user name [max 20 characters]: ";
            getline(cin, customerUserName);
            cout << "Enter new password [max 20 characters]: ";
            getline(cin, customerPassword);

            customerId = idGenerator("shopperId.txt");
            ofstream regStafFile1;
            regStafFile1.open("mmuStaff.txt", ios::app);
            if(regStafFile1)
            {
                regStafFile1 << "|" << setw(10) << customerId;
                regStafFile1 << "|" << setw(30) << customerName;
                regStafFile1 << "|" << setw(100) << address;
                regStafFile1 << "|" << setw(30) << mmuDepartmentName;
                regStafFile1 << "|" << endl;
            }
            regStafFile1.close();
                
            ofstream regStafFile2;
            regStafFile2.open("shopperAccount.txt", ios::app);
            if(regStafFile2)
            {
                regStafFile2 << "|" << setw(10) << customerId << "|" << setw(20) << customerUserName << "|" << setw(20) << customerPassword << "|" << endl;
                cout << "\nYour shopper ID is " << customerId << ".";
                cout << "\nREGISTRATION COMPLETED SUCCESSFULLY!"; 
            }
            regStafFile2.close();

            profileChoice(noCustomerType);
        }
        void displayProfile()
        {
            cout << "\n====================================================================================================" << endl;
            cout << "                                        MMU Staff Shopper Profile                                   " << endl;
            cout << "====================================================================================================" << endl;
			cout << "             MMU Staff Shopper Profile             " << endl;
            cout << "=========================================" << endl;
            viewProfile(staffFile);
        }
        void updateProfile()
        {
            viewProfile(staffFile);
            cout << "\n=========================================" << endl;
            cout << "              Update Profie              " << endl;
            cout << "=========================================" << endl;
            cout << "Please enter your shopper ID: ";
            cin >> staffId;
            cout << "-----------------------------------------" << endl;
            cout << "Fill in your new information to modify your profile." << endl;
            cout << "If you wish to remain some of the information, please retype the same information as previous." << endl << endl;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
            cout << "Enter mmu department name: ";
            getline(cin, mmuDepartmentName);
			cout << "Enter new user name [max 20 characters]: ";
            getline(cin, customerUserName);
            cout << "Enter new password [max 20 characters]: ";
            getline(cin, customerPassword);

            string line, savedLine;
			size_t pos;
			const char * cnvrFileName = staffFile.c_str();
            const char * cnvrFileName1 = cusAccFile.c_str();

			ifstream readStaffFile;
			readStaffFile.open(staffFile, ios::in);

			if(readStaffFile.is_open())
			{
				while(getline(readStaffFile, line))
				{
					pos = line.find(staffId);
					if(pos != string::npos)
					{
						if(pos < 11)
						{
							savedLine = line;
						}
						else
						{
							readStaffFile.close();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readStaffFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getStaffFile;
				getStaffFile.open(staffFile);

				ofstream temporarily;
				temporarily.open("temporarily.txt");

				while(getline(getStaffFile, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temporarily << line << endl;
					}
				}
                temporarily << "|" << setw(10) << staffId;
                temporarily << "|" << setw(30) << customerName;
                temporarily << "|" << setw(100) << address;
                temporarily << "|" << setw(30) << mmuDepartmentName;
                temporarily << "|" << endl;

				getStaffFile.close();
				temporarily.close();
			}

			if(remove(cnvrFileName)==0)
			{
				cout << "Removed selected item from profile. " << endl;

				if(rename("temporarily.txt", cnvrFileName)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}

            savedLine = "";
            line = "";
            ifstream readAccFile;
			readAccFile.open(cusAccFile, ios::in);

			if(readAccFile.is_open())
			{
				while(getline(readAccFile, line))
				{
					pos = line.find(staffId);
					if(pos != string::npos)
					{
						if(pos < 11)
						{
							savedLine = line;
						}
						else
						{
							readAccFile.close();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readAccFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getAccFile;
				getAccFile.open(cusAccFile);

				ofstream temporarilyAcc;
				temporarilyAcc.open("temporarily.txt");

				while(getline(getAccFile, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temporarilyAcc << line << endl;
					}
				}
                temporarilyAcc << "|" << setw(10) << staffId;
                temporarilyAcc << "|" << setw(20) << customerUserName;
                temporarilyAcc << "|" << setw(20) << customerPassword;
                temporarilyAcc << "|" << endl;

				getAccFile.close();
				temporarilyAcc.close();
			}

			if(remove(cnvrFileName1)==0)
			{
				cout << "Removed selected item from profile. " << endl;

				if(rename("temporarily.txt", cnvrFileName1)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}
        }
        void deregister()
        {
            string deChoice;

            cout << "\n=========================================" << endl;
            cout << "            Deregister Profie            " << endl;
            cout << "=========================================" << endl;
            cout << "Are you sure want to deregister?" << endl << endl;
            cout << "If yes, your account will no longer exist. " << endl;
            cout << "If no, your account will remain. " << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Enter your choice [Yes or No]: " << endl;
            cin >> deChoice;

            if(deChoice=="Yes")
            {   
                cout << "Please enter your shopper ID: ";
                cin.ignore();
                getline(cin, staffId);
                cout << staffId;

                string line, savedLine;
                size_t pos;

                //converting string element to cont char * for functions (remove and rename)
                const char * cnvrFileName = staffFile.c_str();
                const char * cnvrFileName1 = cusAccFile.c_str();

                ifstream dltFile;
                dltFile.open(staffFile, ios::in);

                while(getline(dltFile, line))
                {
                    pos = line.find(staffId);

                    if(pos != string::npos)
                    {
                        if(pos < 11) {

                            savedLine = line;

                        }else {

                            dltFile.close();

                        }

                    }
                    
                }

                dltFile.close();

                if(savedLine == "")
                {

                    cout << "Item Not Found" << endl;

                }
                else
                {

                    line = "";

                    ifstream inputStaffFile;
                    inputStaffFile.open(staffFile, ios::in);

                    ofstream temporarily;
                    temporarily.open("temporarily.txt");

                        while(getline(inputStaffFile, line)) 
                        {

                            if(line.compare(savedLine) != 0) 
                            {

                                temporarily << line << "\n";

                            }
                        
                        }

                    inputStaffFile.close();
                    temporarily.close();

                    if(remove(cnvrFileName) == 0) 
                    {

                    cout << "Removed original file" << endl;

                        if(rename("temporarily.txt", cnvrFileName) == 0) 
                        {

                            cout << "Renamed Temp file to Ori file" << endl;

                        }
                        else
                        {

                            cout << "Renamed Failed";

                        }
                    
                
                    }
                    else
                    {

                        cout << "Removed Failed";

                    }
                }

                line = "";
                savedLine = "";

                ifstream dltAccFile;
                dltAccFile.open(cusAccFile, ios::in);

                while(getline(dltAccFile, line))
                {
                    pos = line.find(staffId);
                    if(pos != string::npos)
                    {
                        if(pos < 11) {
                        
                            savedLine = line;

                        }else {

                            dltAccFile.close();

                        }

                    }
                    
                }

                dltAccFile.close();

                if(savedLine == "") 
                {

                    cout << "Item Not Found" << endl;

                }
                else
                {

                    line = "";

                    ifstream inputAccFile;
                    inputAccFile.open(cusAccFile, ios::in);

                    ofstream temporarily;
                    temporarily.open("temporarily.txt");

                        while(getline(inputAccFile, line)) {

                            if(line.compare(savedLine) != 0) {

                                temporarily << line << "\n";

                            }
                        
                        }

                    inputAccFile.close();
                    temporarily.close();

                    if(remove(cnvrFileName1) == 0) {

                    cout << "Removed original file" << endl;

                        if(rename("temporarily.txt", cnvrFileName1) == 0) {

                            cout << "Renamed Temp file to Ori file" << endl;

                        }
                        else
                        {
                            cout << "Renamed Failed";
                        }
                    }
                    else
                    {
                        cout << "Removed Failed";
                    }
                }
            }
            else if(deChoice=="No")
            {
                exit(0);
            }
            else
            {
                cout << "Invalid choice for deregistration!" << endl;
            } 
        }
};

int main()
{
    customer c;
    mmuStudent mstud;
    mmuStaff mstaff;
    int accountChoice;
    int noCustomerType;

    cout << "\n+=========================================+" << endl;
    cout << "|            WELCOME, SHOPPER!            |" << endl;
    cout << "|=========================================|" << endl;
    cout << "|           Choice 1: Register            |" << endl;
    cout << "|           Choice 2: Login               |" << endl;
    cout << "|=========================================|" << endl;
	cout << "|             [Press 0] Exit              |" << endl;
	cout << "|.........................................|" << endl << endl;
    cout << "\nEnter your choice [1 or 2]: ";
    cin >> accountChoice;

    while(!(accountChoice >= 0 && accountChoice <= 2))
    {
        cout << "Invalid choice!" << endl << endl;
        cout << "Enter Your Choice: ";
        cin >> accountChoice;
    }

    shopper *shopper1 = &c;
    shopper *shopper2 = &mstud;
    shopper *shopper3 = &mstaff;

    if(accountChoice==1)
    {   
        cout << "\n-----------------------------------------" << endl;
        cout << "Choose your customer type: " << endl;
        cout << "1. Normal Customer" << endl;
        cout << "2. MMU Student" << endl;
        cout << "3. MMU Staff" << endl;
        cout << "-----------------------------------------" << endl;
        cout << "Enter customer type [1, 2 or 3]: ";
        cin >> noCustomerType;

        switch(noCustomerType)
        {
            case 1: shopper1->registration(); break;
            case 2: shopper2->registration(); break;
            case 3: shopper3->registration(); break;
            default: cout << "Invalid customer type!";
        }
    }
    else if(accountChoice==2)
    {
        login();
    }
    else if(accountChoice==3)
    {
        exit(0);
    }
    else
    {
        cout << "Invalid choice!";
    }

    return 0;
}

int idGenerator(string txtfile)
{
	int id;
	
	ifstream checkId;
	checkId.open(txtfile, ios::in);
	
	if(checkId.is_open())
	{
		checkId >> id;
		checkId.close();
	}
	else
	{
		cout << "Id Auto Generator Failed..." << endl;
	}
	id++;
	
	ofstream addId;
	addId.open(txtfile);
	
	if(addId.is_open())
	{
		addId << id;
	}
	else
	{
		cout << "Id Auto Generator Failed..." << endl;
	}
	return id;
}

void profileChoice(int noCustomerType)
{
    int profileChoice;

    customer c;
    mmuStudent mstud;
    mmuStaff mstaff;
    shopper *shopper1 = new customer;
    shopper *shopper2 = new mmuStudent;
    shopper *shopper3 = new mmuStaff;

    cout << "\n\n********************" << endl;
    cout << "        Menu        " << endl;
    cout << "********************" << endl;
    cout << "Choice 1: Display Profile" << endl;
    cout << "Choice 2: Update Profile" << endl;
    cout << "Choice 3: Deregister   " << endl;
    cout << "Choice 4: Exit    " << endl;
    cout << "\nEnter your choice [1, 2 or 3]: ";
    cin >> profileChoice;

    switch(profileChoice)
    {
        case 1: if(noCustomerType==1) { shopper1->displayProfile(); } 
                else if(noCustomerType==2) { shopper2->displayProfile(); }
                else if(noCustomerType==3) { shopper3->displayProfile(); } break;
        
        case 2: if(noCustomerType==1) { shopper1->updateProfile(); } 
                else if(noCustomerType==2) { shopper2->updateProfile(); }
                else if(noCustomerType==3) { shopper3->updateProfile(); } break;

        case 3: if(noCustomerType==1) { shopper1->deregister(); } 
                else if(noCustomerType==2) { shopper2->deregister(); }
                else if(noCustomerType==3) { shopper3->deregister(); } break;

        case 4: exit(0); break;
        default: cout << "Invalid customer type!";
    }
}

void login()
{
    string line, IdPassCheck;
    string customerUserName, customerPassword;
    char cont;
    int noCustomerType;

    cout << "\n=========================================" << endl;
    cout << "              Shopper Login              " << endl;
    cout << "=========================================" << endl;

    cout << "Please enter your username [max words of 20] : " << endl;
    cin.ignore();
    getline(cin, customerUserName);

    cout << "Please enter your password [max words of 20] : " << endl;
    getline(cin, customerPassword);

    IdPassCheck = customerUserName + customerPassword;

    // cout << "Check :" << IdPassCheck;

    // system("pause");

    system("CLS");

    ifstream logfile;
    logfile.open("shopperAccount.txt", ios::in);


    if(logfile.fail())
    {
        cout << "Failed to open file..." << endl;
        exit(1);
    }
    else
    {
        int counter=0;

        //logfile.seekg(0, ios::beg);
        // for(int i=0; i<10; i++){
        //     logfile >> x;
        //     cout << x << endl;
        // }

        //system("pause");

        //To read every line of the txt file
        while(getline(logfile, line))
        {
            //ignoring the first 3 lines of txt files
            if(counter++ > 3)
            {
                logfile.ignore(12);

                //STARTING OF DELIMITER
                //Delimiter is to delete the "|" in the line and achieve a clean line of text without the "|"
                string delimiter = "|";
                size_t pos = 0;
                string token, word;

                while ((pos = line.find(delimiter)) != string::npos)
                {
                    token = line.substr(0, pos);

                    //regex_replace function
                    //to remove any whitespace by replacing it with a ("") null value
                    token = regex_replace(token,regex("\\s"),"");

                    word = word + token;

                    line.erase(0, pos + delimiter.length());
                }
                //END OF DELIMITER
                
                //cout << word << endl;

                //system("pause");

                if(word.compare(IdPassCheck) == 0)
                {
                    cout << "You are Logged In!!!" << endl;
                    logfile.close();
                    exit(0);
                }
            }
        }

        logfile.close();

        cout << "Incorrect Username and Password...Try Again!" << endl;
        cout << "Try Again?? [y/n] :" ;
        
        cin >> cont; 

        if(tolower(cont) == 'y') 
        {
            login();
        }
    }

    cout << "\n-----------------------------------------" << endl;
    cout << "Choose your customer type: " << endl;
    cout << "1. Normal Customer" << endl;
    cout << "2. MMU Student" << endl;
    cout << "3. MMU Staff" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "Enter your customer type [1, 2 or 3]: ";
    cin >> noCustomerType;

    profileChoice(noCustomerType);   
}

void viewProfile(string filename)
{
    string line, savedLine, headerLine;
    string header[4];
    size_t pos;
    int i=0, counter=0;
    string custId;

    cout << "Please enter your shopper ID : ";
    cin >> custId;

    ifstream cusHeadFile;
    cusHeadFile.open(filename);
    if(!(cusHeadFile.is_open()))
    {
        cout << "Fail to open file...";
    }
    else
    {
        while(getline(cusHeadFile, headerLine))
        {   
            if(counter++ < 4)
            {
                header[i] = headerLine;
                i++;          
            }
        }
    }
    cusHeadFile.close();
    
    line = "";
    ifstream cusProfile(filename);
    if(!(cusProfile.is_open()))
    {
        cout << "Fail to open file...";
    }
    else
    {       
        while(getline(cusProfile, line))
        {
            if((pos = line.find(custId)) != string::npos)
            {
                if(pos<11)
                {
                    savedLine = line;
                }
                else
                {
                    cusProfile.close();
                }  
            }
        }
    }
        cusProfile.close();

    for(int j=0; j<4; j++)
    {
        cout << header[j] << endl;
    }
    
    cout << savedLine << endl;
}