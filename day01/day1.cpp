#include <iostream>
#include<bits/stdc++.h>

using namespace std;

int
increasingCount (const vector < int >&v)
{
  int previousInput = INT_MAX;
  int count = 0;
for (auto & n:v)
    {
      if (n > previousInput)
	count++;
      previousInput = n;
    }

  return count;
}

int
main ()
{
  int input;
  int count = 0;
  int previousInput = INT_MAX;
  vector < int >input_vec;
  while (cin >> input)
    {
      input_vec.push_back (input);
    }

  vector < int >transformed_vec;
  for (int i = 0; i <= input_vec.size () - 3; i++)
    {
      int sum = 0;
      for (int j = i; j < i + 3; j++)
	{
	  sum += input_vec[j];
	}
      transformed_vec.push_back (sum);
    }

  cout << increasingCount (transformed_vec) << endl;

  return 0;
}
