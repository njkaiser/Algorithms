#include <iostream>
#include <math.h>


int karatsuba(int x, int y)
{
  // assumes length of x and y are the same
  int n = static_cast<int>(ceil(log10(x)));

  // check for base case
  if(n <= 1)
  {
    return x * y;
  }
  std::cout << "FOR LENGTH " << n << std::endl;

  int split = static_cast<int>(pow(10, static_cast<int>(n / 2)));

  int a = static_cast<int>(x / split);
  int b = x - a * split;
  int c = static_cast<int>(y / split);
  int d = y - c * split;

  std::cout << a << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  std::cout << d << std::endl;

  int ac = karatsuba(a, c);
  int bd = karatsuba(b, d);
  int abcd = karatsuba(a + b, c + d);
  int adbc = abcd - ac - bd;

  // assumes length is a power of 2
  int ans = pow(10, n) * ac + pow(10, n / 2) * adbc + bd;

  return ans;
}



int main(void)
{
  // long long a = 3141592653589793238462643383279502884197169399375105820974944592;
  // long long b = 2718281828459045235360287471352662497757247093699959574966967627;

  int x = 1234;
  int y = 5678;

  std::cout << karatsuba(x, y) << std::endl;

  return 0;
}
