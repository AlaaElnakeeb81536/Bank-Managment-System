                                                            //BANK MANAGMENT PROJECT

#include <iostream>
#include <iostream>
#include <string>
#include<vector>
#include <fstream>
#include <cctype>
#include <iomanip>
#include<bits/stdc++.h>
#define ll long long
#define MOD 1000000007
#define SIZE 1e6+2
#define endl "\n"
using namespace std;

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************

class account
{
    int account_num;
    char name[50],add[100];
    int balance;
    char type;

public:
    void create_account();          //function to get data from user
    void show_account() const;           //function to show data on screen
    void modify();                //function to add new data
    void deposite(int);           //function to accept amount and add to balance amount
    void withdraw(int);          //function to accept amount and subtract from balance amount
    void report() const;               //function to show data in tabular format
    int return_account_num() const;  //function to return account number
    int retdeposit() const;  //function to return balance amount
    char rettype() const;          //function to return type of account

};

void account::create_account()
{
    cout<<"\nEnter The account No. :";
    cin>>account_num;
    cout<<"\n\nEnter THE name of The account Holder :";
    cin.ignore();
    cin.getline(name,50);
    cout<<"What type of account you want to open saving (s) or current (c) ";
    cin>>type;
    type = toupper(type);
    cout<<"Enter amount for deposite (>=500 for Saving and >=1000 for current) ::";
    cin>> balance;
    cout<<"\n\nyour account is created \n ";
}

void account::show_account() const
{
    cout << "\nAccount No. : " << account_num;
    cout << "\nAccount Holder Name : "<<name;
    cout << "\nType of Account : " << type;
    cout << "\nBalance amount : " << balance;
}

void account::modify()
{
    cout<<"\nAccount_num. : "<<account_num;
    cout << "\nModify Account Holder Name : ";
    cin.ignore();
    cin.getline(name, 50);
    cout << "\nModify Type of Account : ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance amount : ";
    cin >> balance;

}
void account :: deposite(int a)
{
    balance+=a;
    cout<<"total amount you deposite :: \t "<<balance;
}

void account :: withdraw(int a)
{
    balance-=a;
    cout<<"now total amount is left :: "<<balance;

}

void account::report() const
{
    cout << account_num << setw(10) << " " << name << setw(10) << " " << type << setw(6) << balance<< endl;
}

int account::return_account_num() const
{
    return account_num;
}

int account::retdeposit() const
{
    return balance;
}

char account::rettype() const
{
    return type;
}

//***************************************************************
//    	function declaration
//****************************************************************
void write_account();            //function to write record in binary file
void display_sp(int);            //function to display account details given by user
void modify_account(int);        //function to modify record of file
void delete_account(int);        //function to delete record of file
void display_all();              //function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void intro();                    //introductory screen function

//***************************************************************
//    	THE MAIN FUNCTION OF PROGRAM
//****************************************************************

int main() {

 char ch;
    int num;
    intro();
    do
    {
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACCOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8) ";
        cin >> ch;
        system("cls");
        switch (ch)
        {
        case '1':
            write_account();
            break;
        case '2':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 1);
            break;
        case '3':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            deposit_withdraw(num, 2);
            break;
        case '4':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            display_sp(num);
            break;
        case '5':
            display_all();
            break;
        case '6':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            delete_account(num);
            break;
        case '7':
            cout << "\n\n\tEnter The account No. : ";
            cin >> num;
            modify_account(num);
            break;
        case '8':
            cout << "\n\n\tThanks for using bank managemnt system";
            break;
        default:
            cout << "\a";
        }
        cin.ignore();
        cin.get();
    } while (ch != '8');
    return 0;

}

//***************************************************************
//    	function to write in file
//****************************************************************

void write_account()
{
    account ac;
    ofstream outfile;
    outfile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outfile.write(reinterpret_cast<char *>(&ac), sizeof(account));
    outfile.close();
}

//***************************************************************
//    	function to read specific record from file
//****************************************************************

void display_sp(int n)
{
    account ac;
    bool flag = false;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";

    while (inFile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.return_account_num() == n)
        {
            ac.show_account();
            flag = true;
        }
    }
    inFile.close();
    if (flag == false)
        cout << "\n\nAccount number does not exist";
}
//***************************************************************
//    	function to modify record of file
//****************************************************************

void modify_account(int n)
{
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.return_account_num() == n)
        {
            ac.show_account();
            cout << "\n\nEnter The New Details of account" << endl;
            ac.modify();
            int pos = (-1) * static_cast<int>(sizeof(account));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

//***************************************************************
//    	function to delete record of file
//****************************************************************

void delete_account(int n)
{
    account ac;
    ifstream infile;
    ofstream outfile;
    infile.open("account.dat", ios::binary);
    if (!infile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    outfile.open("Temp.dat", ios::binary);
    infile.seekg(0, ios::beg);
    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        if (ac.return_account_num() != n)
        {
            outfile.write(reinterpret_cast<char *>(&ac), sizeof(account));
        }
    }
    infile.close();
    outfile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\tRecord Deleted ..";
}
//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
    account ac;
    ifstream infile;
    infile.open("account.dat", ios::binary);
    if (!infile)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "====================================================\n";
    cout << "A/c no.      NAME           Type  Balance\n";
    cout << "====================================================\n";
    while (infile.read(reinterpret_cast<char *>(&ac), sizeof(account)))
    {
        ac.report();
    }
    infile.close();
}

//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
    int amt;
    bool found = false;
    account ac;
    fstream file;
    file.open("account.dat", ios::binary | ios::in | ios::out);
    if (!file)
    {
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!file.eof() && found == false)
    {
        file.read(reinterpret_cast<char *>(&ac), sizeof(account));
        if (ac.return_account_num() == n)
        {
            ac.show_account();
            if (option == 1)
            {
                cout << "\n\n\tTO DEPOSITE AMOUNT ";
                cout << "\n\nEnter The amount to be deposited";
                cin >> amt;
                ac.deposite(amt);
            }
            if (option == 2)
            {
                cout << "\n\n\tTO WITHDRAW AMOUNT ";
                cout << "\n\nEnter The amount to be withdraw";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal < 500 && ac.rettype() == 'S') || (bal < 1000 && ac.rettype() == 'C'))
                    cout << "Insufficience balance";
                else
                    ac.withdraw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char *>(&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    file.close();
    if (found == false)
        cout << "\n\n Record Not Found ";
}

//***************************************************************
//    	INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    cout << "\n\n\n\t                                             BANK";
    cout << "\n\n\t                                             MANAGEMENT";
    cout << "\n\n\t                                             SYSTEM";
    cout << "\n\n\n\nMADE BY :Alaa Elnakeeb";
    cout << "\n\nEMAIL : alaaelnakeeb81@gmail.com";
    cin.get();
}

//***************************************************************
//    			END OF PROJECT
//***************************************************************
