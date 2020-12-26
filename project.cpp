#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>


class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
        cout<<"\nNEW BOOK ENTRY\n";
        cout<<"\n Please enter the book no. \n";
        cin>>bno;
        cout<<"\n\n Please Enter The Title Of The Book. \n";
        gets(bname);
        cout<<"\n\n Please Enter The Author's Name \n";
        gets(aname);
        cout<<"\n\n\n BOOK CREATED SUCCESSFULLY";
    }

    void show_book()
    {
        cout<<"\n Book no. : "<<bno;
        cout<<"\n Title of the Book: ";
        puts(bname);
        cout<<"Author’s Name : ";
        puts(aname);
    }

    void modify_book()
    {
        cout<<"\n Book No. : "<<bno;
        cout<<"\n Modify Book Title : ";
        gets(bname);
        cout<<"\n Modify Author's Name: ";
        gets(aname);
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}


};  



class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
public:
    void create_student()
    {
        clrscr();
         cout<<"\n NEW STUDENT ENTRY \n";
        cout<<"\n Please Enter The admission No. ";
        cin>>admno;
        cout<<"\n\n Please Enter The Name of The Student ";
        gets(name);
        token=0;
        stbno[0]='/0';
        cout<<"\n\n STUDENT RECORD CREATED.";
    }

    void show_student()
    {
        cout<<"\n Admission No. : "<<admno;
        cout<<"\n Student Name : ";
        puts(name);
        cout<<"\n No of Book issued : "<<token;
        if(token==1)
            cout<<"\n Book No. "<<stbno;
    }

    void modify_student()
    {
        cout<<"\n Admission no. : "<<admno;
        cout<<"\n Modify Student Name : ";
        gets(name);
    }

    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {token=1;}

    void resettoken()
    {token=0;}

    void getstbno(char t[])
    {
        strcpy(stbno,t);
    }

    void report()
    {cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         

fstream fp,fp1;
book bk;
student st;



void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
        clrscr();
        bk.create_book();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\n\n Would you like to add more records?.Please     e       enter Y if your answer is ‘yes’.";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\n\n Would you like to add more records? Please                             e       enter Y if your answer is ‘yes’.";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}



void display_spb(char n[])
{
    cout<<"\n BOOK DETAILS \n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
             flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
        cout<<"\n\n Oops!This book does not exist.";
    getch();
}

void display_sps(char n[])
{
    cout<<"\n STUDENT DETAILS \n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.retadmno(),n)==0))
        {
            st.show_student();
            flag=1;
        }
    }
    
    fp.close();
    if(flag==0)
            cout<<"\n\n Oops! This student does not exist";
     getch();
}





void modify_book()
{
    char n[6];
    int found=0;
    clrscr();
    cout<<"\n\n\t MODIFYING BOOK RECORDS \n";
    cout<<"\n\n\t Please Enter The Book No.";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
            cout<<"\n Please Enter The New Details of                                                           B           book"<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\n\t Record Updated.";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n Oops! Record Not Found ";
        getch();
}


void modify_student()
{
    char n[6];
    int found=0;
    clrscr();
    cout<<"\n\n\t MODIFYING STUDENT RECORDS \n ";
    cout<<"\n\n\t Please Enter The Admission No. Of The           Student";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),n)==0)
        {
            st.show_student();
            cout<<"\n Please Enter The New Details of  student"<<endl;
            st.modify_student();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Record Updated.";
            found=1;
        }
    }
    
    fp.close();
    if(found==0)
        cout<<"\n\n Oops! Record Not Found ";
    getch();
}




void delete_student()
{
    char n[6];
    int flag=0;    
    clrscr();
        cout<<"\n\n\n\t DELETING STUDENT RECORDS \n ";
        cout<<"\n\n Please Enter The admission No. of the Student Whose Records Are To Be Deleted: ";
        cin>>n;
        fp.open("student.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }
        
    fp2.close();
        fp.close();
        remove("student.dat");
        rename("Temp.dat","student.dat");
        if(flag==1)
             cout<<"\n\n\t Record Deleted.";
        else
             cout<<"\n\n Oops! Record not found.";
        getch();
}


void delete_book()
{
    char n[6];
    clrscr();
    cout<<"\n\n\n\t DELETING BOOKS \n";
    cout<<"\n\n Enter The Book No. Of The Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=0)  
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }
        
    fp2.close();
        fp.close();
        remove("book.dat");
        rename("Temp.dat","book.dat");
        cout<<"\n\n\t Record Deleted. ";
        getch();
}




void display_alls()
{
    clrscr();
         fp.open("student.dat",ios::in);
         if(!fp)
         {
               cout<<"Oops! The file couldn’t be opened. ";
               getch();
               return;
         }

    cout<<"\n\n\t\t STUDENT LIST \n\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }
         
    fp.close();
    getch();
}

void display_allb()
{
    clrscr();
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"Oops! The file could not be opened.";
               getch();
               return;
         }

    cout<<"\n\n\t\t BOOK LIST \n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
         fp.close();
         getch();
}



void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
    clrscr();
    cout<<"\n\n ISSUING BOOKS \n";
    cout<<"\n\n\t Please Enter The Student's Admission No.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
        fp1.open("book.dat",ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                      cout<<"\n\n\t Please Enter the Book No. ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmpi(bk.retbno(),bn)==0)
                    {
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                               int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t Book issued. Please return within 15 days. Every day past the 15th day will attract a fine of one Rupee.";
                    }
                    }
                  if(flag==0)
                        cout<<"Oops! This book does not exist.";
            }
                else
                  cout<<"You have not returned the last book. ";

        }
    }
          if(found==0)
        cout<<"Oops! Student record not exist.";
    getch();
      fp.close();
      fp1.close();
}



void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\n DEPOSITING BOOKS \n";
    cout<<"\n\n\t Please Enter The Student’s Admission No.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmpi(bk.retbno(),st.retstbno())==0)
            {
                bk.show_book();
                flag=1;
                cout<<"\n\n Please Enter The Number Of Days In Which The Book Was Deposited";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*1;
                   cout<<"\n\n Fine: "<<fine;
                }
                    st.resettoken();
                    int pos=-1*sizeof(st);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Book deposited successfully.";
            }
            }
          if(flag==0)
            cout<<"Oops! This book does not exist";
              }
         else
            cout<<"Oops! No book is issued. Please check!!";
        }
       }
      if(found==0)
    cout<<"Oops! Student record does not exist.";
    getch();
  fp.close();
  fp1.close();
  }



void intro()
{
    clrscr();
    gotoxy(35,11);
    cout<<”WELCOME TO BIBLIOTECH.\n”
    cout<<"LIBRARY";
    gotoxy(35,14);
    cout<<"MANAGEMENT";
    gotoxy(35,17);
    cout<<"SYSTEM";
    cout<<"\n\n A Gupta-Sharma Production";
    getch();
}



void admin_menu()
{
    clrscr();
    int ch2;
    cout<<"\n\n\n\t ADMINISTRATOR MENU";
    cout<<"\n\n\t 1. CREATE STUDENT RECORDS";
    cout<<"\n\n\t 2. DISPLAY ALL STUDENTS RECORDS";
    cout<<"\n\n\t 3. DISPLAY A SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t 4. MODIFY STUDENT RECORDS";
    cout<<"\n\n\t 5. DELETE STUDENT RECORDS";
    cout<<"\n\n\t 6. CREATE A BOOK ";
    cout<<"\n\n\t 7. DISPLAY ALL BOOKS ";
    cout<<"\n\n\t 8. DISPLAY A SPECIFIC BOOK ";
    cout<<"\n\n\t 9. MODIFY A BOOK ";
    cout<<"\n\n\t 10. DELETE A BOOK ";
    cout<<"\n\n\t 11. GO BACK TO MAIN MENU";
    cout<<"\n\n\t Please Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: clrscr();
                write_student();break;
            case 2: display_alls();break;
            case 3:
                   char num[6];
                   clrscr();
                   cout<<"\n\n\t Please Enter The Admission No. ";
                   cin>>num;
                   display_sps(num);
                   break;
              case 4: modify_student();break;
              case 5: delete_student();break;
        case 6: clrscr();
            write_book();break;
        case 7: display_allb();break;
        case 8: {
                   char num[6];
                   clrscr();
                   cout<<"\n\n\t Please Enter The Book No. ";
                   cin>>num;
                   display_spb(num);
                   break;
            }
              case 9: modify_book();break;
              case 10: delete_book();break;
             case 11: return;
              default:cout<<"\a";
       }
       admin_menu();
}

void main()
{
    char ch;
    intro();
    do
    {
        clrscr();
        cout<<"\n\n\n\t MAIN MENU";
        cout<<"\n\n\t 1. BOOK ISSUE";
        cout<<"\n\n\t 2. BOOK DEPOSIT";
        cout<<"\n\n\t 3. ADMINISTRATOR MENU";
        cout<<"\n\n\t 4. EXIT";
        cout<<"\n\n\t Please Select Your Option (1-4) ";
          ch=getche();
          switch(ch)
          {
            case '1':clrscr();
                 book_issue();
                    break;
              case '2':book_deposit();
                     break;
              case '3':admin_menu();
                 break;
              case '4':exit(0);
              default :cout<<"\a";
        }
        }while(ch!='4');
}





       
