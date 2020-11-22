#include <filesystem>
#include <iostream>
#include <locale.h>
#include <cstdlib>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    freopen("parse.txt", "w", stdout);
    string dir;
    cin >> dir;
    for (const filesystem::directory_entry &i : filesystem::directory_iterator(dir))
    {
        if (!filesystem::is_directory(i))
        {
            string finam = i.path().filename().string();
            if (finam.find("Greg") != string::npos)
            {
                string res = "";
                res += "			<option value=\"../my_map_solutions/";
                res += finam;
                res += "\">";
                res += finam;
                res.pop_back();
                res.pop_back();
                res.pop_back();
                res.pop_back();
                res += "</option>";
                cout << res << endl;
            }
        }
    }
    return 0;
}