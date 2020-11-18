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

struct Product  // Product Struct for product informations
{
	char* name; // name refers to a pointer, so when dereferenced, name is a char. In this case a pointer initialized to a string located in read-only memory.
	double price; //  Double = decimal number
};

struct ProductStock // ProductStock Struct for stock informations
{
	struct Product product;
	int quantity;
};

struct Shop // Shop Struct for shop infomations
{
	double cash;
	struct ProductStock stock[20];
	int index;
};

struct Customer // Customer Struct for customer informations
{
	char* name;
	double budget;
	struct ProductStock shoppingList[10]; // Nested struct - An Array of 10 elements.
	int index;
};

// Void when used as a function return type, the void keyword specifies that the function does not return a value.
// Void does not provide a result value to its caller. Those functions are called for their side effects, such as performing some task or writing to their output parameters.
// https://docs.microsoft.com/en-us/cpp/cpp/void-cpp?view=msvc-160, 15/11/2020
// https://en.wikipedia.org/wiki/Void_type, 15/11/2020


// ============================================================================================================================================================================

// printProduct() function will be used to print product informations
void printProduct(struct Product p)
{
	printf("Product's name: %s \nProduct's price: %.2f\n", p.name, p.price); // Print the product name and its price.
	printf("\n");
}

struct Shop createAndStockShop()
{
	
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
	int i = 0;

    fp = fopen("stock1.csv", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

	getline(&line, &len, fp);
	// read cash in 
	double cashInshop = atof(line);
	struct Shop shop = { cashInshop };


	while ((read = getline(&line, &len, fp)) != -1)
	{
            char *n = strtok(line, ",");
            char *p = strtok(NULL, ",");
            char *q = strtok(NULL, ",");
            // convert to datatypes
            double price = atof(p);
            int quantity = atoi(q);
            char *name = malloc(sizeof(char)*50);
            strcpy(name, n);

			
            struct Product product = {name, price};
            struct ProductStock stockItem = {product, quantity};
            shop.stock[shop.index++]=stockItem;
    }

	return shop;
}

void printShop(struct Shop s) // This will print shop details like cash and stock available
{
	printf("\n\n\n------------------------------------------------------------\n                  WELCOME TO THE 'C' SHOP \n------------------------------------------------------------\n ");
	printf("**********************************************************\n");

    printf("\n");
	printf("============================================================\n");
    printf("   Cash in the Shop: EUR %.2f \n", s.cash); // print how much cash Store has in cash. Taken from stock.csv file
    printf("============================================================\n");
	printf("   Credit/Debit card payments acceptable in this Shop\n"); // just to inform customers that card payments are avilable
	printf("============================================================\n");
	printf("\n");
	printf("\n");
    printf("\n*** STOCK AVAILABLE IN 'C' SHOP ***\n");
    printf("\n");

	for (int i = 0; i < s.index; i++) // 'for' loop displays the stock details to the output
	{
		
		printProduct(s.stock[i].product);
		printf("Quantity: %d\n", s.stock[i].quantity); // When you press 1st option in Menu selection, this quantity will be given as output.

		printf("-------------------------------------------------------\n");
	}
}

struct Customer customerOrder() // this struct will read order.csv file  
{
	
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i = 0;

	fp = fopen("order.csv", "r"); // fopen reads the customer's order csv file
	
	if (fp == NULL) // error exception
		exit(EXIT_FAILURE);

	getline(&line, &len, fp); // read customer name and budget, so csv file
	
	char *n = strtok(line, ",");
    char *b = strtok(NULL, ",");
	
	char *name = malloc(sizeof(char)*50); //create a local token string variable
    strcpy(name, n);
	double budget = atoi(b);
	struct Customer c ={ name, budget };
	
	// printf("CUSTOMER NAME: %s \nBUDGET: %.2f\n", c.name, c.budget);
	
    while ((read = getline(&line, &len, fp)) != -1)
    {
            char *r = strtok(line, ",");
			char *q = strtok(NULL, ",");
			int quantity = atoi(q);
			char *productname = malloc(sizeof(char)*50);
			strcpy(productname, r);
			struct Product product = {productname};
			struct ProductStock orderItem = {product, quantity};
			c.shoppingList[c.index++]=orderItem;
        }

    return c;
}

//================================================================================================================================

// printCustomer() will be used to print customer's details and order
void printCustomer(struct Customer c) 
{
	printf("\n=======================================================");
	printf("\nCustomer's name: %s \nCustomer's budget: EUR %.2f\n", c.name, c.budget); // Prints customer's name and budget
    printf("=======================================================\n");
	printf("\n");

	for (int i = 0; i < c.index; i++) // Start loop through each of the items in the shopping list 
	{
		printProduct(c.shoppingList[i].product); // Print the product informations
		printf("The customer wants %d of above\n", c.shoppingList[i].quantity);
		printf("\n-------------------------------------------------------\n");
	}
}

// =====================================================================================================================================

// searching both and comparing and returning price
double findPrice(struct Shop s, struct Customer c)
{
	struct Product productcustomer;
	double sum =0;
	double shortamount;
	
    printf("\n");
    printf("\n=======================================================\n");
	printf("\n      ***  Total to pay by customer  ***  \n");
    printf("=======================================================\n");
    printf("\n");

	for (int i = 0; i < s.index; i++)
	{
		for (int j = 0; j < c.index; j++) // loop through customer order
		{
			struct Product product = s.stock[i].product;
			struct Product productcustomer = c.shoppingList[j].product;
			// compare shop and order
			if (strcmp(product.name, productcustomer.name) == 0)
			{ 
					printf("Product: %s\nPrice: EUR %.2f * Quantity %d\n", c.shoppingList[j].product.name, product.price, c.shoppingList[j].quantity);
				    // check if in stock in store
					printf("In stock: %s, availability: %d\n", c.shoppingList[j].product.name, s.stock[i].quantity);
					printf("-------------------------------------------------------\n");
                    printf("\n");

					if(s.stock[i].quantity < c.shoppingList[j].quantity) // check if Shop has the item quantity
					{
                        printf("Sorry, the Shop has only %d \n \n", s.stock[i].quantity); // if not in stock
                        printf("-----------------------------------------------------\n");
                    }
					else{
				     
					sum = product.price * c.shoppingList[j].quantity + sum; // adding up the bill
					s.stock[i].quantity = s.stock[i].quantity - c.shoppingList[j].quantity;
					
					//i++;		
					}
			}		
		}
	}
		if(c.budget< sum)
		{
			shortamount = (sum - c.budget);
			printf("-----------------------------------------------------------------------------------------\n");
			printf("We are sorry, alternative tender required or you might need more money to pay: EUR %.2f \n", shortamount );
			printf("-----------------------------------------------------------------------------------------\n");
			printf("=========================================================================================\n");
							
		}
		else{
			printf("\n");
			printf("Total to pay by customer: EUR %.2f\n", sum);
            printf("===================================\n");
            printf("\n\n");
            printf("=======================================================\n");
			
            printf("\n*** Cash and availability of products in the Shop ***  \n");
            printf("=======================================================\n");
            printf("\n");
			
			
			s.cash = s.cash + sum; // add customer's bill to the shop's float
			printf("Cash has been updated and now is: EUR %.2f\n", s.cash);
			printf("\n-------------------------------------------------------\n");
			for (int i = 0; i < s.index; i++)
			{
				printf("Product's name: %s\nProduct's quantity after shopping: %d \n",s.stock[i].product.name, s.stock[i].quantity );
                printf("\n");
            }

		}

	return -1; 
}

// ========================================================================================================================================
struct Customer orderlive()
{
	printf("\n");
	printf("           *** Welcome to the Live Shop ***              \n");
	printf("=======================================================\n");
	printf("What is your name? "); // live Shop will ask for your name
	char *name = malloc(sizeof(char)*50);
    scanf(" %s", name);

	printf("\n");
	printf("What is your budget? "); // live Shop will ask for budget
	double budget;
	scanf("%lf", &budget);
	
	printf("\n");
	printf("What would you like to buy? "); // live Shop will ask for product you would like to buy
	char *p = malloc(sizeof(char)*50);
	char temp;
	scanf("%c", &temp); 
	scanf("%[^\n]s", p); 
	  
	printf("\n");
	printf("How many would you like to buy? "); // live Shop will ask how many products ypu would like to buy
	int q;
	scanf(" %d", &q);
	
	printf("------------------------------------------------------");
	struct Customer nc ={name, budget};
	printf("\nCustomer's name: %s\nCustomer's budget: %.2f",nc.name,nc.budget );

	struct Product product = {p};
	struct ProductStock orderItem = {product, q};
	nc.shoppingList[nc.index++]=orderItem;

	printf("\nProduct's name: %s\nquantity: %d", nc.shoppingList[0].product.name,nc.shoppingList[0].quantity );

	
   return nc;
}

// ===========================================================================================================================================
// int main(void) is the beginning of a function definition, (void) is the list of parameters that main is expecting from its caller. 
// In most cases, its caller is the operating system.

int main(void)
{
	
    struct Shop shop = createAndStockShop();
    printShop(shop);

    struct Customer c = customerOrder();
    printCustomer(c);
	
	findPrice(shop, c);


	struct Customer nc = orderlive();
	findPrice(shop, nc );
	

    return 0;
}

// https://stackoverflow.com/questions/12225171/difference-between-int-main-and-int-mainvoid, 18/11/2020