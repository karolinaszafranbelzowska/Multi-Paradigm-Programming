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
        
    def __repr__(self): # The __repr__ function is used to return an object
        return f"{self.product}Quantity: {self.quantity:.0f}\n"

class Customer: # Customer class will give us all important details about customer

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
        str = f""
        Customer_order.calculate_costs(self,s.stock)
        Customer_order.check_stock(self)
        str = f"{self.name} wants to buy:\n" # name of the customer and her/his shopping list
        for item in self.shopping_list: # iterate through the shopping list
            cost = item.cost() # method that calculates the cost of the item, ProductStock class is called here.
            str += f"\n{item}" 
            if (cost == 0):
                str += f"{self.name} doesn't know how much that costs because this item is out of stock or Alternative Tender Required.\n"
            else:
                str += f"The cost of this purchase is: EUR{cost}\n"
        if Customer_order.order_cost(self) <=  self.budget:
            s.cash += Customer_order.order_cost(self)
            str += f"\nThe total cost for {self.name} is EUR{Customer_order.order_cost(self):.2f}. \nTransaction complete. \nThe customer now has EUR{self.budget - Customer_order.order_cost(self):.2f}. \nThe Shop cash is now EUR{s.cash:.2f}."
            for item in self.shopping_list: # Iterate through all items in the shopping list
                for prod in s.stock:        # Iterate the item from shopping list through the shop stock 
                    if item.product.name == prod.product.name:          # If names are equal then adjust quantities outlined below
                        prod.quantity = prod.quantity - item.quantity   # Update shop quantities  
        else:
            str += f"\nThe total cost for the customer is: EUR {Customer_order.order_cost(self):.2f}. \nThe customer now has EUR {self.budget - Customer_order.order_cost(self)}."
      
        return str 

class Customer_order:

    def order_cost(self):
        total_order = 0
        
        for list_item in self.shopping_list:
            total_order += list_item.cost()
        
        return total_order

    def check_stock(self):
        str = f""
        for item in self.shopping_list:
            for prod in s.stock:
                    if item.product.name == prod.product.name and item.quantity > prod.quantity:
                        print(f"The product(s) that customer asked: {item.product.name} is(are) not available,  we apologize for the product being unavailable.\n")
                        Menu().main()

    def calculate_costs(self, price_list):
        for shop_item in price_list:
            for list_item in self.shopping_list:
                if (list_item.name() == shop_item.name()):
                    list_item.product.price = shop_item.unit_price()

class Live_mode: # Live_mode will activate interactive mode 

    def __init__(self):
        print("\n          *** Welcome to the Live Shop ***         ")
        print("========================================================")
        self.name = input("What is your name? ") # live Shop will ask for your name
        self.budget= float(input(f"{self.name} what is your budget: ")) # live shop will ask you for the budget
        print("Today we can offer you products which are listed below:") # Stock will be printed
        print(s)
        self.shopping_list=[]
        additional_items = "Y"
        while (additional_items == "Y"):
            name = input("What would you like to buy? ") # live Shop will ask for product you would like to buy
            quantity = int(input("How many would you like to buy? "))
            p = Product(name)
            ps = ProductStock(p, quantity)
            self.shopping_list.append(ps)
            additional_items = input("Would you like to order additional items? Y/N \n")
    
    def __repr__(self):    
        return Customer.__repr__(self)

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

    def __repr__(self): 
        str = ""
        str += f'\nShop has EUR {self.cash} in cash.\n'
        
        for item in self.stock:
            str += f"{item}\n"
        return str

class Menu:
    def display_menu(self):
        print("\n               Main Menu Python_OOP Shop\n")
        print("========================================================")
        print("1- Check shop cash & stock")
        print("2- Customer - csv file")
        print("3- Live mode")
        print("4- Exit")

    def main(self):
        while True:
            self.display_menu()
            choice = input("Enter your choice: ")

            if (choice == "1"):
                print(s)
                
            elif (choice == "2"):
                c = Customer("order.csv")
                print(c)
            
            elif (choice == "3"):
                c = Live_mode()
                print(c)
                
            
            elif (choice == "4"):
                exit()

            else:
                print("This is not a valid selection\n")
        
print('=======================================================')
print('-------------------------------------------------------\n           Welcome to the Python_OOP Shop \n-------------------------------------------------------')
print(f'*******************************************************')

print(f'')
print(f'   Credit/Debit card payments acceptable in this Shop') # just to inform customers that card payments are avilable
print(f'=======================================================\n')

s = Shop('stock1.csv')
# print(s)
# print_shop(s)

# c = Customer('order.csv')
# c.calculate_costs(s.stock) # s.stock - passing in the stock array which comes from the shop and it comes in as price_list
# print(c)

Menu().main()


 