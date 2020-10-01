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
//#include<cstring>
#include<fstream>

#include <regex>

//#include <conio.h>
//#include <stdio.h>
//#include <stdlib.h>


using namespace std;

//functions prototypes
void header();
int navigation();
int idGenerator();

//Lists of classes

class item {

    protected:
    int itemId, noUnits, navchoice;
    string itemName, itemCompany, itemType, dltItem;
    double price;

};

class magazine : public item {

    private:
    int year, month, totalSalesUnits;
    double totalSalesAmount;

    public:
    void choiceMag(){

        navchoice = navigation();

        if(navchoice == 1) {

            addMagazine();

        }else if(navchoice == 2) {

            updateMagazine();

        }else if(navchoice == 3) {

            deleteMagazine();

        }else if(navchoice == 4) {

            displaySales();

        }

    }

    void addMagazine() {

        int id;

        //Start of Id Auto Generator
        id = idGenerator();
        //End of Id Auto Generator

        cout << "\n\n========Add Magazine Form=======" << endl;
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

        ofstream addmag;
        addmag.open("magazine.txt", ios::app);

        if(addmag.fail()) {

            cout << "Error writing to the file, program ends...try again!" << endl;
            exit(1);

        }else{

            addmag << "\n" << "|" << setw(11) << id;
            addmag << "|" << setw(30) << itemName;
            addmag << "|" << setw(14) << price;
            addmag << "|" << setw(11) << noUnits;
            addmag << "|" << setw(30) << itemCompany;
            addmag << "|" << setw(4) << year;
            addmag << "|" << setw(5) << month << "|";
            addmag.close();

            cout << "Item added successfully!" << endl;

            choiceMag();

        }

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
        void choiceBook(){

        navchoice = navigation();

        if(navchoice == 1) {

            addBook();

        }else if(navchoice == 2) {

            updateBook();

        }else if(navchoice == 3) {

            deleteBook();

        }else if(navchoice == 4) {

            displaySales();

        }

    }

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
    void choiceMovie(){

        navchoice = navigation();

        if(navchoice == 1) {

            addMovie();

        }else if(navchoice == 2) {

            updateMovie();

        }else if(navchoice == 3) {

            deleteMovie();

        }else if(navchoice == 4) {

            displaySales();

        }

    }

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

class owner : public magazine, public book, public movie{

    private:
    string ownerId, ownerPassword, ownerName, ownerCompany;
    int navchoice, itemchoice;

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

        int id=0;
        string idtry;

        //Start of Id Auto Generator
        ifstream checkId;
        checkId.open("ownerId.txt", ios::in);

            if(checkId.fail()) {

                cout << "Auto Generate Id Function Failed..." << endl;

            }else{

                checkId >> id;
                checkId.close();

            }

        id++;

        ofstream addId;
        addId.open("ownerId.txt");

            if(addId.fail()) {

                cout << "Auto Generate Id Function Failed..." << endl;

            }else{

                addId << id;
                addId.close();

            }
        //End of Id Auto Generator

        cout << "\n\n===================Owner Register====================" << endl;

        cout << "Please enter your new username[max words of 10] : " << endl;
        cin.ignore();
        getline(cin, ownerName);

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

                regfile << "\n" << "|" << setw(8) << id;
                regfile << "|" << setw(20) << ownerName;
                regfile << "|" << setw(20) << ownerPassword << "|";
                regfile.close();

                cout << "Account Registered !!!" << endl;
                    
            }

    }

    void login() {

        string line, IdPassCheck;
        int loggedin = 0;
        char cont;

        cout << "\n\n===============Owner Login===============" << endl;

        cout << "Please enter your username [max words of 10] : " << endl;
        cin.ignore();
        getline(cin, ownerName);

        cout << "Please enter your password [max words of 15] : " << endl;
        getline(cin, ownerPassword);

        IdPassCheck = ownerName + ownerPassword;

        //system("pause");

        system("CLS");

        ifstream logfile;
        logfile.open("ownerAccount.txt", ios::in);


            if(logfile.fail()) {

                cout << "Failed to open file...program ends" << endl;
                exit(1);

            }else{

                int counter=0;

                //system("pause");

                //To read every line of the txt file
                while(getline(logfile, line)){

                    //ignoring the first 3 lines of txt files
                    if(counter++ > 3) {

                        logfile.ignore(10, '\n');

                        //STARTING OF DELIMITER
                        //Delimiter is to delete the "|" in the line and achieve a clean line of text without the "|"
                        string delimiter = "|";
                        size_t pos = 0;
                        string token, word;

                            while ((pos = line.find(delimiter)) != string::npos) {

                                token = line.substr(0, pos);

                                //regex_replace function
                                //to remove any whitespace by replacing it with a ("") null value
                                token = regex_replace(token,regex("\\s"),"");

                                word = word + token;

                                line.erase(0, pos + delimiter.length());

                            }
                        //END OF DELIMITER

                        if(word.compare(IdPassCheck) == 0){

                            cout << "You are Logged In!!!" << endl;
                            logfile.close();
                            loggedin = 1;

                        }

                    }

                }

                if(loggedin == 1) {

                    itemChoose();

                }else{

                    cout << "Incorrect Username and Password...Try Again!" << endl;
                    cout << "Try Again?? [y/n] :" ;
                    
                    cin >> cont; 

                        if(tolower(cont) == 'y') {

                            login();

                        }

                }

            }

    }

    void itemChoose() {

        cout << "============Item Choosing=============" << endl;
        cout << "Magazine                             1" << endl;
        cout << "Book                                 2" << endl;
        cout << "Movie                                3" << endl;

        cout << "Select your choice: ";
        cin >> itemchoice;

        if(itemchoice == 1) {

            cout << "Redirecting to Magazine..." << endl;
            choiceMag();

        }else if(itemchoice == 2) {

            cout << "Redirecting to Book..." << endl;
            choiceBook();

        }else if(itemchoice == 3) {

            cout << "Redirecting to Movie..." << endl;
            choiceMovie();

        }else{

            cout << "You entered an invalid choice, try again mate!" << endl;
            itemChoose();

        }

    }

};


//main function
int main() {

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

int navigation() {

    int navchoice;

    cout << "\n\n============Navigation Bar============" << endl;
    cout << "Insert Items                         1" << endl;
    cout << "Update Items                         2" << endl;
    cout << "Delete Items                         3" << endl;
    cout << "Display Sales                        4" << endl;
  
    cout << "Select Your Choice: ";
    cin >> navchoice;

        if(!(navchoice>=1 && navchoice<=4)) {

            cout << "You entered an invalid choice...Try Again!!!" << endl;
            navigation();

        }

    return navchoice;

}

int idGenerator() {

    int id;

        //Start of Id Auto Generator
        ifstream checkId;
        checkId.open("shopItemId.txt", ios::in);

            if(checkId.fail()) {

                cout << "Auto Generate Id Function Failed..." << endl;

            }else{

                checkId >> id;
                checkId.close();

            }

        //id increment
        id++;

        ofstream addId;
        addId.open("shopItemId.txt");

            if(addId.fail()) {

                cout << "Auto Generate Id Function Failed..." << endl;

            }else{

                addId << id;
                addId.close();

            }
        //End of Id Auto Generator

        return id;

}