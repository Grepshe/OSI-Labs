#include <filesystem>
#include <iostream>
#include <locale.h>
#include <cstdlib>

using namespace std;

int main()
{
  setlocale(LC_ALL, "Russian");
  system("chcp 1251");
  string dir;
  cin >> dir;
  for (const filesystem::directory_entry& i : filesystem::directory_iterator(dir))
  {
    if(!filesystem::is_directory(i))
      cout << i.path().string() << endl;
  }
  return 0;
}