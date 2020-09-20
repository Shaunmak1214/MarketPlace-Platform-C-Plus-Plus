#include<iostream>
#include<iomanip>
#include<string>
#include<cstring>
#include<fstream>

//for C strings
using namespace std;

int main() {

    string command, //to choose what to do each time
    name, password, //the ones that are found in the file
    inName, inPassword, //the ones you are going to input from keyboard
    registerName, registerPassword; //also what you're going to input
    //and if you know C strings, just replace that with something like
    /*
    char
    command[9],
    name[31], password[31], //it could be any size, but like this you have got 30 characters at your
    //disposal, if you consider it to be enough
    inName[31], inPassword[31],
    registerName[31], registerPassword[31];
    */
    while (1) {

        cout << "(register/exit/login)\n" << "Command: ";
        getline(cin, command);

        //(for C strings)
        //cin.get(command, 9);
        //cin.get();

        if (command=="exit") //(for C strings) if (!strcmp(command, "exit"))
        {
            return 1;
        }
        if (command=="register") //(for C strings) if (!strcmp(command, "register"))
        {
            //open file for registration
            ofstream g("registration.txt"); //ofstream is the one for getting data from the file, 
            //and the file does not even have to exist. If it's ofstream, it'll take care of it for you.
            //but be warned that if there is a file called "registration.txt" in the name folder as the
            //.exe file, the contents will be deleted
            if (!g.is_open()) {//if it's not open, then there is no such file with the given name inside
            //the folder (that is, in the folder where the .exe file is going to be)
            
                cout<<"could not open file\n"; //just so that you know why it won't work if it doesn't
                return 0;
                
            }
            cout<<"\n\n\n" //3 newlines
                <<"New Username: ";
            getline(cin, registerName); //input from keyboard will go into registerName
            cout<<"New Password: ";
            getline(cin, registerPassword); //input from keyboard will go into registerPassword
            g<<registerName; //this basically says "put whatever's to the right (registerName) into
            //g ("registration.txt")".
            g<<'\n'; //and now there will be a new line
            g<<registerPassword; //and now the password
            //all placed safely in the file that g opened
            g.close(); //always make sure you close the file, or else you might end up with some nasty
            //stuff in the memory
        }
        if (command=="login") //(for C strings) if (!strcmp(command, "login"))
        {
            //open file, and then put the name and password into the strings
            ifstream f("registration.txt"); //ifstream is the one for getting data from the file, and
            //let us assume you've already created a file called "registration.txt"
            if (!f.is_open()) //if it's not open, then there is no such file with the given name inside
            //the folder (that is, in the folder where the .exe file is going to be)
            {
                cout<<"could not open file\n"; //just so that you know why it won't work if it doesn't
                return 0;
            }
            getline(f, name, '\n'); //reads the user name from file f (which is using "registration.txt")
            getline(f, password, '\n'); //reads the password from file f (which is using "registration.txt")
            //also, if you tell the file to get you that text up until '\n', that's when you know it reads
            //the whole line at most, and won't go any further
            //and that is done by the 3rd parameter
            f.close(); //you don't need it open now, since you have the name and password from the file

            //login
            while (1)
            {
                //you are going to input the name and password here
                cout<<"\n\n\n"
                    <<"Enter Username: ";
                getline(cin, inName);
                cout<<"Enter Password: ";
                getline(cin, inPassword);
                //or this, if you are working with C strings (second version of declaration)
                //cin.get(inName, 31);
                //cin.get();
                //cin.get(inPassword, 31);
                //cin.get();
                //and the "cin.get()" after each input line is necessary, or else[...]
                //no idea what's happening inside istream, but it's mandatory if you don't want your
                //input to get stuck or worse
                if (inName==name && inPassword==password)
                {
                    cout<<"Login Successful\n" //the '\n' is a character, so that's why I can add it 
                    //and it will automatically output a newline in console, alongside the string
                        <<"Welcome, "
                        <<inName;
                    break; //just exit the while loop if you've entered the valid account
                }
                cout<<"incorrect name or password\n"; //if you haven't entered the valid account,
                //then the while loop is not done yet. So that's why this output is without condition
            }
            //now do something about the account
        }
        cout<<"\n\n\n\n\n"; //give it 5 newlines
    }
    return 1;
}