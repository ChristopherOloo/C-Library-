#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h> // use #include <windows.h> for windows
//where getc(stdin) replace with getch() for window & system("clear") replace with system("cls")
//pointers of global files
FILE *Vw=NULL,*fb=NULL,*fd=NULL,*fg=NULL,*fissue=NULL,*fuser=NULL,*fp=NULL;
//list of function prototypes used in the system
void home(void); 
void returnfunc(void);
void Librarian_password(void);  
void Librarian_home(void); 
void addbooks(void);
void searchbooks(void);
void editbooks(void);
void viewbooks(void);
void issued_record();
void issuebooks(void);
void deletebooks(void);
void returnbooks(void);
  
void User(void);
void Registration(void);

//Default Password of the Librarian
char lib_password[8] = "chrisgud";

//Book structure
struct Book
{
	int book_id;
	char Title[15];
	char Author[15];
	int quantity;
	int rack_no;	
};
struct Book sample;
//exit function for Exiting pages
void Exit(void)
{
	int i;
	for(i = 3;i>0; i--)
	{
		puts("pleas Wait...");
		sleep(1);
		printf("%d:-->",i);
		system("clear");
	}
	puts("You have succesfully exited");	
}
int main(void)
	{
		
		home();	
		return 0;
	}
struct login
{
char firstname[12];
char lastname[12];
char username[25];
char password[10];
};
/*Function  for searching books*/
void searchbook()
{
    int Book_id,a;
    char Book_title[16];
    system("clear"); // use system("cls") for windows
    fp = fopen("booksinfo.dat", "rb+");//opening a file to store books...
    if(fp==NULL) //if the file cannot be opened
    puts("Error opening file!");
    else //if the file has been opened
    {   
        puts("\t\t*************************** Search Book ******************************");
        puts("\tsearch by:---> 1.Book Id \t\t---> 2.Book Title \t\t --> 3.Exit");
        printf("Enter your choice:");
        scanf("%d",&a);
        struct Book sample;
        if (a == 1)
        {
                    printf("\t\tEnter book id:");
                    scanf("%d",&Book_id);
                    while(!feof(fp))
                    {
                        int results=fread(&sample,sizeof(sample),1,fp); //scaning the file for book id
                        if(results!=0 && Book_id==sample.book_id && sample.book_id!=0)// comparing the book ids
                        {
                            printf("\n\t\tThe Book Exists\n");
                            sleep(1);
                            printf("\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                            printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);
                        }
                                        
                    }
                    fclose(fp);
        }
        if (a == 2)
         {

                    printf("\t\tEnter book title:");
                    scanf("%s",Book_title);
                    while(!feof(fp))
                    {
                        int results=fread(&sample,sizeof(sample),1,fp);
                        if(results!=0 && strcmp(Book_title,sample.Title)==0)//comparing the book titles
                        {
                            printf("\n\t\tThe Book Exists\n");
                            printf("\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                            printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);                     
                        }
                        
                    }
                    fclose(fp);
         }
         if (a == 3)
            {
                // Librarian_home();
                // User_home()
            }
         
       
            else
            {
                searchbook();
            }
    }
}
//function for viewing books
void viewbooks(void)
{
    system("clear");
    fb = fopen("booksinfo.dat", "rb+");
	if (fb == NULL)
	{
		puts("Error opening the file");
	}
	else
	{
        puts("\t\t\t*********************** BOOK LIST **************************************");
        puts("\n\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************\n");

        printf("\t\t\t%6s %6s %6s %14s %23s\n", "BOOK ID","QUANTITY", "RACK No.","TITLE", "AUTHOR");
        struct Book sample;
        while(!feof(fb))
        {   
	        int results=fread(&sample,sizeof(sample),1,fb);
            if (results!=0 && sample.book_id != 0)// allows us to view books whose id is not 0
            {
                printf("\t\t\t%6d %6d %6d \t%16s \t%16s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);
            }
            
        }
        puts("\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************");
   
    }
    fclose(fb);
}
void User_home(void)
{
		system("clear");
		int n,r;
		puts("\n\n***************User Section********************\n");
		puts("\n*************************************************\n");
		puts("Select a task to perform from the list below:");
		puts("\t-->1.Search Books\n");
		puts("\t-->2.View Books\n");
		puts("\t-->3.Exit\n");
		puts("*************************************************");
		printf("\nEnter Your Choice:");
		scanf("%d",&n);
	switch (n)
	{
		case 1:
			searchbook();  //call Search book functin
            User_home();
            
            
			break;
		case 2:
			viewbooks();     //call viewbooks function
            puts("Press 1 to back");
            scanf("%d",&r);

            if (r==1) 
            {
                sleep(1);
                User_home(); //call user home function
            }
            else
            {
                viewbooks(); //call view book function
            }

			break;
		case 3:
                home(); //call home fxn to go back
			break;	
		default:
			system("clear");
			puts("INVALID CHOICE TRY AGAIN");
			User_home(); //for recursion of the function
			break;
	}
}
void login(void)
{
    FILE *log;
	system("clear");//reserve for windows system("cls")
	char username[25];
    char password[10];
	char correct = 'n'; // variable that allows us to exit a loop
    log=fopen("login.dat","rb+");//opening file for reading
    printf("\nEnter your user name and password to login\n");
    printf("\t\nUsername:");
    scanf("%s",username);
    printf("\t\nPassword:");
    scanf("%s",password);
    while(!feof(log) && correct == 'n')
    {

		struct login a;
		int result = fread(&a, sizeof(struct login), 1, log);
        if(result != 0 && strcmp(username,a.username) == 0 && strcmp(password,a.password) == 0)//compares if username and password matches those in login file
        {

            printf("Successful login!");
            printf("\nWelcome! %s",username);
			correct = 'y'; // allows us to exit the loop once the results have been found
            User_home();//User_home function
        }
    }
    if(correct == 'n')
        {
            printf("Please Enter correct UserName and password");
            login();
        }
    fclose(log);
}
void registration(void)
{
    system("clear");
	// struct login a;
	FILE *log = NULL; 
	log=fopen("login.dat","a+"); //open a login file for reading and updating
    rewind(log);
    char username[20],stop='n'; // stop allows us to exit a loop

	if (log == NULL) // if file cannot be opened
        {
            puts("ERROR! OPENING FILE!");
        }
	else
	{
		printf("\n\tEnter your username:");
		scanf("%s",username);
        while(!feof(log) && stop=='n')
        {
            struct login a;
            fread(&a,sizeof(struct login),1,log);
            if (strcmp(username,a.username)==0)
                {
                    puts("Username has already been taken");
                    stop='y';  
                    sleep(1);
                    registration();
                }
        }
        if (stop =='n')
            {
                struct login a;
                strcpy(a.username,username);
                printf("\n\tEnter your firstname:"); //append data into the login file
                scanf("%s",a.firstname);
                printf("\n\tEnter your lastname:");
                scanf("%s",a.lastname);
                printf("\n\tEnter your password not exceeding 10 characters:");
                scanf("%s",a.password);
                fwrite(&a,sizeof(struct login),1,log);
                printf("Your username is:%s\n",a.username);
                sleep(1);
            }
	}
	fclose(log);
 	login();    //call login function
}	
int Users(void)
{
	system("clear");
	puts("\t############################## LIBRARY SYSTEM #################################");
    printf("\n\n\t\t\t-->Press 1. to REGISTER \t\t-->Press 2. to LOGIN\n");
	puts("\n\t\t\t-->Press 3. to Exit");
    int num;
	printf("\n\n\t\tPlease enter what you wish to do:");
    scanf("%d",&num);
	if (num==1)
	{
		system("clear");
		printf("Welcome to registration page");
		registration();//call registration function
	}
	else if (num==2)
	{
	system("clear");
	printf("\nEnter your details below for verification");
	login();//call login function
	}
	else if (num==3)
	{
		system("clear");
		main();
	}
	else
	{
		system("clear");
		puts("Invalid stop");
		Users();
	}
	
 return 0;
}

//function home for the home page to the user
void home(void)
{
	system("clear");
	// system("color 0A"); //for windows
	puts("\t############################## LIBRARY SYSTEM #################################");
	puts("\n\t\t\t\tPlease select your Category\n"); //prompts user to enter his/her Category i.e User or Admin
	puts("\t\t\t........................................................."); 
	puts("\t\t\t\t--->1.LIbrarian \t\t --->2.Users");
	puts("\n\t\t\t\t--->3.Exit");
	puts("\t\t\t........................................................."); 
	printf("\t\t\tSelect your choice:");
	int n;
	scanf("%d",&n);
		switch(n)
		{
			case 1:
				Librarian_password();
				
				break;
				
			case 2:
				Users();
				break;
			case 3:
				Exit();
                exit(0);
				break;				
			default:
				system("clear");
				printf("\t Invalid Choice! Try Again\n");
				home();
		}
}
// Password for the Librarian to Log in

void Librarian_password()
{
	system("clear");
	char pass[8];
	
	printf("\t\tEnter Your Password:");
    scanf("%s",pass);

	if(strcmp(pass,lib_password)==0){
		system("clear");
		Librarian_home();
	}
	
	else{
		system("clear");
		printf("\n\t Incorrect Password! Try Again");
		sleep(3); //works in linux use delay for windows1
		Librarian_password();
		
	}

	
}
void issuebook(void)
{ 
    system("clear");
    system("clear");
    struct ISSUED
    {
        char username[20];
        int bookid;
        char booktitle[20];
    };
    struct ISSUED issued;
    int n,Book_id;
    int y,d;
    char option1='n',option2='n',username[12];
    fp = fopen("booksinfo.dat", "rb+");
    fissue = fopen("issue.dat", "a+");
    fuser=fopen("login.dat","rb+");
    if (fp==NULL && fissue==NULL && fissue==NULL)
        {
            puts("Error opening the file");
        }
    else
    {
        struct Book sample;
        struct login a;
        puts("\n\t************************** ISSUE BOOK SECTION *******************************");
        puts("\n\n\t*****************************************************************************");
        puts("\t*****************************************************************************");
        printf("\n\n\t\t--> 1.Issue a Book \t\t--> 2.View Issued Books\n");
        printf("\n\t\t--> 3.Search Issued Books \t--> 4.Remove Issued book\n");
        printf("\n\t\t--> 5.Exit\n");
        puts("\n\n\t*****************************************************************************");
        puts("\t*****************************************************************************");
        printf("\n\t\t Enter your choice :  ");
        scanf("%d",&n);
        switch (n)
        {
            case 1: //issue a book
            system("clear");
            printf("\n\t\tEnter the Book id to be issued:");
            scanf("%d",&Book_id);
            printf("\n\t\tEnter the username of the user:");
            scanf("%s",username);
            char book_title[20];
            int coun=0;
            while(!feof(fp) && option1=='n' )
                {
                    int results=fread(&sample,sizeof(struct Book),1,fp);
                    coun+=results;
                    if (results!=0 && Book_id==sample.book_id && sample.quantity>0)
                    {
                        fseek(fp,(coun-1)*sizeof(struct Book),SEEK_SET);
                        --sample.quantity;
                        fseek(fp,(coun-1)*sizeof(struct Book),SEEK_SET);
                        fwrite(&sample,sizeof(struct Book),1,fp);
                        strcpy(book_title, sample.Title);
                        printf("\t\t The Books Record is available");
                        sleep(1);
                        printf("\tBeing Issued to:%s",username);
                        printf("\n\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                        printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);				
                        option1 = 'y';
                    }
                    
                    
                }
            while(!feof(fuser) && option2=='n')
            {
                int results=fread(&a,sizeof(struct login),1,fuser);
                if (results!=0 && strcmp(username,a.username)==0)
                {
                    puts("username available");
                    option2='y';
                }
                
            }
                if(option2=='n') 
                {
                    //if user not in the system
                    printf("No such user exists\n\n");
                }
                if (option1=='n')
                    {
                        //if no book of such id is found
                        printf("\t\t No book of such Id exist");
                        sleep(1);  
                        issuebook();
                    }
                if (option1 == 'y' && option2=='y')
                    {
                        struct ISSUED issued;
                        sleep(1);
                        strcpy(issued.username,username);
                        issued.bookid=Book_id;
                        strcpy(issued.booktitle,book_title);
                        printf("Book issued succesfully");
                        fwrite(&issued,sizeof(struct ISSUED),1,fissue);
                        fclose(fp);
                        fclose(fissue);
                        fclose(fuser);
                        printf("\n\t\t Issue More Book? --> Press 1[yes]\t\t--> Press 2[no]:");
				        scanf("%d",&y);
                        if (y==1)
                        {
                            sleep(1);
                            issuebook();
                        }
                        else
                        {
                            issuebook();
                        }
                    }
                break;
            case 2://view issued books
                system("clear");
                fissue=fopen("issue.dat","rb+");
                if (fissue==NULL) 
                    {
                       puts("Error opening the file");
                    }
                else
                {
                    puts("\t\t\t***********************ISSUEDBOOK LIST **************************************");
                    puts("\n\n\t\t\t**********************************************************************");
                    puts("\t\t\t**********************************************************************\n");
                    printf("\t\t\t%12s %12s %14s\n", "Username", "Book Id","Book title");
                    struct ISSUED issued;
                    while(!feof(fissue))
                    {   
                        int results=fread(&issued,sizeof(struct ISSUED),1,fissue);
                        if (results!=0 && issued.bookid != 0)
                        {
                            printf("\t\t\t%12s %12d %14s\n",issued.username,issued.bookid,issued.booktitle);
                        }
                    }
                    
                    puts("\n\t\t\t**********************************************************************");
                    puts("\t\t\t**********************************************************************");

                }
                    printf("\t\t\t-->Press 1 to go back :");
                    scanf("%d",&d);
                    if (n==1)
                        {
                            issuebook();
                        }                    
                    fclose(fissue);
                break;
            case 3://search issued book
                system("clear");
                int stop;
                fissue=fopen("issue.dat","rb+");
                if (fissue==NULL)
                    {
                        puts("Error opening the file");
                    }
                else
                {
                      printf("Enter the book id: ");
                      scanf("%d",&Book_id); 
                      while(!feof(fissue))
                    {
                        int results=fread(&issued,sizeof(issued),1,fissue);
                        if(results!=0 && Book_id==issued.bookid && issued.bookid!=0)
                        {
                            printf("\n\t\tThe Book Exists\n");
                            sleep(1);
                            printf("\t\t\t%6s %6s %14s\n", "Username", "Book Id","Book title");
                            printf("\t\t\t%6s %6d %14s\n",issued.username,issued.bookid,issued.booktitle);
                           
                        }
                    }
                    fclose(fissue);
                    sleep(2);
                    issuebook();
                }
                    break;
                                                  
                case 4:// remove issued book
                    system("clear");
                    int Book_id;
                    char findbook='n';
                    fissue =fopen("issue.dat", "rb+");
                    fp=fopen("booksinfo.dat","rb+");
	                rewind(fissue);	// for taking file pointer to the begining of the file
                        printf("\t\t Enter the Book ID to Delete :  ");
                        scanf("%d",& Book_id);
                        struct ISSUED issued;
                        int count=0;        
		                while(!feof(fissue) && findbook=='n')
                        { 
                            int results=fread(&issued,sizeof(struct ISSUED),1,fissue);
                            count += results;
                            //finding if the user input matches book id in the system 
			                if(results !=0 && Book_id== issued.bookid )
                            {
                            fseek(fissue,(count-1)*sizeof(struct ISSUED),SEEK_SET);
                            ++sample.quantity;
                            fseek(fissue,(count-1)*sizeof(struct ISSUED),SEEK_SET);
                            printf("\t\t The Books Record is available\n");
                            sleep(1);
                            printf("\t\t\t%6s %6s %14s\n", "Username", "Book Id","Book title ");
                            printf("\t\t\t%6s %6d %14s\n",issued.username,issued.bookid,issued.booktitle);			
                            findbook = 'y';
                            }
		                }                        
                        int count1 =0;
                        while(!feof(fp)&& findbook == 'y')
                        {
                            struct Book sample;
                            int result1 = fread(&sample, sizeof(struct Book), 1 ,fp);
                                count1+= result1;
                             if(result1 !=0 && Book_id== sample.book_id )
                            {
                            fseek(fp,(count1-1)*sizeof(struct Book),SEEK_SET);
                            ++sample.quantity;
                            fseek(fp,(count1-1)*sizeof(struct Book),SEEK_SET);
                            fwrite(&sample,sizeof(struct Book), 1, fp);
                            }
                        }
                        
                        if(findbook =='n')
                        {
                            //if no book of such id is found
                            printf("\t\t No book of such Id exist");
                            issuebook();
                            sleep(2);
                        }
                        if (findbook =='y')
                        {
                            puts("\t\t\tAre you true to remove?-->Press 1.[Yes] -->2.[No]");
                            sleep(1);
                            scanf("%d",&stop);
                            switch (stop)
                            {
                                case 1:
                                    fseek(fissue,(count-1)*sizeof(struct ISSUED),SEEK_SET);
                                    struct ISSUED blank = {"",0,""};
                                    fseek(fissue,(count-1)*sizeof(struct ISSUED),SEEK_SET);
                                    fwrite(&blank,sizeof(struct ISSUED),1,fissue);
                                    fclose(fissue);
                                    sleep(1);
                                    issuebook();
                                    break;
                                case 2:
                                    issuebook();// call a function to exit this function                        
                                    break;
                                default:
                                    puts("Invalid option try again");
                                    issuebook();
                                    break;
                            }
                        }
                        break;
                case 5:
                    system("clear");
                    sleep(1);
                    Librarian_home();//call Librarian Home
                    break;         
                default:
                puts("Invalid stop");
                issuebook();
                break;
        }
    }
    fclose(fp);
    fclose(fuser);
    fclose(fissue);
}
void viewusers(void)
{
    system("clear");
    FILE *Vw;
    Vw=fopen("login.dat","rb+");
    if (Vw==NULL)
        {
            puts("Error opening the file!");
        }
    else
    {
        puts("\t\t\t*********************** USERS' LIST **********************************");
        puts("\n\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************\n");
        printf("\t\t\t%14s %12s %12s\n","USERNAME","FIRSTNAME","LASTNAME");
        struct login a;
        while(!feof(Vw))
        {
        int results=fread(&a,sizeof(struct login),1,Vw);
        if (results !=0)
            {
        
                printf("\t\t\t%12s %12s %12s\n",a.username,a.firstname,a.lastname);
            }
        }
        puts("\n\t\t\t**********************************************************************");
        puts("\t\t\t**********************************************************************");
    }
    fclose(Vw);
    int n;
    printf("\t\t\t --> Press 1. to back:");
    scanf("%d",&n);
    switch (n)
    {
        case 1:
            system("clear");
            Librarian_home(); //call librarian home
            break;
    
        default:
            system("clear");
            puts("\n\t\t\tInvalid stop\n");
            viewusers();
            break;
    }
    
   
}
//function Librarian for all  administrative use
void delete_users()
{
    FILE *log;
    system("clear");
    char stop='n',username[20];
    log=fopen("login.dat","rb+");
    if (log== NULL )
        {
            puts("Error opening the file!");
        }
    else
    {
        struct login a;
        int count=0;
        printf("\n\tEnter your username to delete:");
        scanf("%s",username);
        while(!feof(log) && stop == 'n')
            {
                int results=fread(&a,sizeof(struct login),1,log);
                count+=results;
                if (results!=0 && strcmp(username,a.username)==0)
                    {
                       printf("\n\tUser Available");
                       sleep(1);
                        printf("\n\t\t\t%14s %12s %12s\n","USERNAME","FIRSTNAME","LASTNAME");
                        printf("\t\t\t%12s %12s %12s\n",a.username,a.firstname,a.lastname);
                        stop='y';
                    }
                
            }
            if (stop=='n')
             {
                puts("User doesnt exist!");
                sleep(1);
                delete_users();    /* code */
            }
            if (stop=='y')
            {
               puts("Are you sure you want to delete?\t-->Press 1.[Yes] \t-->Press 2.[No]");
               printf("Enter your Choice:");
               int Choice;
               scanf("%d",&Choice);
               switch (Choice)
                {
                    case 1:
                        fseek(log,(count-1)*sizeof(struct login),SEEK_SET);
                        struct login blank = {"","","",""};
                        fseek(log,(count-1)*sizeof(struct login),SEEK_SET);
                        fwrite(&blank,sizeof(struct login),1,log);
                        puts("User Deleted...");
						sleep(2);
                        fclose(log);
						Librarian_home();
                        break;
                    case 2:
						puts("Please wait...");
						sleep(1);
                        Librarian_home();
                        break;                
                    default:
                        puts("Invalid stop try again");
                        delete_users();
                        break;
                }
            }
            
            

        
    }
}

 void edit_users()
 {
     FILE *log;
     system("clear");
     log=fopen("login.dat","rb+");
     char username[25],stop='n';
     if (log==NULL)
        {
            puts("Error opening the file");
        }
    else
    {
        int count=0;
        struct login a;
        printf("\n\t Enter username to edit:");
        scanf("%s",username);
        while(!feof(log) && stop=='n')
            {
                int result=fread(&a,sizeof(struct login),1,log);
                count+=result;
                if (result!=0 && strcmp(username,a.username)==0)
                    {
                        printf("User Available");
                        sleep(1);
                        printf("\n\t\t\t%14s %12s %12s\n","USERNAME","FIRSTNAME","LASTNAME");
                        printf("\t\t\t%12s %12s %12s\n",a.username,a.firstname,a.lastname);
                        stop='y';

                    }
            }
        if (stop=='n')
            {
               puts("No such Username exists");
               edit_users();
            }
        if (stop=='y')
            {
                puts("Continue editing? --> Press 1.[Yes] --> Press 2.[No]");
                sleep(1);
                int choice;
                scanf("%d",&choice);
                switch(choice)
                {
                    case 1:
                 fseek(log,(count-1)*sizeof(struct login),SEEK_SET);
                    printf("\n\tEnter New Username:"); //append data into the login file
                    scanf("%s",a.username);
                    printf("\n\tEnter New Firstname:");
                    scanf("%s",a.firstname);
                    printf("\n\tEnter New lastname:");
                    scanf("%s",a.lastname);
                    printf("\n\tEnter New Password:");
                    scanf("%s",a.password);
                    sleep(1);
                    fseek(log,(count-1)*sizeof(struct login),SEEK_SET);
                    fwrite(&a, sizeof(struct login),1 ,log);
                    fclose(log);
                    puts("\n\tUser succesfully edited");
                    puts("\n\tEdit another User?\t press 1.(Yes) or 2.(No)");
                    int n;
                    scanf("%d",&n);
                    if (n == 1)
                        {
                            edit_users(); 
                        }
                        else 
                        {
                        puts("Invalid option try again");
                        Librarian_home();
                        }
                    break;
                    case 2:
                    puts("\tPlease wait...");
                    sleep(1);
                    Librarian_home();
                    break; 
                    default:
                    puts("Invalid entry please try again");
                    edit_users();        
                 }
             }
    }
}   
void Librarian_home(void)
{
	int choice,n;
	system("clear");
	printf("\n\n\t\t*************** LIBRARIAN SECTION *************************\n");
    printf("\n\n\t\t***********************************************************\n");
	puts("\t\t***********************************************************");
	puts("\n\t\t\tSelect a task to perform from the list below");
    printf("\n\t\t\t--> 1.Add books\t\t--> 2.Delete books\n");
    printf("\n\t\t\t--> 3.Search books\t--> 4.View books\n");
    printf("\n\t\t\t--> 5.Issue books\t--> 6.Edit book records\n");
    printf("\n\t\t\t--> 7.View Users\t--> 8.Delete Users\n");
    printf("\n\t\t\t--> 9.Edit Users\t--> 10.Exit\n");
    puts("\n\t\t***********************************************************");
	puts("\t\t***********************************************************");
    printf("\t\t\tSelect your Choice:");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1: //call addbooks
			addbooks();
            puts("\t\tPress 1 to back");
            scanf("%d",&n);
            if (n==1)
            {
               sleep(1);
               Librarian_home(); 
            }
            else
            {
                addbooks();
            }
            
			break;
		
		case 2: //delete books
			deletebooks();
            puts("\t\tPress 1 to back");
            scanf("%d",&n);
            if (n==1)
            {
               sleep(1);
               Librarian_home(); 
            }
            else
            {
                deletebooks();
            }
            
			break;
			
		case 3://search books
			searchbook();
            Librarian_home(); 
            
			break;
			
		case 4: //view books
		    viewbooks();
            puts("\t\tPress 1 to back");
            scanf("%d",&n);
            if (n==1)
            {
               sleep(1);
               Librarian_home(); 
            }
            else
            {
                viewbooks();
            }
            
			break;

			
		case 5: //isssue books
			issuebook();
            puts("\t\tPress 1 to back");
            scanf("%d",&n);
            if (n==1)
            {
               sleep(1);
               Librarian_home(); 
            }
            else
            {
                issuebook();
            }
            
			break;
			
		case 6: //edit books
			editbooks();
            puts("\t\tPress 1 to back");
            scanf("%d",&n);
            if (n==1)
            {
               sleep(1);
               Librarian_home(); 
            }
            else
            {
                editbooks();
            }
            
			break;
			
		case 7: //view users
			viewusers();
			break;
		case 8: //Delete users
            delete_users();
            break;
        case 9: //edit users
           edit_users(); //call edit user function
           break;
        case 10: //exit function
            home();
            break;
		default:
			system("clear");
			
			// system("color 7C");
			printf("\t\t Invalid choice! Try Again");
			Librarian_home();
            break;
			
	}
}

//adding books
void addbooks(void)
{
    system("clear");
    puts("\t********************** Add Books ********************");
    int n,Book_id;
    FILE *fp;
    fp=fopen("booksinfo.dat","a+"); //open sample login file for appending and updating

	if (fp == NULL)
        {
            puts("ERROR! OPENING FILE!");
        }
    else 
    {
		
        struct Book sample;
        Book_id=sample.book_id;
		printf("\n\tEnter Book ID:"); //append data into the login file
		scanf("%d",&Book_id);
        while(!feof(fp))
        {
            fread(&sample,sizeof(struct Book),1,fp);
            if (Book_id==sample.book_id)
                {
                    puts("Book with similar Id exists");
                    sleep(1);
                    Book_id=0;
                    addbooks();
                }
        }
        
        if(Book_id!=0)
            { 
                sample.book_id=Book_id;
                printf("\n\tEnter Book Title:");
                scanf("%s",sample.Title);
                printf("\n\tEnter Book Author:");
                scanf("%s",sample.Author);
                printf("\n\tEnter Book rack no:");
                scanf("%d",&sample.rack_no);
                printf("\n\tEnter Quantity:");
                scanf("%d",&sample.quantity);

                if(sample.quantity < 1){
                    puts("Wrong qauntity... Enter valid numbers.");
                    addbooks();
                    sleep(2);
                }
                // fseek(fp,0,SEEK_END); // moving the file to the end allow appending of the next file
                sleep(2);
                fwrite(&sample, sizeof(struct Book),1 , fp);
                fclose(fp);
                puts("\n\tBook succesfully added");
                puts("\n\tAdd another book?\t press 1.(Yes) or 2.(No)");
                scanf("%d",&n);
                
                

                if (n == 1)
                    {
                        addbooks(); 
                    }
                
                else
                {
                   system("clear");
                   Librarian_home();                     
                }
            }
    }
} 

// function for deleting books from the record 
void deletebooks(void)
{
    system("clear");
    FILE *fp;
    int Book_Id;
    char findbook='n'; int stop;
	system("clear");
    fp =fopen("booksinfo.dat", "rb+");
	rewind(fp);	// for taking file pointer to the begining of the file
	if (fp == NULL)
        {
        puts("Error opening the file!");
        }
    else
    {  
        printf("\t\t Enter the Book ID to Delete :  ");
	    scanf("%d", &Book_Id);
	    
        struct Book sample;
        int count=0;        
		while(!feof(fp) && findbook=='n')
        { 
            int results=fread(&sample,sizeof(struct Book),1,fp);
            count += results;
			//finding if the user input matches book id in the system 
			if(results !=0 && sample.book_id==Book_Id && findbook=='n')
            {
				printf("\t\t The Books Record is available\n");
                sleep(1);
				printf("\n\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);				
				findbook = 'y';
			}
			
		}
		if(findbook =='n')
        {
			//if no book of such id is found
            printf("\t\t No book of such Id exist");
            deletebooks();
            sleep(2);
		}
        if (findbook =='y')
            {
                puts("\t\t\tAre you true to delete?-->Press 1.[Yes] -->2.[No]");
				printf("\t\t\tEnter your choice:");
                sleep(1);
                scanf("%d",&stop);
                switch (stop)
                {
                    case 1:
                        fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                        struct Book blank = {0,"","",0,0};
                        fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                        fwrite(&blank,sizeof(struct Book),1,fp);
                        puts("Book Deleted...");
						sleep(2);
                        fclose(fp);
						Librarian_home();
                        break;
                    case 2:
						puts("Please wait...");
						sleep(1);
                        Librarian_home();
                        break;                
                    default:
                        puts("Invalid option try again");
                        deletebooks();
                        break;
                }


            }
    }
}  

// function for editing books
void editbooks(void)
{
    system("clear");
    FILE *fp=NULL;
    int n,Book_id,choice;
    char stop='n';
    fp=fopen("booksinfo.dat","r+");
    rewind(fp);
    if (fp==NULL)
        {
            puts("Error opening File!!");
        }
    else
    {
        int count=0;
        struct Book sample;
        printf("\n\t\tEnter the Book id to edit:");
        scanf("%d",&Book_id);
       while(!feof(fp) && stop=='n')
        {
            int results=fread(&sample,sizeof(struct Book),1,fp);
            count+=results;
            if (results!=0 && Book_id==sample.book_id && stop=='n')
            {
                printf("\t\t The Books Record is available\n");
                sleep(1);
				printf("\t\t\t%6s %6s %6s %10s %10s\n", "Book Id","Quantity", "Rack No.","Title", "Author");
                printf("\t\t\t%6d %6d %6d \t%13s \t%s\n",sample.book_id,sample.quantity,sample.rack_no,sample.Title,sample.Author);				
				stop = 'y';
            }
            
        }
       
        if (stop=='n')
            {
                //if no book of such id is found
            printf("\t\t No book of such Id exist");
            editbooks();
            sleep(1);  
            }
        if (stop=='y')
        {
            puts("\t\t\tAre you true to edit-->Press 1.[Yes] -->2.[No]");
            sleep(1);
            scanf("%d",&choice);
            switch (choice)
            {
                case 1:
                    fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                    printf("\n\tEnter New Book ID:"); //append data into the login file
                    scanf("%d",&sample.book_id);
                    printf("\n\tEnter New Book Title:");
                    scanf("%s",sample.Title);
                    printf("\n\tEnter New Book Author:");
                    scanf("%s",sample.Author);
                    printf("\n\tEnter New  Book rack no:");
                    scanf("%d",&sample.rack_no);
                    printf("\n\tEnter New Quantity:");
                    scanf("%d",&sample.quantity);

                    if(sample.quantity < 1){
                    puts("Wrong qauntity... Enter valid numbers.");
                    addbooks();
                    sleep(2);
                }
                    // fseek(fp,0,SEEK_END); // moving the file to the end allow appending of the next file
                    sleep(2);
                    fseek(fp,(count-1)*sizeof(struct Book),SEEK_SET);
                    fwrite(&sample, sizeof(struct Book),1 , fp);
                    fclose(fp);
                    puts("\n\tBook succesfully edited");
                    puts("\n\tEdit another book?\t press 1.(Yes) or 2.(No)");
                    scanf("%d",&n);
                    if (n == 1)
                        {
                            editbooks(); 
                        }
                        else 
                        {
                        puts("Invalid stop try again");
                        Librarian_home();
                        }
                    break;
                case 2:
                puts("Please wait...");
                sleep(2);
                Librarian_home();
                break; 
				default:
				puts("Invalid entry please try again");
				editbooks();        
            }
        }
    }            
}

      
                
        
    
            
     
    
