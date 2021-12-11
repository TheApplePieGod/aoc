#pragma once

#include <vector>
#include <string>

struct FilesystemUtils
{
    static std::vector<int> ReadInts(const std::string& path);
    static std::vector<std::string> ReadLines(const std::string& path);
    static std::vector<int> ReadBinary(const std::string& path);
};