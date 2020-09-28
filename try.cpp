//here
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main()
{	
	string userid;
	string password; 
	cout << "Enter user ID: ";
	cin >> userid;
	
	fstream myfile;
	myfile.open("tuna.txt");
	myfile << userid;
	myfile.close();
	
	return 0;
}