#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <string>

using namespace std;

void create_hard_link_from_s(string &s)
{
    string to = s;
    string extention = "";
    if (s.find('.') != string::npos)
    {
        while (s.back() != '.')
        {
            extention.push_back(s.back());
            s.pop_back();
        }
        extention.push_back('.');
        reverse(extention.begin(), extention.end());
    }
    for (int i = 0; i < 100; ++i)
    {
        string to_check = s + to_string(i) + extention;
        if (!filesystem::exists(filesystem::path(to_check)))
        {
            filesystem::create_hard_link(to, to_check);
            return;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    string dir;
    cin >> dir;
    filesystem::path fs_path(dir);
    if (!filesystem::exists(fs_path))
    {
        ofstream file;
        file.open(dir);
        //Oppened
        file.close();
    }
    else
    {
        create_hard_link_from_s(dir); //dir is path to hard link after this
    }

    return 0;
}