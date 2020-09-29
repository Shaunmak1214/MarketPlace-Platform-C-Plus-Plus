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

#include <regex>

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

        //TODO LIST
        //make check for max words to avoid crashing the program

        ofstream regfile;
        regfile.open("ownerAccount.txt", ios::app);

            if(regfile.fail()) {

                cout << "Error writing to the file, program ends...try again!" << endl;
                exit(1);

            }else{

                regfile << "| " << setw(9) << ownerId << " |";
                regfile << setw(15) << ownerPassword << " |" << "\n";

                regfile.close();

                cout << "Account Registered !!!" << endl;
                    
            }

    }

    void login() {

        string line, IdPassCheck;

        cout << "\n\n===============Owner Login===============" << endl;

        cout << "Please enter your user ID [max words of 10] : " << endl;
        cin >> ownerId; 

        cout << "Please enter your password [max words of 15] : " << endl;
        cin.ignore();
        getline(cin, ownerPassword);

        IdPassCheck = ownerId + ownerPassword;

        //cout << "Check :" << IdPassCheck;

        //system("pause");

        system("CLS");

        ifstream logfile;
        logfile.open("ownerAccount.txt", ios::in);

        if(logfile.fail()) {

            cout << "Failed to open file...program ends" << endl;
            exit(1);

        }else{

            int counter=0;

            //ignoring the first 3 lines of txt files using the ignore functio
            logfile.ignore(3, '\n');

            logfile.seekg(0, ios::beg);

            while(getline(logfile, line)){

                if(counter++ > 2) {

                    string delimiter = "|";
                    size_t pos = 0;
                    string token;
                    string word;

                        while ((pos = line.find(delimiter)) != string::npos) {

                            token = line.substr(0, pos);

                            //regex_replace to remove any whitespace by replacing whitespace with ("") null value
                            token = regex_replace(token,regex("\\s"),"");

                            //cout << token << " ";

                            word = token + token;

                            line.erase(0, pos + delimiter.length());

                            //cout << word;

                        }

                    //cout << word << endl;

                    if(word.compare(IdPassCheck) == 0){

                        cout << "You are Logged In!!!" << endl;
                        exit(0);

                    }

                }


            }

            cout << "Login Failed" << endl;

            logfile.close();

        }

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