#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

int main()
{
    Timer timer("Day7Part1");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day7/input.txt");
    std::vector<int> positions = StringUtils::SplitToInt(lines[0], ",");
    
    int minPos = 99999999;
    int maxPos = 0;
    for (int pos : positions)
    {
        if (pos < minPos) minPos = pos;
        if (pos > maxPos) maxPos = pos;
    }

    int minFuel = 99999999;
    for (int i = minPos; i <= maxPos; i++)
    {
        int fuel = 0;
        for (int pos : positions)
            fuel += abs(pos - i);
        if (fuel < minFuel) minFuel = fuel;
    }

    std::cout << "Min fuel: " << minFuel << std::endl;

    return 0;
}