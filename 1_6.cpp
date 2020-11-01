#include <iostream>

using namespace std;

int main()
{
  int n;
  int check = 0;
  cin >> n;
  for (int i = 1; i * i < n; ++i)
    for (int j = 1; j * j < n; ++j)
    {
      if (i * i + j * j == n)
      {
        if (j == check)
          return 0;
        cout << i << " " << j << "\n";
        if (!check)
          check = i;
      }
    }

  return 0;
}