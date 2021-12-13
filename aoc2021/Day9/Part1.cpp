#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

int main()
{
    Timer timer("Day9Part1");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day9/input.txt");
    
    // parse
    int width = 0;
    int height = 0;
    std::vector<int> map;
    for (auto& line : lines)
    {
        width = line.size();
        height++;
        auto values = StringUtils::SplitToInt(line, "");
        map.insert(map.end(), values.begin(), values.end());
    }

    int sum = 0;
    for (int i = 0; i < map.size(); i++)
    {
        int col = i % width;
        if (i < width * height - width && map[i + width] <= map[i]) continue;
        if (i >= width && map[i - width] <= map[i]) continue;
        if (col != 0 && map[i - 1] <= map[i]) continue;
        if (col != width - 1 && map[i + 1] <= map[i]) continue;
        sum += map[i] + 1;
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}