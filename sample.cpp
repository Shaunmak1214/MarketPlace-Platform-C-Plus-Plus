#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;  // now you need sth like this

char uname[20];
char pass[5];
void username();
void ucheck();

int main()   // main is int
{
	//clrscr();
	int a,b,c;
	cout<<"1-existing user\n2-new user: \n";
	cin>>a;
	if(a==1)
	{
		ucheck();
	}
	if(a==2)
	{
		username();
	}

	//system("pause");
}
void username()
{
	ofstream fi;
	fi.open("username.txt",ios::out|ios::app);

	// Does the file even exist?
	if( !fi.is_open() )
	{
		cout << "Error opening file";
		exit(-1);
	}

	cout<<"enter desired username: ";
	cin.clear();              // entirely different way
	cin.ignore();             // of taking input,
	cin.getline(uname, 20);   // not elegant but works
	cout<<"enter desired password: ";

	for(int i=0; i<5; i++)
	{
		pass[i]=getch();
		cout<<"*";
	}
	cout << "\nThank you";
	cin.get();
	fi << uname << "\n"; // removed "\n"
	fi.write((char*)&pass,sizeof(pass));
}
void ucheck()
 {
    char ch,name2[20],pass2[6];
    int found = 0; // Initialize this!
    cout<<"enter username: ";
    cin.clear();
    cin.ignore();
    cin.getline(name2, 20);
    cout<<"enter password: ";
    for(int j=0;j<5;j++)
    {
        pass2[j]=getch();
        cout<<"*";
    }
    pass2[5] = 0;
    ifstream fin;
    fin.open("username.txt",ios::in) ;
    fin.seekg(0);
    fin.getline(uname,20);
    if(strcmp(name2,uname)!=0)
    {
        cout << "\nNo such user\n"; 
        return; // Added just for my convienience
    }
    while(!fin.eof())
    {
        fin.read((char*)&pass,sizeof(pass));
        if(strcmp(pass2,pass)==0)
            found=1;
    }
    if(found==1)
        cout<<"\nwelcome\n";
    else
        cout<<"\nsorry\n";
    fin.close();
 }