// Karolina Szafran - Belzowska, November 2020
// Project Multi Paradigm Programming, Shop Assignment


// call libraries in C
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// to compile and print shop.c in Command Prompt I have to type the following:
// gcc -o shop shop.c
// shop.exe


// A struct (keyword) is used to create a structure and group data together.
// A structure creates a data type that can be used to group items of possibly different types into a singe type.
// https://www.geeksforgeeks.org/structures-c/ 15/11/2020

struct Product // Product Struct for product informations
{
	char *name;	     // name refers to a pointer, so when dereferenced, name is a char. In this case a pointer initialized to a string located in read-only memory.
	double price;	//  Double = decimal number
};

struct ProductStock  // ProductStock Struct for stock informations
{
	struct Product product; // Nested Struct
	int quantity;
};

struct Customer // Customer Struct for customer informations
{
	char *name;
	double budget;
	struct ProductStock shoppingList[10]; // Nested struct - An Array of 10 elements.
	int index;
};

struct Shop // Shop Struct for shop infomations
{
	double cash;
	struct ProductStock stock[20];
	int index;
};



// ================================================================================================================================================================================

// Void when used as a function return type, the void keyword specifies that the function does not return a value.
// Void does not provide a result value to its caller. Those functions are called for their side effects, such as performing some task or writing to their output parameters.
// https://docs.microsoft.com/en-us/cpp/cpp/void-cpp?view=msvc-160, 15/11/2020
// https://en.wikipedia.org/wiki/Void_type, 15/11/2020

// printProduct() and printProduct2 functions will be used to print product informations
void printProduct(struct Product p)
{
	printf(" Product : %s \n Price   : %.2f\n ", p.name, p.price); // Print the product name and its price. 
}                                                                  // When you press 1st option in the Menu selection, this name and price will be given as output. 


void printProduct2(struct Product p)
{
	printf("Product : %s  \n", p.name); //Print just the product's name
}

// ================================================================================================================================================================================



void printCustomer(struct Customer c, struct Shop s)	// Two Structs will be used  in function printCustomer
{
	printf("\nCustomer name   : %s \nCustomer budget : %.2f\n", c.name, c.budget); // Print customer's name and budget
	printf("====================================\n");
	printf("\n");

	double sum = 0;

	for (int i = 0; i < c.index; i++) // Start loop through each of the items in the shopping list 
	{
		int sQuantity = s.stock[i].quantity;
		int cQuantity = c.shoppingList[i].quantity; // quantity bought (customer) is initialising to the quantity request.
			
		printProduct2(c.shoppingList[i].product); // Print the product informations

		printf("Quantity: %d\n\n", c.shoppingList[i].quantity); // Print how much of each item the customer wants
		
		if (cQuantity > sQuantity) // if the customer order is more than the shop quantity then display message below.
		{
			printf("Not enough in the shop, Appologize for any inconvenience caused\n");
		}
		
		else{	
		double total = c.shoppingList[i].quantity *c.shoppingList[i].product.price; // total customer's cost
		sum = sum + total;
		}
		
		printf("------------------------------------\n");

	}
	
	// Print the total cost of the customer items
	printf("Total cost = %.2f\n", sum);

	// Once all the customer items are added, minus from the budget
	printf("Budget balance = %.2f\n", c.budget - sum);
}


void printShop(struct Shop s) // option no 1 in the Menu
{
	printf("\n");
	printf("--------------------------------------------------\n");
	printf("Cash in the Shop: EUR %.2f \n", s.cash); // print how much cash Store has in cash. Taken from stock.csv file
	printf("--------------------------------------------------\n");
	printf("Credit/Debit card payments acceptable in this Shop\n"); // just to inform customers that card payments are avilable
	printf("--------------------------------------------------\n");
	printf("\n");
	printf("\n");

	for (int i = 0; i < s.index; i++) // 'for' loop displays the stock details to the output
	{
		printProduct(s.stock[i].product);

		printf("Quantity: %d\n", s.stock[i].quantity); // When you press 1st option in Menu selection, this quantity will be given as output.

		printf("------------------------------------\n");

	}
}

struct Customer cusOrder()
{
	struct Customer customer = { 0 };

	FILE * fp;

	char *line = NULL;

	size_t len = 0;

	ssize_t read;

	char *array[10];

	// Read the customer CSV
	fp = fopen("customerOrder.csv", "r");

	// Error exception
	if (fp == NULL)

		exit(EXIT_FAILURE);

	// Idea to completed this helped with the use of https://stackoverflow.com/questions/32884789/import-csv-into-an-array-using-c
	// Read the Order CSV File
	while ((read = getline(&line, &len, fp)) != -1)
	{
		int reset = 0;

		char *r = strtok(line, ",");	// Read until comman is found and the result is NULL
		while (r != NULL)               // When not null continue into the while loop
		{
			char *arr = malloc(sizeof(char) *50);	//create a local token string variable

			// Wont run without this used stockoverflow to find solution
			const char *stripNewline(char *textStr)
			{
				return textStr;
			}

			// Value will be stored in r store in an array and keep look at line is NULL
			strcpy(arr, stripNewline(r));
			array[reset++] = arr;
			r = strtok(NULL, ",");
		}

		// The following IF will be used to display the users name from the CSV
		if (strstr(array[0], "Name") != NULL)
		{
			customer.name = array[1];
		}

		// The following IF will be used to display the users Budget from the CSV
		// Needed to add an else if here as name was coming out at Product
		else if (strstr(array[0], "Budget") != NULL)
		{
			// Use alof to cobvert to a decimal
			double budget = atof(array[1]);
			customer.budget = budget;
		}

		// Use the else to display the contents under Name and Budget,
		else
		{
			// Note that this sectons CSV is the same structure as the shop CSV
			// Hence the array positions. Cost is not shown but the balance is

			// Define items and cost
			int items = atoi(array[2]);

			double cost = atof(array[1]);

			//char product = (array[0]);
			struct Product p = { array[0],cost};

			// Add to the shopping list
			struct ProductStock shopList = { p,
				items
			};

			//Update the customer shoppinglist
			customer.shoppingList[customer.index++] = shopList;
		}
	}
	// Return to the function
	return customer;
}

// Read in the contents of the CSV file
struct Shop createAndStockShop()
{
	FILE * fp;

	char *line = NULL;

	size_t len = 0;

	ssize_t read;

	// Open the CSV file and set to read
	fp = fopen("stock.csv", "r");

	// Exception
	if (fp == NULL)

		exit(EXIT_FAILURE);

	// Read in cash value from CSV file.
	getline(&line, &len, fp);

	// ATOF converts converts into a floating point numerical representation
	double cash = atof(line);

	struct Shop shop = { cash
	};

	// Read the remainder of the CSV file and print to the screen
	while ((read = getline(&line, &len, fp)) != -1)
	{
		// Update the CSV file with the shop amount I set
		// Used https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/ for help.
		if (strstr(line, "Cash") != NULL)
		{
			char *n = strtok(line, ",");

			char *c = strtok(NULL, ",");
			// ATOF converts converts into a floating point numerical representation
			double cash = atof(c);

			shop.cash = cash;

		}
		else
		{
			char *n = strtok(line, ",");

			char *p = strtok(NULL, ",");

			char *q = strtok(NULL, ",");

			int quantity = atoi(q);
			// ATOF converts converts into a floating point numerical representation
			double price = atof(p);

			char *name = malloc(sizeof(char) *50);

			strcpy(name, n);

			// Add name and price to product
			struct Product product = { name,
				price
			};

			// add product and quantity ro stockItem
			struct ProductStock stockItem = { product,
				quantity
			};
			
			shop.stock[shop.index++] = stockItem;
		}
	}

	// return to function
	return shop;
}

void reviewOrder(struct Shop s, struct Customer c)
{
	printf("\n\n\n-------------------------------------\n   Customer's shopping list \n-------------------------------------\n \n");
	printf("\n");

	// THis for loop will print the customers shopping list
	for (int i = 0; i < c.index; i++)
	{
		printf("%3i. %s", i, c.shoppingList[i].product.name);
		printf(" Quantity = %d\n", c.shoppingList[i].quantity);
		printf("------------------------------------\n");
	}
	printf("\n\n\n-------------------------------------\n   Stock available in the Shop \n-------------------------------------\n \n");
	printf("\n");
	
	// This for loop will print the shops stock
	// This will look at the customer order and dieplay if they have it or not
	for (int i = 0; i < c.index; i++)
	{
		printf("%3i. %s", i, s.stock[i].product.name);
		printf(" QUANTITY = %d\n", s.stock[i].quantity);
		printf("------------------------------------\n");
	}
}

void checkOrder(struct Shop s, struct Customer c)
{
	for (int i = 0; i < c.index; i++)
	{
		short curStock = 0;

		char *ord = malloc(sizeof(char) *50);

		// Copy string 
		strcpy(ord, c.shoppingList[i].product.name); // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm

		for (int i = 0; i < s.index; i++)
		{
			char *shop = malloc(sizeof(char) *50);
			
			// Copy String
			strcpy(shop, s.stock[i].product.name); // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm

			int sh;

			// Check if the stock is in the shopList
			// If True add else desplay error
			if (strstr(ord, shop) != NULL)
			{
				curStock = 1;
				printf("\nITEM FOUND IN SHOP:%s\n", shop);

				int shopQuant = s.stock[i].quantity;
				int cusQuant = c.shoppingList[i].quantity;
				
				// if the customer order is less than the shop quantity then display message
				if (cusQuant < shopQuant)
				{
					printf("ITEM ADDED\n");
				}
				
				// If greater then display error message
				else
				{
					printf("NOT ENOUGH %s IN SHOP\n", shop);
				}
			}
			
			//reached the end of the list and item was not found
			if (i == s.index - 1 &!curStock)
			{
				//shopping list item is not is shop
				printf("\nITEM NOT FOUND IN SHOP:\t%s\n", ord);
			}
		}
	}

	return;

}

void stockAndCashArranging(struct Shop s, struct Customer c)
{
	printf("\n********* Updated Shop *************\n\n");

	double sum = 0;
	int new = 0;

	// This for loop will compare the customer order with shop contents
	// It will subtract the customer item value form store and add price to store 
	for (int i = 0; i < c.index; i++)
	{
		char *shop = malloc(sizeof(char) *50); 
		strcpy(shop, s.stock[i].product.name);


		// Get the total cost of product and add to store cash
		double total =(c.shoppingList[i].quantity *c.shoppingList[i].product.price);
		sum = sum + total;
	
		// Check if the shop and customer items are a match in the array
		int shopQuant = s.stock[i].quantity;
		int cusQuant = c.shoppingList[i].quantity;

		// if the customer order is less than the shop quantity then display message
		// Used this if else to eliminate adding a project that the shop didnt have enough quantity of
		if (cusQuant>shopQuant)
		{
			printf("NOT ENOUGH %s IN SHOP\n", shop);
		}	
		// If statement that will subtract what the customer ordered from store stock and display on screen
		// This will display a minus number is the customer order is more than what the shop has in stock
		else
		{
			new = s.stock[i].quantity - c.shoppingList[i].quantity;
			printf("NEW AMOUNT OF %s IS %d\n", shop, new);
			
			// After the shop has subtracted the customer items, add the money received to the shop cash
			printf("CURRENT CASH IN SHOP IS : %.2f\n\n",
			s.cash + sum);
		}
	}
	
}

void liveShop(struct Shop s, struct Customer c)
{
	printf("\n********* Live Shop *************\n\n");
	
	char n[100];
	char p[100];
	int  b;
	int  q;
	char ch;
	
	printf("\n  Shop Stock Review \n\n");
	
	// For loop that displays the stock details (Item, Cost)
	for (int i = 0; i < s.index; i++)
	{
		printProduct(s.stock[i].product);
		
		printf("------------------------------------\n");

	}

	   printf( "\nWELCOME TO LIVE MODE:\n");
	   gets( n );
	   
	   printf( "\nENTER PRODUCT :");
	   gets( p );
	   
	   printf("ENTER QUANTITY : ");
	   scanf("%d",&q); 
	   
	   printf("ENTER BUDGET   : ");
	   scanf("%d",&b); 
	   
	   printf("------------------------------------\n");

	for (int i = 0; i < c.index; i++)
	{
		short curStock = 0;

		char *ord = malloc(sizeof(char) *50);

		// Copy string 
		strcpy(ord, p); // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm

		for (int i = 0; i < s.index; i++)
		{
			char *shop = malloc(sizeof(char) *50);
			
			// Copy String
			strcpy(shop, s.stock[i].product.name); // https://www.tutorialspoint.com/c_standard_library/c_function_strcpy.htm

			int sh;
		
			// Check if the stock is in the shopList
			// If True add else desplay error
			if (strstr(ord, shop) != NULL)
			{
				curStock = 1;
				printf("\n * FOUND %s IN SHOP", shop);

				int shopQuant = s.stock[i].quantity;		
				
				// if the customer order is less than the shop quantity then display message
				if (q < shopQuant)
				{
					// Set sum to equal zero
					double sum = 0;
					
					printf(" and the shops current Quantity is : %d. \n * We have enough to fill your order.", s.stock[i].quantity);
					
					// Find total customer cost and store in Var total
					double total = q *c.shoppingList[i].product.price;
					sum = sum + total;
					
					if (total > b)
					{
						printf("\n * TOTAL COST OF PURCHASE IS :%.2f", sum);
						// Once all the customer items are added, minus from the budget
						printf("\n * SORRY YOU ARE IN A MINUS DO NOT HAVE ENOUGH MONEY :  %.2f\n", b - sum);
						
						printf("\nLIVE MODE FINISHED\n");
						printf("------------------------------------\n");
					}
					
					else{
						int new = 0;
						// Print the total cost of the customer items
						printf("\n * TOTAL COST OF PURCHASE IS :%.2f\n", sum);
						
						// Subtract the required quantity from the shop and print 
						new = s.stock[i].quantity - q;
						printf(" * New SHOP STOCK OF %s IS %d\n", shop, new);
						
						// After the shop has subtracted the customer items, add the money received to the shop cash
						printf(" * CURRENT CASH IN SHOP IS : %.2f\n\n", s.cash + sum);
						
						printf("\nLIVE MODE FINISHED\n");
						printf("------------------------------------\n");
		
					}
				}
			
				// If greater then display error message
				else
				{
					printf(" BUT WE DO NOT HAVE ENOUGH IN STOCK. \n * THE CURRENT QUANTITY IN THE SHOP IS : %D\n\nPLEASE TRY AGAIN.\n", s.stock[i].quantity);

					printf("------------------------------------\n");

				}
			 return;
		
			}
			//When reached the end of the shop list and the item was not found output
			if (i == s.index - 1 &!curStock)
			{
				//shopping list item is not is shop
				printf("\nSorry but the product %s was not found in the shop.\n", ord);
				
				printf("\nLIVE MODE FINISHED\n");
			    printf("------------------------------------\n");
			}
		}
		return;
	  
	}
	return;
}

// Refereance https://cboard.cprogramming.com/c-programming/151734-[help]-menu-using-while-loop.html 
// Helped with the menu creation
void display_options();

int input();

void output(float);

int main()
{
	printf("\n\n\n-----------------------------------------\n   WELCOME TO THE KAROLINA's C SHOP \n-----------------------------------------\n \n");
	printf("***  Guarantee of successful shopping  *** \n-----------------------------------------");
	
	struct Shop shop = createAndStockShop();

	struct Customer order = cusOrder();

	float result;

	int choice, num; // Keep showing the menu until the user wants exit (7) 
				   
	// Menu selection items, options given to the customers.
	do {
		printf("\n\nPlease select one of the following options given below:");
		
		printf("\n\n * 1 - Show current Shop contents\n");

		printf(" * 2 - Show the Shop and order content\n");

		printf(" * 3 - Show the customer order and calculate cost\n");

		printf(" * 4 - Show if the Shop has customer's order\n");

		printf(" * 5 - Update Shop's stock\n");
		
		printf(" * 6 - LIVE SHOP mode\n");

		printf(" * 7 - Exit\n\n");

		printf("Please enter your choice: ");

		choice = input();

		switch (choice)
		{
			case 1:

				{
					printShop(shop);
					break;
				}

			case 2:

				{
					reviewOrder(shop, order);
					break;
				}

			case 3:

				{
					printCustomer(order, shop);
					break;
				}

			case 4:

				{
					checkOrder(shop, order);
					break;
				}

			case 5:

				{
					stockAndCashArranging(shop, order);
					break;
				}

			case 6: // live shop mode

				{
					liveShop(shop, order);
					break;
				}
				
			case 7:

				{
					return 0;
				}

			default:

				printf("WRONG INPUT, TRY AGAIN\\n");

		}
	}

	while (choice != 8);
	return 0;
}

int input()
{
	int number;
	scanf("%d", &number);
	return (number);
}



// https://cboard.cprogramming.com/c-programming/78794-char-*name.html 15/11/2020
// https://beginnersbook.com/2014/01/c-arrays-example/
