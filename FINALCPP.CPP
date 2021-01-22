#include<iostream.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<ctype.h>
#include<dos.h>
//____________________________________________
//               C L A S S
//_____________________________________________

class account
{
	int acno, deposit, withdraw,x,pin;
	char name[50];
	char type;
	public:
	void create_account()
	{
		cout<<"====NEW ACCOUNT ENTRY FORM===="<<endl;
		cout<<"Enter The account Number : "<<endl;
		cin>>acno;
		cout<<"Enter The Name of The account Holder: "<<endl;
		gets(name);
		cout<<"Enter Type of The account (C/S) : "<<endl;
		cin>>type;
		type=toupper(type);
		
		cout<<"Enter Initial amount>=500 for Saving & >=1000 for Current :"<<endl;
		cin>>deposit;
		cout<<"Enter 4 digit pin  "<<endl;
		cin>>pin;
		cout<<"Your Account Created Successfully .."<<endl;
	getch();
	}
	void show_account()
	{
		cout<<"-------ACCOUNT STATUS-------\n"<<endl;
		cout<<"Account No.                 : "<<acno<<endl;
		cout<<"Account Holder Name         : "<<name<<endl;
		cout<<"Type of Account             : "<<type<<endl;
		cout<<"Balance amount              : "<<deposit<<endl;
	}

	void dep(int x)
	{
		deposit+=x;
	}
	void draw(int x)
	{
		deposit-=x;
	}
	void report()
	{
		cout<<acno<<"\t\t"<<name<<"\t\t"<<type<<"\t\t" 			<<deposit<<endl;
	}
	int retacno()
	{
		return acno;
	}
	float retdeposit()
	{	return deposit;
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
account ac;  //globally declared


//____________________________________________________________
// 	function to write in file
//____________________________________________________________
void write_account()
{	clrscr();
	fp.open("account.dat",ios::out|ios::app);
	ac.create_account();
	fp.write((char*)&ac,sizeof(account));
	fp.close();
}

//________________________________________________________________
// 	function to read specific record from file
//________________________________________________________________
void display_sp()
{
	clrscr();
	int no,P;
	cout<<"====BALANCE DETAILS===="<<endl;
	cout<<"Enter the Account Number : "<<endl;
	cin>>no;
	int flag=0;
	
	cout<<"Enter pin "<<endl;
	cin>>P;
	fp.open("account.dat",ios::in);
	while(fp.read((char*)&ac,sizeof(account)))
	{
		if(ac.retacno()==no && ac.retpin()==P)


		{
			ac.show_account();
			flag=1;
		}
	}
	fp.close();
	if(flag==0)
	{
		
		cout<<"INCORRECT INFO\n";
	}

	getch();
}


//______________________________________________________________
// 	function to delete record of file
//_______________________________________________________________

void delete_account()
{     	clrscr();
	int no,P;
	cout<<"\t===Delete Record===="<<endl;
	cout<<"\tEnter The Account No. : "<<endl;
	cin>>no;
	cout<<"     Enter Pin  "<<endl;
	cin>>P;
	if(ac.retpin()==P)
{
	fp.open("account.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&ac,sizeof(account)))
	{
		if(ac.retacno()!=no) //transferring all accounts except account to be deleted
		{
			fp2.write((char*)&ac,sizeof(account));
		}
	}
	fp2.close();
	fp.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"\tRecord Deleted .."<<endl;
	getch();
}
else
      {
	  cout<<"INCORRECT INFO"<<endl;
       }
getch();
}
//_______________________________________________________________
// 	function to deposit and withdraw amounts
//_______________________________________________________________
void deposit_withdraw(int option)
{	clrscr();
	int P;
	int no,found=0,amt;

	cout<<"====ACCOUNT TRANSCATION FORM====\n";
	cout<<"Enter The account No. : "<<endl;
	cin>>no;
	cout<<"Enter Pin  "<<endl;
	cin>>P;
	fp.open("account.dat",ios::in|ios::out);
	while(fp.read((char*)&ac,sizeof(account)) && found==0)
	{
		if(ac.retacno()==no&&ac.retpin()==P)
		{
			ac.show_account();
			if(option==1)
			{
				
				cout<<"Enter The amount to DEPOSIT : ";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				
				cout<<"Enter The amount to WITHDRAW : ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(amt>bal)
					cout<<"\nInsufficient balance";
				else
					ac.draw(amt);
			}
			int pos=-1*sizeof(ac);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&ac,sizeof(account));
			cout<<"\t Record Updated "<<endl;
			found=1;
		}
	}
	fp.close();
	if(found==0)
	{
		
		cout<<" INCORRECT INFO \n";
	}

	getch();
}

//________________________________________________________________
// 	THE MAIN FUNCTION OF PROGRAM
//________________________________________________________________
void main()
{	char ch;
	textcolor(BLACK);
	textbackground(RED);
	do
	{
		clrscr();
		cout<<"MAIN MENU"<<endl;
		cout<<"01. NEW ACCOUNT"<<endl;
		cout<<"02. DEPOSIT AMOUNT"<<endl;
		cout<<"03. CLOSE AN ACCOUNT"<<endl;
		cout<<"04. Details"<<endl;
		cout<<"05. Win Money"<<endl;
		cout<<"06. Exit"
		cout<<"Select Your Option (1-6) : ";
		ch=getch();   //not show input
		switch(ch)
		{
			case '1': write_account();
				  break;
			case '2': deposit_withdraw(1);
				  break;
			case '3': delete_account();
				  break;
			case '4' : display_sp();
			case '6': exit(0);
		}
	}while(ch!='7');
}

//***************************************************************************
//                                 END
//***************************************************************************