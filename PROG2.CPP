#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>
#include<string.h>
#include<iostream.h>
#include<iomanip.h>
#define customerfile "c2.txt"
#define recsize 90 //size of record
#define max 44     //no:of record
fstream file;
char buffer [200];
class customer
{
     public:
	      char accno[5],name[10],Addr[10],email[20],occupation[10],loantype[10],phno[10];
	      void initial();
	      void read();
	      int retrieve(int addr,char k[]);
	      void pack();
	      void unpack();
	      void display();
	      void Delete(int addr);
	      void modify(int addr);
	     // void search(int addr,char k[]);
	//      void disp();
 };

 void customer::Delete(int addr)
 {
 int j;
  strcpy(buffer,"#");
  file.open(customerfile,ios::in|ios::out);
  file.seekp(addr*recsize,ios::beg);
   for(j=0;j<recsize-2;j++)
     file<<"#";
  //file<<buffer;
  file<<endl;
  file.close();
}

  void sleep()
{
	for(long int i=0;i<=149999999;i++);
	return;
}

 void customer::pack()
 {
	strcpy(buffer,accno);
	strcat(buffer,"|");
	strcat(buffer,name);
	strcat(buffer,"|");
	strcat(buffer,Addr);
	strcat(buffer,"|");
	strcat(buffer,email);
	strcat(buffer,"|");
	strcat(buffer,phno);
	strcat(buffer,"|");
	strcat(buffer,occupation);
	strcat(buffer,"|");
	strcat(buffer,loantype);
	strcat(buffer,"|");
 }
 void customer::unpack()
 {
    //	char dummy[75];
	file.getline(name,10,'|');
	file.getline(Addr,10,'|');
	file.getline(email,20,'|');
	file.getline(phno,10,'|');
	file.getline(occupation,10,'|');
	file.getline(loantype,10,'|');
       //	file.getline(dummy,75,'\n');
 }


void customer::initial()
{
  int i,j;
  file.open(customerfile,ios::in);
  if(!file)
  {
     file.open(customerfile,ios::out);
     if(!file)
     {
      cout<<"unable to open the file";
      exit(1);
      }
    for(i=0;i<max;i++)
    {
     file.seekp(i*recsize,ios::beg);
     for(j=0;j<recsize-2;j++)
     file<<"#";
     file<<endl;
   }
 }
 file.close();
 return;
 }

void customer::read()
{
cout<<"\nEnter the Account Number = ";
gets(accno);
cout<<"\nEnter the Customer Name = ";
gets(name);
cout<<"\nEnter the Customer Address = ";
gets(Addr);
cout<<"\nEnter the Customer Email id = ";
gets(email);
cout<<"\nEnter the Customer Phone Number = ";
gets(phno);
cout<<"\nEnter the Customer Occuptaion = ";
gets(occupation);
cout<<"\nEnter the Loan type = ";
cout<<"\n\t 1.Education loan";
   cout<<"\n\t 2.Home loan";
   cout<<"\n\t 3.Car laon\n";
   int ch;
   cout<<"\n\t Enter choice:\t ";
   cin>>ch;
   if(ch==1)
   {
	strcpy(loantype,"Education");
	//strcpy(roi,"10");
   }
   else if(ch==2)
   {
	strcpy(loantype,"Home");
	//strcpy(roi,"12");
   }
   else
   {
	strcpy(loantype,"Car");
	//strcpy(roi,"18");
   }
//gets(loantype);
pack();
 return;
 }

 /* void customer::disp()
 {
   int i=0;
 char dummy[10];
 file.open(customerfile,ios::in);
 do
 {
  file.seekg(i*recsize,ios::beg);
  file.getline(dummy,5,'\n');
  if(strcmp(dummy,"####")!=0)
  break;
  file.seekg(i*recsize,ios::beg);
  file.getline(accno,15,'|');
  if(strcmp(accno,k)==0)
  {
    found=1;
	unpack();
	clrscr();
	cout<<"\n\nCustomer Record found : \n";
	cout<<"Account no."<<setw(20)<<"Name"<<setw(20)<<"Address"<<setw(20)<<"Email ID"<<setw(40)<<endl;
	cout<<"--------------------------------------------------------------------------------";
	cout<<accno<<setw(20)<<name<<setw(20)<<Addr<<setw(20)<<email<<setw(40)<<endl;
	cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	cout<<"Phone No."<<setw(20)<<"occupation"<<setw(20)<<"loan type"<<endl;
	cout<<"--------------------------------------------------------------------------------";
	cout<<phno<<setw(20)<<occupation<<setw(20)<<loantype<<endl;
	cout<<"----------x----------x----------x----------x----------x----------x--------------";
	//cout<<accno<<setw(10)<<name<<setw(20)<<addr<<setw(20)<<email<<setw(20)<<phno<<setw(20)<<occupation<<setw(20)<<loantype<<endl;
	//cout<<accno<<"\t\t"<<name<<"\t  "<<Addr<<"\t"<<email<<"\t"<<phno<<"\t"<<occupation<<"\t"<<loantype<<endl;
    break;
  }
else
{
   i++;
   if(i%max==0)
   i=0;
   }
} while(i!=addr);
 if(found==0)
 cout<<"\n Record does not exist in Hash file\n";
 sleep();
 return;

     }
    // gets(c);


}
   */
int hash(char key[])
{
  int i=0,sum=0;
  while(key[i]!='\0')
  {
    sum=sum+(key[i]-48);
    i++;
    }
 return sum % max;
 }

void store(int addr)
{
char dummy[10];
int flag=0,i;
file.open(customerfile,ios::in|ios::out);
file.seekp(addr*recsize,ios::beg);
file.getline(dummy,5,'\n');
if(strcmp(dummy,"####")==0)
{
 file.seekp(addr*recsize,ios::beg);
 file<<buffer;
 flag=1;
 }
 else
{
 for(i=addr+1;i!=addr;i++)
 {
  if(i%max==0)
	 i=0;
   file.seekg(i*recsize,ios::beg);
   file.getline(dummy,5,'\n');
   if(strcmp(dummy,"####")==0)
   {
     cout<<"\n Collision has occured\n";
     cout<<"Home address is"<<addr<<"Actual Address is"<<i<<"\n";
     file.seekp(i*recsize,ios::beg);
     file<<buffer;
     flag=1;
     break;
   }
 }
}
if(i==addr && (!flag))
cout<<"Hash file is full, Record cannot be inserted\n";
file.close();
return;
}

void customer::display()
{
 int i=0;
 char dummy[10];
 file.open(customerfile,ios::in|ios::out);
 cout<<"Accno"<<setw(5)<<"Name"<<setw(10)<<"Address"<<setw(10)<<"Email ID"<<setw(20)<<"Phone No."<<setw(10)<<"occupation"<<setw(10)<<"loan type"<<setw(10)<<endl;
	cout<<"--------------------------------------------------------------------------------";
 for(i=0;i<max;i++)
    {
  file.seekp(i*recsize,ios::beg);
  file.getline(dummy,5,'\n');
  if(strcmp(dummy,"####")==0)
    continue;
  file.seekp(i*recsize,ios::beg);
  file.getline(accno,5,'|');
    unpack();
	cout<<"";
    cout<<accno<<setw(5)<<name<<setw(10)<<Addr<<setw(10)<<email<<setw(20)<<phno<<setw(10)<<occupation<<setw(10)<<loantype<<setw(10)<<endl;
	cout<<"----------x----------x----------x----------x----------x----------x--------------";
      }
      file.close();
      getch();
      return;
 }


int customer::retrieve(int addr,char k[])
{
 int found=0,i;
 char dummy[5];
 i=addr;
 file.open(customerfile,ios::in|ios::out);
 do
 {
  file.seekg(i*recsize,ios::beg);
  file.getline(dummy,5,'\n');
  if(strcmp(dummy,"####")==0)
  break;
  file.seekg(i*recsize,ios::beg);
  file.getline(accno,5,'|');
  if(strcmp(accno,k)==0)
  {
    found=1;
	unpack();
	clrscr();
	cout<<"\n\nCustomer Record found : \n";
	cout<<"Accno"<<setw(5)<<"Name"<<setw(10)<<"Address"<<setw(10)<<"Email ID"<<setw(20)<<"Phone No."<<setw(10)<<"occupation"<<setw(10)<<"loan type"<<endl;
	cout<<"--------------------------------------------------------------------------------";
	cout<<accno<<setw(5)<<name<<setw(10)<<Addr<<setw(10)<<email<<setw(20)<<phno<<setw(10)<<occupation<<setw(10)<<loantype<<setw(10)<<endl;
	//cout<<"--------------------------------------------------------------------------------";
	//cout<<phno<<setw(20)<<occupation<<setw(20)<<loantype<<endl;
	cout<<"----------x----------x----------x----------x----------x----------x--------------";
	//cout<<accno<<setw(10)<<name<<setw(20)<<addr<<setw(20)<<email<<setw(20)<<phno<<setw(20)<<occupation<<setw(20)<<loantype<<endl;
	//cout<<accno<<"\t\t"<<name<<"\t  "<<Addr<<"\t"<<email<<"\t"<<phno<<"\t"<<occupation<<"\t"<<loantype<<endl;
    break;
  }
else
{
   i++;
   if(i%max==0)
   i=0;
   }
} while(i!=addr);
 if(found==0)
 cout<<"\n Record does not exist in Hash file\n";
 sleep();
 getch();
 return (found);
 }

/*void customer :: search (int addr,char k[])
{
 int found=0,i;
 char dummy[10];
 i=addr;
 file.open(customerfile,ios::in|ios::out);
 do
 {
  file.seekg(i*recsize,ios::beg);
  file.getline(dummy,10,'\n');
  if(strcmp(dummy,"####")==0)
	break;
  file.seekg(i*recsize,ios::beg);
  file.getline(accno,10,'|');
  if(strcmp(accno,k)==0)
  {
    found=1;
	cout<<"Record cannot be inserted, It is already present";
    break;
  }
else
{
   i++;
   if(i%max==0)
   i=0;
   }
} while(i!=addr);
 if(found==0)
    store(addr);
 sleep();
 return;
 }
*/

  void customer::modify(int addr)
 {
	 cout<<"\nEnter the Modified Details:\n";
	 Delete(addr);
 }


void main()
{
 int ch,addr,found;
 char skey[15];
 clrscr();
 //char team1[15],team2[15];
 gotoxy(20,7);
 textcolor(YELLOW);
 //cout<<"Enter the team 1 name: ";
 //cin>>team1;
 //gotoxy(20,9);
 //cout<<"Enter the team 2 name: ";
 //cin>>team2;
 customer s;
 clrscr();
 s.initial();
 for(;;)
 {
  clrscr();
  gotoxy(20,5);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  gotoxy(20,7);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  gotoxy(20,22);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  gotoxy(20,24);
  cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
  gotoxy(20,6);
  cout<<"                 MENU                   ";
  gotoxy(20,8);
  cout<<"Enter 1 To Add Customer Details. ";
  gotoxy(20,10);
  cout<<"Enter 2 To Display Customer Details. ";
  gotoxy(20,12);
  //cout<<"Enter 3 To Display the Customer Details: ";
  //gotoxy(22,13);
  cout<<"Enter 3 To Search & Modify the Customer Details. ";
  gotoxy(20,14);
  cout<<"Enter 4 To Search & Delete the Customer Details. ";
  gotoxy(20,16);
  cout<<"Enter 5 To Display All HASH File Records. ";
  gotoxy(20,18);
  cout<<"Enter 6 To Exit. ";
  gotoxy(20,20);
  cout<<"Enter Your Choice - ";
  cin>>ch;
  gotoxy(0,0);
  switch(ch)
 {
  case 1: clrscr();
	  cout<<endl<<"Enter Customer Details: "<<endl;
	  s.read();
	  addr=hash(s.accno);
	//  found=s.retrieve(addr,s.accno);
	 // if(found)
	store(addr);
	  //s.search(addr,s.accno);
	  cout<<"Done..."<<endl;
	  getch();
	  break;
  case 2:
	 clrscr();
	 gotoxy(20,8);
	 cout<<"Enter Account Number: ";
	 cin>>skey;
	 cout<<"Details of Acoount NO. - "<<skey<<" are -";
	 gotoxy(0,0);
	 addr=hash(skey);
	 s.retrieve(addr,skey);
	 break;
  case 5:
    clrscr();
	textcolor(YELLOW);
    s.display();
	break;
  case 3:
	 clrscr();
	 gotoxy(20,8);
	 cout<<"Enter Account Number: ";
	 cin>>skey;
	 gotoxy(0,0);
	 addr=hash(skey);
	 s.modify(addr);
	 s.read();
	 store(addr);
	 cout<<"Record is Successfully Updated... "<<endl;
	 getch();
	break;
  case 4:
	 clrscr();
	 gotoxy(20,8);
	 cout<<"Enter Account Number";
	 cin>>skey;
	 gotoxy(0,0);
	 addr=hash(skey);
	 s.Delete(addr);
	 cout<<"\nCustomer with "<<skey<<" is deleted Successfully.. ";
	 getch();
	break;
  case 6:cout<<"\n\n\n\n\n\t\t\t@@@@@....THANKING U....@@@@@@\n";
	 sleep();
		exit(0);
		textcolor(YELLOW);
		break;
  default:
	cout<<"\n\n\n\n\n\t !!!!!.......SORRY INVALID CHOICE, RE-ENTER THE CHOICE.......!!!!!\n";
	textcolor(WHITE);
	sleep();
     break;
 }
file.close();
}
}
