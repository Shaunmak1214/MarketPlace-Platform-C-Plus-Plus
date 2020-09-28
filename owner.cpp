// Program: owner.cpp
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
#include<cstring>
#include<fstream>

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

//functions prototypes
void header();

//Lists of classes

class owner {

    private:
    string ownerId, ownerPassword, ownerName, ownerCompany;
    int navchoice;

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

        struct id_generator {

            id_generator() : _id (0) {

                std::ifstream ifs("ownerAccount.txt");
                ifs >> _id;
                //cout << _id;

            }

            ~id_generator() {

                std::ofstream ofs("previous_id.txt", std::ios_base::out | std::ios_base::trunc);
                ofs << _id;

            }

            int operator()() { 
                return _id++; 
            }

            int _id;
        };

        system ("CLS");

        ofstream regfile;
        regfile.open("ownerAccount.txt", ios::app);

        cout << "\n\n===================Owner Register====================" << endl;

        //Id will be auto generated, so no need owner to enter by himself.
        //They just need to enter new password.
        //(Refer to guideline)
        //By Sin Yin ^.^

        cout << "Please enter your new user ID [max words of 10] : " << endl;
        cin.ignore();
        getline(cin, ownerId);

        cout << "Please enter your new password [max words of 15] : " << endl;
        getline(cin, ownerPassword);

        regfile << "| " << setw(8) << ownerId << " |";
        regfile << setw(15) << ownerPassword << " |" << "\n";

        regfile.close();

    }

    void login() {

        string line;

        cout << "\n\n===============Owner Login===============" << endl;

        cout << "Please enter your user ID [max words of 10] : " << endl;
        cin >> ownerId;

        cout << "Please enter your password [max words of 15] : " << endl;
        cin.ignore();
        getline(cin, ownerPassword);

        ifstream logfile;
        logfile.open("ownerAccount.txt", ios::in);

        logfile.close();

    }

    void navigation() {

        cout << "============Navigation Bar============" << endl;
        cout << "View All Items                       1" << endl;
        cout << "Insert New Items                     2" << endl;
        cout << "Update Items                         3" << endl;
        cout << "Delete Items                         4" << endl;

        cout << "Select Your Choice: ";
        cin >> navchoice;

    }

};

class item {

    protected:
    int itemId, noUnits;
    string itemName, itemCompany, itemType, dltItem;
    double price;

    public:

};

class magazine : public item {

    private:
    int year, month, totalSalesUnits;
    double totalSalesAmount;

    public:
    void addMagazine() {

        cout << "========Add Magazine Form=======" << endl;
        cout << "Magazine Name       :";
        cin.ignore();
        getline(cin, itemName);

        cout << "Magazine Price      :";
        cin >> price;

        cout << "Number of units     :";
        cin >> noUnits;

        cout << "Name of the company :";
        cin.ignore();
        getline(cin, itemCompany);

        cout << "Year                :";
        cin >> year;

        cout << "Month               :";
        cin >> month;

    }

    void updateMagazine() {

        cout << "========Update Magazine Form=======" << endl;
        cout << "Magazine Name       :";
        cin.ignore();
        getline(cin, itemName);

        cout << "Magazine Price      :";
        cin >> price;

        cout << "Number of units     :";
        cin >> noUnits;

        cout << "Name of the company :";
        cin.ignore();
        getline(cin, itemCompany);

        cout << "Year                :";
        cin >> year;

        cout << "Month               :";
        cin >> month;

    }

    void deleteMagazine() {

        cout << "Name of the item u would like to delete? [Item name must be typed out exactly how it is]";
        cin.ignore();
        getline(cin, dltItem);

    }

    void displaySales() {
        
        cout << "=====Magazine Sales Report=====" << endl;
        cout << "Total Sales Amount : " << totalSalesAmount << endl;
        cout << "Total Sales Units  : " << totalSalesUnits << endl;

    }
};

class book : public item {

    private:
    string authorName;
    int totalSalesUnits;
    double totalSalesAmount;

    public:
    void addBook() {

        cout << "========Add Book Form=======" << endl;
        cout << "Book Name           :";
        cin.ignore();
        getline(cin, itemName);

        cout << "Book Price          :";
        cin >> price;

        cout << "Number of units     :";
        cin >> noUnits;

        cout << "Name of the company :";
        cin.ignore();
        getline(cin, itemCompany);

        cout << "Author Name         :";
        cin.ignore();
        getline(cin, authorName);

    }

    void updateBook() {

        cout << "========Update Book Form=======" << endl;
        cout << "Book Name           :";
        getline(cin, itemName);

        cout << "Book Price          :";
        cin >> price;

        cout << "Number of units     :";
        cin >> noUnits;

        cout << "Name of the company :";
        getline(cin, itemCompany);

        cout << "Author Name         :";
        getline(cin, authorName);

    }

    void deleteBook() {

        cout << "Name of the item u would like to delete? [Item name must be typed out exactly how it is]";
        getline(cin, dltItem);

    }

    void displaySales() {

        cout << "=====Book Sales Report=====" << endl;
        cout << "Total Sales Amount : " << totalSalesAmount << endl;
        cout << "Total Sales Units  : " << totalSalesUnits << endl;

    }

};

class movie : public item {

    private:
    string mainActorName;
    int totalSalesUnits;
    double totalSalesAmount;

    public:
    void addMovie() {

        cout << "========Add Movie Form=======" << endl;
        cout << "Movie Name           :";
        getline(cin, itemName);

        cout << "Movie Price          :";
        cin >> price;

        cout << "Number of units      :";
        cin >> noUnits;

        cout << "Name of the company  :";
        getline(cin, itemCompany);

        cout << "Main Actor Name      :";
        getline(cin, mainActorName);

    }

    void updateMovie() {

        cout << "========Update Movie Form=======" << endl;
        cout << "Movie Name           :";
        getline(cin, itemName);

        cout << "Movie Price          :";
        cin >> price;

        cout << "Number of units      :";
        cin >> noUnits;

        cout << "Name of the company  :";
        getline(cin, itemCompany);

        cout << "Main Actor Name      :";
        getline(cin, mainActorName);

    }

    void deleteMovie() {

        cout << "Name of the item u would like to delete? [Item name must be typed out exactly how it is]";
        getline(cin, dltItem);

    }
        
    void displaySales() {

        cout << "=====Movie Sales Report=====" << endl;
        cout << "Total Sales Amount : " << totalSalesAmount << endl;
        cout << "Total Sales Units  : " << totalSalesUnits << endl;

    }

};

//main function
int main() {

    owner O;

    //o.navigation();

    header();

    return 0;

}

//functions
void header() {

    int choice;
    
    owner o;

    o.menu();
    
    cout << "Enter Your Choice :";
    cin >> choice;

    //Validation of choice making, to ensure user submit the correct choice to move on

        while(!(choice <= 3 && choice >= 1)) {

            cout << "\n\n###################ALERT#######################" << endl;
            cout << "## Please enter a valid choice (eg: 1, 2, 3) ##" << endl;
            cout << "###############################################" << endl;

            cout << "\nEnter Your Choice: ";
            cin >> choice;

        }

            if(choice == 1) {

                o.registration();

            }else if(choice == 2) {

                o.login();

            }else if(choice == 3) {

                exit(0);

            }

}