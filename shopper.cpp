/**********|**********|**********|
Program: shopper.cpp
Course: Object Oriented Programming
Year: 2020/2021 Trimester 1
Name: Ong Sin Yin
ID: 1181203333
Lecture Section: TC02
Tutorial Section: TT04
Email: 1181203333@student.mmu.edu.my
Phone: 018-4093684
**********|**********|**********/

#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<fstream>

#include <regex>

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

//Function prototype
void menuChoice();
// void reg_setCustomerType(int noCustomerType, int customerId);

class shopper
{
    protected:
        string customerName;
        string address;
        int noCustomerType;
        int customerId = 1000;
        string customerUserName;
        string customerPassword;

    public:
        void menu()
        {
        	cout << "=========================================" << endl;
        	cout << "            WELCOME, SHOPPER!            " << endl;
        	cout << "=========================================" << endl << endl;
            cout << "********************" << endl;
            cout << "        Menu        " << endl;
            cout << "********************" << endl;
            cout << "Choice 1: Register" << endl;
            cout << "Choice 2: Login   " << endl;
            cout << "Choice 3: Exit    " << endl;
        }
        /*void registration()
        {
            cout << "\n=========================================" << endl;
            cout << "           Shopper Registration          " << endl;
            cout << "=========================================" << endl;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter full address: ";
            getline(cin, address);
            cout << "\n-----------------------------------------" << endl;
            cout << "Choose your customer type: " << endl;
            cout << "1. Normal Customer" << endl;
            cout << "2. MMU Student" << endl;
            cout << "3. MMU Staff" << endl;
            cout << "-----------------------------------------" << endl;
            cout << "Enter customer type [1, 2 or 3]: ";
            cin >> noCustomerType;
			reg_setCustomerType(noCustomerType, customerId);
			cout << "Enter new user name (max 20 alphabets): ";
            getline(cin, customerUserName);
            cout << "Enter new password (max 20 alphabets): ";
            getline(cin, customerPassword);
            
            struct idGenerator {

                int id;
                string line;

                idGenerator() : id (0) {

                    ifstream idfile;

                    ifstream ifs("shopperAccount.txt");

                    if(idfile.fail()) {

                        cout << "Failed to open file...program ends" << endl;
                        exit(1);

                    }else{

                        ifs >> id;
                        
                    }
                }
            

                ~idGenerator() {

                    ofstream ofs("ownerAccount.txt", std::ios_base::out | std::ios_base::trunc);
                    ofs << id;

                }

                int operator()() { 

                    return id++; 

                }
    };
            
            ofstream regFile1;
            regFile1.open("shopperProfile.txt", ios::app);
            if(regFile1)
            {
            	regFile1 << "|" << setw(7) << customerId;
				regFile1 << "|" << setw(50) << customerName;
				regFile1 << "|" << setw(100) << address;
				regFile1 << "|" << setw(16) << noCustomerType;
			}
			regFile1.close();
            
            ofstream regFile2;
			regFile2.open("shopperAccount.txt", ios::app);
			if(regFile2)
			{
				regFile2 << "|" << setw(10) << customerId << "|" << setw(20) << customerUserName << "|" << setw(20) << customerPassword << "|" << endl;
				cout << "\nREGISTRATION COMPLETED SUCCESSFULLY!"; 
			}
			regFile2.close();
        }*/
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
};

/*class customer : public shopper
{
    private:
        string customerType = "Normal Student";
    public:
        void setCustomerType(int customerId)
        {
            cin.ignore();
        }
        friend shopper;
};

class mmuStudent : public shopper
{
    private:
        string customerType = "MMU Student";;
        string mmuCourseName;
    public:
        void setCustomerType(int customerId)
        {
            cout << "\nEnter your course name: ";
            cin.ignore();
            getline(cin, mmuCourseName);
        }
};

class mmuStaff : public shopper
{
    private:
        string customerType = "MMU Staff";
        string mmuDepartment;
    public:
        void setCustomerType(int customerId)
		{
            cout << "\nEnter the name of department: ";
            cin.ignore();
            getline(cin, mmuDepartment);
        }
};

class item
{
    protected:
        int itemId, noUnits;
        string itemName, itemCompany, itemType;
        double price;

    public:
        void viewItem(); 
        void addItem();
        void deleteItem();
        void modifyItem();
        void viewRecord();
        void deleteRecord();
};

class magazine : public item
{
    private:
    	int year, month;
    
    public:
};

class book : public item
{
    private:
    string authorName;

    public:
};

class movie : public item {

    private:
    string mainActorName;

    public:
};

class payment
{   
	private:
        int cardNum;
        
    public:
        void payment()
        {
            string cardNum;
			bool checkInt;
			char choice;
			
			cout << "Proceed to payment? [Enter Y or N]: ";
			cin >> choice;
		    
			if(choice=='Y')
			{
				cout << "\nPlease enter your payment card number (10 digit): ";
		    	cin >> cardNum;
		    	
				if(cardNum.length() == 10)
			    {
					for(int i=0; i<cardNum.length(); i++)
					{
						if(isdigit(cardNum[i])==false)
						{
							checkInt = false;
						}
						else
						{
							checkInt = true;
						}
					}
				}
				else
				{
					checkInt = false;
				}
				
				if(checkInt == true)
				{
					cout << "\nTransaction completed successfully!";
				}
				else
				{
					cout << "\nInvalid payment card number.";
				}
		    }
		    else
		    {
		        exit(1);
		    }       
};
*/
//int main
int main()
{
    shopper S;

    menuChoice();
    

    return 0;

} 

//Function
void menuChoice()
{
    int choice;
    
    shopper s;

    s.menu();
    
    cout << "\nEnter Your Choice: ";
    cin >> choice;

    while(!(choice <= 3 && choice >= 1))
    {
        cout << "\n\n###################ALERT#######################" << endl;
        cout << "## Please enter a valid choice (eg: 1, 2, 3) ##" << endl;
        cout << "###############################################" << endl;

        cout << "\nEnter Your Choice: ";
        cin >> choice;
    }

    if(choice == 1)
    {
        //s.registration();
        cout << endl;
    }
    else if(choice == 2)
    {
        s.login();
    }
    else if(choice == 3)
    {
        exit(0);
    }
}
/*
void reg_setCustomerType(int noCustomerType, int customerId)
{
	if(noCustomerType==1)
    {
        customer c;
        c.setCustomerType(customerId);
    }
    else if(noCustomerType==2)
    {
        mmuStudent mstud;
        mstud.setCustomerType(customerId);
    }
    else if(noCustomerType==3)
    {
        mmuStaff mstaff;
        mstaff.setCustomerType(customerId);
    }
}

void itemChoice()
{
	int cartOption;
	int categoryOption;
	
	cout << "\n=========================================" << endl;
    cout << "             Shopping Cart              " << endl;
    cout << "=========================================" << endl;
    cout << "             1. View item                " << endl;
    cout << "             2. Add item                 " << endl;
    cout << "             3. Delete item              " << endl;
    cout << "             4. Modify item              " << endl;
	cout << "=========================================" << endl;
	cout << "Choose an option [Enter 1, 2, 3 or 4]: ";
	cin >> cartOption;
	
	cout << "********************" << endl;
	cout << "      Item Type     " << endl;
	cout << "********************" << endl;
	cout << "Category 1: Magazine" << endl;
	cout << "Category 2: Book    " << endl;
	cout << "Category 3: Movie   " << endl;
	cout << "Choose an item type [Enter 1, 2 or 3]: ";
	cin >> categoryOption;
	
		
}

void setCartOption(int cartOption)
{
	magazine ma;
	book bo;
	movie mo;
	
	switch(cartOption)
	{
		case 1: setAction(ma); break;
		case 2: setAction(bo); break;
		case 3: setAction(mo); break;
		default: cout << "Invalid option for shopping cart!"; 
	}
}

void setCategoryOption(&category)
{
	switch(option)
	{
		case 1: category.viewItem(); break;
		case 2: category.addItem(); break;
		case 3: category.deleteItem(); break;
		case 4: category.modifyItem(); break;
		default: cout << "Invalid option for item type!";
	}
}*/
