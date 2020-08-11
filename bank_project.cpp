#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
fstream bfile;
class bank
{
    char name[30];
    int balance;
    public:
    int acc;
    void account()
    {
        cout<<"Enter name :";
        cin>>name;
        cout<<"Enter balance:";
        cin>>balance;
    }
    void show()
    {
        cout<<"\nName        :";
        cout<<name;
        cout<<"\nAccount No. :"<<acc;
        cout<<"\nBalance     :"<<balance;
        cout<<"\n\n";
    }
    int getacc()
     {
       return acc;
     }
    void deposit(int x)
     {
       balance+=x;
     }
    void withdraw(int x)
     {
       balance-=x;
     }
    int return_bal()
     {
        return balance;
     }
};


int dis(int n)
{
	bank b;
	int flag=0;
	bfile.open("Reco.txt",ios::binary|ios::in);
	while(bfile.read((char *)&b, sizeof(b)))
	{
		if(b.getacc()==n)
		{   cout<<"\nBALANCE DETAILS";
			b.show();
			flag=1;
			bfile.close();
			return (flag);
		}
	}
	bfile.close();
	if(flag==0)
		cout<<"\n\nAccount number does not exist";
    return(flag);
}

int check(int n)
{
	bank b;
	int flag=0;
	bfile.open("Reco.txt",ios::binary|ios::in);
	while(bfile.read((char *) &b, sizeof(b)))
	{
		if(b.getacc()==n)
		{
			flag=1;
			bfile.close();
			return (flag);
		}
	}
	bfile.close();
   return(flag);
}




void create()
{

    int r;
    bank b;
    cout<<"Enter Account No. : ";
    cin>>b.acc;
    int k=check(b.acc);
    if(k==1)
    {
        cout<<"\nAccount already exists\n\n\n";
    }
    else
    {
    bfile.open("Reco.txt",ios::out|ios::app|ios::binary);
    b.account();
    bfile.write((char*)&b,sizeof(b));
    bfile.close();
    cout<<"\n**ACCOUNT CREATED**\n";
    }
}



void display()
{
    bank b;
    bfile.open("Reco.txt",ios::in|ios::binary);
    while(bfile.read((char*)&b,sizeof(b)))
    b.show();
    bfile.read((char*)&b,sizeof(b));
    bfile.close();
}




void deporwith()
{
bank b;
int acc,c,flag=0,amt;
cout<<"Enter account : ";
cin>>acc;
	bfile.open("Reco.txt", ios::binary|ios::in|ios::out);

	while((bfile.read((char *)&b, sizeof(b))) && flag==0)
	{
		if(b.getacc()==acc)
		{
			cout<<"\n\n1.Deposit";
			cout<<"\n2.Withdraw";
			cout<<"\n\nEnter choice : ";
			cin>>c;
			if(c!=1 && c!=2)
                cout<<"\nwrong choice";

			b.show();
			switch(c)
			{

				case 1:
				       cout<<"\n\nEnter The amount to be deposited : ";
				       cin>>amt;
				       b.deposit(amt);

                       break;
			    case 2:
				        cout<<"\n\nEnter The amount to be withdraw : ";
				        cin>>amt;

				        if(amt>b.return_bal())
					    cout<<"\n * Insufficient balance*\n ";
				        else
					    b.withdraw(amt);

			}

            int pos=(-1)*sizeof(b);
			bfile.seekp(pos,ios::cur);
			bfile.write((char *)&b, sizeof(b));
			cout<<"\n\n\t Record Updated";
			flag=1;
	       }
	}

	if(flag==0)
		cout<<"\n\n Record Not Found ";
			bfile.close();
}
int main()
{
    int c,acc;
    do{
    cout<<"\n1.Create new account";
    cout<<"\n2.Display All";
    cout<<"\n3.Display Balance Details";
    cout<<"\n4.Deposit/Withdraw";
    cout<<"\n5.EXIT\n";
    cout<<"\nEnter choice : ";
    cin>>c;
    switch(c)
    {
     case 1:create();
            break;
     case 2:display();
            break;
     case 3:cout<<"\n\nEnter account number :";
            cin>>acc;
            dis(acc);
            break;
     case 4:deporwith();
            break;
     case 5:break;
     default:cout<<"\nWrong Choice";
     }}while(c!=5);
}
