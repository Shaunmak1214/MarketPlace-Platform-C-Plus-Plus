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
using namespace std;

class shopper
{
    protected:
        string customerName;
        string address;
        int noCustomerType;
        string customerId;
        string customerPassword;

    public:
        void menu()
        {
            cout << "====================" << endl;
            cout << "        Menu        " << endl;
            cout << "====================" << endl;
            cout << "Choice 1: Register" << endl;
            cout << "Choice 2: Login   " << endl;
            cout << "Choice 3: Exit    " << endl;
        }
        void registration()
        {
            cout << "========Shopper Registration=========" << endl;
            cout << "Enter name: ";
            cin.ignore();
            getline(cin, customerName);
            cout << "Enter full address: ";
            cin.ignore();
            getline(cin, address);
            cout << "\n-----------------------------" << endl;
            cout << "Choose your customer type: " << endl;
            cout << "1. Normal Customer" << endl;
            cout << "2. MMU Student" << endl;
            cout << "3. MMU Staff" << endl;
            cout << "-----------------------------" << endl;
            cout << "Enter customer type [1, 2 or 3]: ";
            cin >> noCustomerType;

            if(noCustomerType==1)
            {
                customer c;
                c.registration();
            }
            else if(noCustomerType==2)
            {
                mmuStudent mstud;
                mstud.registration();
            }
            else if(noCustomerType==3)
            {
                mmuStaff mstaff;
                mstaff.registration();
            }
            cout << "Enter new password: ";
            cin >> customerPassword;
        }
        void login()
        {
            cout << "===========Shopper Login===========" << endl;
            cout << "Enter ID: ";
            cin >> customerId;
            cout << "Enter Password: ";
            cin >> customerPassword;
        }
        void updateProfile();
        void deregister();
};

class customer : public shopper
{
    private:
        string customerType;
    public:
        void registration()
        {
            customerType = "Normal Student";
        }
};

class mmuStudent : public shopper
{
    private:
        string customerType;
        string mmuCourseName;
    public:
        void registration()
        {
            customerType = "MMU Student";
            cout << "\nPlease provide your course name: ";
            cin >> mmuCourseName;
        }
        
};

class mmuStaff : public shopper
{
    private:
        string customerType;
        string mmuDepartment;
    public:
        void registration()
        {
            customerType = "MMU Staff";
            cout << "\nPlease enter the name of department: ";
            cin >> mmuDepartment;
        }
};

class item 
{
    private:
        int itemId, noUnits;
        string itemName, itemCompany, itemType;
        double price;

    public:
        void viewItem()
        {
            cout << endl;
        }
        void addItem();
        void deleteItem();
        void modifyItem();
        void viewRecord();
        void deleteRecord();
};

/*class payment
{   private:
        int cardNum;
    public:
        void payment()
        {
            cout << "Please enter your payment card number (10 digit): ";
            cin >> cardNum;
            cout << "Success";
        }
};*/ 

//Function prototype
void header();

//int main
int main()
{
    shopper S;

    header();


    return 0;

} 

//Function
void header()
{
    int choice;
    
    shopper s;

    s.menu();
    
    cout << "Enter Your Choice :";
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
        s.registration();
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