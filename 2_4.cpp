#include <filesystem>
#include <fstream>
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <string>

using namespace std;

void perms_write(filesystem::perms p)
{
    namespace fs = filesystem;
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
              << '\n';
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");
    string dir;
    cin >> dir;
    filesystem::path fs_path(dir);
    filesystem::create_symlink(fs_path, "my_symlink");
    auto perm = filesystem::status("my_symlink").permissions();
    perms_write(perm);

    return 0;
}