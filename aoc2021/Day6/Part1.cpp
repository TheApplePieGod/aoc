#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

int main()
{
    Timer timer("Day6Part1");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day6/input.txt");
    std::vector<int> fish = StringUtils::SplitToInt(lines[0], ",");
    
    for (int day = 0; day < 80; day++)
    {
        int startingSize = fish.size();
        for (int i = 0; i < startingSize; i++)
        {
            if (fish[i] == 0)
            {
                fish[i] = 6;
                fish.emplace_back(8);
            }
            else
                fish[i]--;
        }
    }

    std::cout << "Count: " << fish.size() << std::endl;

    return 0;
}