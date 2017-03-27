// REQUIRED FILE: QuickSort.txt

// The file contains all of the integers between 1 and 10,000 (inclusive,
// with no repeats) in unsorted order. The integer in the ith row of the
// file gives you the ith entry of an input array. Your task is to compute
// the total number of comparisons used to sort the given input file by
// QuickSort. As you know, the number of comparisons depends on which
// elements are chosen as pivots, so we'll ask you to explore three
// different pivoting rules.

// You should not count comparisons one-by-one. Rather, when there is a
// recursive call on a subarray of length m , you should simply add m − 1
// to your running total of comparisons. (This is because the pivot element
// is compared to each of the other m − 1 elements in the subarray in this
// recursive call.)

// WARNING: The Partition subroutine can be implemented in several different
// ways, and different implementations can give you differing numbers of
// comparisons. For this problem, you should implement the Partition
// subroutine exactly as it is described in the video lectures (otherwise you
// might get the wrong answer).

// TODO: DIRECTIONS FOR PROBLEM 1:
// For the first part of the programming assignment, you should always use the
// first element of the array as the pivot element.

// TODO: DIRECTIONS FOR PROBLEM 2:
// Compute the number of comparisons (as in Problem 1), always using the
// final element of the given array as the pivot element. Again, be sure to
// implement the Partition subroutine exactly as it is described in the video
// lectures.

// TODO: DIRECTIONS FOR THIS PROBLEM:
// Compute the number of comparisons (as in Problem 1), using the
// "median-of-three" pivot rule. [The primary motivation behind this rule is
// to do a little bit of extra work to get much better performance on input
// arrays that are nearly sorted or reverse sorted.] In more detail, you should
// choose the pivot as follows. Consider the first, middle, and final elements
// of the given array. (If the array has odd length it should be clear what the
// "middle" element is; for an array with even length 2k, use the kth element
// as the "middle" element. So for the array 4 5 6 7, the "middle" element is
// the second one ---- 5 and not 6!) Identify which of these three elements is
// the median (i.e., the one whose value is in between the other two), and use
// this as your pivot. As discussed in the first and second parts of this
// programming assignment, be sure to implement Partition exactly as described
// in the video lectures (including exchanging the pivot element with the
// first element just before the main Partition subroutine).
//
// EXAMPLE: For the input array 8 2 4 5 7 1 you would consider the first (8),
// middle (4), and last (1) elements; since 4 is the median of the set
// {1,4,8}, you would use 4 as your pivot element.

// Recall from the lectures that, just before the main Partition subroutine,
// you should exchange the pivot element (i.e., the last element) with the
// first element.

#include <fstream>
#include <iostream>
#include <string>



class QuickSort
{
public:
  int comparisons = 0;
  int method_;


private:
  void swap(int arr[], int index1, int index2)
  {
    int temp = arr[index1];
    arr[index1] = arr[index2];
    arr[index2] = temp;
  }

  int partition(int arr[], int L, int R)
  {
    comparisons += R-L-1; // counting how many comparisons are made

    int pivot;
    int idx;

    if(method_ == 0)
    {
      pivot = arr[L];
      idx = L;
    }
    else if(method_ == 1)
    {
      pivot = arr[R];
      idx = R;
    }
    else if(method_ == 2)
    {
      if((arr[L] >= arr[(L+R)/2]) && (arr[L] <= arr[R]))
      {
        pivot = arr[L];
        idx = L;
      }
      else if((arr[L] <= arr[(L+R)/2]) && (arr[L] >= arr[R]))
      {
        pivot = arr[L];
        idx = L;
      }
      else if((arr[(L+R)/2] >= arr[L]) && (arr[(L+R)/2] <= arr[R]))
      {
        pivot = arr[(L+R)/2];
        idx = (L+R)/2;
      }
      else if((arr[(L+R)/2] <= arr[L]) && (arr[(L+R)/2] >= arr[R]))
      {
        pivot = arr[(L+R)/2];
        idx = (L+R)/2;
      }
      else if((arr[R] >= arr[(L+R)/2]) && (arr[R] <= arr[L]))
      {
        pivot = arr[R];
        idx = R;
      }
      else if((arr[R] <= arr[(L+R)/2]) && (arr[R] >= arr[L]))
      {
        pivot = arr[R];
        idx = R;
      }
      else
        std::cout << "WTF MATE" << std::endl;
    }
    else
      std::cout << "ERROR: INVALID METHOD PASSED TO PARTITION FUNCTION (options are 0, 1, or 2)" << std::endl;

    swap(arr, L, idx); // set pivot as first value so we can do comparisons
    int swapcount = 0;
    int i = L + 1;
    for(int j = L + 1; j <= R; ++j)
    {
      if(arr[j] < pivot)
      {
        if(i != j && arr[i] > pivot) // make sure we don't do unnecessary swaps
        {
          swap(arr, j, i);
          ++swapcount;
        }
        ++i;
      }
    }
    swap(arr, L, i-1);
    return i-1; // this is the pivot location, to be used for recursion
  }


void Sort(int arr[], int L, int R)
{
  if(R - L < 1) { ; } // base case #1 - do nothing
  else if((R - L < 2) && (arr[L] > arr[R]))  // base case #2 - swap if needed
  {
    swap(arr, L, R);
  }
  else // if not either of the base cases, do stuff
  {
    int pivotindex = partition(arr, L, R);
    Sort(arr, L, pivotindex-1);
    Sort(arr, pivotindex+1, R);
  }
}


public:
  QuickSort(int arr[], int L, int R, int method)
  {
    // int arr_[R-L+1] = arr; // unnecessary to create new array on heap, waste of memory/time
    method_ = method;
    Sort(arr, L, R);
  }
}; // END OF QuickSort CLASS
//##############################################################################


int main(int argc, char **argv)
{
  int n = 10000; // # of integers in file
  int arr[n];    // data structure for holding input values from file
  std::string m; // string parser individual values

  // import data from file
  std::ifstream input;
  input.open("QuickSort.txt");
  for(int i = 0; i < n; ++i)
  {
    std::getline(input, m);
    arr[i] = std::stoi(m, nullptr);
  }
  input.close();

  // debug test case 1:
  // int n = 8;
  // int arr[8] = {3, 8, 2, 5, 1, 4, 7, 6};

  // debug test case 2:
  // int n = 50;
  // int arr[50] = {17, 47, 15, 23, 33, 2, 34, 41, 45, 35, 36, 14, 3, 32, 40, 31, 38, 44, 39, 1, 50, 10, 48, 24, 29, 18, 42, 43, 5, 37, 28, 21, 13, 19, 20, 49, 16, 25, 6, 27, 9, 46, 8, 12, 30, 22, 4, 11, 7, 26};

  // debug test case 3: reverse order (to make performance discrepancy apparent)
  // int n = 5000;
  // int arr[5000];
  // for(int i = 0; i < n; ++i)
  // {
  //   arr[i] = n-i;
  // }

  QuickSort qs = QuickSort(arr, 0, n-1, 2); // 0=first, 1=last, 2=median (see instructions)

  // verify everything looks good
  std::cout << "           first 10: ";
  for(int a = 0; a < 10; ++a) // print out first 10, just to check
  { std::cout << arr[a] << ' '; }
  std::cout << std::endl;

  // verify everything looks good
  std::cout << "            last 10: ";
  for(int a = n-10; a < n; ++a) // print out last 10, just to check
  { std::cout << arr[a] << ' '; }
  std::cout << std::endl;

  // verify correct order
  int tmp = 99;
  int maxdiff = 0;
  for(int m = 0; m < n-1; ++m)
  {
    tmp = arr[m+1] - arr[m];
    maxdiff = (tmp > maxdiff) ? tmp : maxdiff;
  }
  std::cout << "max difference in array: " << maxdiff << std::endl;

  // verify min/max are correct
  int max = 0;
  int min = 999;
  for(int m = 0; m < n; ++m)
  {
    max = (arr[m] > max) ? arr[m] : max;
    min = (arr[m] < min) ? arr[m] : min;
  }
  std::cout << "max value in array: " << max << std::endl;
  std::cout << "min value in array: " << min << std::endl;

  // print out the value we're actually looking for
  std::cout << "number of comparisons made: " << qs.comparisons << std::endl;

  return 0;
}
