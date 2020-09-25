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

using namespace std;

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

        ofstream myfile;

        myfile.open("ownerAccount.txt");

        cout << "\n\n========Owner Register=========" << endl;
        
        //Id will be auto generated, so no need owner to enter by himself.
        //They just need to enter new password.
        //(Refer to guideline)
        //By Sin Yin ^.^

        /*cout << "Please enter your new user ID: " << endl;
        cin >> ownerId;*/

        myfile << "\n";
        myfile << ownerId;
        

        cout << "Please enter your new password: " << endl;
        cin.ignore();
        getline(cin, ownerPassword);

        myfile << "\n";
        myfile << ownerPassword;

        myfile.close();

    }

    void login() {

        cout << "\n\n===========Owner Login===========" << endl;

        cout << "Please enter your user ID: " << endl;
        cin >> ownerId;
        
        cout << "Please enter your password: " << endl;
        getline(cin, ownerPassword);

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
    string itemName, itemCompany, itemType;
    double price;

};

class magazine : public item {
    
    private:
    int year, month, totalSalesUnits;
    double totalSalesAmount;

    public:
    void addMagazine() {

        cout << "========Add Magazine Form=======" << endl;
        cout << "Magazine Name       :";
        getline(cin, itemName);

        cout << "Magazine Price      :";
        cin >> price;

        cout << "Number of units     :";
        cin >> noUnits;

        cout << "Name of the company :";
        getline(cin, itemCompany);

        cout << "Year                :";
        cin >> year;

        cout << "Month               :";
        cin >> month;

    }

        void updateMagazine() {

        cout << "========Update Magazine Form=======" << endl;
        cout << "Magazine Name       :";
        getline(cin, itemName);

        cout << "Magazine Price      :";
        cin >> price;

        cout << "Number of units     :";
        cin >> noUnits;

        cout << "Name of the company :";
        getline(cin, itemCompany);

        cout << "Year                :";
        cin >> year;

        cout << "Month               :";
        cin >> month;

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
        getline(cin, itemName);

        cout << "Book Price          :";
        cin >> price;

        cout << "Number of units     :";
        cin >> noUnits;

        cout << "Name of the company :";
        getline(cin, itemCompany);

        cout << "Author Name         :";
        cin >> authorName;

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
        cin >> authorName;

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
        cin >> mainActorName;

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
        cin >> mainActorName;

    }
        
    void displaySales() {

        cout << "=====Movie Sales Report=====" << endl;
        cout << "Total Sales Amount : " << totalSalesAmount << endl;
        cout << "Total Sales Units  : " << totalSalesUnits << endl;

    }

};

//functions prototypes
void header();

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