#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::vector<int> FilesystemUtils::ReadInts(const std::string& path)
{
    std::ifstream f(path);
    std::vector<int> output;

    std::string line;
    while (std::getline(f, line))
    {
        if (line.empty()) continue;
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

std::string FilesystemUtils::ReadAsString(const std::string& path)
{
    std::ifstream f(path);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
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

std::vector<std::string> StringUtils::Split(const std::string& str, const std::string& delim)
{
    std::vector<std::string> output;

    std::string buffer;
    for (char c : str)
    {
        buffer.push_back(c);
        if (buffer.length() > delim.length())
        {
            if (strcmp(&buffer.back() - delim.length() + 1, delim.data()) == 0)
            {
                output.emplace_back(buffer.substr(0, buffer.length() - delim.length()));
                buffer.clear();
            }
        }
    }
    if (!buffer.empty())
        output.emplace_back(buffer);

    return output;
}

// not performant but it's fine
std::vector<int> StringUtils::SplitToInt(const std::string& str, const std::string& delim)
{
    auto split = Split(str, delim);

    std::vector<int> output;
    output.reserve(split.size());

    for (auto elem : split)
        output.emplace_back(stoi(elem));

    return output;
}