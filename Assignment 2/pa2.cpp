// This file contains all of the 100,000 integers between 1 and 100,000
// (inclusive) in some order, with no integer repeated. Your task is to
// compute the number of inversions in the file given, where the ith row
// of the file indicates the ith entry of an array. Because of the large
// size of this array, you should implement the fast divide-and-conquer
// algorithm covered in the video lectures.

#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>



int sortCountSplitInv(int arr[], int e0, int em, int ef)
{
  int L = ef - e0 + 1;
  int tmp[L];
  std::copy(arr + e0, arr + ef + 1, tmp);

  int count = 0;
  int i = 0;
  int j = em - e0 + 1;
  int imax = j;
  int jmax = ef - e0 + 1;
  for(int n = 0; n < L; ++n)
  {
    if(i == imax)
    {
      arr[e0 + n] = tmp[j];
      ++j;
    }
    else if(j == jmax)
    {
      arr[e0 + n] = tmp[i];
      ++count;
      ++i;
    }
    else if(tmp[i] > tmp[j])
    {
      arr[e0 + n] = tmp[j];
      ++j;
    }
    else
    {
      arr[e0 + n] = tmp[i];
      ++count;
      ++i;
    }
    // std::cout << "selected: " << arr[e0 + n] << std::endl;
  }
  return count;
}


int sortcount(int arr[], int e0, int ef)
{
  int L = ef - e0 + 1; // # of elements

  if(L == 1) { return 0; } // base case - nothing to compare to, return
  if(L == 2) // base case - compare 2 elements
  {
    if(arr[e0] > arr[ef])
    {
      int tmp = arr[ef];
      arr[ef] = arr[e0];
      arr[e0] = tmp;
      return 1;
    }
    else { return 0; }
  }

  int n = L / 2 - 1;
  if(L % 2) { n += 1; } // if odd, one of the 2 splits will be 1 longer
  int x = sortcount(arr, e0, e0+n);
  int y = sortcount(arr, e0+n+1, ef);
  int z = sortCountSplitInv(arr, e0, e0+n, ef);

  return z;
}



int main(int argc, char **argv)
{
  int n = 100000; // # of integers in array
  std::string m; // individual values
  int arr[n]; // data structure for holding int values

  std::ifstream input;
  input.open("integerArray.txt");
  for(int i = 0; i < n; ++i)
  {
    std::getline(input, m);
    arr[i] = std::stoi(m, nullptr);
  }
  input.close();

  // int n = 6;
  // int arr[6] = {1, 3, 5, 2, 4, 6};

  // std::sort(arr, arr + n);
  int ans = sortcount(arr, 0, n-1);
  std::cout << "number of split inversions: " << ans << std::endl;

  // for(int a = 0; a < 10; ++a) // print out first 10, just to check
  // { std::cout << arr[a] << std::endl; }

  return 0;
}
