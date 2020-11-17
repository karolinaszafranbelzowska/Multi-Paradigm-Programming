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

// print shop details
void printShop(struct Shop s)
{
	printf("Shop has %.2f in cash\n", s.cash);
	for (int i = 0; i < s.index; i++)
	{
		
		printProduct(s.stock[i].product);
		printf("The shop has %d of the above\n", s.stock[i].quantity);
	}
}

// reading in customers from csv
struct Customer orderAndshop(){
	
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int i = 0;

	fp = fopen("order.csv", "r");
	// if file doesn't exist exit program
	if (fp == NULL)
		exit(EXIT_FAILURE);

	getline(&line, &len, fp);
	// read customer name and budget
	char *n = strtok(line, ",");
    char *b = strtok(NULL, ",");
	
	char *name = malloc(sizeof(char)*50);
    strcpy(name, n);
	double budget = atoi(b);
	struct Customer c ={ name, budget };
	//struct Shop shop = { cashInshop };
	printf("CUSTOMER NAME: %s \nBUDGET: %.2f\n", c.name, c.budget);
	
    while ((read = getline(&line, &len, fp)) != -1)
    {
            char *p = strtok(line, ",");
			char *q = strtok(NULL, ",");
			int quantity = atoi(q);
			char *productname = malloc(sizeof(char)*50);
			strcpy(productname, p);
			struct Product product = {productname};
			struct ProductStock orderItem = {product, quantity};
			c.shoppingList[c.index++]=orderItem;

        }

    return c;
}

// printCustomer() will be used to print customer's details and order
void printCustomer(struct Customer c) 
{
	printf("\n");
	printf("\nCustomer's name: %s \nCustomer's budget: %.2f\n", c.name, c.budget); // Prints customer's name and budget
    printf("====================================\n");
	printf("\n");

	for (int i = 0; i < c.index; i++) // Start loop through each of the items in the shopping list 
	{
		printProduct(c.shoppingList[i].product); // Print the product informations
		printf("The customer wants %d of above\n", c.shoppingList[i].quantity);
		
		printf("\n------------------------------------\n");
	}

}

// searching both and comparing and returning price
double findProductPrice(struct Shop s, struct Customer c)
{
	struct Product productcustomer;
	double sum =0;
	double shortamount;
	
	printf("\n--------Total to pay by customer--------\n");
	for (int i = 0; i < s.index; i++)
	{
		// loop through customer order
		for (int j = 0; j < c.index; j++)
		{
			struct Product product = s.stock[i].product;
			struct Product productcustomer = c.shoppingList[j].product;
			// compare shop and order
			if (strcmp(product.name, productcustomer.name) == 0)
			{ 
					printf("%s, Price %.2f * Quantity %d\n", c.shoppingList[j].product.name, product.price, c.shoppingList[j].quantity);
				    // check if in stock in store
					//printf("In stock: Name: %s, Quantity %d\n", current.shoppingList[j].product.name, s.stock[i].quantity);
					// check if the shop has the item quantity
					if(s.stock[i].quantity < c.shoppingList[j].quantity)
					{
						//perror("Not in stock");
						printf("Sorry, We have only %d \n \n", s.stock[i].quantity);
					}
					else{
				     // adding up the bill
					sum = product.price * c.shoppingList[j].quantity + sum;
					s.stock[i].quantity = s.stock[i].quantity - c.shoppingList[j].quantity;
					
					//i++;		
					}
			}		
		}
	}
		if(c.budget< sum)
		{
			shortamount = (sum - c.budget);
			printf("----------------------\n");
			printf("Oh No!!!\n" );
			printf("I'm sorry but alternative tender required, you might need more money to pay: %.2f \n", shortamount );
			printf("----------------------\n");
							
		}
		else{
			printf("\n");
			printf("Total Customer Bill: %.2f\n", amount);
			// new float in shop
			printf("\n");
			printf("--------Shop Cash--------\n");
			// add to the shop float
			s.cash = s.cash + amount;
			printf("Shop cash has been updated: %.2f\n", s.cash);
			//printf("Shop cash has been updated: %d\n", s.stock);
			for (int i = 0; i < s.index; i++)
			{
				printf("%s, in stock: %d \n",s.stock[i].product.name, s.stock[i].quantity );

			}

		}

	return -1; 
}

struct Customer orderlive()
{

	// what's your name?
	printf("What is your name?\n");
	char *name = malloc(sizeof(char)*50);
    scanf(" %s", name);

	// budget
	printf("What is your budget?\n");
	double budget;
	scanf("%lf", &budget);
	

	printf("What would you like to buy?");
	char *p = malloc(sizeof(char)*50);
	char temp;
	scanf("%c", &temp); 
	scanf("%[^\n]s", p); 
	  

	printf("How many?\n");
	int quantity;
	scanf(" %d", &quantity);
	

	struct Customer newcurrent ={name, budget};
	printf("\nName : %s, Budget: %.2f",newcurrent.name,newcurrent.budget );

	struct Product product = {p};
	struct ProductStock orderItem = {product, quantity};
	newcurrent.shoppingList[newcurrent.index++]=orderItem;

	printf("\nName : %s, quantity: %d", newcurrent.shoppingList[0].product.name,newcurrent.shoppingList[0].quantity );

	
   return newcurrent;
	

}
int main(void)
{


	
	struct Shop shop = createAndStockShop();
	printShop(shop);

	struct Customer current = orderAndshop();
	//printf("Name: %s,  budget %f,  \n", current.name, current.budget);	
	

    printCustomer(current);

	// searching for price
	findProductPrice(shop, current);


	struct Customer newcurrent = orderlive();
	findProductPrice(shop, newcurrent );
	

    return 0;
}
