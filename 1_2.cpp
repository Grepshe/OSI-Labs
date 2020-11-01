#include <bits/stdc++.h>

using namespace std;

int main()
{
  freopen("in.txt", "r", stdin);
  map<char, char> eqal_brac;
  eqal_brac['('] = ')';
  eqal_brac['['] = ']';
  eqal_brac['{'] = '}';
  stack<char> psp_stck;
  string text = "";
  char bufc;
  while (cin >> bufc)
  {
    if (bufc == '(' || bufc == '[' || bufc == '{')
    {
      psp_stck.push(bufc);
    }
    if (bufc == ')' || bufc == ']' || bufc == '}')
    {
      if (psp_stck.empty())
      {
        cout << "No";
        return 0;
      }
      if (eqal_brac[psp_stck.top()] == bufc)
      {
        psp_stck.pop();
      }
      else
      {
        cout << "No";
        return 0;
      }
    }
  }
  if (psp_stck.empty())
  {
    cout << "Yes";
  }
  else
  {
    cout << "No";
  }

  return 0;
}