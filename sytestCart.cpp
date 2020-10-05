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

void itemChoice();
int idGenerator(string txtfile);

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
		magazine() { itemCartId=""; }
    	void viewItem()
    	{
			string line;
    		cout << "\n=========================================" << endl;
            cout << "              View Magazine              " << endl;
            cout << "=========================================" << endl;
			ifstream viewMaFile(maCartFile);
			if(viewMaFile.fail())
			{	
				cout << "Fail to open file...";
			}
			else
			{
				while(getline(viewMaFile, line))
				{
					cout << line << endl;
				}
			}
			viewMaFile.close();
		}
        void addItem()
        {
			string line, savedLine;
			size_t pos;
			cout << "\n=========================================" << endl;
            cout << "               Add Magazine              " << endl;
            cout << "=========================================" << endl;
			cout << "Enter item id: ";
			cin.ignore();
			getline(cin, itemCartId);

			ifstream readMaFile;
			readMaFile.open(maFile, ios::in);

			if(readMaFile)
			{
				while(getline(readMaFile, line))
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
							readMaFile.close();

							cout << itemCartId << " does not exist. Please re-enter an valid id: ";
							getline(cin, itemCartId);
							addItem();

						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			
			readMaFile.close();	

			ofstream addMaFile;
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
			
		}
        void deleteItem()
		{
			string line, savedLine;
			size_t pos;
			const char * cnvrFileName = maCartFile.c_str();
			cout << "\n=========================================" << endl;
            cout << "             Delete Magazine             " << endl;
            cout << "=========================================" << endl;
			cout << "Enter item id: ";
			cin.ignore();
			getline(cin, itemCartId);

			ifstream readMaCartFile;
			readMaCartFile.open(maCartFile, ios::in);

			if(readMaCartFile.is_open())
			{
				while(getline(readMaCartFile, line))
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
							readMaCartFile.close();

							cout << itemCartId << " does not exist. Please re-enter an valid id: ";
							getline(cin, itemCartId);
							addItem();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readMaCartFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getFile;
				getFile.open(maCartFile, ios::in);

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
				cout << "Removed selected item from shopping cart. " << endl;

				if(rename("temporarily.txt", cnvrFileName)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}
		}
        void modifyItem() 
		{
            string line;
            string id;
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

            cout << "Item Id u wanna update? " << endl;
            cin.ignore();
            getline(cin, id);

            ifstream posFinder;
            posFinder.open("magazineCart.txt", ios::in);

            while(getline(posFinder, line)) {

                if(counter++ > 3) {
                    
                    while((pos = line.find(delimeter, position)) != string::npos) {

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

            if(mod.fail()){

                cout << "fail to open" << endl;
				exit(0);

            }else{


                while(getline(mod, line)) {

                        if((pos = line.find(id)) != string::npos) {

                            if(pos < 10) {

                                savedLine = line;

                            }

                        }

                }

                mod.close();

				if(savedLine == "") {

                    cout << "Item Not Found" << endl;
                    exit(0);

                }else{


                    cout << "ITEM ID FOUND" << endl;

					while(z < 109) {

						cout << "=";

						z++;

					}
					cout << "\n" <<savedLine << endl;

					z = 0;

					while(z < 109) {

						cout << "=";

						z++;

					}

                    cout << "\nnew no of units :" << endl;
                    //cin.ignore();
                    getline(cin, newUnits);

                    ifstream mod1;
                    mod1.open("magazineCart.txt", ios::in);   

                    ofstream temp;
                    temp.open("temp.txt");

                        while(getline(mod1, line)) {

                            if(line.compare(savedLine) != 0) {

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

						if(temp.fail()) {

							cout << "failed to open" << endl;
							exit(0);

						}else{

							temp << "|" <<setw(7) << itemId;
							temp << "|" <<setw(30) << name;
							temp << "|" <<setw(14) << price;
							temp << "|" <<setw(11) << newUnits;
							temp << "|" <<setw(30) << compName;
							temp << "|" <<setw(4) << year;
							temp << "|" <<setw(5) << month << "|" << "\n";

							temp.close();

							cout << "Item inserted" << endl;

							remove("magazineCart.txt");
							rename("temp.txt" , "magazineCart.txt");

						}

                }

            }
		}
		void viewRecord()
		{
			string line;
    		cout << "\n=========================================" << endl;
            cout << "           View Shopping Record          " << endl;
            cout << "=========================================" << endl;
			ifstream viewMaFile(maRecordFile);
			if(viewMaFile.fail())
			{	
				cout << "Fail to open file...";
			}
			else
			{
				while(getline(viewMaFile, line))
				{
					cout << line << endl;
				}
			}
			viewMaFile.close();
		}
		void clearRecord()
		{
			int counter=0;
			int i=0;
			string dltChoice;
			string headerLine;
			string header[4];
			cout << "\n=========================================" << endl;
            cout << "          Delete Shopping Record         " << endl;
            cout << "=========================================" << endl;
			cout << "Are you sure want to clear your shopping history? [Yes or No]" << endl;
			cin >> dltChoice;
            
			if(dltChoice=="Yes")
			{
				ifstream dltFile;
				dltFile.open(maRecordFile, ios::in);

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
				insertFile.open(maRecordFile);

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
			else if(dltChoice=="No")
			{
				exit(0);
			}
			else
			{
				cout << "Invalid choice!";
			}
		}
		void clearCart()
		{
			int counter=0;
			int i=0;
			string dltChoice;
			string headerLine;
			string header[4];
			cout << "\n=========================================" << endl;
            cout << "          Delete Shopping Record         " << endl;
            cout << "=========================================" << endl;
			cout << "Are you sure want to clear your shopping history? [Yes or No]" << endl;
			cin >> dltChoice;
            
			if(dltChoice=="Yes")
			{
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
				insertFile.close();
			}
			else if(dltChoice=="No")
			{
				exit(0);
			}
			else
			{
				cout << "Invalid choice!";
			}
		}
		void addRecord()
		{
			string line, savedLine;
			size_t pos;
			cout << "\n=========================================" << endl;
            cout << "            Add Magazine Record          " << endl;
            cout << "=========================================" << endl;

			ifstream readMaFile;
			readMaFile.open(maCartFile, ios::in);

			if(readMaFile)
			{
				while(getline(readMaFile, line))
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
							readMaFile.close();

							cout << itemCartId << " does not exist. Please re-enter an valid id: ";
							getline(cin, itemCartId);
							addItem();

						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			
			readMaFile.close();	

			ofstream addMaFile;
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
		}
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
		book() { itemCartId=""; }
    	void viewItem()
    	{
    		string line;
    		cout << "\n=========================================" << endl;
            cout << "               View Book                " << endl;
            cout << "=========================================" << endl;
			ifstream viewBoFile(boCartFile);
			if(viewBoFile.fail())
			{	
				cout << "Fail to open file...";
			}
			else
			{
				while(getline(viewBoFile, line))
				{
					cout << line << endl;
				}
			}
			viewBoFile.close();
		}
        void addItem()
        {
        	string line, savedLine;
			size_t pos;
			cout << "\n=========================================" << endl;
            cout << "                 Add Book                " << endl;
            cout << "=========================================" << endl;
			cout << "Enter item id: ";
			cin.ignore();
			getline(cin, itemCartId);

			ifstream readBoFile;
			readBoFile.open(boFile, ios::in);

			if(readBoFile)
			{
				while(getline(readBoFile, line))
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
							readBoFile.close();

							cout << itemCartId << " does not exist. Please re-enter an valid id: ";
							getline(cin, itemCartId);
							addItem();

						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}

			readBoFile.close();	

			ofstream addBoFile;
			addBoFile.open(boCartFile, ios::app);

			if(addBoFile.is_open())
			{
				addBoFile << savedLine << endl;
			}
			else
			{
				cout << "Fail to open file...";
			}
			addBoFile.close();

		}
        void deleteItem()
        {
        	string line, savedLine;
			size_t pos;
			const char * cnvrFileName = boCartFile.c_str();
			cout << "\n=========================================" << endl;
            cout << "                Delete Book              " << endl;
            cout << "=========================================" << endl;
			cout << "Enter item id: ";
			cin.ignore();
			getline(cin, itemCartId);

			ifstream readBoCartFile;
			readBoCartFile.open(boCartFile, ios::in);

			if(readBoCartFile.is_open())
			{
				while(getline(readBoCartFile, line))
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
							readBoCartFile.close();

							cout << itemCartId << " does not exist. Please re-enter an valid id: ";
							getline(cin, itemCartId);
							addItem();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readBoCartFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getFile;
				getFile.open(boCartFile, ios::in);

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
				cout << "Removed selected item from shopping cart. " << endl;

				if(rename("temporarily.txt", cnvrFileName)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}
		}
        void modifyItem() 
		{
            string line;
            string id;
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

            cout << "Item Id u wanna update? " << endl;
            cin.ignore();
            getline(cin, id);

            ifstream posFinder;
            posFinder.open("bookCart.txt", ios::in);

            while(getline(posFinder, line)) {

                if(counter++ > 3) {
                    
                    while((pos = line.find(delimeter, position)) != string::npos) {

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

            if(mod.fail()){

                cout << "fail to open" << endl;
				exit(0);

            }else{


                while(getline(mod, line)) {

                        if((pos = line.find(id)) != string::npos) {

                            if(pos < 10) {

                                savedLine = line;

                            }

                        }

                }

                mod.close();

				if(savedLine == "") {

                    cout << "Item Not Found" << endl;
                    exit(0);

                }else{


                    cout << "ITEM ID FOUND" << endl;

					while(z < 129) {

						cout << "=";

						z++;

					}
					cout << "\n" <<savedLine << endl;

					z = 0;

					while(z < 129) {

						cout << "=";

						z++;

					}

                    cout << "\nnew no of units :" << endl;
                    //cin.ignore();
                    getline(cin, newUnits);

                    ifstream mod1;
                    mod1.open("bookCart.txt", ios::in);   

                    ofstream temp;
                    temp.open("temp.txt");

                        while(getline(mod1, line)) {

                            if(line.compare(savedLine) != 0) {

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

						if(temp.fail()) {

							cout << "failed to open" << endl;
							exit(0);

						}else{

							temp << "|" <<setw(7) << itemId;
							temp << "|" <<setw(30) << name;
							temp << "|" <<setw(14) << price;
							temp << "|" <<setw(11) << newUnits;
							temp << "|" <<setw(30) << compName;
							temp << "|" <<setw(30) << authorName << "|" << "\n";

							temp.close();

							cout << "Item inserted" << endl;

							remove("bookCart.txt");
							rename("temp.txt" , "bookCart.txt");

						}

                }

            }
		}
		void viewRecord()
		{
			string line;
    		cout << "\n=========================================" << endl;
            cout << "               View Record               " << endl;
            cout << "=========================================" << endl;
			ifstream viewMaFile(boRecordFile);
			if(viewMaFile.fail())
			{	
				cout << "Fail to open file...";
			}
			else
			{
				while(getline(viewMaFile, line))
				{
					cout << line << endl;
				}
			}
			viewMaFile.close();
		}
		void clearRecord()
		{
			int counter=0;
			int i=0;
			string dltChoice;
			string headerLine;
			string header[4];
			cout << "\n=========================================" << endl;
            cout << "          Delete Shopping Record         " << endl;
            cout << "=========================================" << endl;
			cout << "Are you sure want to clear your shopping history? [Yes or No]" << endl;
			cin >> dltChoice;
            
			if(dltChoice=="Yes")
			{
				ifstream dltFile;
				dltFile.open(boRecordFile, ios::in);

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
				insertFile.open(boRecordFile);

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
			else if(dltChoice=="No")
			{
				exit(0);
			}
			else
			{
				cout << "Invalid choice!";
			}
		}
		void clearCart()
		{
			int counter=0;
			int i=0;
			string dltChoice;
			string headerLine;
			string header[4];
			cout << "\n=========================================" << endl;
            cout << "          Delete Shopping Record         " << endl;
            cout << "=========================================" << endl;
			cout << "Are you sure want to clear your shopping history? [Yes or No]" << endl;
			cin >> dltChoice;
            
			if(dltChoice=="Yes")
			{
				ifstream dltFile;
				dltFile.open(boCartFile, ios::in);

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
				insertFile.open(boCartFile);

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
			else if(dltChoice=="No")
			{
				exit(0);
			}
			else
			{
				cout << "Invalid choice!";
			}
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
		movie() { itemCartId=""; }
    	void viewItem()
    	{
    		string line;
    		cout << "\n=========================================" << endl;
            cout << "               View Movie                " << endl;
            cout << "=========================================" << endl;
			ifstream viewMoFile(moCartFile);
			if(viewMoFile.fail())
			{	
				cout << "Fail to open file...";
			}
			else
			{
				while(getline(viewMoFile, line))
				{
					cout << line << endl;
				}
			}
			viewMoFile.close();
		}
        void addItem()
        {
        	string line, savedLine;
			size_t pos;
			cout << "\n=========================================" << endl;
            cout << "               Add Magazine              " << endl;
            cout << "=========================================" << endl;
			cout << "Enter item id: ";
			cin.ignore();
			getline(cin, itemCartId);

			ifstream readMoFile;
			readMoFile.open(moFile, ios::in);

			if(readMoFile)
			{
				while(getline(readMoFile, line))
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
							readMoFile.close();

							cout << itemCartId << " does not exist. Please re-enter an valid id: ";
							getline(cin, itemCartId);
							addItem();

						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}

			readMoFile.close();	

			ofstream addMoFile;
			addMoFile.open(moCartFile, ios::app);

			if(addMoFile.is_open())
			{
				addMoFile << savedLine << endl;
			}
			else
			{
				cout << "Fail to open file...";
			}
			addMoFile.close();
		}
        void deleteItem()
        {
        	string line, savedLine;
			size_t pos;
			const char * cnvrFileName = moCartFile.c_str();
			cout << "\n=========================================" << endl;
            cout << "                Delete Book              " << endl;
            cout << "=========================================" << endl;
			cout << "Enter item id: ";
			cin.ignore();
			getline(cin, itemCartId);

			ifstream readMoCartFile;
			readMoCartFile.open(moCartFile, ios::in);

			if(readMoCartFile.is_open())
			{
				while(getline(readMoCartFile, line))
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
							readMoCartFile.close();

							cout << itemCartId << " does not exist. Please re-enter an valid id: ";
							getline(cin, itemCartId);
							addItem();
						}
					}
				}
			}
			else
			{
				cout << "Fail to open file...";
			}
			readMoCartFile.close();

			if(savedLine == "")
			{
				cout << "Item not found" << endl;
			}
			else
			{
				line = "";

				ifstream getFile;
				getFile.open(moCartFile, ios::in);

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
				cout << "Removed selected item from shopping cart. " << endl;

				if(rename("temporarily.txt", cnvrFileName)==0)
				{
					cout << "Renamed temporarily file to original file" << endl;
				}
				else
				{
                    cout << "Renamed Failed";
                }
            }
			else
			{
                cout << "Removed Failed";
			}
		}
        void modifyItem() 
		{
            string line;
            string id;
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

            cout << "Item Id u wanna update? " << endl;
            cin.ignore();
            getline(cin, id);

            ifstream posFinder;
            posFinder.open("movieCart.txt", ios::in);

            while(getline(posFinder, line)) {

                if(counter++ > 3) {
                    
                    while((pos = line.find(delimeter, position)) != string::npos) {

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

            if(mod.fail()){

                cout << "fail to open" << endl;
				exit(0);

            }else{


                while(getline(mod, line)) {

                        if((pos = line.find(id)) != string::npos) {

                            if(pos < 10) {

                                savedLine = line;

                            }

                        }

                }

                mod.close();

				if(savedLine == "") {

                    cout << "Item Not Found" << endl;
                    exit(0);

                }else{


                    cout << "ITEM ID FOUND" << endl;

					while(z < 129) {

						cout << "=";

						z++;

					}
					cout << "\n" <<savedLine << endl;

					z = 0;

					while(z < 129) {

						cout << "=";

						z++;

					}

                    cout << "\nnew no of units :" << endl;
                    //cin.ignore();
                    getline(cin, newUnits);

                    ifstream mod1;
                    mod1.open("movieCart.txt", ios::in);   

                    ofstream temp;
                    temp.open("temp.txt");

                        while(getline(mod1, line)) {

                            if(line.compare(savedLine) != 0) {

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

						if(temp.fail()) {

							cout << "failed to open" << endl;
							exit(0);

						}else{

							temp << "|" <<setw(7) << itemId;
							temp << "|" <<setw(30) << name;
							temp << "|" <<setw(14) << price;
							temp << "|" <<setw(11) << newUnits;
							temp << "|" <<setw(30) << compName;
							temp << "|" <<setw(30) << mainActorName << "|" << "\n";

							temp.close();

							cout << "Item inserted" << endl;

							remove("movieCart.txt");
							rename("temp.txt" , "movieCart.txt");

						}

                }

            }
		}
		void viewRecord()
		{
			string line;
    		cout << "\n=========================================" << endl;
            cout << "               View Record               " << endl;
            cout << "=========================================" << endl;
			ifstream viewMaFile(moRecordFile);
			if(viewMaFile.fail())
			{	
				cout << "Fail to open file...";
			}
			else
			{
				while(getline(viewMaFile, line))
				{
					cout << line << endl;
				}
			}
			viewMaFile.close();
		}
		void clearRecord()
		{
			int counter=0;
			int i=0;
			string dltChoice;
			string headerLine;
			string header[4];
			cout << "\n=========================================" << endl;
            cout << "          Delete Shopping Record         " << endl;
            cout << "=========================================" << endl;
			cout << "Are you sure want to clear your shopping history? [Yes or No]" << endl;
			cin >> dltChoice;
            
			if(dltChoice=="Yes")
			{
				ifstream dltFile;
				dltFile.open(moRecordFile, ios::in);

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
				insertFile.open(moRecordFile);

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
			else if(dltChoice=="No")
			{
				exit(0);
			}
			else
			{
				cout << "Invalid choice!";
			}
		}
		void clearCart()
		{
			int counter=0;
			int i=0;
			string dltChoice;
			string headerLine;
			string header[4];
			cout << "\n=========================================" << endl;
            cout << "          Delete Shopping Record         " << endl;
            cout << "=========================================" << endl;
			cout << "Are you sure want to clear your shopping history? [Yes or No]" << endl;
			cin >> dltChoice;
            
			if(dltChoice=="Yes")
			{
				ifstream dltFile;
				dltFile.open(moCartFile, ios::in);

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
				insertFile.open(moCartFile);

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
			else if(dltChoice=="No")
			{
				exit(0);
			}
			else
			{
				cout << "Invalid choice!";
			}
		}

};

class payment
{   
	private:
        int cardNum;
        
    public:
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
					
					/*item *item1 = &ma;
					item *item2 = &bo;
					item *item3 = &mo;*/

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
	itemChoice(); 
	
	return 0;
}

void itemChoice()
{
	magazine ma;
	book bo;
	movie mo;
	
	item *item1 = &ma;
	item *item2 = &bo;
	item *item3 = &mo;
	
	int cartOption;
	int categoryOption;
	
	cout << "\n=========================================" << endl;
    cout << "         Action for Shopping Cart        " << endl;
    cout << "=========================================" << endl;
    cout << "             1. View Item                " << endl;
    cout << "             2. Add Item                 " << endl;
    cout << "             3. Delete Item              " << endl;
    cout << "             4. Modify Item              " << endl;
	cout << "             5. Display Record           " << endl;
	cout << "             6. Clear Record             " << endl;
	cout << "             7. Clear Cart               " << endl;
	cout << "=========================================" << endl;
	cout << "             [Press 0] Exit              " << endl;
	cout << "........................................." << endl << endl;
	cout << "Choose an option [Enter 1, 2... or 7]: ";
	cin >> cartOption;
	
	while(!(cartOption>=0 && cartOption<=7))
	{
		cout << "\nInvalid option for shopping cart!" << endl;
		cout << "Please enter an valid option: ";
		cin >> cartOption;
	}
	
	cout << "\n=========================================" << endl;
	cout << "       Item Type for Shopping Cart       " << endl;
	cout << "=========================================" << endl;
	cout << "           Category 1: Magazine          " << endl;
	cout << "           Category 2: Book              " << endl;
	cout << "           Category 3: Movie             " << endl;
	cout << "=========================================" << endl;
	cout << "             [Press 0] Exit              " << endl;
	cout << "........................................." << endl << endl;
	cout << "Choose the category you want [Enter 1, 2 or 3]: ";
	cin >> categoryOption;
	
	while(categoryOption!=0 && categoryOption!=1 && categoryOption!=2 && categoryOption!=3)
	{
		cout << "\nInvalid option for item type!" << endl;
		cout << "Please enter an valid option: ";
		cin >> categoryOption;
	}
	
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
				{ ma.viewRecord(); }
				else if(cartOption==6)
				{ ma.clearRecord(); }
				else if(cartOption==7)
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
				{ bo.viewRecord(); }
				else if(cartOption==6)
				{ bo.clearRecord(); }
				else if(cartOption==7)
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
				{ mo.viewRecord(); }
				else if(cartOption==6)
				{ mo.clearRecord(); }
				else if(cartOption==7)
				{ mo.clearCart(); }
				break;
		case 0: exit(0);
		default: cout << "Invalid option!"; 
	}
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
