// Program: TC02.1181203334.Mak.Yen.Wei.cpp
// Course: Object Oriented Programming
// Year: 2020/2021 Trimester 1
// Name: Mak Yen Wei
// ID: 1181203334
// Lecture Section: TC02
// Tutorial Section: TT04
// Email: 1181203334@student.mmu.edu.my
// Phone: 018-9495849

#include<iostream>
#include<iomanip>
#include<string>

using namespace std;

//Lists of classes
class owner {

    private:
    string ownerId, ownerPassword, ownerName, ownerCompany;

    public:
    void menu() {

        cout << "====================" << endl;
        cout << "        Menu        " << endl;
        cout << "====================" << endl;
        
        cout << "Choice #1: Register" << endl;
        cout << "Choice #2: Login   " << endl;
        cout << "Choice #3: Exit    " << endl;

    }

    void registration() {

        cout << "\n\n======Owner Register=======" << endl;
        
        cout << "Please enter your new user ID: " << endl;
        cin >> ownerId;
        
        cout << "Please enter your new password: " << endl;
        cin >> ownerPassword;

    }

    void login() {

        cout << "\n\n=========Owner Login=========" << endl;

        cout << "Please enter your user ID: " << endl;
        cin >> ownerId;
        
        cout << "Please enter your password: " << endl;
        cin >> ownerPassword;
    }

};

class item {
    
    private:
    int itemId, noUnits;
    string itemName, itemCompany, itemType;
    double price;

    public:
    
    friend class magazine;
    friend class book;
    friend class movie;

};

class magazine {
    
    private:
    int year, month, totalSalesUnits;
    double totalSalesAmount;

    public:
    void displaySales() {
        
        cout << "=====Magazine Sales Report=====" << endl;
        cout << "Total Sales Amount : " << totalSalesAmount << endl;
        cout << "Total Sales Units  : " <<totalSalesUnits << endl;

    }
};

class book {

    private:
    string authorName;
    int totalSalesUnits;
    double totalSalesAmount;

    public:
    void displaySales() {

        cout << "=====Book Sales Report=====" << endl;
        cout << "Total Sales Amount : " << totalSalesAmount << endl;
        cout << "Total Sales Units  : " <<totalSalesUnits << endl;

    }

};

class movie {

    private:
    string mainActorName;
    int totalSalesUnits;
    double totalSalesAmount;

    public:
    void displaySales() {

        cout << "=====Movie Sales Report=====" << endl;
        cout << "Total Sales Amount : " << totalSalesAmount << endl;
        cout << "Total Sales Units  : " <<totalSalesUnits << endl;

    }

};

//functions prototypes
void choice();

//main function
int main() {

    owner o;

    choice();

    return 0;

}

//functions
void choice() {

    int choice;
    
    owner O;

    O.menu();
    
    cout << "Enter Your Choice :";
    cin >> choice;

        while(!(choice <= 3 && choice >= 1)) {

            cout << "\n\n###################ALERT#######################" << endl;
            cout << "## Please enter a valid choice (eg: 1, 2, 3) ##" << endl;
            cout << "###############################################" << endl;

            cout << "\nEnter Your Choice: ";
            cin >> choice;

        }

            if(choice == 1) {

                O.registration();

            }else if(choice == 2) {

                O.login();

            }else if(choice == 3) {

                exit(0);
        
            }

}