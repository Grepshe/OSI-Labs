#include <iostream>

using namespace std;

int main()
{
  int m;
  cin >> m;
  int fib_n = 1;
  int fib_prevn = 1;
  int n = 1;
  while (fib_n <= m)
  {
    fib_prevn = fib_n + fib_prevn;
    swap(fib_n, fib_prevn);
    n++;
  }
  cout << n << " " << fib_n;

  return 0;
}