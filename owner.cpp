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
#include<string> //string object usage
#include<fstream> // for file functions
#include<cstring> //for string::functions
#include<conio.h> //for getch funnction
#include<stdio.h> //for remove() and rename()
#include<stdlib.h> //for system("cls") fucntion / size_t object
#include<regex> //for regex.replace function

using namespace std;

//functions prototypes
void header();
int homeNav();
int itemChoose();

int navigation(int type);
int idGenerator(string txtfile);

char commonUpdate(string fileName, int itemType);
char commonDelete(string fileName);
char viewItems(string fileName, int startLimit);
void displaySalesByRange(string fileName, string itemType, string salesFilename);
void displaySales(string fileName, string itemType, string salesFilename);

//Lists of classes
class item {

    protected:
    int itemId, noUnits, counter;
    string itemName, itemCompany, itemType, dltItem, line, savedLine;
    string fileName = "shopItemId.txt";
    double price;
    size_t pos;
    char cont;

    public:
    //virtual function
    virtual void addItem() {}
    virtual void updateItem() {}
    virtual void deleteItem() {}
    //pure virtual function
    virtual void dispItem() = 0;
    virtual void dispSales() = 0;
    virtual void dispSalesRange() = 0;

};

//Magazine Class

class magazine : public item {

    private:
    //private data members initialization
    int year, month, totalSalesUnits;
    double totalSalesAmount;
    string magFilename, recordFilename, itemType, salesFilename;

    public:

    //default constructor
    magazine() {

        magFilename = "magazine.txt";
        recordFilename = "magazineRecord.txt";
        salesFilename = "magSales.txt";
        itemType = "Magazine";

    }

    //Add item function
    void addItem() {

        //Variable declaration
        int itemId;

        //id generator function
        itemId = idGenerator(fileName);

        //Header
        cout << "\n\n==============Add Magazine Form=============" << endl;

        cout << "Magazine Name [Max characters of 30]       :";
        cin.ignore();
        getline(cin, itemName);

            //Check if input length is longer than 30 or shorter than 0
            while(itemName.length() > 30 || itemName.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT #############################" << endl;
                cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                cout << "##############################################################" << endl;
                cout << "Magazine Name [Max characters of 30]       :";
                getline(cin, itemName);
                cout << endl;

            }

        cout << "Magazine Price                             :";
        cin >> price;

            //Check if price input is a negative number
            while(price < 0) {

                //If price is a negative number, then prompt user to input again
                cout << "\n\n################## ALERT #####################" << endl;
                cout << "Price cannot be a negative number...Fix It !!!" << endl;
                cout << "##############################################" << endl;
                cout << "Magazine Price                             :";
                cin >> price;
                cout << "\n";

            }

        cout << "Number of units                            :";
        cin >> noUnits;

            //Check if noUnits is a negative number
            while(noUnits < 0) {

                //if noUnits is a negative number, then prompt user to input again
                cout << "\n\n################## ALERT #####################" << endl;
                cout << "Units cannot be a negative number...Fix It !!!" << endl;
                cout << "##############################################" << endl;
                cout << "Number of units                            :";
                cin >> noUnits;
                cout << "\n";

            }

        cout << "Name of the company [Max characters of 30] :";
        cin.ignore();
        getline(cin, itemCompany);

            //Check if input length is longer than 30 or shorter than 0
            while(itemCompany.length() > 30 || itemCompany.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT ################################" << endl;
                cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                cout << "#################################################################" << endl;
                cout << "Name of the company [Max characters of 30] :";
                getline(cin, itemCompany);
                cout << endl;

            }

        cout << "Year                                       :";
        cin >> year;

            //Check if year is is greater than 9999 or lesser than 0
            while(year > 9999 || year < 0) {

                //if year is is greater than 9999 or lesser than 0 prompt user to input again
                cout << "\n\n############## ALERT #################" << endl;
                cout << "Year value is invalid ...Fix It !!!" << endl;
                cout << "#######################################" << endl;
                cout << "Year                                       :";
                cin >> year;

            }

        cout << "Month                                      :";
        cin >> month;

            //Check if month is greater than 12 or lesser than 1, then prompt user to input again
            while(month > 12 || month < 1) {

                cout << "\n\n############## ALERT #################" << endl;
                cout << "Month value is invalid ...Fix It !!!" << endl;
                cout << "#######################################" << endl;
                cout << "Month                                       :";
                cin >> month;

            }

        //opening file
        ofstream addmag;
        addmag.open("magazine.txt", ios::app);

            //Condition if file failed to open
            if(addmag.fail()) {

                cout << "Error writing to the file, program ends...try again!" << endl;
                addmag.close();
                exit(1);

            //Condition if file open succeed
            }else{

                //writing into file
                addmag << "\n" << "|" << setw(7) << itemId;
                addmag << "|" << setw(30) << itemName;
                addmag << "|" << setw(14) << setprecision(2) << fixed << price;
                addmag << "|" << setw(11) << noUnits;
                addmag << "|" << setw(30) << itemCompany;
                addmag << "|" << setw(4) << year;
                addmag << "|" << setw(5) << month << "|";
                addmag.close();

                cout << "Magazine item added successfully!" << endl;
                cout << "Redirecting you back to item choosing" << endl;

                //Going back to item choosing menu
                itemChoose();

            }

    }


    //Update Item Function
    void updateItem() {

        //return value to navigate users to item choose menu
        char returnValue = commonUpdate(magFilename, 1);

        //if returnValue is 's' (that means update function is a success), then prompt success output and redirect users to item choosing menu
        if(returnValue == 's') {

            cout << "Item Updated!!" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        //if returnValue is not 's' (that means update function is not a success), then prompt failed output then redirect users to item choosing menu
        }else{

            cout << "Failed to update" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }

    }

    //Delete Item Function
    void deleteItem() {

        //take return value to achieve function looping
        //if users failed to delete an item, there is a choice to retry again and again.
        char returnValue = commonDelete(magFilename);

        //while returnValue is always not equal to s, (s means success of deletion)
        while(returnValue != 's') {

            switch(returnValue) {

                //if users input y (that means user request to try again with the function), then run case'y'
                case 'y' : returnValue = commonDelete(magFilename); break;

                //if users input n (thats means user request to exit the function), then redirect users to item choose menu
                case 'n' : itemChoose();

            }

        }

        //if returnValue is equal to 's', then redirect users to item choosing menu
        cout << "Redirecting you back to item choosing" << endl;
        itemChoose();

    }

    //viewing item function
    void dispItem() {

        //Variable declaration
        string line;
        char choice;
        int startLimit = 4;
        int lineCount;

        //Open file
        ifstream view;
        view.open(magFilename, ios::in);

            //Get data line by line in file
            while(getline(view, line)) {

                //Increment to count how many lines there is in the file
                lineCount++;

            }

        //close file
        view.close();

        //Return value to make next page and previous page function
        choice = viewItems(magFilename, startLimit);

            //While choice is not equals to e(e means exit)
            while(choice != 'e') {

                if(choice == 'n') {

                    //Make next page function by adding startlimit by 11
                    if(startLimit <= lineCount-10) {

                        startLimit = startLimit+11;

                    }

                    //run function again with updated startLimit function
                    choice = viewItems(magFilename, startLimit);

                }else if(choice == 'p') {

                    //Make previous page function by substrating startlimit by 11
                    if(startLimit >= 14) {

                        startLimit = startLimit-11;

                    }

                    //run function again with updated startLimit function
                    choice = viewItems(magFilename, startLimit);

                }

            }

        //If return value Choice is equals to e(means user wish to exit)
        cout << "View Finished" << endl;
        cout << "Redirecting you back to item choosing" << endl;
        //Redirect user back to item choosing menu
        itemChoose();

    }

    //Display Sales by Range Function
    void dispSalesRange() {

        displaySalesByRange(recordFilename, itemType, salesFilename);

    }

    //Display Magazine Sales function
    void dispSales() {

        displaySales(recordFilename, itemType, salesFilename);

    }
};

//Book Class

class book : public item {

    private:
    //private data members initialization
    string authorName, bookFilename, recordFilename, itemType, salesFilename;

    public:

    //default constructor
    book() {

        bookFilename = "book.txt";
        recordFilename = "bookRecord.txt";
        itemType = "Book";
        salesFilename = "bookSales.txt";

    }
    //Add item function
    void addItem() {

        //Variable declaration
        int id;

        //id generator function
        id = idGenerator(fileName);

        //Header
        cout << "========Add Book Form=======" << endl;
        cout << "Book Name [Max characters of 30]          :";
        cin.ignore();
        getline(cin, itemName);

            //Check if input length is longer than 30 or shorter than 0
            while(itemName.length() > 30 || itemName.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT #############################" << endl;
                cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                cout << "##############################################################" << endl;
                cout << "Book Name [Max characters of 30]       :";
                getline(cin, itemName);
                cout << endl;

            }

        cout << "Book Price                                :";
        cin >> price;

            //Check if price input is a negative number
            while(price < 0) {

                //If price is a negative number, then promp user to input again
                cout << "\n\n################## ALERT #####################" << endl;
                cout << "Price cannot be a negative number...Fix It !!!" << endl;
                cout << "##############################################" << endl;
                cout << "Book Price                             :";
                cin >> price;
                cout << "\n";

            }

        cout << "Number of units                            :";
        cin >> noUnits;

            //Check if noUnits is a negative number
            while(noUnits < 0) {

                //if noUnits is a negative number, then prompt user to input again
                cout << "\n\n################## ALERT #####################" << endl;
                cout << "Units cannot be a negative number...Fix It !!!" << endl;
                cout << "##############################################" << endl;
                cout << "Number of units                            :";
                cin >> noUnits;
                cout << "\n";

            }

        cout << "Name of the company [Max characters of 30] :";
        cin.ignore();
        getline(cin, itemCompany);

            //Check if input length is longer than 30 or shorter than 0
            while(itemCompany.length() > 30 || itemCompany.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT ################################" << endl;
                cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                cout << "#################################################################" << endl;
                cout << "Name of the company [Max characters of 30] :";
                getline(cin, itemCompany);
                cout << endl;

            }

        cout << "Author Name [Max characters of 30]         :";
        getline(cin, authorName);

            //Check if input length is longer than 30 or shorter than 0
            while(authorName.length() > 30 || authorName.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT ###############################" << endl;
                cout << "Author name entered is either too long or too short...Fix It !!!" << endl;
                cout << "################################################################" << endl;
                cout << "Author Name [Max characters of 30]        :";
                getline(cin, authorName);
                cout << endl;

            }

        //opening file
        ofstream addBook;
        addBook.open("book.txt", ios::app);

        //Condition if file failed to open
        if(addBook.fail()) {

            cout << "Error writing to the file, program ends...try again!" << endl;
            itemChoose();

        //COndition if file open succeed
        }else{

            //writing into file
            addBook << "\n" << "|" << setw(7) << id;
            addBook << "|" << setw(30) << itemName;
            addBook << "|" << setw(14) << setprecision(2) << fixed << price;
            addBook << "|" << setw(11) << noUnits;
            addBook << "|" << setw(30) << itemCompany;
            addBook << "|" << setw(30) << authorName << "|";
            addBook.close();

            cout << "Book item added successfully!" << endl;

            //Going back to item choosing menu
            itemChoose();

        }

    }

    //Update item Function
    void updateItem() {

        //return value to navigate users to item choose menu
        char returnValue = commonUpdate(bookFilename, 2);

        //if returnValue is 's' (that means update function is a success), then prompt success output and redirect users to item choosing menu
        if(returnValue == 's') {

            cout << "Item Updated!!" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        //if returnValue is not 's' (that means update function is not a success), then prompt failed output then redirect users to item choosing menu
        }else {

            cout << "Failed to update" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }

    }

    //Delete Item Function
    void deleteItem() {

        //take return value to achieve function looping
        //if users failed to delete an item, there is a choice to retry again and again.
        char returnValue = commonDelete(bookFilename);

        //while returnValue is always not equal to s, (s means success of deletion)
        while(returnValue != 's') {

            switch(returnValue) {

                //if users input y (that means user request to try again with the function), then run case'y'
                case 'y' : returnValue = commonDelete(bookFilename); break;

                //if users input n (thats means user request to exit the function), then redirect users to item choose menu
                case 'n' : itemChoose();

            }

        }

        //if returnValue is equal to 's', then redirect users to item choosing menu
        cout << "Redirecting you back to item choosing" << endl;
        itemChoose();

    }

    //viewing item function
    void dispItem() {

        //Variable declaration
        string line;
        char choice;
        int startLimit = 4;
        int lineCount;

        //Open File
        ifstream view;
        view.open(bookFilename, ios::in);

            //Get data line by line in file
            while(getline(view, line)) {

                //Increment to count how many lines there is in the file
                lineCount++;

            }

        //close file
        view.close();

        //Return value to make next page and previous page function
        choice = viewItems(bookFilename, startLimit);

            //While choice is not equals to e(e means exit)
            while(choice != 'e') {

                if(choice == 'n') {

                    //Make next page function by adding startlimit by 11
                    if(startLimit <= lineCount-10) {

                        startLimit = startLimit+11;

                    }

                    //run function again with updated startLimit function
                    choice = viewItems(bookFilename, startLimit);

                }else if(choice == 'p') {

                    //Make previous page function by substrating startlimit by 11
                    if(startLimit >= 14) {

                        startLimit = startLimit-11;

                    }

                    //run function again with updated startLimit function
                    choice = viewItems(bookFilename, startLimit);

                }

            }

        //If return value Choice is equals to e(means user wish to exit)
        cout << "View Finished" << endl;
        cout << "Redirecting you back to item choosing" << endl;
        //Redirect user back to item choosing menu
        itemChoose();

    }

    void dispSalesRange() {

        displaySalesByRange(recordFilename, itemType, salesFilename);

    }

    //Display Book Sales function
    void dispSales() {

        displaySales(recordFilename, itemType, salesFilename);

    }

};

//Moevie Class
class movie : public item {

    private:
    //private data members initialization
    string mainActorName, movieFileName, recordFileName, itemType, salesFilename;

    public:

    //default constructor
    movie() {

        movieFileName = "movie.txt";
        recordFileName = "movieRecord.txt";
        salesFilename = "movieSales.txt";
        itemType = "Movie";

    }

    //Add item function
    void addItem() {

        //Variable declaration
        int id;

        //id generator function
        id = idGenerator(fileName);

        //Header
        cout << "========Add Movie Form=======" << endl;

        cout << "Movie Name [Max characters of 30]          :";
        cin.ignore();
        getline(cin, itemName);

            //Check if input length is longer than 30 or shorter than 0
            while(itemName.length() > 30 || itemName.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT #############################" << endl;
                cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                cout << "##############################################################" << endl;
                cout << "Movie Name [Max characters of 30]          :";
                getline(cin, itemName);
                cout << endl;

            }

        cout << "Movie Price                                :";
        cin >> price;

            //Check if price input is a negative number
            while(price < 0) {

                //If price is a negative number, then prompt user to input again
                cout << "\n\n################## ALERT #####################" << endl;
                cout << "Price cannot be a negative number...Fix It !!!" << endl;
                cout << "##############################################" << endl;
                cout << "Movie Price                                :";
                cin >> price;
                cout << "\n";

            }

        cout << "Number of units                            :";
        cin >> noUnits;

            //Check if noUnits is a negative number
            while(noUnits < 0) {

                //if noUnits is a negative number, then prompt user to input again
                cout << "\n\n################## ALERT #####################" << endl;
                cout << "Units cannot be a negative number...Fix It !!!" << endl;
                cout << "##############################################" << endl;
                cout << "Number of units                               :";
                cin >> noUnits;
                cout << "\n";

            }

        cout << "Name of the company [Max characters of 30] :";
        cin.ignore();
        getline(cin, itemCompany);

            //Check if input length is longer than 30 or shorter than 0
            while(itemCompany.length() > 30 || itemCompany.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT ################################" << endl;
                cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                cout << "#################################################################" << endl;
                cout << "Name of the company [Max characters of 30] :";
                getline(cin, itemCompany);
                cout << endl;

            }

        cout << "Main Actor Name [Max characters of 30]     :";
        getline(cin, mainActorName);

            //Check if input length is longer than 30 or shorter than 0
            while(mainActorName.length() > 30 || mainActorName.length() <= 0) {

                //if input length is longer than 30 or shorter than 0 then prompt user to input agqain
                cout << "\n\n########################## ALERT ################################" << endl;
                cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                cout << "#################################################################" << endl;
                cout << "Main Actor Name [Max characters of 30]     :";
                getline(cin, mainActorName);
                cout << endl;

            }

        //opening file
        ofstream addMovie;
        addMovie.open("movie.txt", ios::app);

            //Condition if file failed to open
            if(addMovie.fail()) {

                cout << "Error writing to the file, program ends...try again!" << endl;
                exit(1);

            //Condition if file open succeed
            }else{

                //writing into file
                addMovie << "\n" << "|" << setw(7) << id;
                addMovie << "|" << setw(30) << itemName;
                addMovie << "|" << setw(14) << setprecision(2) << fixed << price;
                addMovie << "|" << setw(11) << noUnits;
                addMovie << "|" << setw(30) << itemCompany;
                addMovie << "|" << setw(30) << mainActorName << "|";
                addMovie.close();

                cout << "Movie item added successfully!" << endl;
                cout << "Redirecting you back to item choosing" << endl;

                //Going back to item choosing menu
                itemChoose();

            }

    }

    //Update Item Function
    void updateItem() {

        //return value to navigate users to item choose menu
        char returnValue = commonUpdate(movieFileName, 2);

        //if returnValue is 's' (that means update function is a success), then prompt success output and redirect users to item choosing menu
        if(returnValue == 's') {

            cout << "Item Updated!!" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        //if returnValue is not 's' (that means update function is not a success), then prompt failed output then redirect users to item choosing menu
        }else{

            cout << "Failed to update" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }
    }

    //Delete Item Function
    void deleteItem() {

        //take return value to achieve function looping
        //if users failed to delete an item, there is a choice to retry again and again.
        char returnValue = commonDelete(movieFileName);

        //while returnValue is always not equal to s, (s means success of deletion)
        while(returnValue != 's') {

            switch(returnValue) {

                //if users input y (that means user request to try again with the function), then run case'y'
                case 'y' : returnValue = commonDelete(movieFileName); break;

                //if users input n (thats means user request to exit the function), then redirect users to item choose menu
                case 'n' : itemChoose();

            }

        }

        //if returnValue is equal to 's', then redirect users to item choosing menu
        cout << "Redirecting you back to item choosing" << endl;
        itemChoose();

    }

    //viewing item function
    void dispItem() {

        //Variable declaration
        string line;
        char choice;
        int startLimit = 4;
        int lineCount;

        //open file
        ifstream view;
        view.open(movieFileName, ios::in);

            //Get data line by line in file
            while(getline(view, line)) {

                //Increment to count how many lines there is in the file
                lineCount++;

            }

        //close file
        view.close();

        //Return value to make next page and previous page function
        choice = viewItems(movieFileName, startLimit);

            //While choice is not equals to e(e means exit)
            while(choice != 'e') {

                if(choice == 'n') {

                    //Make next page function by adding startlimit by 11
                    if(startLimit <= lineCount-10) {

                        startLimit = startLimit+11;

                    }

                    //run function again with updated startLimit function
                    choice = viewItems(movieFileName, startLimit);

                }else if(choice == 'p') {

                    //Make previous page function by substrating startlimit by 11
                    if(startLimit >= 14) {

                        startLimit = startLimit-11;

                    }

                    //run function again with updated startLimit function
                    choice = viewItems(movieFileName, startLimit);

                }

            }

        //If return value Choice is equals to e(means user wish to exit)
        cout << "View Finished" << endl;
        cout << "Redirecting you back to item choosing" << endl;
        //Redirect user back to item choosing menu
        itemChoose();

    }

    //Display Sales by Range Function
    void dispSalesRange() {

        displaySalesByRange(recordFileName, itemType, salesFilename);

    }

    //Display Movie Sales function
    void dispSales() {

        displaySales(recordFileName, itemType, salesFilename);

    }

};

//Owner class with inheritance of sub class magazine, book and movie
class owner : public magazine, public book, public movie{

    private:
    //private data members declaration
    string ownerId, ownerPassword, ownerName, ownerCompany;
    string ownerFileName = "ownerAccount.txt";

    public:

    //Registration fucntion
    void registration() {

        int id=0;
        string filename = "ownerId.txt";

        //Start of Id Auto Generator
        id = idGenerator(filename);
        //End of Id Auto Generator

        //Header
        cout << "\n\n===================Owner Register====================" << endl;

        cout << "Please enter your new username[max words of 10] : " << endl;
        cin.ignore();
        getline(cin, ownerName);

        //Removing all whitespace between characters using regex library
        ownerName = regex_replace(ownerName,regex("\\s"),"");

        cout << "Please enter your new password [max words of 15] : " << endl;
        getline(cin, ownerPassword);

        //Removing all whitespace between characters using regex library
        ownerPassword = regex_replace(ownerPassword,regex("\\s"),"");

        cout << "\n\nComfirmation [spaces between characters is deleted]" << endl;
        cout << "Username :" << ownerName << endl;
        cout << "Password :" << ownerPassword << "\n\n";

        system("pause");

        //Opening file for write in usage
        ofstream regfile;
        regfile.open(ownerFileName, ios::app);

            //if fail failed to open
            if(regfile.fail()) {

                cout << "Error writing to the file" << endl;
                cout << "Redirecting you back to Home" << endl;
                //Redirect users back to Home Menu
                homeNav();

            }else{

                //Writing data to file
                regfile << "\n" << "|" << setw(8) << id;
                regfile << "|" << setw(20) << ownerName;
                regfile << "|" << setw(20) << ownerPassword << "|";
                regfile.close();

                cout << "Account Registered !!!" << endl;
                cout << "Login is Skipped !!!" << endl;
                //Redirecting users to item choosing menu if account is registered
                itemChoose();

            }

    }

    //Login function
    void login() {

        //Variable declaration
        string line, IdPassCheck;
        int loggedin = 0;
        char cont;
        int menuReturn;

        //Clear terminal using stdlib.h library
        system("CLS");

        cout << "\n\n============================Owner Login============================" << endl;

        cout << "Please enter your username [max words of 10] [No Space Allowed]: " <<  endl;
        cin.ignore();
        getline(cin, ownerName);

        cout << "Please enter your password [max words of 15] [No Space Allowed]: " << endl;
        getline(cin, ownerPassword);

        //Gather up enetered username and password
        IdPassCheck = ownerName + ownerPassword;

        //Clear terminal using stdlib.h library
        system("CLS");

        //opening file
        ifstream logfile;
        logfile.open(ownerFileName, ios::in);

            //if file failed to open
            if(logfile.fail()) {

                cout << "Failed to open file..." << endl;
                cout << "Redirecting you back to Home" << endl;
                //Redirecting users back to home menu
                homeNav();

            //if file opens
            }else{

                //set initial counter
                int counter=0;

                    //To read every line of the txt file
                    while(getline(logfile, line)){

                        //ignoring the file 10 pieces of data
                        logfile.ignore(10, '\n');

                            //ignoring the first 3 lines of txt files
                            if(counter++ > 3) {

                                //STARTING OF DELIMITER
                                //Delimiter is to delete the "|" in the line and achieve a clean line of text without the "|"
                                string delimiter = "|";
                                size_t pos = 0;
                                string token, word;

                                    //While loop to find delimeter position, position of delimeter is stored in pos with a data type of size_t
                                    while ((pos = line.find(delimiter)) != string::npos) {

                                        //token will be equal to all character found on string line from left until it hits the value of pos
                                        //substr function made this possible
                                        //the first parameter tells where it should read from the line, and the second parameters tells it where it should stop reading
                                        // eg: line: "Hi There", token=line.substr(0, 1), token will be "H"
                                        token = line.substr(0, pos);

                                        //regex_replace function
                                        //to remove any whitespace by replacing it with a ("") null value
                                        token = regex_replace(token,regex("\\s"),"");

                                        word = word + token;

                                        //Using erase function to erase the characters that are already checked
                                        line.erase(0, pos + delimiter.length());

                                    }
                                //END OF DELIMITER

                                //Compare users input with the data in file
                                if(word.compare(IdPassCheck) == 0){

                                    cout << "You are Logged In!!!" << "\n\n" ;
                                    logfile.close();
                                    loggedin = 1;

                                }

                            }

                    }

                if(loggedin == 1) {

                    menuReturn = itemChoose();

                    while(menuReturn == 0) {

                        system("CLS");

                        cout << "Invalid Choice, read carefully stupid" << "\n\n";

                        menuReturn = itemChoose();

                    }

                }else{

                    cout << "Incorrect Username and Password...Try Again!" << endl;
                    cout << "Try Again?? [y/n] :" ;

                    cin >> cont;

                        if(tolower(cont) == 'y') {

                            //recursive function
                            login();

                        }

                }

            }

    }

    //Update Account function
    void updateAccount() {

        string line, savedLine;
        size_t pos;
        int position = 0;

        //.c_str() function to convert a string to a const char*
        //conversion have to be made because on line(1183 and 1187)rename and remove function only takes const char * as parameter and cannot take string as parameter
        const char* cnvrOFN = ownerFileName.c_str();

        cout << "\n\nPlease key in your ID to proceed update...: ";
        cin.ignore();
        getline(cin, ownerId);

        //opening file
        ifstream upd;
        upd.open(ownerFileName, ios::in);

            //get data line by line
            while(getline(upd, line)) {

                //get position where ownerId is found in line
                pos = line.find(ownerId);

                    if(pos != string::npos) {

                        //if position is lesser than 12, that means the value found in the line is under the ownerId column
                        if(pos < 12) {

                            savedLine = line;

                        }

                    }

            }

        upd.close();

            //savedLine is empty that means id is not found
            if(savedLine == "") {

                cout << "\nId not found, u might have to register an account huh? " << endl;
                cout << "Redirecting you to main menu..." << endl;
                system("pause");
                homeNav();

            }else{

                //initialize line to empty because code below will reuse the same variable
                line = "";

                cout << "\n################" << endl;
                cout << "Id found as : " << ownerId << endl;
                cout << "################" << endl;

                //open file
                ifstream updateAcc;
                updateAcc.open(ownerFileName, ios::in);

                ofstream temp;
                temp.open("temp.txt");

                    while(getline(updateAcc, line)) {

                        if(line.compare(savedLine) != 0) {

                            temp << line << "\n";

                        }

                    }

                cout << "\n\n================================================================" << endl;
                cout << "                      Update Account Form" << endl;
                cout << "================================================================" << endl;

                cout << "Please enter your new username[max words of 10] : " << endl;
                //cin.ignore();
                getline(cin, ownerName);

                //Remove any whitespace between characters
                ownerName = regex_replace(ownerName,regex("\\s"),"");

                cout << "\nPlease enter your new password [max words of 15] : " << endl;
                getline(cin, ownerPassword);

                //Remove any whitespace between characters
                ownerPassword = regex_replace(ownerPassword,regex("\\s"),"");

                //Promp comfirmation box
                cout << "\n\nComfirmation [spaces between characters is deleted]" << endl;
                cout << "Username :" << ownerName << endl;
                cout << "Password :" << ownerPassword << "\n\n";

                system("pause");

                //write into file
                temp << "|" << setw(8) << ownerId;
                temp << "|" << setw(20) << ownerName;
                temp << "|" << setw(20) << ownerPassword << "|";

                //file closing
                updateAcc.close();
                temp.close();

                //removing the original file
                if(remove(cnvrOFN) == 0) {

                        //Rename temp.txt file to original file to replace it
                        if(rename("temp.txt", cnvrOFN) == 0) {

                            cout << "\n\nAccount Updated !!!" << endl;
                            cout << "Redirecting you to main menu... \n\n" << endl;
                            system("pause");
                            //redirecting user back to home
                            homeNav();

                        }

                }else{

                    cout << "\nOriginal file removed Failed" << endl;
                    system("pause");
                    homeNav();

                }

            }

    }

    //initialize friend function of itemchoose
    friend int itemChoose();
};


//main function
int main() {

    //variable declaration
    int homeNavReturn;

    //run homenav
    homeNavReturn = homeNav();

        while(homeNavReturn == 0) {

            homeNavReturn = homeNav();

        }

    return 0;

}

//functions
int homeNav() {

    //variable and object declaration
    owner o;
    int choice;

        for(int i=0; i<29; i++) {

            cout << char(177);

        }

    cout << "\n" << char(178) <<  "            Menu           " << char(178) << endl;

    cout << char(178) << "===========================" << char(178) << endl;
    cout << char(178) << " Register                1 " << char(178) << endl;
    cout << char(178) << " Login                   2 " << char(178) << endl;
    cout << char(178) << " Update Account          3 " << char(178) << endl;
    cout << char(178) << " ------------------------- " << char(178) << endl;
    cout << char(178) << " Logout                  4 " << char(178) << endl;

        for(int i=0; i<29; i++) {

            cout << char(177);

        }

    cout << "\nEnter Your Choice :";
    cin >> choice;

    //Validation of choice making, to ensure user submit the correct choice to move on

        while(!(choice <= 4 && choice >= 1)) {

            return 0;

        }

            if(choice == 1) {

                o.registration();

            }else if(choice == 2) {

                o.login();

            }else if(choice == 3) {

                o.updateAccount();

            }else if(choice == 4) {

                exit(0);

            }
}

int itemChoose() {

    //variable declaration
    int type;
    int itemChoice = 0;

    //Pure virtual and virtual fucntion declaration
    item *item1 = new magazine;
    item *item2 = new book;
    item *item3 = new movie;

        for(int i=0; i<40; i++) {

            cout << char(177);

        }

    cout << "\n" << char(178) <<  "             Item Choosing            " << char(178) << endl;
    cout << char(178) << "======================================" << char(178) << endl;

    cout << char(178) << " Magazine                          1  " << char(178) << endl;
    cout << char(178) << " Book                              2  " << char(178) << endl;
    cout << char(178) << " Movie                             3  " << char(178) << endl;
    cout << char(178) << " Display All Sales                 4  " << char(178) << endl;
    cout << char(178) << " ------------------------------------ " << char(178) << endl;
    cout << char(178) << " Back                              5  " << char(178) << endl;
    cout << char(178) << " Exit                              0  " << char(178) << endl;

        for(int i=0; i<40; i++) {

            cout << char(177);

        }

    cout << "\nSelect your choice: ";
    cin >> itemChoice;

        if(itemChoice == 1) {

            cout << "\n\nRedirecting to Magazine..." << endl;

            type = 1;

            system("pause");

            //passing type to navigation function
            navigation(type);

        }else if(itemChoice == 2) {

            cout << "\n\nRedirecting to Book..." << endl;

            type = 2;

            system("pause");

            //passing type to navigation function
            navigation(type);

        }else if(itemChoice == 3) {

            cout << "\n\nRedirecting to Movie..." << endl;

            type = 3;

            system("pause");

            //passing type to navigation function
            navigation(type);

        }else if(itemChoice == 4){

            item1->dispSales();
            item2->dispSales();
            item3->dispSales();

        }else if(itemChoice == 5){

            homeNav();

        }else if(itemChoice == 0){

            exit(0);

        }else{

            return 0;

        }


}

int navigation(int type) {

    //clear terminal
    system("CLS");

    //object and variable declaration
    magazine m;
    book b;
    movie mo;
    int navChoice;

    //Pure virtual function and virtual function declaration
    item *item1 = new magazine;
    item *item2 = new book;
    item *item3 = new movie;

        for(int i=0; i<40; i++) {

            cout << char(177);

        }

            if(type == 1) {

                cout << "\n" << char(178) << "       " << "Magazine" <<  " Navigation Bar        " << char(178) << endl;

            }else if(type == 2) {

                cout << "\n" << char(178) << "         " << "Book"<<  " Navigation Bar          " << char(178) << endl;

            }else{

                cout << "\n" << char(178) << "         " << "Movie" <<  " Navigation Bar         " << char(178) << endl;

            }

    cout << char(178) << "======================================" << char(178) << endl;
    cout << char(178) << " Insert Items                      1  " << char(178) << endl;
    cout << char(178) << " Update Items                      2  " << char(178) << endl;
    cout << char(178) << " Delete Items                      3  " << char(178) << endl;
    cout << char(178) << " View Items                        4  " << char(178) << endl;
    cout << char(178) << " Display Sales                     5  " << char(178) << endl;
    cout << char(178) << " Display Sales By Range            6  " << char(178) << endl;
    cout << char(178) << " ------------------------------------ " << char(178) << endl;
    cout << char(178) << " Back                              7  " << char(178) << endl;

        for(int i=0; i<40; i++) {

            cout << char(177);

        }

    cout << "\nSelect Your Choice: ";
    cin >> navChoice;



        if(!(navChoice>=1 && navChoice<=6)) {

            cout << "\n\nYou entered an invalid choice...Try Again!!!" << endl;
            cout << "Redirecting you back to item choosing..." << "\n\n";
            itemChoose();

        }else{

            switch(navChoice) {

                case 1:

                    if(type == 1) {

                        item1->addItem();

                    }else if(type == 2) {

                        item2->addItem();

                    }else if(type == 3) {

                        item3->addItem();

                    }

                    break ;

                case 2:

                    if(type == 1) {

                        item1->updateItem();

                    }else if(type == 2) {

                        item2->updateItem();

                    }else if(type == 3) {

                        item3->updateItem();

                    }

                    break ;

                case 3:

                    if(type == 1) {

                        item1->deleteItem();

                    }else if(type == 2) {

                        item2->deleteItem();

                    }else if(type == 3) {

                        item3->deleteItem();

                    }

                    break ;

                case 4:

                    if(type == 1) {

                        item1->dispItem();

                    }else if(type == 2) {

                        item2->dispItem();

                    }else if(type == 3) {

                        item3->dispItem();

                    }

                    break ;

                case 5:

                    if(type == 1) {

                        item1->dispSales();

                    }else if(type == 2) {

                        item2->dispSales();

                    }else if(type == 3) {

                        item3->dispSales();

                    }

                    break ;

                case 6:

                    if(type == 1) {

                        item1->dispSalesRange();

                    }else if(type == 2) {

                        item2->dispSalesRange();

                    }else if(type == 3) {

                        item3->dispSalesRange();

                    }

                    break ;

                case 7:

                    itemChoose();

                    break;

                default: exit(0);
            }

        }



}

//id generator function
int idGenerator(string txtfile) {

    int id;

    //Start of Id Auto Generator
    //open file
    ifstream checkId;
    checkId.open(txtfile, ios::in);

        //if file failed to open
        if(checkId.fail()) {

            cout << "Auto Generate Id Function Failed..." << endl;

        }else{

            //get value and store it inside id
            checkId >> id;
            checkId.close();

        }

    //id increment
    id++;

    ofstream addId;
    addId.open(txtfile);

        if(addId.fail()) {

            cout << "Auto Generate Id Function Failed..." << endl;

        }else{

            //writing new incremented value to file
            addId << id;
            addId.close();

        }
    //End of Id Auto Generator

    return id;

}

//commonUpdate function
char commonUpdate(string fileName, int itemType) {

    //Variable declaration
    int noUnits, year, month;
    string itemName, itemCompany, line, savedLine, id, authorName, mainActorName;
    double price;
    char cont, value;
    size_t pos;

    //converting string element to cont char * for functions (remove and rename)
    const char * cnvrFileName = fileName.c_str();

    ifstream updFile;
    updFile.open(fileName, ios::in);

    cout << "\n\n========Update Form=======" << endl;
    cout << "\nItem Id you want to update        :";
    cin.ignore();
    getline(cin, id);

        //Get data line by line
        while(getline(updFile, line)) {

            //find if id exist
            pos = line.find(id);

                if(pos != string::npos) {

                    //check if the position of id found is lesser than 10
                    //this way to make sure id is under the itemid column
                    if(pos < 10) {

                        savedLine = line;

                    }else {

                        updFile.close();

                        cout << "\n" << id << " has found not be an Id " << endl;
                        cout << "Redirecting you back to Item Choosing..." << endl;
                        return 'n';


                    }

                }

        }

    updFile.close();
    value = 0;

        //savedLine is empty that means id is not found
        if(savedLine == "") {

            cout << "\n\nItem Not Found" << endl;
            cout << "Redirecting you back to Item Choosing..." << endl;
            return 'n';

        }else{

            cout << "\n\n#####################################" << endl;
            cout << id << " has been found, update allowed !!!" << endl;
            cout << "#####################################" << endl;
            cout << endl;

            line = "";

            //opening files
            ifstream inputFile;
            inputFile.open(fileName, ios::in);

            ofstream temp;
            temp.open("temp.txt");

                //get data line by line
                while(getline(inputFile, line)) {

                    //compare line with previously save line with the specific id
                    if(line.compare(savedLine) != 0) {

                        //if the above condition is not true then write it to temp.txt file
                        temp << line << "\n";

                    }

                }

                if(itemType == 1) {

                    cout << "Magazine Name [Max characters of 30]       :";

                    getline(cin, itemName);

                        while(itemName.length() > 30 || itemName.length() <= 0) {

                            cout << "\n\n########################## ALERT #############################" << endl;
                            cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "##############################################################" << endl;
                            cout << "Magazine Name [Max characters of 30]       :";
                            cin.ignore();
                            getline(cin, itemName);
                            cout << endl;

                        }

                    cout << "Magazine Price                             :";
                    cin >> price;

                        while(price < 0) {

                            cout << "\n\n################## ALERT #####################" << endl;
                            cout << "Price cannot be a negative number...Fix It !!!" << endl;
                            cout << "##############################################" << endl;
                            cout << "Magazine Price                             :";
                            cin >> price;
                            cout << "\n";

                        }

                    cout << "Number of units                            :";
                    cin >> noUnits;

                        while(noUnits < 0) {

                            cout << "\n\n################## ALERT #####################" << endl;
                            cout << "Units cannot be a negative number...Fix It !!!" << endl;
                            cout << "##############################################" << endl;
                            cout << "Number of units                            :";
                            cin >> noUnits;
                            cout << "\n";

                        }

                    cout << "Name of the company [Max characters of 30] :";
                    cin.ignore();
                    getline(cin, itemCompany);

                        while(itemCompany.length() > 30 || itemCompany.length() <= 0) {

                            cout << "\n\n########################## ALERT ################################" << endl;
                            cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "#################################################################" << endl;
                            cout << "Name of the company [Max characters of 30] :";
                            getline(cin, itemCompany);
                            cout << endl;

                        }

                    cout << "Year                                       :";
                    cin >> year;

                        while(year > 9999 || year < 0) {

                            cout << "\n\n############## ALERT #################" << endl;
                            cout << "Year value is invalid ...Fix It !!!" << endl;
                            cout << "#######################################" << endl;
                            cout << "Year                                       :";
                            cin >> year;

                        }

                    cout << "Month                                      :";
                    cin >> month;

                        while(month > 12 || month < 1) {

                            cout << "\n\n############## ALERT #################" << endl;
                            cout << "Month value is invalid ...Fix It !!!" << endl;
                            cout << "#######################################" << endl;
                            cout << "Month                                       :";
                            cin >> month;

                        }

                    temp << "|" << setw(7) << id;
                    temp << "|" << setw(30) << itemName;
                    temp << "|" << setw(14) << setprecision(2) << fixed << price;
                    temp << "|" << setw(11) << noUnits;
                    temp << "|" << setw(30) << itemCompany;
                    temp << "|" << setw(4) << year;
                    temp << "|" << setw(5) << month << "|";

                }else if(itemType == 2) {

                    cout << "Book Name [Max characters of 30]          :";
                    cin.ignore();
                    getline(cin, itemName);

                        while(itemName.length() > 30 || itemName.length() <= 0) {

                            cout << "\n\n########################## ALERT #############################" << endl;
                            cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "##############################################################" << endl;
                            cout << "Book Name [Max characters of 30]       :";
                            getline(cin, itemName);
                            cout << endl;

                        }

                    cout << "Book Price                                :";
                    cin >> price;

                        while(price < 0) {

                            cout << "\n\n################## ALERT #####################" << endl;
                            cout << "Price cannot be a negative number...Fix It !!!" << endl;
                            cout << "##############################################" << endl;
                            cout << "Book Price                             :";
                            cin >> price;
                            cout << "\n";

                        }

                    cout << "Number of units                            :";
                    cin >> noUnits;

                        while(noUnits < 0) {

                            cout << "\n\n################## ALERT #####################" << endl;
                            cout << "Units cannot be a negative number...Fix It !!!" << endl;
                            cout << "##############################################" << endl;
                            cout << "Number of units                            :";
                            cin >> noUnits;
                            cout << "\n";

                        }

                    cout << "Name of the company [Max characters of 30] :";
                    cin.ignore();
                    getline(cin, itemCompany);

                        while(itemCompany.length() > 30 || itemCompany.length() <= 0) {

                            cout << "\n\n########################## ALERT ################################" << endl;
                            cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "#################################################################" << endl;
                            cout << "Name of the company [Max characters of 30] :";
                            getline(cin, itemCompany);
                            cout << endl;

                        }

                    cout << "Author Name [Max characters of 30]         :";
                    getline(cin, authorName);

                        while(authorName.length() > 30 || authorName.length() <= 0) {

                            cout << "\n\n########################## ALERT ###############################" << endl;
                            cout << "Author name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "################################################################" << endl;
                            cout << "Author Name [Max characters of 30]        :";
                            getline(cin, authorName);
                            cout << endl;

                        }

                    temp << "|" << setw(7) << id;
                    temp << "|" << setw(30) << itemName;
                    temp << "|" << setw(14) << setprecision(2) << fixed << price;
                    temp << "|" << setw(11) << noUnits;
                    temp << "|" << setw(30) << itemCompany;
                    temp << "|" << setw(11) << authorName << "|";

                }else{

                    cout << "Movie Name [Max characters of 30]          :";
                    cin.ignore();
                    getline(cin, itemName);

                        while(itemName.length() > 30 || itemName.length() <= 0) {

                            cout << "\n\n########################## ALERT #############################" << endl;
                            cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "##############################################################" << endl;
                            cout << "Movie Name [Max characters of 30]          :";
                            getline(cin, itemName);
                            cout << endl;

                        }

                    cout << "Movie Price                                :";
                    cin >> price;

                        while(price < 0) {

                            cout << "\n\n################## ALERT #####################" << endl;
                            cout << "Price cannot be a negative number...Fix It !!!" << endl;
                            cout << "##############################################" << endl;
                            cout << "Movie Price                                :";
                            cin >> price;
                            cout << "\n";

                        }

                    cout << "Number of units                            :";
                    cin >> noUnits;

                        while(noUnits < 0) {

                            cout << "\n\n################## ALERT #####################" << endl;
                            cout << "Units cannot be a negative number...Fix It !!!" << endl;
                            cout << "##############################################" << endl;
                            cout << "Number of units                               :";
                            cin >> noUnits;
                            cout << "\n";

                        }

                    cout << "Name of the company [Max characters of 30] :";
                    cin.ignore();
                    getline(cin, itemCompany);

                        while(itemCompany.length() > 30 || itemCompany.length() <= 0) {

                            cout << "\n\n########################## ALERT ################################" << endl;
                            cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "#################################################################" << endl;
                            cout << "Name of the company [Max characters of 30] :";
                            getline(cin, itemCompany);
                            cout << endl;

                        }

                    cout << "Main Actor Name [Max characters of 30]     :";
                    getline(cin, mainActorName);

                        while(mainActorName.length() > 30 || mainActorName.length() <= 0) {

                            cout << "\n\n########################## ALERT ################################" << endl;
                            cout << "Company name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "#################################################################" << endl;
                            cout << "Main Actor Name [Max characters of 30]     :";
                            getline(cin, mainActorName);
                            cout << endl;

                        }

                    temp << "|" << setw(7) << id;
                    temp << "|" << setw(30) << itemName;
                    temp << "|" << setw(14) << setprecision(2) << fixed << price;
                    temp << "|" << setw(11) << noUnits;
                    temp << "|" << setw(30) << itemCompany;
                    temp << "|" << setw(30) << mainActorName << "|";

                }

            //closing of file
            temp.close();
            inputFile.close();

                //Remove the original file
                if(remove(cnvrFileName) == 0) {

                        //Renaming temp.txt to original file
                        if(rename("temp.txt", cnvrFileName) == 0) {

                            cout << "Item Updated !!" << endl;
                            value = 's';
                            return value;

                        }else{

                            cout << "Renamed Failed";
                            return 'n';

                        }

                }else{

                    cout << "Removed Failed";
                    return 'n';

                }

        }

}

//commonDelete function
char commonDelete(string fileName) {

    //variable declaration
    string line, dltItem, savedLine;
    char value;
    size_t pos;

    //converting string element to cont char * for functions (remove and rename)
    const char * cnvrFileName = fileName.c_str();

    //opening file
    ifstream dltMag;
    dltMag.open(fileName, ios::in);

    cout << "Id of the item u would like to delete? :";
    cin.ignore();
    getline(cin, dltItem);

        //get data line by line
        while(getline(dltMag, line)) {

            //find user input data in line and save the position to pos
            pos = line.find(dltItem);

                if(pos != string::npos) {

                    //if position is lesser than 12, that means id found is under the itemid column
                    if(pos < 12) {

                        savedLine = line;

                    }else {

                        dltMag.close();

                        cout << dltItem << " has found not be an Id, please enter the correct Id" << endl;
                        cout << "Would you like to try again? [y/n] :" << endl;
                        cin >> value;
                        return value;

                    }

                }

        }

    dltMag.close();
    value = 0;

        if(savedLine == "") {

            cout << "Item Not Found" << endl;
            cout << "Do you wish to continue deleting? [y/n] :" << endl;
            cin >> value;
            return value;

        }else{

            //Reinitialization for reusability
            line = "";

            //file opening
            ifstream inputFile;
            inputFile.open(fileName, ios::in);

            ofstream temp;
            temp.open("temp.txt");

                //Get data line by line
                while(getline(inputFile, line)) {

                    //Compare line with savedLine
                    if(line.compare(savedLine) != 0) {

                        temp << line << "\n";

                    }

                }

            //closing of file
            inputFile.close();
            temp.close();

            //remove original file
            if(remove(cnvrFileName) == 0) {

                //rename temp.txt to original file name
                if(rename("temp.txt", cnvrFileName) == 0) {

                    cout << "Renamed Temp file to Ori file" << endl;
                    value = 's';
                    return value;

                }else{

                    cout << "Renamed Failed";
                    itemChoose();

                }

            }else{

                cout << "Removed Failed";
                itemChoose();

            }

        }

}

//viewItems function
char viewItems(string fileName, int startLimit) {

    //Clear Terminal
    system("CLS");

    //Variable Declaration
    string line, headerLine;
    int counter = 0;
    int counter1 = 0;
    int counter3 = 0;
    int lineCount = 0;
    int i=0;
    char choice;
    const int printCount = 10;

    //array to store header
    string header[4];

    //file opening
    ifstream view;
    view.open(fileName, ios::in);

        //This while loop is to get the file header and store each line into a string array
        while(getline(view, headerLine)) {

            lineCount++;

            if(counter3++ <= 3) {
                //storing header inside array
                header[i] = headerLine;
                i++;

            }

        }

    //closing of file
    view.close();

    //Redeclaration for reusability
    line = "";

    const int startPoint = 4;

        //Output of header
        for(int z=0; z<4; z++) {

            cout << header[z] << endl;

        }


    //View Items
    ifstream print;
    print.open(fileName, ios::in);

        while(getline(print, line)) {

            if(counter++ >= startLimit) {

                if(counter1++ <= printCount) {

                    cout << line << endl;

                }

            }

        }

    //file closing
    print.close();

    cout << "\n[ Next Page [n]/ Previous Page [p]/ Exit [e] ] " << endl;
    cin >> choice;
    return choice;

}

void displaySalesByRange(string fileName, string itemType, string salesFilename) {

    string line, name, companyName, price, units, cnvrName, cnvrCompanyName;
    string detector = "|";
    double cnvrPrice;
    double totalPrice = 0;
    int startRange, endRange, cnvrUnits;
    int totalUnits = 0;
    int counter = 0;
    int pos = 0;
    int i = 0;
    int position = 0;
    int posArr[15];

    cout << "\n\nDisplaying Sales By Range :)" << endl;

    cout << "\nEnter your start range :";
    cin >> startRange;

    cout << "\nEnter your end range :";
    cin >> endRange;
    cout << endl;

    ifstream positionFinder;
    positionFinder.open(fileName, ios::in);

        while(getline(positionFinder, line)) {

            //skip thru the first 4 lines of txt file
            if(counter++ > 3) {

                //find detector in the line and store the position inside pos
                while((pos = line.find(detector, position)) != string::npos) {

                    //position increment
                    position = pos+1;

                    //store every detector position insdie array
                    posArr[i] = pos;

                    i++;

                }

            }

        }

    positionFinder.close();

    counter = 0;
    line = "";

        for(int z = 0; z<itemType.length() +4  ; z++) {

            cout << char(177);

        }

    cout << endl;

    cout << char(177) << " " << itemType << " "  << char(177) << endl;

        for(int z = 0; z < 91; z++) {

            cout << char(177);

        }

    cout << endl;
    cout << char(177) << " ";

        for(int z = 0; z < 87; z++) {

            cout << "=";

        }

    cout << " " << char(177) << endl;

    cout << char(177) << setw(30) << "Product Name" << "|";
    cout << setw(30) << "Company Name" << "|";
    cout << setw(11) << "No of units" << "|";
    cout << setw(14) << "Price" << " " << char(177);

    cout << "\n" << char(177) << " ";

        for(int z = 0; z < 87; z++) {

            cout << "=";

        }

    cout << " " << char(177);

    ifstream disp;
    disp.open(fileName, ios::in);

        while(getline(disp, line)) {

            if(counter++ > 3) {

                //cut the line into sections and store them in different variables
                name = line.substr((posArr[1])+2, ((posArr[2])-(posArr[1]))-2);
                price = line.substr((posArr[2])+2, ((posArr[3])-(posArr[2]))-1);
                units = line.substr((posArr[3])+2, ((posArr[4])-(posArr[3]))-1);
                companyName = line.substr((posArr[4])+2, ((posArr[5])-(posArr[4]))-2);

                //Remove all whitespaces
                cnvrName = regex_replace(name,regex("\\s"),"");
                cnvrCompanyName = regex_replace(companyName,regex("\\s"),"");

                //convert string into int or double
                cnvrPrice = stoi(price);
                cnvrUnits = stoi(units);

                    if(cnvrPrice >= startRange && cnvrPrice <= endRange) {

                        //cout << line << endl;
                        cout << "\n" << char(177) << setw(30) << cnvrName << "|";
                        cout << setw(30) << cnvrCompanyName << "|";
                        cout << setw(11) << cnvrUnits << "|";
                        cout << setw(14) << setprecision(2) << fixed << cnvrPrice << " " << char(177) << endl;
                        cout << char(177) << " ";

                            for(int z = 0; z < 87; z++) {

                                cout << "-";

                            }

                        cout << " " << char(177);

                        //Calculating totalUNits and totalPrice
                        totalUnits = totalUnits + cnvrUnits;
                        totalPrice = totalPrice + cnvrPrice;

                    }

            }

        }

    disp.close();

    cout << "\n" << char(177) << "                                                               " << setw(10) << totalUnits;
    cout << setw(15) << setprecision(2) << fixed << totalPrice << " " << char(177) << endl;
    cout << char(177) << " ";

        for(int z = 0; z < 87; z++) {

            cout << "-";

        }

    cout << " " << char(177) << endl;

    cout << char(177) << "                                       End of table                                      " << char(177) << endl;

        for(int z = 0; z < 91; z++) {

            cout << char(177);

        }

    cout << "\n\n";

}

//displaySales function
void displaySales(string fileName, string itemType, string salesFilename) {

    //Variable declaration
    string line;
    string price, units, id, companyName, name, cnvrName, cnvrCompanyName;
    string detector = "|";

    #define totalColumn 15

    int cnvrUnits;
    double cnvrPrice;
    double totalPrice = 0;

    int posArr[totalColumn];

    int pos = 0;
    int counter = 0;
    int counter1 = 0;
    int i = 0;
    int z = 0;
    int totalUnits = 0;
    int position = 0;

    //opening of file
    ifstream positionFinder;
    positionFinder.open(fileName, ios::in);

        //get data line by line
        while(getline(positionFinder, line)) {

            //skip thru the first 4 lines of txt file
            if(counter++ > 3) {

                //find detector in the line and store the position inside pos
                while((pos = line.find(detector, position)) != string::npos) {

                    //position increment
                    position = pos+1;

                    //store every detector position insdie array
                    posArr[i] = pos;

                    i++;

                }

            }

        }

    //closing of file
    positionFinder.close();

    //redeclaration of reusability
    counter = 0;
    line = "";

    //opening file
    ifstream disp;
    disp.open(fileName, ios::in);

    ofstream write;
    write.open(salesFilename);

    write << itemType << " Sales Analysis" << endl;

    write << "|------------------------------+------------------------------+-----------+--------------|" << "\n";


    write << "|" << setw(30) << "Product Name" << "|";
    write << setw(30) << "Company Name" << "|";
    write << setw(11) << "No of units" << "|";
    write << setw(14) << "Price" << "|" << "\n";

    write << "|------------------------------+------------------------------+-----------+--------------|";

        for(z = 0; z<itemType.length() +4  ; z++) {

            cout << char(177);

        }

    cout << endl;

    cout << char(177) << " " << itemType << " "  << char(177) << endl;

        for(int z = 0; z < 91; z++) {

            cout << char(177);

        }

    cout << endl;
    cout << char(177) << " ";

        for(int z = 0; z < 87; z++) {

            cout << "=";

        }

    cout << " " << char(177) << endl;

    cout << char(177) << setw(30) << "Product Name" << "|";
    cout << setw(30) << "Company Name" << "|";
    cout << setw(11) << "No of units" << "|";
    cout << setw(14) << "Price" << " " << char(177);

    cout << "\n" << char(177) << " ";

        for(int z = 0; z < 87; z++) {

            cout << "=";

        }

    cout << " " << char(177);

    //get data line by line
    while(getline(disp, line)) {

        //skip thru the first 4 lines
        if(counter++ > 3) {

            //cut the line into sections and store them in different variables
            name = line.substr((posArr[1])+2, ((posArr[2])-(posArr[1]))-2);
            price = line.substr((posArr[2])+2, ((posArr[3])-(posArr[2]))-1);
            units = line.substr((posArr[3])+2, ((posArr[4])-(posArr[3]))-1);
            companyName = line.substr((posArr[4])+2, ((posArr[5])-(posArr[4]))-2);

            //Remove all whitespaces
            cnvrName = regex_replace(name,regex("\\s"),"");
            cnvrCompanyName = regex_replace(companyName,regex("\\s"),"");

            //convert string into int or double
            cnvrPrice = stoi(price);
            cnvrUnits = stoi(units);

            //write
            write << "\n" << "|" <<setw(30) << cnvrName;
            write << "|" << setw(30) << cnvrCompanyName;
            write << "|" << setw(11) << cnvrUnits;
            write << "|" << setw(14) << setprecision(2) << fixed << cnvrPrice << "|";

            cout << "\n" << char(177) << setw(30) << cnvrName << "|";
            cout << setw(30) << cnvrCompanyName << "|";
            cout << setw(11) << cnvrUnits << "|";
            cout << setw(14) << setprecision(2) << fixed << cnvrPrice << " " << char(177) << endl;
            cout << char(177) << " ";

                for(int z = 0; z < 87; z++) {

                    cout << "-";

                }

            cout << " " << char(177);

            //Calculating totalUNits and totalPrice
            totalUnits = totalUnits + cnvrUnits;
            totalPrice = totalPrice + cnvrPrice;
        }

    }

    cout << "\n" << char(177) << "                                                               " << setw(10) << totalUnits;
    cout << setw(15) << setprecision(2) << fixed << totalPrice << " " << char(177) << endl;
    cout << char(177) << " ";

        for(int z = 0; z < 87; z++) {

            cout << "-";

        }

    cout << " " << char(177) << endl;

    cout << char(177) << "                                       End of table                                      " << char(177) << endl;

        for(int z = 0; z < 91; z++) {

            cout << char(177);

        }

    cout << "\n\n";

    write << "\n" << "                                                                " << setw(10) << totalUnits << "|" << setw(14) << totalPrice << "|";

        //removing original file
        if(remove(salesFilename.c_str())) {

                //renaming temp.txt to original file
                if(rename("temp.txt", salesFilename.c_str())) {

                    cout << salesFilename << " Updated" << endl;

                }

        }else{

            cout << "File removed failed" << endl;

        }

    //closing file
    disp.close();
    write.close();

    system("pause");

}

/*
REFERENCE
string::find :
    http://www.cplusplus.com/reference/string/string/find/
string::compare :
    http://www.cplusplus.com/reference/string/string/compare/
istream::ignore :
    http://www.cplusplus.com/reference/istream/istream/ignore/ or http://www.java2s.com/Code/Cpp/File/TheignoreFunction.htm
string array :
    https://www.geeksforgeeks.org/array-strings-c-3-different-ways-create/
delimiter :
    https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
update/delete :
    https://stackoverflow.com/questions/34507989/update-and-delete-data-from-file-in-c
converting string to const char* :
    https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
converting string to int (stoi()function) :
    https://careerkarma.com/blog/c-plus-plus-string-to-int/
PVF :
    https://www.learncpp.com/cpp-tutorial/126-pure-virtual-functions-abstract-base-classes-and-interface-classes/
Fastest way to read only last line of text file :
    https://stackoverflow.com/questions/11876290/c-fastest-way-to-read-only-last-line-of-text-file
string.h > strtok
    http://www.cplusplus.com/reference/cstring/strtok/
string.h > substr()
    https://www.geeksforgeeks.org/substring-in-cpp/
*/
