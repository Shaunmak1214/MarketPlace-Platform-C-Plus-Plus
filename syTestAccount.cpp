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

class shopper
{
    protected:
        int customerId;
        string customerName;
        string address;
        string customerUserName;
        string customerPassword;

    public:
        void login()
        {
            string line, IdPassCheck;
            char cont;

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
                cout << "Failed to open file...program ends" << endl;
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

                        if(word.compare(IdPassCheck) == 0){

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
            
        }
        void updateProfile();
        void deregister();
        virtual void registration()=0;
};

class customer : public shopper
{
    private:
        string customerType = "Normal Customer";
    public:
        void registration()
        {
            cout << "\n=========================================" << endl;
            cout << "           Shopper Registration          " << endl;
            cout << "=========================================" << endl;
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
                cout << "\nREGISTRATION COMPLETED SUCCESSFULLY!"; 
            }
            regCusFile2.close();
        }
};

class mmuStudent : public shopper
{
    private:
        string customerType = "MMU Student";;
        string mmuCourseName;
    public:
        void registration()
        {
            cout << "\n=========================================" << endl;
            cout << "           Shopper Registration          " << endl;
            cout << "=========================================" << endl;
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
            cout << "\nEnter your course name: ";
            getline(cin, mmuCourseName);

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
                cout << "\nREGISTRATION COMPLETED SUCCESSFULLY!"; 
            }
            regStudFile2.close();
        }
};

class mmuStaff : public shopper
{
    private:
        string customerType = "MMU Staff";
        string mmuDepartmentName;
    public:
        void registration()
		{
            cout << "\n=========================================" << endl;
            cout << "           Shopper Registration          " << endl;
            cout << "=========================================" << endl;
            cout << "Welcome, " << customerType << "! Please fill in the information below. " << endl; 
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
			cout << "Enter new user name [max 20 characters]: ";
            getline(cin, customerUserName);
            cout << "Enter new password [max 20 characters]: ";
            getline(cin, customerPassword);
            cout << "\nEnter the name of department: ";
            getline(cin, mmuDepartmentName);

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
                cout << "\nREGISTRATION COMPLETED SUCCESSFULLY!"; 
            }
            regStafFile2.close();
        }
};

int main()
{
    customer c;
    mmuStudent mstud;
    mmuStaff mstaff;
    int accountChoice;
    int noCustomerType;

    cout << "=========================================" << endl;
    cout << "            WELCOME, SHOPPER!            " << endl;
    cout << "=========================================" << endl << endl;
    cout << "********************" << endl;
    cout << "        Menu        " << endl;
    cout << "********************" << endl;
    cout << "Choice 1: Register" << endl;
    cout << "Choice 2: Login   " << endl;
    cout << "Choice 3: Exit    " << endl;
    cout << "\nEnter your choice [1, 2 or 3]: ";
    cin >> accountChoice;

     while(!(accountChoice >= 1 && accountChoice <= 3))
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
            default: "Invalid customer type!";
        }
    }
    /*else if(accountChoice==2)
    {
        
    }*/
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