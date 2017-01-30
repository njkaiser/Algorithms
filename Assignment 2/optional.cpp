// 1. You are given as input an unsorted array of n distinct numbers, where
// n is a power of 2. Give an algorithm that identifies the second-largest
// number in the array, and that uses at most n+log2n−2 comparisons.


// NEED TO IMPLEMENT - NOT SURE HOW YET


// #include <stdio>
//
// int main(int argc, char **argv)
// {
//
//
//   return 0;
// }

// 2. You are a given a unimodal array of n distinct elements, meaning that
// its entries are in increasing order up until its maximum element, after
// which its elements are in decreasing order. Give an algorithm to compute
// the maximum element that runs in O(log n) time.

// *****************************************************************************
// BINARY SEARCH CAN DO THIS IN log(n) TIME
#include <iostream>
#include <assert.h>


int comp(int arr[], int ind1, int ind2)
{
  std::cout << "indices: " << ind1 << ", " << ind2 << std::endl;
  if(ind2-ind1 <= 1)
  {
    int retval = (arr[ind1] > arr[ind2]) ? arr[ind1] : arr[ind2];
    std::cout << "returned " << retval << " due to adjacent indices" << std::endl;
    return retval;
  }

  int option1 = comp(arr, ind1, ind1+(ind2-ind1)/2);
  int option2 = comp(arr, ind1+(ind2-ind1)/2 + 1, ind2);
  int retval = (option1 > option2) ? option1 : option2;
  std::cout << "returned " << retval << " from comparison" << std::endl;
  // return (option1 > option2) ? option1 : option2;
  return retval;
}


int main(int argc, char **argv)
{
  int arr[] = {5, 6, 7, 8, 4, 2, 1, 0};
  int L = sizeof(arr) / sizeof(arr[0]) - 1;
  int answer = comp(arr, 0, L); // feed it the first and last indices
  std::cout << "answer: " << answer << std::endl;

  return 0;
}
// *****************************************************************************



// 3. You are given a sorted (from smallest to largest) array A of n distinct
// integers which can be positive, negative, or zero. You want to decide
// whether or not there is an index i such that A[i] = i. Design the fastest
// algorithm that you can for solving this problem.

// *****************************************************************************
// // THIS IS BASICALLY BINARY SEARCH AGAIN
// #include <iostream>
//
// int go(int arr[], int ind1, int ind2)
// {
//   std::cout << "indices: " << ind1 << ", " << ind2 << std::endl;
//   if(ind1 == arr[ind1]) { return ind1; }
//   else if(ind2 == arr[ind2]) { return ind2; }
//   else if(ind2-ind1 <= 1) { return -1; }
//   std::cout << "made it here" << std::endl;
//
//   int ans1 = go(arr, ind1 + 1, ind1+(ind2-ind1)/2);
//   int ans2 = go(arr, ind1+(ind2-ind1)/2, ind2 - 1);
//
//   return (ans1 > ans2) ? ans1 : ans2;
// }
//
//
// int main(int argc, char **argv)
// {
//   // indices:   0, 1, 2, 3, 4, 5, 6, 7  (indices for below array)
//   int arr[] = {-1, 0, 1, 2, 5, 6, 7, 8};
//   int L = sizeof(arr) / sizeof(arr[0]) - 1;
//   int answer = go(arr, 0, L); // feed it the first and last indices
//   std::cout << "answer: " << answer << std::endl;
//
//   return 0;
// }
// *****************************************************************************



// 4. You are given an n by n grid of distinct numbers. A number is a local
// minimum if it is smaller than all of its neighbors. (A neighbor of a
// number is one immediately above, below, to the left, or the right. Most
// numbers have four neighbors; numbers on the side have three; the four
// corners have two.) Use the divide-and-conquer algorithm design paradigm
// to compute a local minimum with only O(n) comparisons between pairs of
// numbers. (Note: since there are n^2 numbers in the input, you cannot
// afford to look at all of them. Hint: Think about what types of recurrences
// would give you the desired upper bound.)


// NEED TO IMPLEMENT - NOT SURE HOW YET
