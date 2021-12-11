#include "FilesystemUtils.h"

#include <iostream>
#include <fstream>

std::vector<int> FilesystemUtils::ReadInts(const std::string& path)
{
    std::ifstream f(path);
    std::vector<int> output;

    std::string line;
    while (std::getline(f, line))
    {
        try
        {
            output.emplace_back(stoi(line));
        }
        catch (std::exception e)
        { std::cout << "Failed to parse file" << std::endl; }
    }

    return output;
}

std::vector<std::string> FilesystemUtils::ReadLines(const std::string& path)
{
    std::ifstream f(path);
    std::vector<std::string> output;

    std::string line;
    while (std::getline(f, line))
        output.emplace_back(line);

    return output;
}

std::vector<int> FilesystemUtils::ReadBinary(const std::string& path)
{
    std::ifstream f(path);
    std::vector<int> output;

    std::string line;
    while (std::getline(f, line))
    {
        int finalNum = 0;

        for (char c : line)
            finalNum = (finalNum << 1) | (c == '0' ? 0 : 1);

        output.emplace_back(finalNum);
    }

    return output;
}