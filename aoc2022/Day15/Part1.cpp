#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

struct Range
{
    int Begin = 0;
    int End = 0;
    int Invalid = 0;
};

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day15/input.txt", { "\n", " ", "=" });
    
    u32 y = 2000000;
    std::unordered_map<u32, std::vector<Range>> grid;
    for (auto& line : root.C)
    {
        int sx = line.C[2].C[1].I;
        int sy = line.C[3].C[1].I;
        int bx = line.C[8].C[1].I;
        int by = line.C[9].C[1].I;
        
        int dist = MathUtils::Abs(sx - bx) + MathUtils::Abs(sy - by);
        for (int i = -dist; i <= dist; i++)
        {
            if (i + sy != y) continue;

            int factor = (i + dist);
            if (i > 0) factor = (dist - i);
            auto& arr = grid[sy + i];
            int start = sx - factor;
            int end = sx + factor;
            int invalid = 0;
            bool add = true;
            for (int j = 0; j < arr.size(); j++)
            {
                if (start <= arr[j].End && start >= arr[j].Begin && end > arr[j].End)
                    start = arr[j].End + 1;
                else if (end >= arr[j].Begin && end <= arr[j].End && start < arr[j].Begin)
                    end = arr[j].Begin - 1;
                else if (start >= arr[j].Begin && end <= arr[j].End)
                {
                    add = false;
                    break;
                }
            }
            if (!add) continue;
            if (sy + i == by && bx >= start && bx <= end)
                invalid++;
            arr.push_back({ start, end, invalid });
        }
    }
    
    int sum = 0;
    auto& arr = grid[y];
    // Remove duplicate intervals
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr.size(); j++)
        {
            if (i == j) continue;
            if (arr[j].Begin >= arr[i].Begin && arr[j].End <= arr[i].End)
            {
                arr[j] = arr.back();
                arr.pop_back();
                j--;
            }
        }
    }

    for (auto& ran : arr)
        sum += ran.End - ran.Begin + 1 - ran.Invalid;
    
    std::cout << sum << std::endl;

    return 0;
}