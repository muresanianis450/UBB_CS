'''First problem
Generate the first prime number larger than a given natural number n'''
from graphlib import TopologicalSorter


    #isprime() function returns a boolean value if the number is prime
def isprime(n):
    if n < 2:
        return False
    if(n%2 == 0 and n!=2):
        return False
    for i in range(3,n//2+1,2):
        if(n%i == 0):
            return False
    return True
    #next_prime_number() return the first prime number bigger than n
def next_prime_number(n):
    n+=1
    while not(isprime(n)):
        n+=1
    return n
number = input('Please enter a number: ')
    #if the number is not a positive integer than
try:
    value = int(number)
    print( next_prime_number(value))
except ValueError:
    print("Please enter a natural number")









