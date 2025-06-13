
"""Determine the n-th element of the sequence 1,2,3,2,2,5,2,2,3,3,3,7,2,2,3,3,3,...
obtained from the sequence of natural numbers by replacing composed
numbers with their prime divisors, each divisor d being written d times,
without memorizing the elements of the sequence."""
def isprime(n:int): #modified
    for i in range (2,n):
        if n%i==0:
            return 0
    return 1

def the_nth(n : int):
    s=0
    m=1
    while (s<=n):
        x=m
        m+=1
        d=2
        if isprime(x)==1:
            s=s+1
            print(x)
            if s>=n:
                return x
        else:
            while x>1:
                if(x%d==0):
                    for i in range(0,d):
                        print(d)
                    s=s+d #everytime I find a prime number d it will appear of d times
                while(x%d==0):
                    x=int(x/d) # I divide x until there's no more prime number in the original x
                if s>=n:
                    return d
                d+=1
n=int(input("Insert n: "))
print(the_nth(n))