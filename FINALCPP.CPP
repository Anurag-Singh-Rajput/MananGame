#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <process.h>
#include <ctype.h>
using namespace std;
//____________________________________________
//               C L A S S
//_____________________________________________

class account
{
	int acno, deposit, withdraw, x, pin;
	char name[50];
	char type;

public:
	void create_account()
	{
		cout << "====NEW ACCOUNT ENTRY FORM====" << endl;
		cout << "Enter The account Number : " << endl;
		cin >> acno;
		cin.ignore();
		cout << "Enter The Name of The account Holder: " << endl;
		gets(name);
		cout << "Enter Type of The account (C/S) : " << endl;
		cin >> type;
		type = toupper(type);

		cout << "Enter Initial amount>=500 for Saving & >=1000 for Current :" << endl;
		cin >> deposit;
		cout << "Enter 4 digit pin  " << endl;
		cin >> pin;
		cout << "Your Account Created Successfully .." << endl;
		getch();
	}
	void show_account()
	{
		cout << "-------ACCOUNT STATUS-------\n"
			 << endl;
		cout << "Account No.                 : " << acno << endl;
		cout << "Account Holder Name         : " << name << endl;
		cout << "Type of Account             : " << type << endl;
		cout << "Balance amount              : " << deposit << endl;
	}

	void dep(int x)
	{
		deposit += x;
	}
	void draw(int x)
	{
		deposit -= x;
	}
	void report()
	{
		cout << acno << " " << name << " " << type << " " << deposit << endl;
	}
	int retacno()
	{
		return acno;
	}
	float retdeposit()
	{
		return deposit;
	}
	char rettype()
	{
		return type;
	}

	int retpin()
	{
		return pin;
	}
};

fstream fp;
account ac; //globally declared

//____________________________________________________________
// 	function to write in file
//____________________________________________________________
void write_account()
{
	fp.open("account.dat", ios::out | ios::app);
	ac.create_account();
	fp.write((char *)&ac, sizeof(account));
	fp.close();
}

//________________________________________________________________
// 	function to read specific record from file
//________________________________________________________________
void display_sp()
{

	int no, P;
	cout << "====BALANCE DETAILS====" << endl;
	cout << "Enter the Account Number : " << endl;
	cin >> no;
	int flag = 0;

	cout << "Enter pin " << endl;
	cin >> P;
	fp.open("account.dat", ios::in);
	while (fp.read((char *)&ac, sizeof(account)))
	{
		if (ac.retacno() == no && ac.retpin() == P)

		{
			ac.show_account();
			flag = 1;
		}
	}
	fp.close();
	if (flag == 0)
	{

		cout << "INCORRECT INFO\n";
	}

	getch();
}

//______________________________________________________________
// 	function to delete record of file
//_______________________________________________________________

void delete_account()
{
	int no, P;
	cout << "===Delete Record====" << endl;
	cout << "Enter The Account No. : " << endl;
	cin >> no;
	cout << "     Enter Pin  " << endl;
	cin >> P;
	if (ac.retpin() == P)
	{
		fp.open("account.dat", ios::in | ios::out);
		fstream fp2;
		fp2.open("Temp.dat", ios::out);
		fp.seekg(0, ios::beg);
		while (fp.read((char *)&ac, sizeof(account)))
		{
			if (ac.retacno() != no) //transferring all accounts except account to be deleted
			{
				fp2.write((char *)&ac, sizeof(account));
			}
		}
		fp2.close();
		fp.close();
		remove("account.dat");
		rename("Temp.dat", "account.dat");
		cout << "Record Deleted .." << endl;
		getch();
	}
	else
	{
		cout << "INCORRECT INFO" << endl;
	}
	getch();
}

// function to win loose money

void win_loose(int option, int x)
{
	int P;
	int no, found = 0;

	cout << "====ACCOUNT TRANSCATION FORM====\n";
	cout << "Enter The account No. : " << endl;
	cin >> no;
	cout << "Enter Pin  " << endl;
	cin >> P;
	fp.open("account.dat", ios::in | ios::out);
	while (fp.read((char *)&ac, sizeof(account)) && found == 0)
	{
		if (ac.retacno() == no && ac.retpin() == P)
		{
			if (option == 1)
			{
				ac.dep(x);
			}
			if (option == 2)
			{

					ac.draw(x);
			}
			int pos = -1 * sizeof(ac);
			fp.seekp(pos, ios::cur);
			fp.write((char *)&ac, sizeof(account));
			cout << "Record Updated " << endl;
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{

		cout << " INCORRECT INFO \n";
	}

	getch();
}

//_______________________________________________________________
// 	function to deposit and withdraw amounts
//_______________________________________________________________
void deposit_withdraw(int option)
{
	int P;
	int no, found = 0, amt;

	cout << "====ACCOUNT TRANSCATION FORM====\n";
	cout << "Enter The account No. : " << endl;
	cin >> no;
	cout << "Enter Pin  " << endl;
	cin >> P;
	fp.open("account.dat", ios::in | ios::out);
	while (fp.read((char *)&ac, sizeof(account)) && found == 0)
	{
		if (ac.retacno() == no && ac.retpin() == P)
		{
			ac.show_account();
			if (option == 1)
			{

				cout << "Enter The amount : ";
				cin >> amt;
				ac.dep(amt);
			}
			if (option == 2)
			{

				cout << "Enter The amount : ";
				cin >> amt;
				int bal = ac.retdeposit() - amt;
				if (amt > bal)
					cout << "\nInsufficient balance";
				else
					ac.draw(amt);
			}
			int pos = -1 * sizeof(ac);
			fp.seekp(pos, ios::cur);
			fp.write((char *)&ac, sizeof(account));
			cout << "Record Updated " << endl;
			found = 1;
		}
	}
	fp.close();
	if (found == 0)
	{

		cout << " INCORRECT INFO \n";
	}

	getch();
}

// function to ask questions

void ques()
{
	int dep, ans = 0;
	int a[5];
	cout << "Welcome to the Quiz." <<endl;
	cout << "If you answer all the 5 questions correctly you will gain double the price else you lose it all. ENTER OPTIONS CAREFULLY" <<endl;
	cout << "Enter the money you want to bet" <<endl;
	cin >> dep;
	cout << "Ques 1 - Is C++ Object Oriended Language? 1.Yes 2.No "<<endl;
	cin >> ans;
	if (ans == 1)
	{
		a[0] = 1;
	}
	else
		a[0] = 0;
	cout << "Ques 2 - Which of these uses an interpreter? 1.Java 2.C++ 3.Python 4.None of the above"<<endl;
	cin >> ans;
	if (ans == 3)
	{
		a[1] = 1;
	}
	else
		a[1] = 0;
	cout << "Ques 3 - Which one of these is not a programming language? 1.C 2.Java 3.Python 4.HTML"<<endl;
	cin >> ans;
	if (ans == 4)
	{
		a[2] = 1;
	}
	else
		a[2] = 0;
	cout << "Ques 4 - Which of the following is widely used to decorate web pages? 1.C++ 2.CSS 3.Java 4.C#"<<endl;
	cin >> ans;
	if (ans == 2)
	{
		a[3] = 1;
	}
	else
		a[3] = 0;
	cout << "Ques 5 - Which of the following is used to read as well as write in files in Dat File Handling? 1.fstream 2.ifstream 3.ofstream 4.None"<<endl;
	cin >> ans;
	if (ans == 1)
	{
		a[4] = 1;
	}
	else
		a[4] = 0;

	int flag = 1;
	for (int i = 0; i < 5; i++)
	{
		if (a[i] != 1)
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
	{
		win_loose(1,dep*2);
	}
	else win_loose(2,dep);
}

//________________________________________________________________
// 	THE MAIN FUNCTION OF PROGRAM
//________________________________________________________________
int main()
{
	char ch;
	do
	{

		cout << "MAIN MENU" << endl;
		cout << "01. NEW ACCOUNT" << endl;
		cout << "02. DEPOSIT AMOUNT" << endl;
		cout << "03. CLOSE AN ACCOUNT" << endl;
		cout << "04. Details" << endl;
		cout << "05. Win Money" << endl;
		cout << "06. Exit" << endl;
		cout << "Select Your Option (1-6) : ";
		ch = getch(); //not show input
		switch (ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			deposit_withdraw(1);
			break;
		case '3':
			delete_account();
			break;
		case '4':
			display_sp();
			break;
		case '5':
			ques();
			break;
		case '6':
			exit(0);
		}
	} while (ch != '7');

	return 0;
}

//***************************************************************************
//                                 END
//***************************************************************************