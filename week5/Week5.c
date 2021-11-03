#include<stdio.h>
#include"btree.h"

int main()
{
  char pb[]= "phonebook.db";
  btinit();
  BTA *book;
  book=btopn(pb, 0, 0);
  if(book==NULL)
    {
      book=btcrt(pb,0, 0);
    }
char name[20];
  long int  pn;
  int search;
  int check;
  char c;
  int ch;
  do
{
	system("cls");
printf("\t\t**********WELCOME TO PHONEBOOK*************");

printf("\n\n\t\t\t  MENU\t\t\n\n");
printf("\t1.Add Number   \t2.Search   \t3.Delete Number  \n\t4.Exit");

switch(ch)
{
	case '1':
		printf("\n Enter name: ");
        scanf("%s",&name);check=bfndky(book, name, &search);
		if(check==0)
		  {
		    printf("Already existed!.\nDo you want update(y/n):");
		    scanf("%c",&c);
		    if(c=='y')
		      {
			printf("Enter phone number: ");
			scanf("%ld",&pn);
			bupdky(book,name,pn);
		      }
		  }
		else
		  {
		    printf("Enter phone number: ");
		    scanf("%ld",&pn);
		    binsky(book,name, pn);
		  }
		break;
                
    
   case '2': 
        printf("\nEnter name of person to search\n");
        scanf("%s",&name);
        check=bfndky(book,name,&search);
	    if(check==0)
	      {
		printf("%i\n",search);
	      }
	    else
	      {
		printf("Person not found\n");
	      }	    
	    break;
	    
    case '3': deletenumber();
        printf("Enter CONTACT'S NAME:");
		scanf("%s",&name);
		if(check!=1)
		{
		printf("NO CONACT'S RECORD TO DELETE.");
		}
		else {
			bdelky(book,name);
		}
		break;
    case '4':
    	printf("Exit!\n");
	    btcls(book);
	    ch=0;
	    break;
   
    
    
    default:
                system("cls");
                printf("\nEnter 1 to 4 only");
                printf("\n Enter any key");
                getch();
    
}}
while (ch!=0);}

