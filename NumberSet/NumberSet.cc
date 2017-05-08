#include <iostream>
#include <vector>
#include "NumberSet.h"
using namespace std;

NumberSet::NumberSet() : v(0)
{
// empty
}

void NumberSet::add(int A)
{
   v.push_back(A);
}

int NumberSet::searchVector(int A)
{
   for (int x = 0; x < v.size(); x++)
      if (v[x] == A)
         return x;
   return -1;
}

void NumberSet::remove(int A)
{
     for (int x = 0; x < v.size(); x++)

      if (v[x] == A)
        v.erase(v.begin() + x);

   cout << "\n";
}

void NumberSet::clear()
{
   v.clear();
}

int NumberSet::size()
{
   cout << v.size() << "\n\n";
}

void NumberSet::output()
{
   for (int x = 0; x < v.size(); x++)
      cout << v[x] << " ";
   cout << "\n";
}



