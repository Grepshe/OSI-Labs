#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <string>
#include <chrono>
#include <ctime>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    string dir;
    cin >> dir;
    vector<pair<filesystem::file_time_type, string>> vec;
    if (dir == "NONE")
        dir = filesystem::current_path().string();
    for (const filesystem::directory_entry &i : filesystem::directory_iterator(dir))
    {
        if (!filesystem::is_directory(i))
        {
            vec.push_back({filesystem::last_write_time(i.path()), i.path().string()});
        }
    }
    sort(vec.begin(), vec.end());
    //Will be standart in C++20
    for (auto &i : vec)
    {
        cout << i.second << endl;
    }
    return 0;
}