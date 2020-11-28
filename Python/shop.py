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
    print(f'\nProduct name: {p.name} \nProduct price: {p.price}')


def print_customer(c):
    print(f'======================================================')
    print(f'======================================================\n')
    print(f'Customer name: {c.name} \nCustomer budget: {c.budget}')
    print(f'------------------------------\n')
    for item in c.shopping_list:
        print_product(item.product)
        
        print(f'The customer wants {item.quantity} of above product')
        
        cost = item.quantity * item.product.price
        print(f'The cost to {c.name} will be EUR {cost}')
        
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

s = create_and_stock_shop()
print_shop(s)

c = read_customer("order.csv")
print_customer(c)