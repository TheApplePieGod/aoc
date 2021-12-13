#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

struct ScopeEvaluation
{
    int NextPos;
    int ErrorPos;
    bool IsIncomplete = false;
};

char GetClosingChar(char og)
{
    switch (og)
    {
        default: return 0;
        case '(': return ')';
        case '[': return ']';
        case '{': return '}';
        case '<': return '>';
    }
}

int GetPointValue(char c)
{
    switch (c)
    {
        default: return 0;
        case ')': return 3;
        case ']': return 57;
        case '}': return 1197;
        case '>': return 25137;
    }
}

ScopeEvaluation EvaluateScope(const std::string& line, int startPos, bool root = false)
{
    int pos = startPos + 1;
    for (pos; pos < line.size(); pos++)
    {
        char c = line[pos];
        if (c == '(' || c == '[' || c == '{' || c == '<')
        {
            auto res = EvaluateScope(line, pos);
            pos = res.NextPos;
            if (res.ErrorPos != -1)
                return res;
        }
        else if (c != GetClosingChar(line[startPos]))
            return { -1, pos };
        else if (!root)
            return { pos, -1 };
    }

    return { pos, -1, pos >= line.size() || line[pos - 1] != line[startPos] };
}

int main()
{
    Timer timer("Day10Part1");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day10/input.txt");
    
    int score = 0;
    for (auto& line : lines)
    {
        ScopeEvaluation eval = EvaluateScope(line, 0, true);
        if (!eval.IsIncomplete && eval.ErrorPos != -1)
            score += GetPointValue(line[eval.ErrorPos]);
    }

    std::cout << "Score: " << score << std::endl;

    return 0;
}