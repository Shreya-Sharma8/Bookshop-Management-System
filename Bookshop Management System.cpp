/* TOPIC:: BOOKSHOP MANAGEMENT SYSTEM

   MAIN FUNCTIONS PERFORMED BY THE SYSTEM:: add books,update books,delete boooks,
                                            show books,search a book,check availability of a book,
                                            add customer details,show customer details,
											add to cart,view cart,generate a bill
   MADE BY:: 
   			NAMES:-SHREYA SHARMA
*/

   
#include<fstream>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<cstdio>
#include<iomanip>
using namespace std;
 
class transaction
{
	protected:
	    char name[50],author_name[50],genre[50];
        int isbn,quantity;
        float price,disc,sum,cost,fcost;
	public:
		void bill() //generates the bill for the books purchased by the customer
	    {
	    	ifstream cart;
		    cart.open("cart.txt", ios::in);
		    if (!cart)
		    {
		    	cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
		        cout<<"\nFile Opening Error!\n"; 
				cout<<"\n******NO ITEMS IN YOUR CART!******\n";
				cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
				return;
			}
		    else 
			{
				cout<<"YOUR CART ITEMS ARE AS FOLLOWS : - ";
				cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
                cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<setw(25)<<"Per piece Cost"<<setw(15)<<"Final Cost"<<endl;
			 	cart>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        while (!cart.eof())
				{
		            cost=(price-(price*(disc/100)));
	                fcost=cost*quantity;
			    	cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<setw(25)<<cost<<setw(15)<<fcost<<endl;
				    sum=sum+fcost;
				    cart>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        }
		    }
		    cout<<"\n******YOUR FINAL BILL IS : "<<sum<<" Rupees******\n";
		    cout<<"\n******THANK YOU FOR SHOPPING!!!******\n";
		    cout<<"\n---------------------------------------------------------------------------------------------------------------------\n";
	        cart.close();	
	        remove("cart.txt");
	    }
};
 
class customer:public 	transaction
{
	protected:
		char c_name[50],hno[50],street[50],gen;
		int mob,age;
	public:
		void customer_details() //stores the customer's details in a file
		{
			fstream cust;
		    cout<<"\nENTER DETAILS OF THE CUSTOMER::\n";
		    cout<<"\nName: ";
		    fflush(stdin);
		    cin>>c_name;
		    cout<<"\nAge: ";
		    cin>>age;
		    cout<<"\nGender(M:MALE , F:FEMALE): ";
		    cin>>gen;
		    cout<<"\nMobile Number: ";
		    cin>>mob;
		    cout <<"\nAddress:(hno and street) :\n";
		    fflush(stdin);
	        cin>>hno;
	        fflush(stdin);
	        cin>>street;
	        
		    cust.open("customer.txt",ios::out | ios::app);
		    cust<<c_name<<"\t\t"<<age<<"\t\t"<<gen<<"\t\t"<<mob<<"\t\t"<<hno<<"\t"<<street<<"\n";
		    cust.close();
		}
		void show_customer_details() //displays the details of the customer who have visited the bookshop
		{
			fstream cust;
			cust.open("customer.txt", ios::in);
		    if (!cust)
		        cout<<"\nFile Opening Error!\n";   
            else
			{
				cout<<"\n Customer details are as follows ::--\n";
				cout<<"------------------------------------------------------------------------------------------------------------------\n";
			   	cout<<"NAME"<<setw(18)<<setfill(' ')<<"AGE"<<setw(15)<<"GENDER"<<setw(15)<<"MOBILE NO"<<setw(18)<<"ADDRESS"<<endl;
				cust>>c_name>>age>>gen>>mob>>hno>>street;
				while(!cust.eof()) 
				{
					cout<<c_name<<setw(15)<<age<<setw(15)<<gen<<setw(15)<<mob<<setw(15)<<hno<<" "<<street<<endl;
					cust>>c_name>>age>>gen>>mob>>hno>>street;
				}
				cout<<"------------------------------------------------------------------------------------------------------------------\n";
			}
			cust.close();
		}
	    void add_to_cart() //customer can add the books he wants to purchase here
	    {
	    	ifstream book;                  
	        int isbno,qn,count=0,choice; 
	        fstream cart;
	        if(!cart)
	            fstream cart("cart.txt");
	        do
	        {
		    book.open("book.txt", ios::in);
		    if (!book)
		        cout<<"\nFile Opening Error!";   
		    else 
			{
				ofstream book1("book1.txt");
				cart.open("cart.txt",ios::out | ios::app);
	            cout<<"\nEnter the ISBN number of the book which you want to save to your cart : ";
			 	cin>>isbno;
			 	book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        while (!book.eof())
				{
				    if (isbn==isbno) 
					{
						count++;
			            cout<<"------------------------------------------------------------------------------------------------------------------\n";
						cout<<"\n******BOOK Found!!!******\n";
						cout<<"\n Book details are as follows ::--\n";
						cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
						cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
						cout<<"\nEnter the quantity of the book : ";
						cin>>qn;
	                    cart<<isbn<<"\t\t"<<name<<"\t\t"<<author_name<<"\t\t"<<genre<<"\t\t"<<price<<"\t\t"<<qn<<"\t\t"<<disc<<"\n";
	                    cout<<"\n*******Book Saved into your Cart!!*******\n";
	                    cout<<"------------------------------------------------------------------------------------------------------------------\n";
	                    if(quantity-qn !=0)
		                	book1<<isbn<<"\t\t"<<name<<"\t\t"<<author_name<<"\t\t"<<genre<<"\t\t"<<price<<"\t\t"<<quantity-qn<<"\t\t"<<disc<<"\n";
					}
					else
						book1<<isbn<<"\t\t"<<name<<"\t\t"<<author_name<<"\t\t"<<genre<<"\t\t"<<price<<"\t\t"<<quantity<<"\t\t"<<disc<<"\n";
		            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        }
		        book1.close();
	            book.close();
	            remove("book.txt");
				rename("book1.txt","book.txt");	
	            cart.close();
			    if (count == 0)
			    {
			    	cout<<"------------------------------------------------------------------------------------------------------------------\n";
			    	cout<<"\n******BOOK NOT FOUND , Try Again****** \n";
			    	cout<<"------------------------------------------------------------------------------------------------------------------\n";
				}
				cout<<"\nDo you want to add another book to your cart :: Enter 1:YES 0:NO :- ";
				cin>>choice;	
		    }
		    }while(choice);
		}
		void show_cart() //customer can view the books added to his cart by him before billing
        {
	    	ifstream cart;
	        int isbno,count=0;
	    	cart.open("cart.txt",ios::in);
	    	if(!cart)
	    	{
	    		cout<<"\n******YOUR CART IS EMPTY******\n";
	    	}
	    	else
	    	{
		    	cout<<"\n------------------------------------------------------------------------------------------------------------------\n";
		    	cout<<"|||||| YOUR CART |||||||\n";
		    	cart>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		    	cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
		    	while(!cart.eof())
		    	{
		    		cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
		    		cart>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		    		count++;
		    	}
				if(count==0)
				{
					cout<<"------------------------------------------------------------------------------------------------------------------\n";
					cout<<"\n******YOUR CART IS EMPTY******\n";
				}
		 		cout<<"------------------------------------------------------------------------------------------------------------------\n";
		 	}
	    }
	    
	    void show_book() // this function displays all the books cureently in the bookshop
		{
		    fstream book;
		    book.open("book.txt",ios::in);
		    if (!book)
		        cout<<"\nFile Opening Error!\n";
		    else 
			{
				cout<< "\n*****BOOKS CURRENTLY IN THE BOOKSHOP ARE:*****\n";
		    	cout<<"------------------------------------------------------------------------------------------------------------------\n";
		        cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
		        book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        while (!book.eof()) 
				{
		
		            cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
		            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        }
		        cout<<"------------------------------------------------------------------------------------------------------------------\n\n";
		        book.close();
		    }
       }
	    void check_availability(int isbno) //function used to check if a book is available or not in the bookshop(using isbn no of the book) 
	    {
		    fstream book;
		    int count = 0;
		    book.open("book.txt", ios::in);
		    if (!book)
		        cout<<"\nFile Opening Error!";
		    else 
			{
		  
		        book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        while (!book.eof())
				{
		  
		            if (isbno==isbn) 
					{
						cout<<"------------------------------------------------------------------------------------------------------------------\n";
						cout<<"\n********BOOK AVAILABLE!!!**********\n";
						cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
						cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
		                cout<<"\n------------------------------------------------------------------------------------------------------------------\n";
						count++;
		                break;
		            }
		            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        }
	            book.close();
		        if (count == 0)
		        {
	                cout<<"------------------------------------------------------------------------------------------------------------------";
		            cout<<"\n*******BOOK OUT OF STOCK*******\n";
		            cout<<"------------------------------------------------------------------------------------------------------------------\n";
		        }
	        }
	    }
	    void search_book()// one can search a particular book in the bookshop using different parameters
	    {
		    fstream book;
		    int ch;
		    char nm[50],aname[50],gen[50];
	        int isbno,count=0;
		    book.open("book.txt", ios::in);
		    if (!book)
		        cout<<"\nFile Opening Error!";   
		    else 
			{
				cout<<"---------------------------------------------------------------------------------------------------------------------\n";
		        cout<<"\nPress 1 to to search by NAME";
		        cout<<"\nPress 2 to to search by AUTHOR'S NAME";
		        cout<<"\nPress 3 to to search by GENRE\n";
			 	cin>>ch;
			 	switch(ch)
			 	{
					case 1: cout<<"\nENTER BOOK NAME:: ";
		                    cin>>nm;
		                    book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		                    while (!book.eof())
							{
					            if (strcmp(name,nm)==0) 
								{
									cout<<"---------------------------------------------------------------------------------------------------------------------\n";
									cout<<"*******BOOK AVAILABLE!!!*******\n";
								    cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
									cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
					                count++;
					            }
					            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
					        }
				            book.close();
					        if (count == 0)
					        {
					            cout<<"------------------------------------------------------------------------------------------------------------------\n";
					            cout<<"\n******BOOK NOT FOUND******\n";
					            cout<<"------------------------------------------------------------------------------------------------------------------\n";
					        }
					        break; 	
					case 2: cout<<"\nENTER AUTHOR'S 'NAME:: ";
		                    cin>>aname;
		                    book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		                    while (!book.eof())
							{
					            if (strcmp(author_name,aname)==0) 
								{
									cout<<"------------------------------------------------------------------------------------------------------------------\n";
									cout<<"\n******BOOK AVAILABLE!!!******\n";
									cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
								    cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
					                cout<<"------------------------------------------------------------------------------------------------------------------\n";
									count++;
					            }
					            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
					        }
				            book.close();
					        if (count == 0)
					        {
							    cout<<"------------------------------------------------------------------------------------------------------------------\n";
					            cout<<"\n******BOOK NOT FOUND******\n";
					            cout<<"------------------------------------------------------------------------------------------------------------------\n";
					        }
					        break; 	
					case 3: cout<<"\nENTER THE GENRE:: ";
		                    cin>>gen;
		                    book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		                    while (!book.eof())
							{
					            if (strcmp(gen,genre)==0) 
								{
						            cout<<"------------------------------------------------------------------------------------------------------------------\n";
									cout<<"\n******BOOK AVAILABLE!!!*******\n";
									cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
									cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
					                cout<<"------------------------------------------------------------------------------------------------------------------\n";
								    count++;
					            }
					            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
					        }
				            book.close();
					        if (count == 0)
					            cout<<"\nBOOK NOT FOUND\n";
					        break; 	
				}
						
			}
		}
};
 
class admin:public customer
{                     
    public:
    	void add_book()    //admin can add new books to the bookshop
						   //(assumption:book name, author name are one word non-spaced strings)
		{
		    fstream book;
		    cout<<"\nENTER BOOK DETAILS TO ADD BOOK";
		    cout<<"\nISBN Number: ";
		    cin>>isbn;
		    cout<<"\nBook Name: ";
		    fflush(stdin);
		    cin>>name;
		    cout <<"\nAuthor Name: ";
		    fflush(stdin);
		    cin>>author_name;
		    cout <<"\nGenre: ";
		    fflush(stdin);
		    cin>>genre;	
		    cout <<"\nPrice of Book: ";
		    cin>>price;
		    cout<<"\nNumber of Books : ";
		    cin>>quantity;
		    cout <<"\nDiscount on Book: ";
		    cin>>disc;
	
		    book.open("book.txt",ios::out | ios::app);
		    book<<isbn<<"\t"<<name<<"\t"<<author_name<<"\t"<<genre<<"\t"<<price<<"\t"<<quantity<<"\t"<<disc<<"\n";
		    book.close();
		}
		void update_book() //function used to update book parameters if required
	    {
		    fstream book;
	        int isbno,count=0,choice,num=1;
		    book.open("book.txt", ios::in | ios::out);
		    if (!book)
		        cout<<"\nFile Opening Error!";   
		    else 
			{
				ofstream book1("book1.txt");
	            cout<<"Enter the ISBN number of the book that you want to update : ";
			 	cin>>isbno;
		        book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        while (!book.eof())
				{
				    if (isbn==isbno) 
					{
						cout<<"------------------------------------------------------------------------------------------------------------------\n";
						cout<<"\n******BOOK Found!!!******\n";
						cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
						cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
					    do
					    {
					    	cout<<"\nEnter the field you want to update \n1:ISBN no. || 2:Book Name || 3:Author Name || 4:Genre || 5:Price || 6:Quantity || 7:Discount ::- ";
					        cin>>choice;
						    switch(choice)
					        {
					    	case 1:
					    		cout<<"\nEnter the new ISBN No. : ";
					    		cin>>isbn;
					    		break;
					    	case 2 :
					    		cout<<"\nEnter the new Book Name : ";
					    		cin>>name;
					    		break;
					    	case 3 :
					    		cout<<"\nEnter the new Author Name : ";
					    		cin>>author_name;
					    		break;
					    	case 4 :
					    		cout<<"\nEnter the new Genre : ";
					    		cin>>genre;
					    		break;
					    	case 5 :
					    		cout<<"\nEnter the new price : ";
					    		cin>>price;
					    		break;
					    	case 6 :
					    		cout<<"\nEnter the new quantity : ";
					    		cin>>quantity;
					    		break;
					    	case 7 :
					    		cout<<"\nEnter the new Discount : ";
					    	    cin>>disc;
					            break;
					    	default :
					    		cout<<"INVALID CHOICE , TRY AGAIN ";
					    	}
					    	cout<<"Do you want to update more fields of this book : 1 for yes || 0 for no :- ";
					    	cin>>num;
						}while(num);    
				        count++;
		            }
		            book1<<isbn<<"\t\t"<<name<<"\t\t"<<author_name<<"\t\t"<<genre<<"\t\t"<<price<<"\t\t"<<quantity<<"\t\t"<<disc<<"\n";
		            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        }
	            book.close();
	            book1.close();
			    if (count == 0)
			    {
			    	cout<<"------------------------------------------------------------------------------------------------------------------\n";
			    	cout<<"\n******BOOK NOT FOUND******\n";
			    	cout<<"------------------------------------------------------------------------------------------------------------------\n";
			    	remove("book1.txt");
			    	return;
				}
				else
				{
					cout<<"------------------------------------------------------------------------------------------------------------------\n";
					cout<<"\n******BOOK RECORD UPDATED******\n";
					cout<<"------------------------------------------------------------------------------------------------------------------\n";
				}
				remove("book.txt");
				rename("book1.txt","book.txt");		
		    }
	    }
	    void remove_book() //admin can delete certain books from the bookshop
	    {
		    fstream book;
		    int isbno;
		    int count=0;
		    book.open("book.txt", ios::in | ios::out);
		    if (!book)
		        cout<<"\nFile Opening Error!";   
		    else 
			{
				ofstream book1("book1.txt");
	            cout<<"Enter the ISBN number of the book that you want to delete : ";
			 	cin>>isbno;
			 	book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        while (!book.eof())
				{
				    if (isbn==isbno) 
					{
						count++;
						cout<<"------------------------------------------------------------------------------------------------------------------\n";
						cout<<"\n******BOOK Found!!!******\n";
						cout<<"\n Book details are as follows ::--";
						cout<<"Book ID"<<setw(12)<<setfill(' ')<<"Book Name"<<setw(15)<<"Author Name"<<setw(15)<<"Genre"<<setw(15)<<"Price"<<setw(15)<<"Quantity"<<setw(15)<<"Discount"<<endl;
						cout<<isbn<<setw(15)<<name<<setw(15)<<author_name<<setw(15)<<genre<<setw(15)<<price<<setw(15)<<quantity<<setw(15)<<disc<<endl;
					    cout<<"\n*****BOOK RECORD DELETED*******";
					    cout<<"------------------------------------------------------------------------------------------------------------------\n";
		            }
		            else
		                book1<<isbn<<"\t\t"<<name<<"\t\t"<<author_name<<"\t\t"<<genre<<"\t\t"<<price<<"\t\t"<<quantity<<"\t\t"<<disc<<"\n";
		            book>>isbn>>name>>author_name>>genre>>price>>quantity>>disc;
		        }
	            book.close();
	            book1.close();
			    if (count == 0)
			    {
			    	cout<<"------------------------------------------------------------------------------------------------------------------\n";
			    	cout<<"\nBOOK NOT FOUND \n";
			    	cout<<"------------------------------------------------------------------------------------------------------------------\n";
			    	remove("book1.txt");
			    	return;
				}
				remove("book.txt");
				rename("book1.txt","book.txt");		
		    }
	    }
};
  
int main()
{
    int choice,ch,chh,isbn;
    
	admin ad;              //Derived class from Multilevel Inheritance
	 
    cout<<setw(100)<<setfill('*')<<" WELCOME TO THE BOOKSHOP MANAGEMENT SYSTEM "<<setw(72)<<setfill('*')<<"\n\n\n";
    do
    {
        cout<<setw(60)<<setfill('#');
        cout<<"\n****** MAIN MENU ******\n";
        cout<<"\nPress 1 to ADMIN MENU";
        cout<<"\nPress 2 to CUSTOMER MENU";
        cout<<"\nPress 3 to EXIT\n";
	    cout<<setw(55)<<setfill('#');
	 	cout<<"\n\nENTER THE CHOICE: ";
	 	cin>>choice;
	 	switch(choice)
	    {
	    	case 1:do
		           {
				        cout<<setw(125)<<setfill('#');
				        cout<<"\nPress 1 to TO ADD BOOKS";
				        cout<<"\nPress 2 to SHOW ALL BOOKS";
				        cout<<"\nPress 3 to CHECK AVAILABILITY";
				        cout<<"\nPress 4 to SEARCH A BOOK";
				        cout<<"\nPress 5 to UPDATE BOOKS";
				        cout<<"\nPress 6 to DELETE BOOKS";
				        cout<<"\nPress 7 to SHOW CUSTOMER RECORD";
				        cout<<"\nPress 8 to GO TO MAIN MENU\n";
					    cout<<setw(120)<<setfill('#');
					 	cout<<"\n\nENTER THE CHOICE: ";
					 	cin>>chh;
					 	switch(chh)
					    {
					        case 1:do 
							      {
				                    ad.add_book();
				                    cout<<"\nDo you want to add more books? (Enter 0 for No and 1 for Yes):";
				                    cin>>ch;
				                  } 
							      while (ch==1);
				                  break;
					        case 2:ad.show_book();
					               break;
					        case 3:int isbn;
					               cout<<"\nPlease Enter the ISBN number of book::";
					               cin>>isbn;
					               ad.check_availability(isbn);
					               break; 
							case 4:ad.search_book();
							       break;	              
					        case 5:ad.update_book();
							       break;
					        case 6:ad.remove_book();
							       break; 
							case 7:ad.show_customer_details();
							       break;	     	  
							case 8:break;
							default:cout<<"\n******INVALID CHOICE******\n";	             
					    }
					}
				    while(chh!=8);
				    break;
			case 2:do
				    {
				        cout<<setw(125)<<setfill('#');
				        cout<<"\nPress 1 to TO ADD YOUR DETAILS(if first visit)";
				        cout<<"\nPress 2 to SHOW ALL BOOKS";
				        cout<<"\nPress 3 to CHECK AVAILABILITY";
				        cout<<"\nPress 4 to SEARCH A BOOK";
				        cout<<"\nPress 5 to ADD TO CART";
				        cout<<"\nPress 6 to VIEW YOUR CART";
				        cout<<"\nPress 7 to GENERATE A BILL";
				        cout<<"\nPress 8 to GO TO MAIN MENU\n";
					    cout<<setw(120)<<setfill('#');
					 	cout<<"\n\nENTER THE CHOICE: ";
					 	cin>>chh;
					 	switch(chh)	    
					 	{
					 		case 1:ad.customer_details();
					               break;
					 		case 2:ad.show_book();
					               break;
					        case 3:int isbn;
					               cout<<"\nPlease Enter the ISBN number of book::";
					               cin>>isbn;
					               ad.check_availability(isbn);
					               break; 
							case 4:ad.search_book();
							       break;	              
							case 5:ad.add_to_cart();
					               break;
							case 6:ad.show_cart();
							        break; 
							case 7:ad.bill();
					               break;		       
					        case 8:break; 
							default:cout<<"\n******INAVALID CHOICE******\n";           
					    }
					}
					while(chh!=8);
					break;
			case 3:exit(0);		
		}
	}
	while(choice!=3);
	return 0;
}
