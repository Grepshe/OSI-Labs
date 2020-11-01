#include <bits/stdc++.h>

using namespace std;

template <class T, class = enable_if<is_integral_v<T>>>
T my_gcd(T a, T b)
{
  return b ? gcd(b, a % b) : a;
}

int main()
{
  int a, b;
  cin >> a >> b;
  cout << my_gcd(a, b);

  return 0;
}