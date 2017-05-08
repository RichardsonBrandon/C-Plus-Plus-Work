/*
1. Create the comparison class - funnyorder: Given two positive integers a
and b.  Let a' be the remainder of (a divided by 10) and b' the remainder
of (b divided by 10).  funnyorder returns true if a' < b'; returns false
otherwise.  For example, 15 is "less" than 7 according to funnyorder.

2. print the set elements with a space between the elements
(with respect to funnyorder).


Here is an example:
input: 10 2 41 8 9 31 0
output 10 41 2 8 9
 */

// Brandon Richardson
// 4/16/15
// CSCI 3000 A
// Assignment 5

#include <iostream>
#include <set>
using namespace std;


//1. declare and define the funnyorder:
struct funnyorder
{
  bool operator() (int a, int b)
  {
     int a_prime, b_prime;

     a_prime = a % 10;
     b_prime = b % 10;

     return a_prime < b_prime;
  }
};




int main()
{
  set<int, funnyorder> A;
  int in;
  cout<<"\nEnter a sequence of positive integers (ends your sequence with 0):";
  while(cin>>in)
   {
     if (in==0)
       break;
     A.insert(in);
   }

  //2. print the set elements
  set<int, funnyorder>::const_iterator i;
  for (i = A.begin( ); i != A.end( ); i++)
    cout << *i << " ";
  cout << endl;




  return 0;
}
