#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <string>
#include <chrono>
#include <ctime>
#include <algorithm>

using namespace std;

time_t to_time_t(filesystem::file_time_type time_point)
{
    using namespace chrono;
    auto system_clock_time_point = time_point_cast<
        system_clock::duration>(time_point -
                                filesystem::file_time_type::clock::now() + system_clock::now());
    return system_clock::to_time_t(system_clock_time_point);
}

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
        auto tim = to_time_t(i.first);
        cout << i.second << " " << std::asctime(localtime(&tim)) << endl;
    }
    return 0;
}
