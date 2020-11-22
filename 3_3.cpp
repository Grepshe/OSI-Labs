#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unordered_map>

int factor(int n)
{
    int res = 1;
    for (int i = 1; i <= n; ++i)
        res *= i;
    return res;
}

int main(int argc, char **argv)
{
    std::string a_out_name = "out";
    int n = 1;
    bool a_c = false;
    bool a_o = false;

    for (int i = 1; i < argc; i++)
    {
        if (argv[i][1] == 'c')
            a_c = true;
        if (argv[i][1] == 'n')
            n = atoi(argv[++i]);
        if (argv[i][1] == 'o')
        {
            a_out_name = argv[++i];
            a_o = true;
        }
    }

    std::vector<pid_t> pids;
    int is_main = 1;
    while (n)
    {
        n--;
        pids.push_back(fork());
        if (!pids.back())
        {
            is_main = 0;
            std::string filename = a_out_name;
            filename += ".";
            filename += std::to_string((long)getpid());
            std::ofstream out_file(filename);
            out_file << "Posnanskiy Grigoriy Dmitrievich " << factor((long)getpid() - (long)getppid()) << std::endl;
            break;
        }
    }
    if (is_main)
    {
        for (pid_t i : pids)
            waitpid(i, NULL, NULL);
        std::ofstream out_file;
        if (a_o)
            out_file.open(a_out_name);
        for (long i : pids)
        {
            std::string filename = a_out_name;
            filename += ".";
            filename += std::to_string(i);
            std::ifstream in_file(filename);
            if (a_o)
                out_file << in_file.rdbuf();
            else
                std::cout << in_file.rdbuf();
            if (a_c)
                std::remove(filename.c_str());
        }
    }
    return 0;
}