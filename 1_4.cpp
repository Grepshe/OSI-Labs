#include <iostream>

using namespace std;

int main()
{
  int n;
  cin >> n;
  int skipped_odds_count = (1 + (n - 1)) * (n - 1) / 2;
  int res = (2 * (2 * skipped_odds_count + 1) + 2 * (n - 1)) * n / 2;
  cout << n << "^3 = " << res;

  return 0;
}