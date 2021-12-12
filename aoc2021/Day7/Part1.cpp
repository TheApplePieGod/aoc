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
    
    

    //std::cout << "Count: " << fish.size() << std::endl;

    return 0;
}