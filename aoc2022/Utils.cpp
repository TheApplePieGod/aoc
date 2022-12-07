#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

void ReadInternal(ReadObject& node, const std::vector<std::string>& split, u32 splitIndex)
{
    if (splitIndex >= split.size()) return;

    node.D = split[splitIndex];
    
    auto values = StringUtils::Split(node.E, split[splitIndex]);
    for (auto& value : values)
    {
        auto& elem = node.C.emplace_back();
        elem.E = value;
        if (value.size() < 15)
            elem.I = atoi(value.c_str());
        
        ReadInternal(elem, split, splitIndex + 1);
    }
}

ReadObject FilesystemUtils::Read(std::string_view path, const std::vector<std::string>& split)
{
    ReadObject root;
    root.E = ReadAsString(path);
    
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
                auto trimmed = Trim(Substring(buffer, 0, buffer.length() - delim.length()));
                output.emplace_back(trimmed);
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

std::string_view StringUtils::Trim(std::string_view str)
{
    if (str.empty()) return str;

    int start = 0;
    int end = str.size() - 1;
    while ((str[start] == ' ' || str[start] == '\n' || str[start] == '\t' || str[start] == '\r') && start <= end)
        start++;
    while ((str[end] == ' ' || str[end] == '\n' || str[end] == '\t' || str[end] == '\r') && end >= 0)
        end--;

    return std::string_view(str.data() + start, end + 1);
}

std::string StringUtils::Join(const std::vector<std::string>& strs, std::string delim)
{
    if (strs.empty()) return std::string();

    std::string result = strs[0];
    for (u32 i = 1; i < strs.size(); i++)
    {
        if (!delim.empty())
            result += delim;
        result += strs[i];
    }
    
    return result;
}