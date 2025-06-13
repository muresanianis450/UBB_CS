/*
 *
*a. Generate the first n prime numbers (n is a given natural number).
*
b. Given a vector of numbers, find the longest contiguous subsequence
such that any two consecutive elements are relatively prime.
 */

#include <stdio.h>
#include <stdlib.h>

void menu()
//Function for the menu
{
 printf("\n1. Read the vector");
 printf("\n2. Generate all prime numbers smaller than a given natural number\n");
 printf("3. Find the longest increasing contiguous subsequence,\n   such the sum of that any 2 consecutive elements is a prime number.");
 printf("\n0. Exit\n\n");
}

int is_prime(int n)
//Function that checks if a number is prime or not
{
 if (n==2)
  return 1;
 if(n==1 || n==0)
   return 0;
 if (n%2==0)
  return 0;
 for (int i=3;i<=n/2;i+=2)
  if (n%i==0)
   return 0;
 return 1;
}

void generate_primes(int n) {
    for (int i=2;i<=n;i++)
    if (is_prime(i))
    printf("%d ", i);
}

typedef struct
/*Structure for the vector
 *v.content - the elements of the vector
 *v.length - the length of the vector in that point
 */

{
 int content[100]; int length;
}vector;

// ........................................................ Question-> why do we use vector instead of int or void???(we used that at the seminar) is it because i return a vector?
vector read_vector() {
 vector v;
 v.length = 0;

 printf("Enter your elements: ");
 do {
  scanf("%d", &v.content[v.length++]);
 }while (v.content[v.length-1]!=0);
 v.length--;
 return v;
}
void print_vector(vector v) {
 for (int i=0;i<v.length;i++)
  printf("%d ", v.content[i]);
}

void longest_contiguos(vector v, vector *new) {
 vector current;
 current.length = 0;
 new->length = 0;

 for (int i = 0; i < v.length; i++) {
  current.length = 1;
  current.content[0] = v.content[i];

  for (int j = i + 1; j < v.length; j++) {
   if (is_prime(current.content[current.length - 1] + v.content[j])) {
    current.content[current.length++] = v.content[j];
   } else {
    break;
   }
  }

  if (current.length > new->length) {
   *new = current;
  }
 }
}
int main() {
 int choice= -1;
 vector v;
 while(1) {

  menu();
  printf("Enter your choice: ");
  scanf("%d", &choice);

  switch(choice) {
   case 1: {
    v = read_vector();
    printf("The vector read is: ");
    print_vector(v);
    break;
   }
   case 2: {
    int n;
    printf("Enter the number n: ");
    scanf("%d", &n);
    generate_primes(n);
    break;
   }
   case 3: {
    vector subsequence;
    longest_contiguos(v,&subsequence);
    if (subsequence.length == 1) {
     if (is_prime(subsequence.content[0]))
      printf("%d", subsequence.content[0]);
     else printf("No subsequence found");
    }
    else
     print_vector(subsequence);
    continue;

   }
   case 0:
    printf("Exiting...");
   exit(0);
   default:
    printf("Invalid choice, choose a number in range 0-2\n");
   //continue;
  }
 }
 return 0;
}