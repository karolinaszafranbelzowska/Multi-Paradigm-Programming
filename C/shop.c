
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Product
{
    char* name;
    double price;
};

struct ProductStock
{
    struct Product product;
    int quantity;
};

struct Shop
{
    double cash;
    struct ProductStock stock[20];
    int index;
};

struct Customer
{
    char* name;
    double budget;
    struct ProductStock shoppingList[10];
    int index;

};

// print Product info
void printProduct(struct Product p)
{
    printf("---------------------------------------\n");
    printf("Product name: %s \nProduct price: %.2f Euro\n", p.name, p.price);
    printf("---------------------------------------\n");
}

// print Customer info
void printCustomer(struct Customer c)
{
    printf("---------------------------------------\n");
    printf("Customer name: %s \nCustomer budget: %.2f Euro\n", c.name, c.budget);
    printf("---------------------------------------\n");
    for(int i = 0; i < c.index; i++)
    {
        printProduct(c.shoppingList[i].product);
        printf("%s ORDERS %d OF ABOVE PRODUCT\n", c.name, c.shoppingList[i].quantity);
        double cost = c.shoppingList[i].quantity * c.shoppingList[i].product.price;
        printf("The cost to %s will be %.2f Euro\n", c.name, cost);
    }
}

struct Shop createAndStockShop()
{
    struct Shop shop = {200};
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    

    fp = fopen("stock.csv","r"); // r = read only
    if (fp == NULL)
        exit(EXIT_FAILURE);
    
    
    while ((read = getline(&line, &len, fp)) != -1)
    {
        
        // printf("Retrived line of length %zu:\n", read);
        // printf("%s IS A LINE", line);

            char *n = strtok(line, ",");
            char *p = strtok(NULL, ",");
            char *q = strtok(NULL, ",");
            int quantity = atoi(q);
            double price = atof(p);
            char *name = malloc(sizeof(char) * 50);
            strcpy(name, n);
            struct Product product = {name, price};
            struct ProductStock stockItem = {product, quantity};
            shop.stock[shop.index++] = stockItem;
    }
        
    return shop;
}

void printShop(struct Shop s)
{
    printf("Shop has %.2f in cash\n", s.cash);
    for (int i = 0; i < s.index; i++)
    {
        printProduct(s.stock[i].product);
        printf("The shop has %d of the above\n", s.stock[i].quantity);
    }

}

// model the entities
int main(void)
{
    // struct Product coke = { "Can of coke", 1.05};
    // printf("The %s costs %.2f\n", coke.name, coke.price);
    // struct Product bread = {"Bread", 0.70};
    
    // printProduct(coke);

    // struct Customer karolina = { "Karolina", 100.00, "Euro"};
    // printf("Customer name is %s\n", karolina.name);
    

    // struct ProductStock cokeStock = {coke, 10};
    // printf("The shop has %d of the product %s\n", cokeStock.quantity, cokeStock.product.name);
    
    // struct ProductStock breadStock = {bread, 2};
    
    // karolina.shoppingList[karolina.index++] = cokeStock;
    // karolina.shoppingList[karolina.index++] = breadStock;

    // printCustomer(karolina);

    struct Shop shop = createAndStockShop();
    printShop(shop);

    // printf("The shop has %d of the product, which are: %s\n", cokeStock.quantity, cokeStock.product.name);
    
    return 0;

}