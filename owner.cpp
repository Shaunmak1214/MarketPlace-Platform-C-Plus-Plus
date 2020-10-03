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
#include<stdlib.h> //for system("cls") fucntion
#include<regex> //for regex.replace function

using namespace std;

//functions prototypes
void header();

int navigation();
int idGenerator(string txtfile);

char commonUpdate(string fileName, int itemType);
char commonDelete(string fileName);
char viewItems(string fileName, int startLimit, int printCount);

//Lists of classes
class item {

    protected:
    int itemId, noUnits, navchoice, counter;
    string itemName, itemCompany, itemType, dltItem, line, savedLine;
    string filename = "shopItemId.txt";
    double price;
    size_t pos;
    char cont;

    public:
    virtual void displaySales() = 0;

};

class magazine : public item{

    private:
    int year, month, totalSalesUnits;
    double totalSalesAmount;
    string magFilename = "magazine.txt";

    public:
    void choiceMag() {

        navchoice = navigation();

        if(navchoice == 1) {

            addMagazine();

        }else if(navchoice == 2) {

            updateMagazine();

        }else if(navchoice == 3) {

            deleteMagazine();

        }else if(navchoice == 4) {

            viewMagazine();

        }else if(navchoice == 5) {

            displaySales();

        }else if(navchoice == 6) {

            //itemChoose();

        }

    }

    void addMagazine() {

        int itemId;

        //id generator function
        itemId = idGenerator(filename);

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
            addmag.close();
            exit(1);

        }else{

            addmag << "\n" << "|" << setw(11) << itemId;
            addmag << "|" << setw(30) << itemName;
            addmag << "|" << setw(14) << price;
            addmag << "|" << setw(11) << noUnits;
            addmag << "|" << setw(30) << itemCompany;
            addmag << "|" << setw(4) << year;
            addmag << "|" << setw(5) << month << "|";
            addmag.close();

            cout << "Magazine item added successfully!" << endl;

            choiceMag();

        }

    }

    void updateMagazine() {

        char returnValue = commonUpdate(magFilename, 1);

        if(returnValue == 's') {

            cout << "Item Updated" << endl;

        }else{

            choiceMag();

        }

    }

    void deleteMagazine() {

        char returnValue = commonDelete(magFilename);

        while(returnValue != 's') {

            switch(returnValue) {

                case 'y' : returnValue = commonDelete(magFilename); break;

                case 'n' : choiceMag();

            }

        }

        cout << "Passed while loop" << endl;
        choiceMag();

    }

    void viewMagazine() {

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
    string bookFilename = "book.txt"; 

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

            viewBook();

        }else if(navchoice == 5) {

            displaySales();

        }

    }

    void addBook() {

        int id;

        //id generator function
        id = idGenerator(filename);

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
        getline(cin, authorName);

        ofstream addBook;
        addBook.open("book.txt", ios::app);

        if(addBook.fail()) {

            cout << "Error writing to the file, program ends...try again!" << endl;
            exit(1);

        }else{

            addBook << "\n" << "|" << setw(7) << id;
            addBook << "|" << setw(30) << itemName;
            addBook << "|" << setw(10) << price;
            addBook << "|" << setw(11) << noUnits;
            addBook << "|" << setw(30) << itemCompany;
            addBook << "|" << setw(11) << authorName << "|";
            addBook.close();

            cout << "Book item added successfully!" << endl;

            choiceBook();

        }

    }

    void updateBook() {

        char returnValue = commonUpdate(bookFilename, 2);

        if(returnValue == 's') {

            cout << "Item Updated!!" << endl;

        }else {

            cout << "Failed" << endl;

        }

    }

    void deleteBook() {

        char returnValue = commonDelete(bookFilename);

        while(returnValue != 's') {

            switch(returnValue) {

                case 'y' : returnValue = commonDelete(bookFilename); break;

                case 'n' : choiceBook();

            }

        }

        cout << "Passed while loop" << endl;
        choiceBook();

    }

    void viewBook() {

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
    string movieFileName = "movie.txt";

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

            viewMovie();

        }else if(navchoice == 5) {

            displaySales();

        }

    }

    void addMovie() {

        int id;

        //id generator function
        id = idGenerator(filename);

        cout << "========Add Movie Form=======" << endl;
        cout << "Movie Name           :";
        cin.ignore();
        getline(cin, itemName);

        cout << "Movie Price          :";
        cin >> price;

        cout << "Number of units      :";
        cin >> noUnits;

        cout << "Name of the company  :";
        cin.ignore();
        getline(cin, itemCompany);

        cout << "Main Actor Name      :";
        getline(cin, mainActorName);

        ofstream addMovie;
        addMovie.open("movie.txt", ios::app);

        if(addMovie.fail()) {

            cout << "Error writing to the file, program ends...try again!" << endl;
            exit(1);

        }else{

            addMovie << "\n" << "|" << setw(8) << id;
            addMovie << "|" << setw(30) << itemName;
            addMovie << "|" << setw(11) << price;
            addMovie << "|" << setw(11) << noUnits;
            addMovie << "|" << setw(30) << itemCompany;
            addMovie << "|" << setw(30) << mainActorName << "|";
            addMovie.close();

            cout << "Movie item added successfully!" << endl;

            choiceMovie();

        }

    }

    void updateMovie() {

        char returnValue = commonUpdate(movieFileName, 3);

        while(returnValue != 's') {

            switch(returnValue) {

                case 'y' : returnValue = commonUpdate(movieFileName, 3);

                case 'n' : choiceMovie();

            }

        }

    }

    void deleteMovie() {

        char returnValue = commonDelete(movieFileName);

        while(returnValue != 's') {

            switch(returnValue) {

                case 'y' : returnValue = commonDelete(movieFileName); break;

                case 'n' : choiceMovie();

            }

        }

        cout << "Passed while loop" << endl;
        choiceMovie();

    }

    void viewMovie() {

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
        string filename = "ownerId.txt";

        //Start of Id Auto Generator
        id = idGenerator(filename);
        //End of Id Auto Generator

        cout << "\n\n===================Owner Register====================" << endl;

        cout << "Please enter your new username[max words of 10] : " << endl;
        cin.ignore();
        getline(cin, ownerName);

        cout << "Please enter your new password [max words of 15] : " << endl;
        getline(cin, ownerPassword);

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

        cout << "Please enter your username [max words of 10] [No Space Allowed]: " << endl;
        cin.ignore();
        getline(cin, ownerName);

        cout << "Please enter your password [max words of 15] [No Space Allowed]: " << endl;
        getline(cin, ownerPassword);

        IdPassCheck = ownerName + ownerPassword;

        system("CLS");

        ifstream logfile;
        logfile.open("ownerAccount.txt", ios::in);


            if(logfile.fail()) {

                cout << "Failed to open file...program ends" << endl;
                exit(1);

            }else{

                int counter=0;

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


        int itemchoice = 0;

        cout << "============Item Choosing=============" << endl;
        cout << "Magazine                             1" << endl;
        cout << "Book                                 2" << endl;
        cout << "Movie                                3" << endl;   
        cout << "Back                                 4" << endl;
        cout << "Select your choice: ";
        cin >> itemchoice;  

            if(itemchoice == 1) {   

                cout << "\n\nRedirecting to Magazine..." << endl;
                choiceMag();   

            }else if(itemchoice == 2) { 

                cout << "\n\nRedirecting to Book..." << endl;
                choiceBook(); 

            }else if(itemchoice == 3) { 

                cout << "\n\nRedirecting to Movie..." << endl;
                choiceMovie();  

            }else{  

                cout << "\n\nYou entered an invalid choice, try again mate!" << endl;
                itemChoose();  

            }

    }

};


//main function
int main() {

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

    return 0;

}

//functions

int navigation() {

    int navchoice;

    cout << "\n\n============Navigation Bar============" << endl;
    cout << "Insert Items                         1" << endl;
    cout << "Update Items                         2" << endl;
    cout << "Delete Items                         3" << endl;
    cout << "View Items                           4" << endl;
    cout << "Display Sales                        5" << endl;
    cout << "Back                                 6" << endl;
  
    cout << "Select Your Choice: ";
    cin >> navchoice;

        if(!(navchoice>=1 && navchoice<=4)) {

            cout << "You entered an invalid choice...Try Again!!!" << endl;
            navigation();

        }

    return navchoice;

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

        cout << "========Update Magazine Form=======" << endl;

        cout << "Item Id you want to update        :";
        cin.ignore();
        getline(cin, id);

            while(getline(updFile, line)) {

                pos = line.find(id);

                    if(pos != string::npos) {

                        if(pos < 15) {

                            savedLine = line;

                        }else {

                            updFile.close();

                            cout << id << " has found not be an Id, please enter the correct Id" << endl;
                            cout << "Would you like to try again? [y/n] :" << endl;
                            cin >> value;

                            return value;

                        }

                    }

            }

        updFile.close();
        value = 0;

        if(savedLine == "") {

            cout << "Item Not Found" << endl;
            cout << "Do you with to continue updating? [y/n] :" << endl;
            cin >> cont;
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

            if(itemType == 1) {

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

                temp << "|" << setw(11) << id;
                temp << "|" << setw(30) << itemName;
                temp << "|" << setw(14) << price;
                temp << "|" << setw(11) << noUnits;
                temp << "|" << setw(30) << itemCompany;
                temp << "|" << setw(4) << year;
                temp << "|" << setw(5) << month << "|";

            }else if(itemType == 2) {

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
                getline(cin, authorName);

                temp << "|" << setw(7) << id;
                temp << "|" << setw(30) << itemName;
                temp << "|" << setw(11) << price;
                temp << "|" << setw(11) << noUnits;
                temp << "|" << setw(30) << itemCompany;
                temp << "|" << setw(11) << authorName << "|";

            }else{

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

                cout << "Main Actor Name     :";
                getline(cin, mainActorName);

                temp << "|" << setw(8) << id;
                temp << "|" << setw(30) << itemName;
                temp << "|" << setw(11) << price;
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

                        if(pos < 15) {

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
    int i=0;
    char choice;

    string header[4];

    ifstream view;
    view.open(fileName, ios::in);

    //This while loop is to get the file header and store each line into a string array
    while(getline(view, headerLine)) {

        if(counter3++ <= 3) {

            header[i] = headerLine;
            i++;

        }

    }
    view.close();

        //Output of header
        for(int z=0; z<4; z++) {

            cout << header[z] << endl;

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

/*
Reference
string array : https://www.geeksforgeeks.org/array-strings-c-3-different-ways-create/
delimiter : https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
update/delete : https://stackoverflow.com/questions/34507989/update-and-delete-data-from-file-in-c
converting string to const char* : https://stackoverflow.com/questions/347949/how-to-convert-a-stdstring-to-const-char-or-char
*/