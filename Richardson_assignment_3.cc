// Author: Brandon Richardson
// Date: 3/16/15
// CSCI 3100 A

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

string ispalindrome(char A[], int start, int end);

int main()
{
   char input[50];

   fstream textfile;
   textfile.open("inputfile.txt");

   while (textfile >> input)
   {
      int len = strlen(input);
      cout << ispalindrome(input, 0, len - 1);
   }

   textfile.close();

   return 0;
}

string ispalindrome(char A[], int start, int end)
{
   if (start >= end)
   {
      return ("YES\n");
   }

   if (A[start] != A[end])
   {
      return ("NO\n");
   }
   return ispalindrome(A, ++start, --end);
}
