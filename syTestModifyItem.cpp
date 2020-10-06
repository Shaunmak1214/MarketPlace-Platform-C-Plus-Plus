#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<regex>
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
    
    public:
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

        void modifyItem() {
			
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
            posFinder.open("shoppingCart.txt", ios::in);

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
            mod.open("shoppingCart.txt", ios::in);

            if(mod.fail()){

                cout << "fail to open" << endl;
				exit(0);

            }else{

				//cout << "Hi" << endl;

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
                    mod1.open("shoppingCart.txt", ios::in);   

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

							remove("shoppingCart.txt");
							rename("temp.txt" , "shoppingCart.txt");

						}

                }

            }

		}
		void deductItem()
		{
			cout << "1218" << endl;
		}
};

class book : public item
{
    private:
	string itemCartId;
    string authorName;
	string boFile = "book.txt";
    string boCartFile = "bookCart.txt";

    public:
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
            cout << "               Add Magazine              " << endl;
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
        	cout << "1317" << endl;
		}
		void deductItem()
		{
			cout << "1318" << endl;
		}

};

class movie : public item {

    private:
    string itemCartId;
	string mainActorName;
	string moFile = "movie.txt";
    string moCartFile = "movieCart.txt";

    public:
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
        	cout << "1417" << endl;
		}
		
		void deductItem()
		{

			string line;
			string token = "|";
			string saved, saved1, saved2, saved3, saved4, saved5, saved6;
			int lineCount = 0;
			int count = 0;

			size_t pos = 0;
			int counter = 0 ;
			int position = 0;
			int posArr[15];
			int i = 0;

			ifstream posFinder;	
			posFinder.open("shoppingCart.txt", ios::in);

			if(!(posFinder.fail())) {

				while(getline(posFinder, line)) {

					if(counter++ > 3) {

						while((pos = line.find(token, position)) != string::npos) {

							position = pos+1;
							posArr[i] = pos;
							i++;
							
						}

					lineCount++;

					}

				}

			}else{

				cout << "Failed" << endl;

			}

			cout << lineCount << endl;

			i=0;

			posFinder.close();

			line = "";
			counter = 0;
			i = 0;
			string* itemArr = new string [lineCount];
			string* prodName = new string [lineCount];
			string* price = new string [lineCount];
			int* unitArr = new int [lineCount];
			string* compName = new string [lineCount];
			string* year = new string [lineCount];
			string* month = new string [lineCount];

			string cartUnitLine;

			ifstream getdata;
			getdata.open("shoppingCart.txt");

				while(getline(getdata, line)) {

					if(counter++ > 3) {

						//cout << i << endl;
						 saved = line.substr((posArr[0])+1, ((posArr[1])-(posArr[0]))-1);
						saved1 = line.substr((posArr[1])+1, ((posArr[2])-(posArr[1]))-1);
						saved2 = line.substr((posArr[2])+1, ((posArr[3])-(posArr[2]))-1);
						saved3 = line.substr((posArr[3])+1, ((posArr[4])-(posArr[3]))-1);
						saved4 = line.substr((posArr[4])+1, ((posArr[5])-(posArr[4]))-1);
						saved5 = line.substr((posArr[5])+1, ((posArr[6])-(posArr[5]))-1);
						saved6 = line.substr((posArr[6])+1, ((posArr[7])-(posArr[6]))-1);

						cartUnitLine = regex_replace(saved3,regex("\\s"),"");


						itemArr[i] = regex_replace(saved,regex("\\s"),"");
						prodName[i] = regex_replace(saved1,regex("\\s"),"");
						price[i] = regex_replace(saved2,regex("\\s"),"");
						unitArr[i] = stoi(cartUnitLine);
						compName[i] = regex_replace(saved4,regex("\\s"),"");
						year[i] = regex_replace(saved5,regex("\\s"),"");
						month[i] = regex_replace(saved6,regex("\\s"),"");

						saved = "";
						saved1 = "";
						saved2 = "";
						saved3 = "";
						saved4 = "";
						saved5 = "";
						saved6 = "";
						cartUnitLine = "";

						i++;

					}

				}

			getdata.close();

			i = 0;

			// while(i < lineCount) {

			// 	cout << itemArr[i] << " " << prodName[i] << " " << price[i] << " " << unitArr[i] << " " << compName[i] << " " << year[i] << " " << month[i] << endl;
			// 	i++;

			// }

			system("pause");

			line = "";
			saved = "";
			i = 0;
			pos = 0;
			counter = 0;

			int* savedPrice = new int [lineCount];
			string* savedMagLine = new string[lineCount];
			string priceLine;
			string savedLine;

			int checkLineCount = 0;

			ifstream upd;
			upd.open("magazine.txt");

				while(getline(upd, line)) {

					//cout << "hi" << endl;

					if(counter++ > 3) {

						while(i < lineCount) {

							//cout << i << endl;

							//cout << itemArr[i] << endl;

							pos = line.find(itemArr[i]);

							//cout << pos << endl;

							if(pos != string::npos) {

								if(pos < 15) {

									savedMagLine[i] = line;

									priceLine = line.substr((posArr[3])+1, ((posArr[4])-(posArr[3]))-1);
									savedLine = regex_replace(priceLine,regex("\\s"),"");

									savedPrice[i] = stoi(savedLine);

									line = "";
									priceLine = "";
									savedLine = "";

								}

							}
							//pos = 0;
							
							i++;
						}
						i = 0;
					}
					checkLineCount++;
				}

			upd.close();

			for(int z = 0; z< lineCount; z++) {

				//cout << savedPrice[z] << endl;

			}

			for(int z = 0; z< lineCount; z++) {

				cout << savedMagLine[z] << endl;

			}

			system("pause");

			i = 0;
			line = "";
			int trueCounter = 0;

			ifstream upd1;
			upd1.open("magazine.txt", ios::in);

			ofstream write;
			write.open("temp.txt");

			string* check = new string[checkLineCount];
			string* sav = new string[checkLineCount];
			string* skip = new string[checkLineCount];
			int exist = 0;
			int z = 0;

				// while(getline(upd1, line)) {

				// 	while(i < lineCount) {

				// 		if((line.compare(savedMagLine[i])) != 0) {

				// 			cout << savedMagLine[i] << endl;

				// 			if(trueCounter < 1) {

				// 				//if((line.compare(savedMagLine[i])) != 0) {

				// 					write << line << "\n";
				// 					trueCounter++;

				// 				//}

				// 			}

				// 		}
				// 		i++;
				// 	}
				// 	trueCounter = 0;
				// 	i = 0;
				// }
				while(getline(upd1, line)) {

					if(i++ <= checkLineCount){

						if(line.compare(savedMagLine[i]) != 0 ) {

							check[z] = line;
							//cout << line << endl;
							
							//i++;

							cout << exist << endl;
							cout << check[z] << endl;

							//line="";
						}else{

							skip[z] = line;
							cout << "******" << "\n" << skip[z] << endl;
							exist++;

						}
						

					}

					i = 0;
					z++;
					line="";

				}

				if(exist>0) {

							cout << "byebye! ";
							//for(int i = 0; i < checkLineCount; i++) {
							
								//cout << skip[i] << endl;

							//}


						}else{

							for(int i = 0; i < checkLineCount; i++) {
								
								cout << sav[i] << endl;

							}

						} 		


				/*while(getline(upd1, line)) {

					check[i] = line;

					i++;

				}

				for(int i = 0; i < checkLineCount; i++) {

					for(int z = 0; z < lineCount ; z++) {

						if(check[i].compare(savedMagLine[i]) != 0 ) {

							sav[i] = check[i];
							exist++;

						}
						else if(check[i].compare(savedMagLine[i]) == 0 ) {
							skip[i] = check[i];
							cout << check[i];
						}

					}
					

						if(exist>0) {

							cout << "byebye! ";
							//for(int i = 0; i < checkLineCount; i++) {
							
								//cout << skip[i] << endl;

							//}


						}else{

							for(int i = 0; i < checkLineCount; i++) {
								
								cout << sav[i] << endl;

							}

						} 

				}*/

				// while(i < lineCount) {

				// 	while(getline(upd, line)) {

				// 		if(line.compare(savedMagLine[i]) != 0) {

				// 			if(trueCounter < 1) {

				// 				cout << line << endl;
				// 				trueCounter++;

				// 			}

				// 		}

				// 	}
				// 	trueCounter = 0;
				// }

			upd1.close();
			write.close();

			exit(0);


			delete[] itemArr;
			delete[] prodName;
			delete[] unitArr;
			delete[] compName;
			delete[] year;
			delete[] month;

			delete[] savedPrice;
			delete[] savedMagLine;
			
			delete[] check, 
			delete[] sav;
			delete[] skip;
		}

};

class payment
{   
	private:
        int cardNum;
        
    public:
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
					
					item *item1 = &ma;
					item *item2 = &bo;
					item *item3 = &mo;

					ma.deductItem();
					bo.deductItem(); 
					mo.deductItem();

					/*ifstream deduct1;
					deduct1.open("magazine.txt");

						if(!(deduct1.fail())){

							

						}else{

							cout << "Failed to open Magazine.txt" << endl;

						}*/
					
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
	//itemChoice();

	payment p;
	p.checkPayment();
	
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
    cout << "             1. View item                " << endl;
    cout << "             2. Add item                 " << endl;
    cout << "             3. Delete item              " << endl;
    cout << "             4. Modify item              " << endl;
	cout << "=========================================" << endl;
	cout << "Choose an option [Enter 1, 2, 3 or 4]: ";
	cin >> cartOption;
	
	while(cartOption!=1 && cartOption!=2 && cartOption!=3 && cartOption!=4)
	{
		cout << "\nInvalid option for shopping cart!" << endl;
		cout << "Please enter an valid option: ";
		cin >> cartOption;
	}
	
	cout << "\n*****************************************" << endl;
	cout << "       Item Type for Shopping Cart       " << endl;
	cout << "*****************************************" << endl;
	cout << "           Category 1: Magazine          " << endl;
	cout << "           Category 2: Book              " << endl;
	cout << "           Category 3: Movie             " << endl;
	cout << "*****************************************" << endl;
	cout << "Choose the category you want [Enter 1, 2 or 3]: ";
	cin >> categoryOption;
	
	while(categoryOption!=1 && categoryOption!=2 && categoryOption!=3)
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
				break;
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
