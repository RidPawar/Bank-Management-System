#include<iostream>
#include<iomanip>
#include<conio.h>
#include<cctype>
#include<fstream>
using namespace std;

class account{
	
	int acno;
	char name[50];
	int deposit;
	char type;
	
	public:
		void create_account();
		void show_account();
		void modify();
		void dep(int);
		void draw(int);
		void report();
		int retacno();
		int retdeposit();
		char rettype();
};

void account::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>acno;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount(>=500 for Saving and >=1000 for current ) : ";
	cin>>deposit;
	cout<<"\n\n\nAccount Created..";
}

void account::show_account() 
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nAccount Holder Name : ";
	cout<<name;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<deposit;
}

void account::modify()
{
	cout<<"\nAccount No. : "<<acno;
	cout<<"\nModify Type of Account : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nModify Balance amount : ";
	cin>>deposit;
}

void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report()
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int account::retacno() 
{
	return acno;
}

int account::retdeposit() 
{
	return deposit;
}

char account::rettype() 
{
	return type;
}

fstream fp;
account ac;

void write_account()  //function to write record in binary file
{
	fp.open("bank.dat",ios::out|ios::app);
    ac.create_account();
    fp.write((char*)&ac,sizeof(account));
    fp.close();
    cout<<"\n\nBank Account Has Been Created ";
    getch();
}

void display_sp(int n)
{
    int flag=0;
    fp.open("bank.dat",ios::in);
    while(fp.read((char*)&ac,sizeof(account)))
    {
        if(ac.retacno()==n)
        {
            ac.show_account();
            flag=1;
        }
    }
    fp.close();
    if(flag==0)
        cout<<"\n\nAccount does not exist";
    getch();
}

void modify_account(int n)
{
	int acc_num,found=0;
	cout<<"\n\n\tTo Modify ";
    cout<<"\n\n\tPlease Enter The account number ";
    cin>>acc_num;
    fp.open("bank.dat",ios::in|ios::out);
    while(fp.read((char*)&ac,sizeof(account)))
    {
    	if(ac.retacno()==n)
        {
            ac.show_account();
            cout<<"\nPlease Enter The New Details "<<endl;
            ac.modify();
            int pos=-1*sizeof(ac);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&ac,sizeof(account));
            cout<<"\n\n\t Record Updated";
            found=1;
        }
	}
	fp.close();
    if(found==0)
        cout<<"\n\n Record Not Found ";
    getch();
	
}

void delete_account(int n){
	
	int acc_num;
    cout<<"\n\n\n\tDelete Record";
    cout<<"\n\nPlease Enter The Account number You Want To Delete";
    cin>>acc_num;
    fp.open("bank.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&ac,sizeof(account)))
    {
        if(ac.retacno()!=acc_num)
        {
            fp2.write((char*)&ac,sizeof(account));
        }
    }
    fp2.close();
    fp.close();
    remove("bank.dat");
    rename("Temp.dat","bank.dat");
    cout<<"\n\n\tAccount Deleted ..";
    getch();
}

void display_all()
{
 
    fp.open("bank.dat",ios::in);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout<<"\n\n\n Program is closing ....";
        getch();
        exit(0);
    }

    cout<<"\n\n\t\tALL Accounts \n\n";
    cout<<"====================================================\n";
    cout<<"A/c No. Name          Type  Balance\n";
    cout<<"====================================================\n";

    while(fp.read((char*)&ac,sizeof(account)))
    {
        ac.report();
    }
    fp.close();
    getch();
}

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=0;
	fp.open("bank.dat",ios::in|ios::out);
    if(!fp)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Entry Menu to create File";
        cout<<"\n\n\n Program is closing ....";
        getch();
        exit(0);
    }
	while(fp.read((char*)&ac,sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Insufficience balance";
				else
					ac.draw(amt);
			}
			int pos=(-1)*sizeof(ac);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&ac,sizeof(account));
			cout<<"\n\n\t Record Updated";
			found=1;
	       }
         }
	fp.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
}

int main()
{
	char ch;
	int num;
	//intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. NEW ACCOUNT";
		cout<<"\n\n\t02. DEPOSIT AMOUNT";
		cout<<"\n\n\t03. WITHDRAW AMOUNT";
		cout<<"\n\n\t04. BALANCE ENQUIRY";
		cout<<"\n\n\t05. ALL ACCOUNT HOLDER LIST";
		cout<<"\n\n\t06. CLOSE AN ACCOUNT";
		cout<<"\n\n\t07. MODIFY AN ACCOUNT";
		cout<<"\n\n\t08. EXIT";
		cout<<"\n\n\tSelect Your Option (1-8) ";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tThanks for using bank managemnt system";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}

