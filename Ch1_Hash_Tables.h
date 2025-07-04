//
// Created by kendricks on 6/21/25.
//

#ifndef CH1_HASH_TABLES_H
#define CH1_HASH_TABLES_H

#include <stdio.h>

constexpr int number_of_branches = 6;
constexpr int min = 0;
constexpr int max = number_of_branches;

int snow_flakes[][number_of_branches] = {
   {1,2,3,4,5,6},
   {3,2,1,6,5,4},
   {2,3,4,5,6,1},
   {4,5,2,7,8,4},
   {4,4,5,2,7,8},
};

inline bool find_identical_left(const int snowflake1[number_of_branches], const int snowflake2[number_of_branches])
{
   for (int offset = min; offset < max; offset++)
   {
      bool passed = false;
      int s1 = 0;
      int s2 = offset;
      for (int i = 0; i < number_of_branches; i++)
      {
         s2 = s2 < 0 ? s2 + max : s2;
         const int a1 = snowflake1[s1];
         const int a2 = snowflake2[s2];
         passed = a1 == a2;
         if (!passed) break;
         s1++;
         s2--;
      }
      if (passed)
         return true;
   }
   return false;
}

inline bool find_identical_right(const int snowflake1[number_of_branches], const int snowflake2[number_of_branches])
{
   for (int offset = min; offset < max; offset++)
   {
      bool passed = false;
      int s1 = 0;
      int s2 = offset;
      for (int i = 0; i < number_of_branches; i++)
      {
         const int a1 = snowflake1[s1];
         const int a2 = snowflake2[s2];
         passed = a1 == a2;
         if (!passed) break;
         s1++;
         s2++;
         s2 = s2 >= max ? min : s2;
      }
      if (passed)
         return true;
   }
   return false;
}

inline void find_identical()
{
   constexpr int size_of_array = sizeof(snow_flakes)/ sizeof(snow_flakes[0]);
   for (int i1 = 0; i1 < size_of_array ; i1++)
   {
      for (int i2 = i1 + 1; i2 < size_of_array ; i2++)
      {
         const bool passed = find_identical_left(snow_flakes[i1], snow_flakes[i2]) || find_identical_right(snow_flakes[i1], snow_flakes[i2]);
         printf("%d - %d : %s \n", i1, i2, passed ? "passed" : "failed");
      }
   }
}

#endif //CH1_HASH_TABLES_H
