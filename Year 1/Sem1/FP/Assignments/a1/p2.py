'''Determine the twin prime numbers p1 and p2 immediately
larger than the given non-null natural number n.
Two prime numbers p and q are called twin if q - p = 2.'''

def is_prime(n):
    if n<2:
        return False
    if n%2==0:
        if n==2:
            return True
        else:
            return False
    for d in range(3,int(n**0.5)+1,2):
        if n % d == 0:
            return False
    return True

from p1 import isprime

number = input("Please enter a number: ")

try:
    p1=int(number)+1    #immediately larger than n
    ok=False
    while not ok:
        if isprime(p1):
            if isprime(p1+2): #p2 must be prime and I define it as being p1+2 as the probleme suggests
                p2=p1+2
                ok=True
            else:
                p1+=1
        else:
            p1+=1
    print(p2)
    print(p1)
except ValueError:
    if(number == float):
        print("PLease enter a natural number! ")
    elif(number != int):
        print("Please enter a number")


