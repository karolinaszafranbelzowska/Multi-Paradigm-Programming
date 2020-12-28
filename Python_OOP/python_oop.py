# Karolina Szafran - Belzowska, December 2020
# Project Multi Paradigm Programming, Shop Assignment

# import csv 
import csv

# to print shop_oop.py in Command Prompt I have to type the following:
# python shop_oop.py

class Product: # class Product contains a name and a price of the products
               # This is the same as struct in C.
    def __init__(self, name, price=0): # price = 0, when we do not the price it defaults the value to 0.
        self.name = name
        self.price = price
    
    def __repr__(self): # returns the name and the price. Represents everything what we should know about the Product.
        return f'Product name:  {self.name}, \nProduct price:  {self.price}\n'

class ProductStock: # class ProductStock contains a product name and a quantity
    
    def __init__(self, product, quantity):
        self.product = product
        self.quantity = quantity
    
    def name(self): # method which helps me to find out the name of the product
        return self.product.name; # I do not have to go through the product every time.
    
    def unit_price(self): # returns the price of the product price.
        return self.product.price;
        
    def cost(self): # it is responsible for calculating the cost.
                    # The ProductStock knows a product and the price, and the quantity.
                    # It refering to what the customer wants to buy, or to how much is in the shop at any time.
                    # It all happens inside the class. Other classes do not have to figure out how to calculate
                    # that cost. 
        return self.unit_price() * self.quantity
        
    def __repr__(self):
        return f"{self.product}Quantity: {self.quantity}\n"

class Customer:

    def __init__(self, path): # it take a path and then open the csv file.
                              # Pulls the informations about itself (name and the budget).
                              # All the informations are about the indyvidual instance of the customer.
        self.shopping_list = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.name = first_row[0]
            self.budget = float(first_row[1])
            for row in csv_reader:
                name = row[0]
                quantity = float(row[1])
                p = Product(name)
                ps = ProductStock(p, quantity)
                self.shopping_list.append(ps) # added to shopping list that belongs inside customer class and it is declared in self.shopping_list = [] 
                
    def calculate_costs(self, price_list): # the customer can consult the shop stock to figure out how much products cost.
        for shop_item in price_list: # for every item in the shop check it against every item that I want to buy and if
                                     # the two names are the same then save the price of the shop items into my product stock instances.
            for list_item in self.shopping_list:
                if (list_item.name() == shop_item.name()):
                    list_item.product.price = shop_item.unit_price()
    
    def order_cost(self):
        cost = 0
        
        for list_item in self.shopping_list: # for every item in the shopping list we go through and get the cost of the item and add them to the total. 
            cost += list_item.cost()
        
        return cost
    
    def __repr__(self): 
        print(f'                 *** CUSTOMER DETAILS ***')
        print(f'---------------------------------------------------------------')
        print(f'Customer name: {self.name}')
        print(f'Customer budget: EUR {self.budget}')

        print(f'---------------------------------------------------------------')
        str = f"{self.name} wants to buy:\n" # name of the customer
        for item in self.shopping_list: # iterate through the shopping list
            cost = item.cost() # method that calculates the cost of the item, ProductStock class is called here.
            str += f"\n{item}" 
            if (cost == 0):
                str += f"{self.name} doesn't know how much that costs :(\n"
            else:
                str += f"The cost of this product: {cost}\n"
               
        str += f"\nThe total cost for the customer is: EUR {self.order_cost()}. The customer now has EUR {self.budget - self.order_cost()}." 
        # self.order_cost - it goes through the shopping list and pulls all the costs together and returns them.
        
        return str 
        
class Shop: 
    
    def __init__(self, path):
        self.stock = []
        with open(path) as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            first_row = next(csv_reader)
            self.cash = float(first_row[0])
            for row in csv_reader:
                p = Product(row[0], float(row[1]))
                ps = ProductStock(p, float(row[2]))
                self.stock.append(ps)

    def live_mode(self,c):
        print("=================================================\n")
        print("  ***Welcome to the Live Shop***   \n")
        print("=================================================\n")
        cust_name = input("What is your name? ") # live shop will  ask for your name
        budget= float(input(f"What is your budget {cust_name}?: "))
        c = Customer(cust_name, budget)
        print("Today we can offer you products which are listed below:")
        # print_shop(s)
        shopping_list=[]
        additional_items = "Y"
        while (additional_items == "Y"):
            name = input("What would you like to buy?: ")
            quantity = int(input("How many would you like to buy?: "))
            p = Product(name)
            ps = ProductStock(p, quantity)
            c.shopping_list.append(ps)
            additional_items = input("Would you like to order additional items? Y/N \n")

        return c
    
    def __repr__(self): 
        str = ""
        str += f'Shop has EUR {self.cash} in cash.\n'
        
        for item in self.stock:
            str += f"{item}\n"
        return str


print('=======================================================')
print('-------------------------------------------------------\n           Welcome to the Python_OOP Shop \n-------------------------------------------------------')
print(f'*******************************************************')

print(f'')
print(f'   Credit/Debit card payments acceptable in this Shop') # just to inform customers that card payments are avilable
print(f'=======================================================\n')
print(f'         *** STOCK AVAILABLE IN PYTHON SHOP *** ')
print(f'-------------------------------------------------------')

def main():
    s.live_mode(c)
   
    
    print("======================================================")
    print("======================================================")
    print("      Thank you for shopping in Python Shop")
    print("======================================================")

s = Shop('stock1.csv')
print(s)
# print_shop(s)

c = Customer('order.csv')
c.calculate_costs(s.stock) # s.stock - passing in the stock array which comes from the shop and it comes in as price_list
print(c)


if __name__ == "__main__":
    main()

 