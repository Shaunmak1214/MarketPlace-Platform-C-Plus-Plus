#include<iostream>
#include<iomanip>
#include<string>
#include<cstring> //For string::functions
#include<fstream>
#include <regex> //For regex.replace function
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int menuChoice();
void profileChoice();
void cartChoice();
void recordChoice();
int itemTypeChoice();
int idGenerator(string textfile);
void displayHeader(string textfile);
void displayItem(string textfile);
void addCartItem(string textfile, string textfile2);
void deleteCartItem(string textfile);
void clearItem(string textfile, string dltChoice);

class item
{
    protected:
        int itemId, noUnits, cartOption;
        string itemName, itemCompany, itemType;
        double price;
        string itemFile = "itemId.txt";

    public:
		item() { itemId=0; }
		void setCartOption(int choice)
		{
			cartOption = choice;			
		}
};

class magazine : public item
{
    private:
		int year, month;
    	string itemCartId;
    	string maFile = "magazine.txt";
		string maCartFile = "magazineCart.txt";
		string maRecordFile = "magazineRecord.txt";
    
    public:
		//default constructor
		magazine() { itemCartId=""; }

    	void viewItem()
    	{
    		cout << "\n====================================================================================================" << endl;
            cout << "                                 View Magazine Item (Shopping Cart)                                 " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(maCartFile);
		}
        void addItem()
        {
			cout << "\n====================================================================================================" << endl;
            cout << "                                 Add Magazine Item (Shopping Cart)                                  " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(maFile);
			addCartItem(maFile, maCartFile);
			displayItem(maCartFile);
		}
        void deleteItem()
		{
			cout << "\n====================================================================================================" << endl;
            cout << "                                Delete Magazine Item (Shopping Cart)                                " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(maCartFile);
			deleteCartItem(maCartFile);
			displayItem(maCartFile);
		}
        void modifyItem() 
		{
            string line;
            string itemCartId;
            string storage[10];
            string savedLine;
            string newUnits;
            string itemId, name, price, compName, year, month;
            int counter = 0;
            int pos = 0;
            int position = 0;
            string delimeter = "|";
            int posArr[13];
            int i = 0;
			int z = 0;

			cout << "\n====================================================================================================" << endl;
            cout << "                                Modify Magazine Item (Shopping Cart)                                " << endl;
            cout << "====================================================================================================" << endl;
			cout << endl;
			displayItem(maCartFile);
			cout << "\nEnter Item ID: ";
			cin.ignore();
			getline(cin, itemCartId);

			ifstream posFinder;
			posFinder.open("magazineCart.txt", ios::in);

			while(getline(posFinder, line))
			{
				if(counter++ > 3)
				{
					while((pos = line.find(delimeter, position)) != string::npos)
					{
						position = pos+1;
						posArr[i] = pos;
						i++; 
					} 
				}
			}
			posFinder.close();

			i = 0;
			counter = 0;
			line = "";
			pos = 0;

			ifstream mod;
			mod.open("magazineCart.txt", ios::in);

			if(mod.fail())
			{
				cout << "Fail to open file..." << endl;
				exit(0);
			}
			else
			{
				while(getline(mod, line))
				{
					if((pos = line.find(itemCartId)) != string::npos)
					{
						if(pos < 10)
						{
							savedLine = line;
						}
					}
				}
			}
			mod.close();

			if(savedLine == "")
			{
                cout << "Item not found. " << endl;
                exit(0);
            }
			else
			{
				cout << "\nYou are allowed to update the number of units only. " << endl;
                cout << "Item ID found. " << endl;

				displayHeader(maCartFile);
				
				cout << "\n" <<savedLine << endl;
				z = 0;

				while(z < 109)
				{
					cout << "-";
					z++;
				}
				
                cout << "\nEnter new no of unit: ";
                getline(cin, newUnits);

                ifstream mod1;
                mod1.open("magazineCart.txt", ios::in);   

                ofstream temp;
                temp.open("temp.txt");

                while(getline(mod1, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temp << line << "\n";
					}
				}
                mod1.close();
                //temp.close();

                //itemId, name, price, compName, year, month;
                itemId = savedLine.substr((posArr[0])+1, ((posArr[1]) - (posArr[0])) -1);
                name = savedLine.substr((posArr[1])+2, ((posArr[2]) - (posArr[1])) -2);
                price = savedLine.substr((posArr[2])+2, ((posArr[3]) - (posArr[2])) -2);
                compName = savedLine.substr((posArr[4])+2 ,((posArr[5]) - (posArr[4])) -2);
                year = savedLine.substr((posArr[5])+1, ((posArr[6]) - (posArr[5])) -1);
                month = savedLine.substr((posArr[6])+2, ((posArr[7]) - (posArr[6])) -2);

				itemId = regex_replace(itemId,regex("\\s"),"");
				name = regex_replace(name,regex("\\s"),"");
				price = regex_replace(price,regex("\\s"),"");
				compName = regex_replace(compName,regex("\\s"),"");
				year = regex_replace(year,regex("\\s"),"");
				month = regex_replace(month,regex("\\s"),"");

				//ofstream temp1;
				//temp1.open("temp.txt");

				if(temp.fail()) 
				{
					cout << "Fail to open file..." << endl;
					exit(0);
				}
				else
				{
					temp << "\n" << "|" <<setw(7) << itemId;
					temp << "|" <<setw(30) << name;
					temp << "|" <<setw(14) << price;
					temp << "|" <<setw(11) << newUnits;
					temp << "|" <<setw(30) << compName;
					temp << "|" <<setw(4) << year;
					temp << "|" <<setw(5) << month << "|";

					temp.close();

					cout << "\nSelected item has successfully modified. " << endl;

					remove("magazineCart.txt");
					rename("temp.txt" , "magazineCart.txt");
				}
            }
        }
		void clearCart()
		{
			string dltChoice;
			displayItem(maCartFile);
			cout << "\n====================================================================================================" << endl;
            cout << "                                    Clear Magazine Item (Shopping Cart)                             " << endl;
            cout << "====================================================================================================" << endl;
			cout << "Are you sure want to clear your shopping cart? [Yes or No]" << endl;
			cin >> dltChoice;
			clearItem(maCartFile, dltChoice);
		}
		void viewRecord()
		{
    		cout << "\n====================================================================================================" << endl;
            cout << "                                      View Shopping Record (Magazine)                               " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(maRecordFile);
		}
		void clearRecord()
		{
			string dltChoice;
			displayItem(maRecordFile);
			cout << "\n====================================================================================================" << endl;
            cout << "                                     Clear Shopping Record (Magazine)                               " << endl;
            cout << "====================================================================================================" << endl;
			cout << "Are you sure want to clear your past shopping record? [Yes or No]" << endl;
			cin >> dltChoice;
			clearItem(maRecordFile, dltChoice); 
		}
		void addRecord()
		{
			string line, savedLine;
			size_t pos;
			int counter=0;
			int i=0, x=0, no=0, n=1;
			string dltChoice;
			string headerLine;
			string header[4];
			
			cout << "\n=========================================" << endl;
            cout << "            Add Magazine Record          " << endl;
            cout << "=========================================" << endl;

			ifstream readMaFile;
			readMaFile.open("magazineCart.txt", ios::in);

			ofstream writeRec;
			writeRec.open("magazineRecord.txt");

				if(readMaFile) {	

					while(getline(readMaFile, line)) {	

						if(counter++ >3) {

							writeRec << line << endl;

						}

					}


				}else{

					cout << "Fail to open file...";

				}
			
			readMaFile.close();	
			writeRec.close();
		}
		/*void addRecord()
		{
			string line, savedLine;
			size_t pos;
			int counter=0;
			int i=0, x=0, no=0, n=1;
			string dltChoice;
			string headerLine;
			string header[4];
			cout << "\n=========================================" << endl;
            cout << "            Add Magazine Record          " << endl;
            cout << "=========================================" << endl;

			ifstream readMaFile;
			readMaFile.open(maCartFile, ios::in);

			if(readMaFile)
			{	
				while(getline(readMaFile, line))
				{	
					if(!readMaFile.eof())
					{
						n++;
					}
				}
				cout << n;
				string *saved = new string[n];
				line="";
				while(getline(readMaFile, line))
				{
					if(x >3)
					{
						saved[no] = line;
						no++;
					}
					x++;
				}
				for(x=0; x<n; x++)
				{
					cout << saved[x] << endl;
				}
				readMaFile.close();	
			}
			else
			{
				cout << "Fail to open file...";
			}
			
			readMaFile.close();	*/

			/*ofstream addMaFile;
			addMaFile.open(maCartFile, ios::app);

			if(addMaFile.is_open())
			{
				addMaFile << savedLine << endl;
			}
			else
			{
				cout << "Fail to open file...";
			}
			addMaFile.close();

			ifstream dltFile;
			dltFile.open(maCartFile, ios::in);

			if(dltFile.is_open())
			{
				while(getline(dltFile, headerLine))
				{
					if(counter++ < 4)
					{
						header[i] = headerLine;
						i++;
					}
				}
			}
			else
			{
				cout << "Fail to load file...";
			}
			dltFile.close();

			ofstream insertFile;
			insertFile.open(maCartFile);

			for(int j=0; j<1; j++)
            {
            	insertFile << header[j];
            }

			for(int j=1; j<4; j++)
            {
            	insertFile << "\n" << header[j];
            }
			insertFile.close();*/
		
};

class book : public item
{
    private:
	string itemCartId;
    string authorName;
	string boFile = "book.txt";
    string boCartFile = "bookCart.txt";
	string boRecordFile = "bookRecord.txt";

    public:
		//default constructor
		book() { itemCartId=""; }
    	void viewItem()
    	{
    		cout << "\n====================================================================================================" << endl;
            cout << "                                   View Book Item (Shopping Cart)                                   " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(boCartFile);
		}
        void addItem()
        {
        	cout << "\n====================================================================================================" << endl;
            cout << "                                   Add Book Item (Shopping Cart)                                   " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(boFile);
			addCartItem(boFile, boCartFile);
			displayItem(boCartFile);
		}
        void deleteItem()
        {
        	cout << "\n====================================================================================================" << endl;
            cout << "                                  Delete Book Item (Shopping Cart)                                " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(boCartFile);
			deleteCartItem(boCartFile);
			displayItem(boCartFile);
		}
        void modifyItem() 
		{
            string line;
            string itemCartId;
            string storage[10];
            string savedLine;
            string newUnits;
            string itemId, name, price, compName, authorName;
            int counter = 0;
            int pos = 0;
            int position = 0;
            string delimeter = "|";
            int posArr[13];
            int i = 0;
			int z = 0;

            cout << "\n====================================================================================================" << endl;
            cout << "                                  Modify Book Item (Shopping Cart)                                  " << endl;
            cout << "====================================================================================================" << endl;
			cout << endl;
			cout << endl;
			displayItem(boCartFile);
			cout << "\nEnter Item ID: ";
            cin.ignore();
            getline(cin, itemCartId);

            ifstream posFinder;
            posFinder.open("bookCart.txt", ios::in);

            while(getline(posFinder, line))
			{
				if(counter++ > 3)
				{
					while((pos = line.find(delimeter, position)) != string::npos)
					{
						position = pos+1;
						posArr[i] = pos;
						i++; 
					} 
				}
			}
			posFinder.close();

            i = 0;
            counter = 0;
            line = "";
            pos = 0;

            ifstream mod;
            mod.open("bookCart.txt", ios::in);

            if(mod.fail())
			{
                cout << "Fail to open file..." << endl;
				exit(0);
			}
			else
			{
                while(getline(mod, line))
				{
					if((pos = line.find(itemCartId)) != string::npos)
					{
						if(pos < 10)
						{
							savedLine = line;
						}
					}
				}
			}
			mod.close();

			if(savedLine == "")
			{
                cout << "Item not found. " << endl;
                exit(0);
            }
			else
			{
				cout << "\nYou are allowed to update the number of units only. " << endl;
                cout << "Item ID found. " << endl;

				displayHeader(boCartFile);
				
				cout << "\n" <<savedLine << endl;
				z = 0;

				while(z < 129)
				{
					cout << "-";
					z++;
				}
				
                cout << "\nEnter new no of unit: ";
                getline(cin, newUnits);

                ifstream mod1;
                mod1.open("bookCart.txt", ios::in);   

                ofstream temp;
                temp.open("temp.txt");

                while(getline(mod1, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temp << line << "\n";
					}
				}

                mod1.close();
                //temp.close();

                //itemId, name, price, compName, authorName;
                itemId = savedLine.substr((posArr[0])+1, ((posArr[1]) - (posArr[0])) -1);
                name = savedLine.substr((posArr[1])+2, ((posArr[2]) - (posArr[1])) -2);
                price = savedLine.substr((posArr[2])+2, ((posArr[3]) - (posArr[2])) -2);
                compName = savedLine.substr((posArr[4])+2 ,((posArr[5]) - (posArr[4])) -2);
                authorName = savedLine.substr((posArr[5])+1, ((posArr[6]) - (posArr[5])) -1);

				itemId = regex_replace(itemId,regex("\\s"),"");
				name = regex_replace(name,regex("\\s"),"");
				price = regex_replace(price,regex("\\s"),"");
				compName = regex_replace(compName,regex("\\s"),"");
				authorName = regex_replace(authorName,regex("\\s"),"");

				//ofstream temp1;
				//temp1.open("temp.txt");

				if(temp.fail()) 
				{
					cout << "Fail to open file..." << endl;
					exit(0);
				}
				else
				{
					temp << "|" <<setw(7) << itemId;
					temp << "|" <<setw(30) << name;
					temp << "|" <<setw(14) << price;
					temp << "|" <<setw(11) << newUnits;
					temp << "|" <<setw(30) << compName;
					temp << "|" <<setw(30) << authorName << "|" << "\n";

					temp.close();

					cout << "\nSelected item has successfully modified. " << endl;

					remove("bookCart.txt");
					rename("temp.txt" , "bookCart.txt");
				}
			}
		}
		void clearCart()
		{
			string dltChoice;
			displayItem(boCartFile);
			cout << "\n====================================================================================================" << endl;
            cout << "                                  Clear Book Item (Shopping Cart)                                   " << endl;
            cout << "====================================================================================================" << endl;
			cout << "Are you sure want to clear your shopping cart? [Yes or No]" << endl;
			cin >> dltChoice;
			clearItem(boCartFile, dltChoice);
		}
		void viewRecord()
		{
    		cout << "\n====================================================================================================" << endl;
            cout << "                                    View Shopping Record (Book)                                     " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(boRecordFile);
		}
		void clearRecord()
		{
			string dltChoice;
			displayItem(boRecordFile);
			cout << "\n====================================================================================================" << endl;
            cout << "                                    Clear Shopping Record (Book)                                    " << endl;
            cout << "====================================================================================================" << endl;
			cout << "Are you sure want to clear your past shopping record? [Yes or No]" << endl;
			cin >> dltChoice;
			clearItem(boRecordFile, dltChoice);
		}
};

class movie : public item {

    private:
    string itemCartId;
	string mainActorName;
	string moFile = "movie.txt";
    string moCartFile = "movieCart.txt";
	string moRecordFile = "movieRecord.txt";

    public:
		//default constructor
		movie() { itemCartId=""; }
    	void viewItem()
    	{
    		cout << "\n====================================================================================================" << endl;
            cout << "                                 View Movie Item (Shopping Cart)                                    " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(moCartFile);
		}
        void addItem()
        {
			cout << "\n====================================================================================================" << endl;
            cout << "                                  Add Movie Item (Shopping Cart)                                    " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(moFile);
			addCartItem(moFile, moCartFile);
			displayItem(moCartFile);
		}
        void deleteItem()
        {
			cout << "\n====================================================================================================" << endl;
            cout << "                                 Delete Movie Item (Shopping Cart)                                  " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(moCartFile);
			deleteCartItem(moCartFile);
			displayItem(moCartFile);
		}
        void modifyItem() 
		{
            string line;
            string itemCartId;
            string storage[10];
            string savedLine;
            string newUnits;
            string itemId, name, price, compName, mainActorName;
            int counter = 0;
            int pos = 0;
            int position = 0;
            string delimeter = "|";
            int posArr[13];
            int i = 0;
			int z = 0;

            cout << "\n====================================================================================================" << endl;
            cout << "                                  Modify Movie Item (Shopping Cart)                                " << endl;
            cout << "====================================================================================================" << endl;
			cout << endl;
			cout << endl;
			displayItem(moCartFile);
			cout << "\nEnter Item ID: ";
			cin.ignore();
			getline(cin, itemCartId);

            ifstream posFinder;
            posFinder.open("movieCart.txt", ios::in);

            while(getline(posFinder, line))
			{
				if(counter++ > 3)
				{
					while((pos = line.find(delimeter, position)) != string::npos)
					{
						position = pos+1;
						posArr[i] = pos;
						i++; 
					} 
				}
			}
			posFinder.close();

            i = 0;
            counter = 0;
            line = "";
            pos = 0;

            ifstream mod;
            mod.open("movieCart.txt", ios::in);

            if(mod.fail())
			{
				cout << "Fail to open file..." << endl;
				exit(0);
			}
			else
			{
				while(getline(mod, line))
				{
					if((pos = line.find(itemCartId)) != string::npos)
					{
						if(pos < 10)
						{
							savedLine = line;
						}
					}
				}
			}
			mod.close();

			if(savedLine == "")
			{
                cout << "Item not found. " << endl;
                exit(0);
            }
			else
			{
				cout << "\nYou are allowed to update the number of units only. " << endl;
                cout << "Item ID found. " << endl;

				displayHeader(moCartFile);
				
				cout << "\n" <<savedLine << endl;
				z = 0;

				while(z < 129)
				{
					cout << "-";
					z++;
				}

                cout << "\nEnter new no of unit: ";
                getline(cin, newUnits);

                ifstream mod1;
                mod1.open("movieCart.txt", ios::in);   

                ofstream temp;
                temp.open("temp.txt");

                while(getline(mod1, line))
				{
					if(line.compare(savedLine) != 0)
					{
						temp << line << "\n";
                    }
                }
                mod1.close();
                //temp.close();

                //itemId, name, price, compName, authorName;
                itemId = savedLine.substr((posArr[0])+1, ((posArr[1]) - (posArr[0])) -1);
                name = savedLine.substr((posArr[1])+2, ((posArr[2]) - (posArr[1])) -2);
                price = savedLine.substr((posArr[2])+2, ((posArr[3]) - (posArr[2])) -2);
                compName = savedLine.substr((posArr[4])+2 ,((posArr[5]) - (posArr[4])) -2);
                mainActorName = savedLine.substr((posArr[5])+1, ((posArr[6]) - (posArr[5])) -1);

				itemId = regex_replace(itemId,regex("\\s"),"");
				name = regex_replace(name,regex("\\s"),"");
				price = regex_replace(price,regex("\\s"),"");
				compName = regex_replace(compName,regex("\\s"),"");
				mainActorName = regex_replace(mainActorName,regex("\\s"),"");

				//ofstream temp1;
				//temp1.open("temp.txt");

				if(temp.fail()) 
				{
					cout << "Fail to open file..." << endl;
					exit(0);
				}
				else
				{
					temp << "|" <<setw(7) << itemId;
					temp << "|" <<setw(30) << name;
					temp << "|" <<setw(14) << price;
					temp << "|" <<setw(11) << newUnits;
					temp << "|" <<setw(30) << compName;
					temp << "|" <<setw(30) << mainActorName << "|" << "\n";

					temp.close();

					cout << "\nSelected item has successfully modified. " << endl;

					remove("movieCart.txt");
					rename("temp.txt" , "movieCart.txt");
				}
			}
		}
		void clearCart()
		{
			string dltChoice;
			displayItem(moCartFile);
			cout << "\n====================================================================================================" << endl;
            cout << "                                    Clear Movie Item (Shopping Cart)                                " << endl;
            cout << "====================================================================================================" << endl;
			cout << "Are you sure want to clear your shopping cart? [Yes or No]" << endl;
			cin >> dltChoice;
			clearItem(moCartFile, dltChoice);
		}
		void viewRecord()
		{
    		cout << "\n====================================================================================================" << endl;
            cout << "                                      View Shopping Record (Movie)                                       " << endl;
            cout << "====================================================================================================" << endl;
			displayItem(moRecordFile);
		}
		void clearRecord()
		{
			string dltChoice;
			displayItem(moRecordFile);
			cout << "\n====================================================================================================" << endl;
            cout << "                                     Delete Shopping Record (Movie)                                      " << endl;
            cout << "====================================================================================================" << endl;
			cout << "Are you sure want to clear your past shopping record? [Yes or No]" << endl;
			cin >> dltChoice;
			clearItem(moRecordFile, dltChoice);
		}
};

class payment
{   
	private:
        int cardNum;
        
    public:
		//default constructor
		payment() { cardNum=0; }
        void checkPayment()
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

					magazine ma;
					book bo;
					movie mo;

					ma.clearCart();
					bo.clearCart();
					mo.clearCart();
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
		}       
};

int main()
{	
	int menuSelection;
	
	menuChoice();

	
	// else if(menuSelection==3)
	// {
	// 	recordChoice();
	// }

	return 0;
}

int menuChoice()
{
	int menuOption;

	cout << "\n+=========================================+" << endl;
    cout << "|                  MENU                   |" << endl;
    cout << "|=========================================|" << endl;
    cout << "|             1. Profile                  |" << endl;
    cout << "|             2. Shopping Cart            |" << endl;
    cout << "|             3. Shopping Record          |" << endl;
	cout << "|             4. Log out                  |" << endl;
	cout << "|=========================================|" << endl;
	cout << "|             [Press 0] Exit              |" << endl;
	cout << "|.........................................|" << endl << endl;
	cout << "Choose an option [Enter 1, 2, 3 or 4]: ";
	cin >> menuOption;

	while(!(menuOption>=0 && menuOption<=4))
	{
		cout << "\nInvalid option for shopping cart!" << endl;
		cout << "Please enter an valid option: ";
		cin >> menuOption;
	}

	if(menuOption==1)
	{
		profileChoice();
	}
	else if(menuOption==2)
	{
		cartChoice(); 
	}
	else if(menuOption==3)
	{
		recordChoice();
	}
}

void profileChoice()
{
	int profileOption;

	cout << "\n+=========================================+" << endl;
    cout << "|            ACTION FOR PROFILE           |" << endl;
    cout << "|=========================================|" << endl;
    cout << "|            1. Display Profile           |" << endl;
    cout << "|            2. Update Profile            |" << endl;
    cout << "|            3. Deregister                |" << endl;
	cout << "|=========================================|" << endl;
	cout << "|             [Press 0] Exit              |" << endl;
	cout << "|.........................................|" << endl << endl;
	cout << "Choose an option [Enter 1, 2, or 3]: ";

	while(!(profileOption>=0 && profileOption<=3))
	{
		cout << "\nInvalid option for shopping cart!" << endl;
		cout << "Please enter an valid option: ";
		cin >> profileOption;
	}
}

void cartChoice()
{
	magazine ma;
	book bo;
	movie mo;
	
	item *item1 = &ma;
	item *item2 = &bo;
	item *item3 = &mo;
	
	int cartOption;
	int categoryOption;
	
	cout << "\n+=========================================+" << endl;
    cout << "|         ACTION FOR SHOPPING CART        |" << endl;
    cout << "|=========================================|" << endl;
    cout << "|           1. View Cart Item             |" << endl;
    cout << "|           2. Add Cart Item              |" << endl;
    cout << "|           3. Delete Cart Item           |" << endl;
    cout << "|           4. Modify Cart Item           |" << endl;
	cout << "|           5. Clear Cart Item            |" << endl;
	cout << "|=========================================|" << endl;
	cout << "|             [Press 0] Exit              |" << endl;
	cout << "|.........................................|" << endl << endl;
	cout << "Choose an option [Enter 1, 2, 3, 4 or 5 ]: ";
	cin >> cartOption;
	
	while(!(cartOption>=0 && cartOption<=5))
	{
		cout << "\nInvalid option for shopping cart!" << endl;
		cout << "Please enter an valid option: ";
		cin >> cartOption;
	}
	
	categoryOption = itemTypeChoice();
	
	switch(categoryOption)
	{
		case 1: item1->setCartOption(cartOption); 
				if(cartOption==1)
				{ ma.viewItem(); }
				else if(cartOption==2)
				{ ma.addItem(); }
				else if(cartOption==3)
				{ ma.deleteItem(); }
				else if(cartOption==4)
				{ ma.modifyItem(); }
				else if(cartOption==5)
				{ ma.clearCart(); }
				break;
		case 2: item2->setCartOption(cartOption); 
				if(cartOption==1)
				{ bo.viewItem(); }
				else if(cartOption==2)
				{ bo.addItem(); }
				else if(cartOption==3)
				{ bo.deleteItem(); }
				else if(cartOption==4)
				{ bo.modifyItem(); }
				else if(cartOption==5)
				{ bo.clearCart(); }
				break;
		case 3: item3->setCartOption(cartOption); 
				if(cartOption==1)
				{ mo.viewItem(); }
				else if(cartOption==2)
				{ mo.addItem(); }
				else if(cartOption==3)
				{ mo.deleteItem(); }
				else if(cartOption==4)
				{ mo.modifyItem(); }
				else if(cartOption==5)
				{ mo.clearCart(); }
				break;
		case 0: exit(0);
		default: cout << "Invalid option!"; 
	}
}

void recordChoice()
{
	magazine ma;
	book bo;
	movie mo;
	
	item *item1 = &ma;
	item *item2 = &bo;
	item *item3 = &mo;

	int recordOption;
	int categoryOption;

	cout << "\n+=========================================+" << endl;
    cout << "|        ACTION FOR SHOPPING RECORD       |" << endl;
    cout << "|=========================================|" << endl;
	cout << "|        1. Display Shopping Record       |" << endl;
	cout << "|        2. Clear Shopping Record         |" << endl;
	cout << "|=========================================|" << endl;
	cout << "|             [Press 0] Exit              |" << endl;
	cout << "|.........................................|" << endl << endl;
	cout << "Choose an option [Enter 1 or 2]: ";

	while(!(recordOption>=0 && recordOption<=2))
	{
		cout << "\nInvalid option for shopping cart!" << endl;
		cout << "Please enter an valid option: ";
		cin >> recordOption;
	}
	
	categoryOption = itemTypeChoice();

	switch(categoryOption)
	{
		case 1: if(recordOption==1)
				{ ma.viewRecord(); }
				else if(recordOption==2)
				{ ma.clearRecord(); }
				break;
		case 2: if(recordOption==1)
				{ bo.viewRecord(); }
				else if(recordOption==2)
				{ bo.clearRecord(); }
				break;
		case 3: if(recordOption==1)
				{ mo.viewRecord(); }
				else if(recordOption==2)
				{ mo.clearRecord(); }
				break;
		case 0: exit(0);
		default: cout << "Invalid option!";
	}
}

int itemTypeChoice()
{
	int itemType;

	cout << "\n+=========================================+" << endl;
	cout << "|       ITEM TYPE FOR SHOPPING CART       |" << endl;
	cout << "|=========================================|" << endl;
	cout << "|           Category 1: Magazine          |" << endl;
	cout << "|           Category 2: Book              |" << endl;
	cout << "|           Category 3: Movie             |" << endl;
	cout << "|=========================================|" << endl;
	cout << "|             [Press 0] Exit              |" << endl;
	cout << "|.........................................|" << endl << endl;
	cout << "Choose the category you want [Enter 1, 2 or 3]: ";
	cin >> itemType;
	
	while(itemType!=0 && itemType!=1 && itemType!=2 && itemType!=3)
	{
		cout << "\nInvalid option for item type!" << endl;
		cout << "Please enter an valid option: ";
		cin >> itemType;
	}

	return itemType;
}

int idGenerator(string txtfile)
{
	int id;
	
	ifstream checkId;
	checkId.open(txtfile, ios::in);
	
	if(checkId.is_open())
	{
		checkId >> id;
		checkId.close();
	}
	else
	{
		cout << "Id Auto Generator Failed..." << endl;
	}
	id++;
	
	ofstream addId;
	addId.open(txtfile);
	
	if(addId.is_open())
	{
		addId << id;
	}
	else
	{
		cout << "Id Auto Generator Failed..." << endl;
	}
	return id;
}

void displayHeader(string textfile)
{
	string headerLine;
	string header[4];
	int counter=0;
	int i=0;

	ifstream dltFile;
	dltFile.open(textfile, ios::in);
	
	if(dltFile.is_open())
	{
		while(getline(dltFile, headerLine))
		{
			if(counter++ < 4)
			{
				header[i] = headerLine;
				i++;
			}
		}
	}
	else
	{
		cout << "Fail to load file...";
	}
	dltFile.close();

	for(int j=0; j<4; j++)
    {
    	cout << "\n" << header[j];
    }
}

void displayItem(string textfile)
{
	string line;

	ifstream viewFile(textfile);
	if(viewFile.fail())
	{	
		cout << "Fail to open file..." << endl;
	}
	else
	{
		while(getline(viewFile, line))
		{
			cout << line << endl;
		}
	}
	viewFile.close();
}

void addCartItem(string textfile, string textfile2)
{
	string line, savedLine;
	size_t pos;
	string itemCartId;
	char againOption;
	int added;

	do{
		cout << "\nEnter Item ID: ";
		cin.ignore();
		getline(cin, itemCartId);
		againOption = 0;

		ifstream readFile;
		readFile.open(textfile, ios::in);

		if(readFile)
		{
			while(getline(readFile, line))
			{
				pos = line.find(itemCartId);
				if(pos != string::npos)
				{
					if(pos<10)
					{
						savedLine = line;
					}
					else
					{
						readFile.close();

						added = 0;
						cout << endl << itemCartId << " does not exist. Please re-enter an valid ID. " << endl;
						cout << "Try again? [Enter Y or N]: ";
						cin >> againOption;
						cout << endl;
					}
				}
			}
		}
		else
		{
			cout << "Fail to open file..." << endl;
		}
		readFile.close();	

		if(!(added == 0))
		{
			ofstream addFile;
			addFile.open(textfile2, ios::app);

			addFile << "\n" << savedLine;
			cout << "\nSelected item has added into shopping cart." << endl;

			addFile.close();
		}

		if(!(againOption=='Y'))
		{
			cout << "\nContinue to add more item? [Enter Y or N]: ";
			cin >> againOption;
		}

	}while(againOption=='Y');

	cout << "\nRedirecting to Menu..." << endl;
	menuChoice();
}

//To delete shopping cart item
void deleteCartItem(string textfile)
{
	string line, savedLine;
	size_t pos;
	string itemCartId;
	const char * cnvrFileName = textfile.c_str();

	cout << "Enter Item ID: ";
	cin.ignore();
	getline(cin, itemCartId);

	ifstream readCartFile;
	readCartFile.open(textfile, ios::in);

	if(readCartFile.is_open())
	{
		while(getline(readCartFile, line))
		{
			pos = line.find(itemCartId);
			if(pos != string::npos)
			{
				if(pos < 10)
				{
					savedLine = line;
				}
				else
				{
					readCartFile.close();

					cout << itemCartId << " does not exist. Please re-enter an valid ID. ";
					getline(cin, itemCartId);
				}
			}
		}
	}
	else
	{
		cout << "Fail to open file...";
	}
	readCartFile.close();

	if(savedLine == "")
	{
		cout << "Item ID not found." << endl;
	}
	else
	{
		line = "";

		ifstream getFile;
		getFile.open(textfile, ios::in);

		ofstream temporarily;
		temporarily.open("temporarily.txt");

		while(getline(getFile, line))
		{
			if(line.compare(savedLine) != 0)
			{
				temporarily << line << endl;
			}
		}
		getFile.close();
		temporarily.close();
	}

	if(remove(cnvrFileName)==0)
	{
		if(rename("temporarily.txt", cnvrFileName)==0)
		{
			cout << "Selected item has removed from shopping cart. " << endl;
		}
		else
		{
            cout << "Error occur. File has been removed. " << endl;
        }
    }
	else
	{
        cout << "Selected item failed to remove. " << endl;
	}
}

//Function to clear all items of shopping cart or shopping record
void clearItem(string textfile, string choice)
{
	int counter=0;
	int i=0;
	string headerLine;
	string header[4];
    
	if(choice=="Yes")
	{
		//Read the first 4 lines (header) and store into an array
		ifstream dltFile;
		dltFile.open(textfile, ios::in);

		if(dltFile.is_open())
		{
			while(getline(dltFile, headerLine))
			{
				if(counter++ < 4)
				{
					header[i] = headerLine;
					i++;
				}
			}
		}
		else
		{
			cout << "Fail to load file...";
		}
		dltFile.close();

		//Output and overwrite the first 4 lines (header) into textfile
		//Other lines are cleared
		ofstream insertFile;
		insertFile.open(textfile);

		for(int j=0; j<1; j++)
    	{
        	insertFile << header[j];
    	}

		for(int j=1; j<4; j++)
    	{
        	insertFile << "\n" << header[j];
    	}
		insertFile.close();
	}
	else if(choice=="No")
	{
		exit(0);
	}
	else
	{
		cout << "Invalid choice!" << endl;
	}
}