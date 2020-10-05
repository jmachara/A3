/*
* class to test string_set
*
*/

#include "string_set.h"
#include <iostream>


int main()
{
   cs3505::string_set set(10);
   for (int i = 0; i < 20000; i++)
   {
      std::string word = std::to_string(i);
      set.add(word);
   }

   return 0;
}