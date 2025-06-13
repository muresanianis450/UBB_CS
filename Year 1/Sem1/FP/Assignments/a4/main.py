from array import array

from iterative_approach import *
from recursive_approach import *
from test import *
from naive_approach import *
from dynamic_programming import *

def create_array():
    n = int(input("Enter the rod length: "))
    price = []
    print("Enter the prices for each piece length:")
    for i in range(1, n + 1):
        price.append(int(input(f"Price for length {i}: ")))
    print("Prices entered:", price)
    return n, price

def main():
    ok = True
    while ok:
        print("Which algorithm would you like to use:")
        print("1. Backtracking")
        print("2. Dynamic Programming")
        print("3. Exit")

        try:
            choice = int(input("Enter your choice (1, 2, or 3): "))
        except ValueError:
            print("Invalid choice. Please enter a number between 1 and 3.")
            continue

        match choice:
            case 1:  # Backtracking
                print("Choose the backtracking method:")
                print("1. Iterative")
                print("2. Recursive")
                print("3. Back to Main Menu")

                try:
                    choice_bkt = int(input("Enter your choice (1, 2, or 3): "))
                except ValueError:
                    print("Invalid choice. Returning to the main menu.")
                    continue

                match choice_bkt:
                    case 1:
                        n = int(input("Enter n: "))
                        bkt_iter(n)
                    case 2:
                        n = int(input("Enter n: "))
                        bkt_rec([], n)
                    case 3:
                        continue  # Go back to the main menu
                    case _:
                        print("Invalid choice. Returning to the main menu.")

            case 2:  # Dynamic Programming
                print("1.Naive approach\n2.Dynamic Programming approach")
                approach=int(input())


                match approach:
                    case 1:
                        n, price = create_array()
                        print(naive_function(price,n,n))
                    case 2:
                        n, price = create_array()
                        print(dynamic_function(price,n))
                    case _:
                        print("Invalid choice. Returning to the main menu.")
            case 3:
                print("Exiting the program.")
                ok = False  # Exit the loop and program

            case _:
                print("Invalid choice. Please enter a number between 1 and 3.")


if __name__ == "__main__":
    test_functions()
    main()
