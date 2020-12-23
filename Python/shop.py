# Karolina Szafran - Belzowska, November 2020
# Project Multi Paradigm Programming, Shop Assignment

# call libraries in Python
from dataclasses import dataclass, field
from typing import List
import csv

# to print shop.py in Command Prompt I have to type the following:
# python shop.py

@dataclass
class Product:
    name: str
    price: float = 0.0

@dataclass 
class ProductStock:
    product: Product
    quantity: int

@dataclass 
class Shop:
    cash: float = 0.0
    stock: List[ProductStock] = field(default_factory=list)

@dataclass
class Customer:
    name: str = ""
    budget: float = 0.0
    shopping_list: List[ProductStock] = field(default_factory=list)

def create_and_stock_shop():
    s = Shop()
    with open('stock1.csv') as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        s.cash = float(first_row[0])
        for row in csv_reader:
            p = Product(row[0], float(row[1]))
            ps = ProductStock(p, float(row[2]))
            s.stock.append(ps)
            # print(ps)
    return s
    
def read_customer(file_path):
    with open(file_path) as csv_file:
        csv_reader = csv.reader(csv_file, delimiter=',')
        first_row = next(csv_reader)
        c = Customer(first_row[0], float(first_row[1]))
        for row in csv_reader:
            name = row[0]
            quantity = float(row[1])
            p = Product(name)
            ps = ProductStock(p, quantity)
            c.shopping_list.append(ps)
        return c 
        
def print_product(p):
    print(f'\nPRODUCT NAME: {p.name} \nPRODUCT PRICE: {p.price}')

def print_product(p):
    print(f'\nProduct name: {p.name} \nProduct price: {p.price}')


def print_customer(c, s):
    check_stock(c, s)
    calculate_costs(c, s)
    total_order = 0

    print(f'======================================================')
    print(f'======================================================\n')
    print(f'Customer name: {c.name} \nCustomer budget: {c.budget}')
    print(f'------------------------------\n')

    for item in c.shopping_list:
        print_product(item.product)
        print(f'{c.name} wants {item.quantity:.0f} of above product')
        cost = item.quantity * item.product.price
        total_order += cost
        print(f'The cost to {c.name} will be EUR{cost:.2f}\n')

    if total_order <= c.budget:
        s.cash += total_order
        print("\n")
        print(f'Summary of the customers shopping basket:')
        print(f'==========================================================================')
        print(f'Customer name is {c.name} and she/he has EUR{c.budget:.2f} for the shopping.\nThe total price of the order for the customer is EUR{total_order:.2f}. \nTrasnaction complete. The customer now has {c.budget-total_order:.2f} remaining in the budget. \nCash in the Shop is now {s.cash}\n')
        for item in c.shopping_list:
            for prod in s.stock:
                if item.product.name == prod.product.name:
                    prod.quantity = prod.quantity - item.quantity
    else:
        print(f'Customer name is {c.name} and she/he has EUR{c.budget:.2f} for the shopping.\nThe total price of the order for {c.name} is €{total_order:.2f}. {c.name} has not enough money to complete the transaction. {s.cash}\n')

def check_stock(c, s):
    for item in c.shopping_list:
        for prod in s.stock:
                if item.product.name == prod.product.name and item.quantity <= prod.quantity:
                    print(item, item.quantity, prod.quantity)
                    print("OK")
                
                elif item.product.name == prod.product.name and item.quantity > prod.quantity:
                    print(f"We do not have enough stock of {item.product.name}, please re-select products to continue with your purchase.")
                    main()

def calculate_costs(c, s):
    for shop_item in s.stock:
        for list_item in c.shopping_list:
            if (list_item.product.name == shop_item.product.name):
                list_item.product.price = shop_item.product.price

def live_mode():
    print("=================================================\n")
    print("  ***Welcome to the Live Shop***   \n")
    print("=================================================\n")
    cust_name = input("What is your name? ") # live shop will  ask for your name
    budget= float(input(f"What is your budget {cust_name}?: "))
    c = Customer(cust_name, budget)
    print("Today we can offer you products which are listed below:")
    print_shop(s)
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

def print_shop(s):
    print(f'-------------------------------------------------------\n           Welcome to the Python Shop \n-------------------------------------------------------')
    print(f'*******************************************************')
    print(f'\n')
    print(f'=======================================================\n')
    print(f'   Cash in the Shop: EUR {s.cash}\n')
    print(f'')
    print(f'   Credit/Debit card payments acceptable in this Shop') # just to inform customers that card payments are avilable
    print(f'=======================================================\n')
    print(f'*** STOCK AVAILABLE IN PYTHON SHOP *** ')
    print(f'---------------------------------------')

    for item in s.stock:
        print_product(item.product)
        print(f'The Shop has {item.quantity} of the above')

def main():
    live_mode()
   
    
    print("======================================================")
    print("======================================================")
    print("      Thank you for shopping in Python Shop")
    print("======================================================")


s = create_and_stock_shop()
print_shop(s)

c = read_customer("order.csv")
print_customer(c, s)

if __name__ == "__main__":
    
    main()