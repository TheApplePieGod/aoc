#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

void ReadInternal(ReadObject& node, const std::vector<std::string>& split, u32 splitIndex)
{
    if (splitIndex >= split.size()) return;

    node.Delimiter = split[splitIndex];
    
    auto values = StringUtils::Split(node.Element, split[splitIndex]);
    for (auto& value : values)
    {
        auto& elem = node.Children.emplace_back();
        elem.Element = value;
        if (value.size() < 15)
        {
            try { elem.IntegerElement = stoi(elem.Element); }
            catch (std::exception e) {}
        }
        
        ReadInternal(elem, split, splitIndex + 1);
    }
}

ReadObject FilesystemUtils::Read(std::string_view path, const std::vector<std::string>& split)
{
    ReadObject root;
    root.Element = ReadAsString(path);
    
    ReadInternal(root, split, 0);
    
    return root;
}

std::vector<int> FilesystemUtils::ReadInts(std::string_view path)
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

std::vector<std::string> FilesystemUtils::ReadLines(std::string_view path)
{
    std::ifstream f(path);
    std::vector<std::string> output;

    std::string line;
    while (std::getline(f, line))
        output.emplace_back(line);

    return output;
}

std::string FilesystemUtils::ReadAsString(std::string_view path)
{
    std::ifstream f(path);
    std::stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}

std::vector<int> FilesystemUtils::ReadBinary(std::string_view path)
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

std::vector<std::string> StringUtils::Split(std::string_view str, std::string_view delim)
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
std::vector<int> StringUtils::SplitToInt(std::string_view str, std::string_view delim)
{
    auto split = Split(str, delim);

    std::vector<int> output;
    output.reserve(split.size());

    for (auto elem : split)
        output.emplace_back(stoi(elem));

    return output;
}

int StringUtils::Find(std::string_view str, std::string_view find)
{
    if (find.empty() || str.empty()) return -1;

    u32 strPtr = 0;
    u32 findPtr = 0;

    while (strPtr < str.size())
    {
        if (find[findPtr] == str[strPtr])
            findPtr++;
        else
        {
            if (findPtr > 0) strPtr--;
            findPtr = 0;
        }

        strPtr++;

        if (findPtr == find.size()) return strPtr - find.size();
    }
    
    return -1;
}

bool StringUtils::Contains(std::string_view str, std::string_view find)
{
    return Find(str, find) != -1;
}

int StringUtils::Find(std::string_view str, char find)
{
    char findArr[2] = { find, 0 };
    return Find(str, findArr);
}

bool StringUtils::Contains(std::string_view str, char find)
{
    return Find(str, find) != -1;
}

std::string_view StringUtils::Substring(std::string_view str, u32 begin, u32 size)
{
    return std::string_view(str.data() + begin, std::min(size, static_cast<u32>(str.size()) - begin));
}