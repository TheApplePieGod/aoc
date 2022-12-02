#pragma once

#include <vector>
#include <string>

struct FilesystemUtils
{
    static std::vector<int> ReadInts(const std::string& path);
    static std::vector<std::string> ReadLines(const std::string& path);
    static std::string ReadAsString(const std::string& path);
    static std::vector<int> ReadBinary(const std::string& path);
};

struct StringUtils
{
    static std::vector<std::string> Split(const std::string& str, const std::string& delim);
    static std::vector<int> SplitToInt(const std::string& str, const std::string& delim);
};