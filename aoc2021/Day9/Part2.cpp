#include <iostream>
#include <unordered_map>
#include <algorithm>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

int CalcBasinSize(const std::vector<int>& map, int mapWidth, std::unordered_map<int, bool>& checked, int lowPointIndex)
{
    if (map[lowPointIndex] == 9) return 0;
    if (checked[lowPointIndex]) return 0;

    int size = 1;
    int col = lowPointIndex % mapWidth;

    if (lowPointIndex >= mapWidth)
        if (map[lowPointIndex - mapWidth] > map[lowPointIndex])
            size += CalcBasinSize(map, mapWidth, checked, lowPointIndex - mapWidth);
    if (lowPointIndex < map.size() - mapWidth)
        if (map[lowPointIndex + mapWidth] > map[lowPointIndex])
            size += CalcBasinSize(map, mapWidth, checked, lowPointIndex + mapWidth);
    if (col != 0)
        if (map[lowPointIndex - 1] > map[lowPointIndex])
            size += CalcBasinSize(map, mapWidth, checked, lowPointIndex - 1);
    if (col != mapWidth - 1)
        if (map[lowPointIndex + 1] > map[lowPointIndex])
            size += CalcBasinSize(map, mapWidth, checked, lowPointIndex + 1);

    checked[lowPointIndex] = true;
    return size;
}

int main()
{
    Timer timer("Day9Part2");
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

    std::vector<int> basinSizes;
    for (int i = 0; i < map.size(); i++)
    {
        int col = i % width;
        if (i < map.size() - width && map[i + width] <= map[i]) continue;
        if (i >= width && map[i - width] <= map[i]) continue;
        if (col != 0 && map[i - 1] <= map[i]) continue;
        if (col != width - 1 && map[i + 1] <= map[i]) continue;
        std::unordered_map<int, bool> checked;
        basinSizes.emplace_back(CalcBasinSize(map, width, checked, i));
    }

    std::sort(basinSizes.begin(), basinSizes.end());

    int answer = basinSizes.back() * *(basinSizes.end() - 2) * *(basinSizes.end() - 3);
    std::cout << "Answer: " << answer << std::endl;

    return 0;
}