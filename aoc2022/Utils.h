#pragma once
#include "Base.h"

struct ReadObject
{
    std::vector<ReadObject> C; // Children
    std::string E; // Element
    int I = 0; // Integer element
    std::string D; // Delimiter
    
    inline bool HasChildren() const { return !C.empty(); }
    inline bool HasElement() const { return !HasChildren(); }
};

struct FilesystemUtils
{
    static ReadObject Read(std::string_view path, const std::vector<std::string>& split);
    static std::vector<int> ReadInts(std::string_view path);
    static std::vector<std::string> ReadLines(std::string_view path);
    static std::string ReadAsString(std::string_view path);
    static std::vector<int> ReadBinary(std::string_view path);
};

struct StringUtils
{
    static std::vector<std::string> Split(std::string_view str, std::string_view delim);
    static std::vector<int> SplitToInt(std::string_view str, std::string_view delim);
    static int Find(std::string_view str, std::string_view find);
    static bool Contains(std::string_view str, std::string_view find);
    static int Find(std::string_view str, char find);
    static bool Contains(std::string_view str, char find);
    static std::string_view Substring(std::string_view str, u32 begin, u32 size = 999999);
};