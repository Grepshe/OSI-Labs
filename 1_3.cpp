#include <bits/stdc++.h>

using namespace std;

long long binpow(long long a, long long n)
{
  if (n == 0)
    return 1;
  if (n % 2 == 1)
    return binpow(a, n - 1) * a;
  else
  {
    long long b = binpow(a, n / 2);
    return b * b;
  }
}

int main()
{
  long long prev = 0, curr = 0;
  int i = 1;
  while (prev <= curr)
  {
    prev = curr;
    curr += binpow(i, i);
    i++;
  }
  cout << i;

  return 0;
}