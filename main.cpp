#include <bits/stdc++.h>
using namespace std;
class Bank
{
	int account_no;
	char name[50];
    char account_type[20];
	int balance;
public:
	void create_account();   //To Create a new account
	void show_account();     //To display an account details
	void modify();           //To modify account details
  	void deposit(int);       //To deposit money to a bank account
	void withdraw(int);      //To withdraw money from a bank account
	void report();           //To display data in a single row
	int return_acc_no();     
	int return_balance();
	string return_acc_type();
};

void Bank::create_account()
{
	system("CLS");
	cout<<"Enter the Account No. : ";
	cin>>account_no;
	cout<<"Enter the Name of the Account holder : ";
	cin.ignore();             // Ignore or clear one or more characters from the input buffer.
	cin.getline(name,50);     //To take only first 50 characters as the name entered by the user
	cout<<"Enter Type of the Account (C/S) : ";
	cin.ignore();                   // Ignore or clear one or more characters from the input buffer.
	cin.getline(account_type,20);   //To take only first 50 characters as the account type entered by the user
	cout<<"Enter The Initial amount : ";
	cin>>balance;
	cout<<"!!!!Account Created!!!!";
}

void Bank::show_account()
{
	cout<<"Account Number : "<<account_no;
    cout<<endl;
	cout<<"Account Holder Name : ";
	cout<<name;
    cout<<endl;
	cout<<"Type of Account : ";
    cout<<account_type;
    cout<<endl;
	cout<<"Balance amount : "<<balance;
    cout<<endl;
}


void Bank::modify()
{
	cout<<"Account Number : "<<account_no;
	cout<<"Modify Account Holder Name : ";
	cin.ignore();                  // Ignore or clear one or more characters from the input buffer.
	cin.getline(name,50);          //To take only first 50 characters as the name entered by the user
	cout<<"Modify Type of Account : ";
	cin.ignore();                    // Ignore or clear one or more characters from the input buffer.
	cin.getline(account_type,20);   //To take only first 50 characters as the account type entered by the user
	
	cout<<"Modify Balance amount : ";
	cin>>balance;
}


void Bank::deposit(int amt)
{
	balance+=amt;
}

void Bank::withdraw(int amt)
{
	balance-=amt;
}

void Bank::report()
{
	cout<<account_no<<setw(10)<<" "<<name<<setw(10)<<" "<<account_type<<setw(6)<<balance<<endl;     //Specifies the minimum number of character positions a variable will consume
}

int Bank::return_acc_no() 
{
	return account_no;
}

int Bank::return_balance()
{
	return balance;
}

string Bank::return_acc_type()
{
	return account_type;
}



void new_account();
void display(int);
void modify_account(int);
void delete_account(int);
void display_all();
void deposit_withdraw(int, int);

int main()
{
	char choice;
	int num;
	do
	{
	system("CLS");    //To clear the screen
	cout<<"*****WELCOME TO OUR BANK*****"<<endl;

		cout<<"1. NEW ACCOUNT"<<endl;
		cout<<"2. DEPOSIT AMOUNT"<<endl;
		cout<<"3. WITHDRAW AMOUNT"<<endl;
		cout<<"4. BALANCE ENQUIRY"<<endl;
		cout<<"5. ALL ACCOUNT HOLDER LIST"<<endl;
		cout<<"6. TERMINATE AN ACCOUNT"<<endl;
		cout<<"7. MODIFY AN ACCOUNT"<<endl;
		cout<<"8. EXIT"<<endl;
		cout<<"Select Your Choice: ";
		cin>>choice;

		switch(choice)
		{
		case '1':
			new_account();
			break;

		case '2':
			system("CLS");     //To clear the screen
			cout<<"Enter The account Number. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;

		case '3':
			system("CLS");    //To clear the screen
			cout<<"Enter The account Number : "; cin>>num;
			deposit_withdraw(num, 2);
			break;

		case '4':
			system("CLS");   //To clear the screen
			cout<<"Enter The account Number : "; cin>>num;
			display(num);
			break;

		case '5':
			display_all();
			break;

		case '6':
			system("CLS");    //To clear the screen
			cout<<"Enter The account Number : "; cin>>num;
			delete_account(num);
			break;

		 case '7':
		 	system("CLS");    //To clear the screen
			cout<<"Enter The account Number : "; cin>>num;
			modify_account(num);
			break;

		 case '8':
		 	system("CLS");     //To clear the screen
			cout<<"*****THANK YOU FOR INVESTING YOUR TRUST IN US*****";
			break;

		 default :
         cout<<"\a";
		}
		cin.ignore();        // Ignore or clear one or more characters from the input buffer.
		cin.get();
    }while(choice!='8');
	return 0;
}


void new_account()
{
	Bank ac;              //Creating object of Bank class
	ofstream outFile;     //Creating an outFile to write information to files.
    //ios=input output stream
    //we are opening file in binary from i.e Operations are performed in binary mode rather than text.
    //app here means append --> All output operations happen at the end of the file, appending to its existing contents.
	outFile.open("account.dat",ios::binary|ios::app);   
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
	outFile.close();
}

void display(int n)
{
	Bank ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"BALANCE DETAILS\n";
    //inFileFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)); Reads the Bank structure data directly from a 
    //file into the memory occupied by ac. The cast is because it expects a char*, and this is how you convert a 
    //pointer of one type to a pointer of a completely unrelated type.
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
	{
		if(ac.return_acc_no()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
    inFile.close();
	if(flag==false)
		cout<<"Account number does not exist";
}



void modify_account(int n)
{
	bool found=false;
	Bank ac;
	fstream File;
    //we are opening file in binary from i.e Operations are performed in binary mode rather than text.
    //And file open for reading and writing
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
		if(ac.return_acc_no()==n)
		{
			ac.show_account();
			cout<<"Enter The New Details of account"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(Bank));
            //Set the position of the pointer in the output sequence with the specified position. 
			File.seekp(pos,ios::cur);
		    File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
		    cout<<"Record Updated";
		    found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"Record Not Found ";
}



void delete_account(int n)
{
	Bank ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
    //Seek 0 position from the begining
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
	{
		if(ac.return_acc_no()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	cout<<"..Record Deleted ..";
}


void display_all()
{
	system("CLS");
	Bank ac;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"ACCOUNT HOLDER LIST"<<endl;;
	cout<<"****************************************************\n";
	cout<<"A/c no.      NAME           Type             Balance\n";
	cout<<"****************************************************\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(Bank)))
	{
		ac.report();
	}
	inFile.close();
}


void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	Bank ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(Bank));
		if(ac.return_acc_no()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"TO DEPOSITSS AMOUNT"<<endl;
				cout<<"Enter The amount to be deposited: ";
				cin>>amt;
				ac.deposit(amt);
			}
		    if(option==2)
			{
				cout<<"TO WITHDRAW AMOUNT";
				cout<<"Enter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.return_balance()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.withdraw(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(Bank));
			cout<<"Record Updated";
			found=true;
	       }
         }
    File.close();
	if(found==false)
		cout<<"Record Not Found ";
}


