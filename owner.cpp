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
#include<fstream>
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
char viewItems(string fileName, int startLimit, int printCount);
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
    virtual void addItem() {}
    virtual void updateItem() {}
    virtual void deleteItem() {}
    virtual void dispItem() = 0;
    virtual void dispSales() = 0;

};

class magazine : public item{

    private:

    int year, month, totalSalesUnits;
    double totalSalesAmount;
    string magFilename, recordFilename, itemType, salesFilename;

    public:

    //constructor
    magazine() {

        magFilename = "magazine.txt";
        recordFilename = "magazineRecord.txt";
        salesFilename = "magSales.txt";
        itemType = "Magazine";

    }

    void addItem() {

        int itemId;

        //id generator function
        itemId = idGenerator(fileName);

        cout << "\n\n==============Add Magazine Form=============" << endl;
        cout << "Magazine Name [Max characters of 30]       :";
        cin.ignore();
        getline(cin, itemName);

            while(itemName.length() > 30 || itemName.length() <= 0) {

                cout << "\n\n########################## ALERT #############################" << endl;
                cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                cout << "##############################################################" << endl;
                cout << "Magazine Name [Max characters of 30]       :";
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

        ofstream addmag;
        addmag.open("magazine.txt", ios::app);

        if(addmag.fail()) {

            cout << "Error writing to the file, program ends...try again!" << endl;
            addmag.close();
            exit(1);

        }else{

            addmag << "\n" << "|" << setw(7) << itemId;
            addmag << "|" << setw(30) << itemName;
            addmag << "|" << setw(14) << setprecision(2) << fixed << price;
            addmag << "|" << setw(11) << noUnits;
            addmag << "|" << setw(30) << itemCompany;
            addmag << "|" << setw(4) << year;
            addmag << "|" << setw(5) << month << "|";
            addmag.close();

            cout << "Magazine item added successfully!" << endl;

            itemChoose();

        }

    }

    void updateItem() {

        char returnValue = commonUpdate(magFilename, 2);

        if(returnValue == 's') {

            cout << "Item Updated!!" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }else {

            cout << "Failed to update" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }

    }

    void deleteItem() {

        char returnValue = commonDelete(magFilename);

        while(returnValue != 's') {

            switch(returnValue) {

                case 'y' : returnValue = commonDelete(magFilename); break;

                case 'n' : itemChoose();

            }

        }

        cout << "Passed while loop" << endl;
        itemChoose();

    }

    void dispItem() {

        char choice;
        int startLimit = 4;
        int printCount = 10;

        choice = viewItems(magFilename, startLimit, printCount);

        while(choice != 'e') {

            if(choice == 'n') {

                startLimit = startLimit+10;
                // printCount = printCount+5;
                choice = viewItems(magFilename, startLimit, printCount);

            }else if(choice == 'p') {

                startLimit = startLimit-10;
                //printCount = printCount-10;
                choice = viewItems(magFilename, startLimit, printCount);

            }

        }

        cout << "View Finished" << endl;
        cout << "Redirecting you back to item choosing" << endl;
        itemChoose();

    }

    void dispSales() {
        
        displaySales(recordFilename, itemType, salesFilename);

    }
};

class book : public item {

    private:

    string authorName, bookFilename, recordFilename, itemType, salesFilename;

    public:

    book() {

        bookFilename = "book.txt";
        recordFilename = "bookRecord.txt";
        itemType = "Book";
        salesFilename = "bookSales.txt";

    }

    void addItem() {

        int id;

        //id generator function
        id = idGenerator(fileName);

        cout << "========Add Book Form=======" << endl;
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

        ofstream addBook;
        addBook.open("book.txt", ios::app);

        if(addBook.fail()) {

            cout << "Error writing to the file, program ends...try again!" << endl;
            itemChoose();

        }else{

            addBook << "\n" << "|" << setw(7) << id;
            addBook << "|" << setw(30) << itemName;
            addBook << "|" << setw(14) << setprecision(2) << fixed << price;
            addBook << "|" << setw(11) << noUnits;
            addBook << "|" << setw(30) << itemCompany;
            addBook << "|" << setw(30) << authorName << "|";
            addBook.close();

            cout << "Book item added successfully!" << endl;
            itemChoose();

        }

    }

    void updateItem() {

        char returnValue = commonUpdate(bookFilename, 2);

        if(returnValue == 's') {

            cout << "Item Updated!!" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }else {

            cout << "Failed to update" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }

    }

    void deleteItem() {

        char returnValue = commonDelete(bookFilename);

        while(returnValue != 's') {

            switch(returnValue) {

                case 'y' : returnValue = commonDelete(bookFilename); break;

                case 'n' : itemChoose();

            }

        }

        cout << "Passed while loop" << endl;
        cout << "Redirecting you back to item choosing" << endl;
        itemChoose();

    }

    void dispItem() {

        char choice;
        int startLimit = 4;
        int printCount = 10;

        choice = viewItems(bookFilename, startLimit, printCount);

        while(choice != 'e') {

            if(choice == 'n') {

                startLimit = startLimit+10;
                // printCount = printCount+5;
                choice = viewItems(bookFilename, startLimit, printCount);

            }else if(choice == 'p') {

                startLimit = startLimit-10;
                //printCount = printCount-10;
                choice = viewItems(bookFilename, startLimit, printCount);

            }

        }

    cout << "View Finished" << endl;
    cout << "Redirecting you back to item choosing" << endl;
    itemChoose();

    }

    void dispSales() {
        
        displaySales(recordFilename, itemType, salesFilename);

    }

};

class movie : public item {

    private:
    string mainActorName, movieFileName, recordFileName, itemType, salesFilename;

    public:
    movie() {

        movieFileName = "movie.txt";
        recordFileName = "movieRecord.txt";
        salesFilename = "movieSales.txt";
        itemType = "Movie";

    }

    void addItem() {

        int id;

        //id generator function
        id = idGenerator(fileName);

        cout << "========Add Movie Form=======" << endl;
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

        ofstream addMovie;
        addMovie.open("movie.txt", ios::app);

        if(addMovie.fail()) {

            cout << "Error writing to the file, program ends...try again!" << endl;
            exit(1);

        }else{

            addMovie << "\n" << "|" << setw(7) << id;
            addMovie << "|" << setw(30) << itemName;
            addMovie << "|" << setw(14) << setprecision(2) << fixed << price;
            addMovie << "|" << setw(11) << noUnits;
            addMovie << "|" << setw(30) << itemCompany;
            addMovie << "|" << setw(30) << mainActorName << "|";
            addMovie.close();

            cout << "Movie item added successfully!" << endl;

            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }

    }

    void updateItem() {

        char returnValue = commonUpdate(movieFileName, 2);

        if(returnValue == 's') {

            cout << "Item Updated!!" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }else {

            cout << "Failed to update" << endl;
            cout << "Redirecting you back to item choosing" << endl;
            itemChoose();

        }
    }

    void deleteItem() {

        char returnValue = commonDelete(movieFileName);

        while(returnValue != 's') {

            switch(returnValue) {

                case 'y' : returnValue = commonDelete(movieFileName); break;

                case 'n' : itemChoose();

            }

        }

        cout << "Passed while loop" << endl;
        cout << "Redirecting you back to item choosing" << endl;
        itemChoose();

    }

    void dispItem() {

        char choice;
        int startLimit = 4;
        int printCount = 10;

        choice = viewItems(movieFileName, startLimit, printCount);

        while(choice != 'e') {

            if(choice == 'n') {

                startLimit = startLimit+10;
                // printCount = printCount+5;
                choice = viewItems(movieFileName, startLimit, printCount);

            }else if(choice == 'p') {

                startLimit = startLimit-10;
                //printCount = printCount-10;
                choice = viewItems(movieFileName, startLimit, printCount);

            }

        }

    cout << "View Finished" << endl;
    cout << "Redirecting you back to item choosing" << endl;
    itemChoose();

    }
        
    void dispSales() {
        
        displaySales(recordFileName, itemType, salesFilename);

    }

};

class owner : public magazine, public book, public movie{

    private:
    string ownerId, ownerPassword, ownerName, ownerCompany;
    string ownerFileName = "ownerAccount.txt";

    public:

    void registration() {

        int id=0;
        string filename = "ownerId.txt";

        //Start of Id Auto Generator
        id = idGenerator(filename);
        //End of Id Auto Generator

        cout << "\n\n===================Owner Register====================" << endl;

        cout << "Please enter your new username[max words of 10] : " << endl;
        cin.ignore();
        getline(cin, ownerName);

        ownerName = regex_replace(ownerName,regex("\\s"),"");

        cout << "Please enter your new password [max words of 15] : " << endl;
        getline(cin, ownerPassword);

        ownerPassword = regex_replace(ownerPassword,regex("\\s"),"");

        cout << "\n\nComfirmation [spaces between characters is deleted]" << endl;
        cout << "Username :" << ownerName << endl;
        cout << "Password :" << ownerPassword << "\n\n";

        system("pause");

        ofstream regfile;
        regfile.open(ownerFileName, ios::app);

            if(regfile.fail()) {

                cout << "Error writing to the file, program ends...try again!" << endl;
                exit(0);

            }else{

                regfile << "\n" << "|" << setw(8) << id;
                regfile << "|" << setw(20) << ownerName;
                regfile << "|" << setw(20) << ownerPassword << "|";
                regfile.close();

                cout << "Account Registered !!!" << endl;
                cout << "Login is Skipped !!!" << endl;
                itemChoose();
                    
            }

    }

    void login() {

        string line, IdPassCheck;
        int loggedin = 0;
        char cont;
        int menuReturn;

        system("CLS");

        cout << "\n\n============================Owner Login============================" << endl;

        cout << "Please enter your username [max words of 10] [No Space Allowed]: " <<  endl;
        cin.ignore();
        getline(cin, ownerName);

        cout << "Please enter your password [max words of 15] [No Space Allowed]: " << endl;
        getline(cin, ownerPassword);

        IdPassCheck = ownerName + ownerPassword;

        system("CLS");

        ifstream logfile;
        logfile.open(ownerFileName, ios::in);


            if(logfile.fail()) {

                cout << "Failed to open file...program ends" << endl;
                exit(1);

            }else{

                int counter=0;

                    //To read every line of the txt file
                    while(getline(logfile, line)){

                        logfile.ignore(10, '\n');

                            //ignoring the first 3 lines of txt files
                            if(counter++ > 3) {

                                //logfile.ignore(10, '\n');

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

                            login();

                        }

                }

            }

    }

    void updateAccount() {

        string line, savedLine;
        size_t pos;
        int position = 0;

        const char* cnvrOFN = ownerFileName.c_str();

        cout << "\n\nPlease key in your ID to proceed update...: ";
        cin.ignore();
        getline(cin, ownerId);

        ifstream upd;
        upd.open(ownerFileName, ios::in);

        while(getline(upd, line)) {

            pos = line.find(ownerId);

                if(pos != string::npos) {

                    if(pos < 12) {

                        savedLine = line;

                    }

                }

        }

        upd.close();

            if(savedLine == "") {

                cout << "\nId not found, u might have to register an account huh? " << endl;
                cout << "Redirecting you to main menu..." << endl;
                system("pause");
                homeNav();

            }else{

                line = "";

                cout << "\n################" << endl;
                cout << "Id found as : " << ownerId << endl;
                cout << "################" << endl;

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
                cin.ignore();
                getline(cin, ownerName);

                ownerName = regex_replace(ownerName,regex("\\s"),"");

                cout << "Please enter your new password [max words of 15] : " << endl;
                getline(cin, ownerPassword);

                ownerPassword = regex_replace(ownerPassword,regex("\\s"),"");

                cout << "\n\nComfirmation [spaces between characters is deleted]" << endl;
                cout << "Username :" << ownerName << endl;
                cout << "Password :" << ownerPassword << "\n\n";

                system("pause");

                temp << "|" << setw(8) << ownerId;
                temp << "|" << setw(20) << ownerName;
                temp << "|" << setw(20) << ownerPassword << "|";

                updateAcc.close();
                temp.close();

                if(remove(cnvrOFN) == 0) {

                    cout << "Original file removed" << endl;

                        if(rename("temp.txt", cnvrOFN) == 0) {

                            cout << "Account Updated !!!" << endl;
                            cout << "Redirecting you to main menu..." << endl;
                            system("pause");
                            homeNav();

                        }

                }else{

                    cout << "Original file removed Failed" << endl;
                    system("pause");
                    homeNav();

                }

            }

    }

    friend int itemChoose();
};


//main function
int main() {

    int homeNavReturn;

    homeNavReturn = homeNav();

        while(homeNavReturn == 0) {

            homeNavReturn = homeNav();

        }

    return 0;

}

//functions
int homeNav() {

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

    int type;
    int itemChoice = 0;

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

            navigation(type);

        }else if(itemChoice == 2) { 

            cout << "\n\nRedirecting to Book..." << endl;

            type = 2;

            system("pause");

            navigation(type);

        }else if(itemChoice == 3) { 

            cout << "\n\nRedirecting to Movie..." << endl;

            type = 3;

            system("pause");

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

    system("CLS");

    magazine m;
    book b;
    movie mo;
    int navChoice;

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
    cout << char(178) << " ------------------------------------ " << char(178) << endl;
    cout << char(178) << " Back                              6  " << char(178) << endl;
    
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
                
                    itemChoose(); 
                    
                    break ;

                default: exit(0);
            }

        }



}

int idGenerator(string txtfile) {

    int id;

    //Start of Id Auto Generator
    ifstream checkId;
    checkId.open(txtfile, ios::in);

        if(checkId.fail()) {

            cout << "Auto Generate Id Function Failed..." << endl;

        }else{

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

            addId << id;
            addId.close();

        }
    //End of Id Auto Generator

    return id;

}

char commonUpdate(string fileName, int itemType) {

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

        while(getline(updFile, line)) {

            pos = line.find(id);

                if(pos != string::npos) {

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

            ifstream inputFile;
            inputFile.open(fileName, ios::in);

            ofstream temp;
            temp.open("temp.txt");

                while(getline(inputFile, line)) {

                    if(line.compare(savedLine) != 0) {

                        temp << line << "\n";

                    }

                }

                if(itemType == 1) {

                    cout << "Magazine Name [Max characters of 30]       :";
                    cin.ignore();
                    getline(cin, itemName);

                        while(itemName.length() > 30 || itemName.length() <= 0) {

                            cout << "\n\n########################## ALERT #############################" << endl;
                            cout << "Item name entered is either too long or too short...Fix It !!!" << endl;
                            cout << "##############################################################" << endl;
                            cout << "Magazine Name [Max characters of 30]       :";
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

            temp.close();
            inputFile.close();

                if(remove(cnvrFileName) == 0) {

                    cout << "removed " << fileName << endl; 

                        if(rename("temp.txt", cnvrFileName) == 0) {

                            cout << "Renamed file" << endl;
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

char commonDelete(string fileName) {

    string line, dltItem, savedLine;
    char value;
    size_t pos;

    //converting string element to cont char * for functions (remove and rename)
    const char * cnvrFileName = fileName.c_str();

    ifstream dltMag;
    dltMag.open(fileName, ios::in);

    cout << "Name of the item u would like to delete? [Item name must be typed out exactly how it is] :";
    cin.ignore();
    getline(cin, dltItem);

        while(getline(dltMag, line)) {

            pos = line.find(dltItem);

                if(pos != string::npos) {

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

            line = "";

            ifstream inputFile;
            inputFile.open(fileName, ios::in);

            ofstream temp;
            temp.open("temp.txt");

                while(getline(inputFile, line)) {

                    if(line.compare(savedLine) != 0) {

                        temp << line << "\n";

                    }
                
                }

            inputFile.close();
            temp.close();

            if(remove(cnvrFileName) == 0) {

                cout << "Removed original file" << endl;

                if(rename("temp.txt", cnvrFileName) == 0) {

                    cout << "Renamed Temp file to Ori file" << endl;
                    value = 's';
                    return value;
                    exit(0);

                }else{

                    cout << "Renamed Failed";
                    exit(0);

                }

            }else{

                cout << "Removed Failed";
                exit(0);

            }

        }

}

char viewItems(string fileName, int startLimit, int printCount) {

    system("CLS"); 

    string line, headerLine;
    int counter = 0;
    int counter1 = 0;
    int counter3 = 0;
    int lineCount = 0;
    int i=0;
    char choice;

    string header[4];

    ifstream view;
    view.open(fileName, ios::in);

    //This while loop is to get the file header and store each line into a string array
    while(getline(view, headerLine)) {

        lineCount++;

        if(counter3++ <= 3) {

            header[i] = headerLine;
            i++;

        }

    }
    view.close();

    //cout << lineCount << endl;

        //Output of header
        for(int z=0; z<4; z++) {

            cout << header[z] << endl;

        }
    
    if(startLimit > lineCount) {

        cout << "Next Page Not Available" <<endl;
        exit(0);

    }

    if(startLimit < 14) {

        cout << "You reached the most previous page possible!" << endl;
        startLimit + 14;

    }

    //View Items
    view.open(fileName, ios::in);

    while(getline(view, line)) {

        if(counter++ >= startLimit) {

            if(counter1++ <= printCount) {

                cout << line << endl;

            }

        }

    }

    cout << "\n[ Next Page [n]/ Previous Page [p]/ Exit [e] ] " << endl;
    cin >> choice;
    return choice;
}

void displaySales(string fileName, string itemType, string salesFilename) {

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



    ifstream positionFinder;
    positionFinder.open(fileName, ios::in);

    // char str[] ="|   1001|                         Prawn|          1000|          2|                        phphph|2001|   12|";
    // char * pch;
    // pch = strtok (str," |");

    //     while (pch != NULL)
    //     {
    //         printf ("%s/",pch);
            
    //         pch = strtok (NULL, " |");
    //     }


    while(getline(positionFinder, line)) {

        if(counter++ > 3) {

            while((pos = line.find(detector, position)) != string::npos) {

                position = pos+1;
                posArr[i] = pos;
                i++; 

            } 

        }

    }
    
    positionFinder.close();


    counter = 0;
    line = "";

    ifstream disp;
    disp.open(fileName, ios::in);

    ofstream write;
    write.open(salesFilename);

    write << setw(30) << "Product Name" << "|";
    write << setw(30) << "Company Name" << "|";
    write << setw(11) << "No of units" << "|";
    write << setw(14) << "Price" << "|";

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

    while(getline(disp, line)) {

        if(counter++ > 3) {

            name = line.substr((posArr[1])+2, ((posArr[2])-(posArr[1]))-2);
            price = line.substr((posArr[2])+2, ((posArr[3])-(posArr[2]))-1);
            units = line.substr((posArr[3])+2, ((posArr[4])-(posArr[3]))-1);
            companyName = line.substr((posArr[4])+2, ((posArr[5])-(posArr[4]))-2);

            cnvrName = regex_replace(name,regex("\\s"),"");
            cnvrCompanyName = regex_replace(companyName,regex("\\s"),"");
            cnvrPrice = stoi(price);
            cnvrUnits = stoi(units);

            write << "\n" << setw(30) << cnvrName << "|";
            write << setw(30) << cnvrCompanyName << "|";
            write << setw(11) << cnvrUnits << "|";
            write << setw(14) << setprecision(2) << fixed << cnvrPrice << "|";

            cout << "\n" << char(177) << setw(30) << cnvrName << "|";
            cout << setw(30) << cnvrCompanyName << "|";
            cout << setw(11) << cnvrUnits << "|";
            cout << setw(14) << setprecision(2) << fixed << cnvrPrice << " " << char(177) << endl;
            cout << char(177) << " ";

                for(int z = 0; z < 87; z++) {

                    cout << "-";

                }

            cout << " " << char(177);

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

    write << "\n" << "                                                               " << setw(10) << totalUnits << "|" << setw(14) << totalPrice << "|";

        if(remove(salesFilename.c_str())) {

            cout << "Original file removed" << endl;

                if(rename("temp.txt", salesFilename.c_str())) {

                    cout << salesFilename << " Updated" << endl;

                }

        }else{

            cout << "File removed failed" << endl;

        }

    disp.close();
    write.close();

    //system("pause");
    //itemChoose();

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