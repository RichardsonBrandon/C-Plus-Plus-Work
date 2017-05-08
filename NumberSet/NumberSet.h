#ifndef NUMBERSET_H
#define NUMBERSET_H
#include <iostream>
#include <vector>
using namespace std;

class NumberSet
{
public:

   NumberSet();
    //Default constructor
   void add(int A);
    //Function that adds the users' chosen number to the set
   int searchVector(int A);
    // Function that searches the vector to determine whether
    // A number is in the set twice
   void remove(int A);
    //Function that removes the users' chosen element of the set
   void clear();
    //Function that clears the users' set
   int size();
    //Function that returns the size of the users' set
   void output();
    //Function that outputs the users' set
private:

   vector<int> v;

};

#endif // NUMBERSET_H
