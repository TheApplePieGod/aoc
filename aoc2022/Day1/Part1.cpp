#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto data = FilesystemUtils::ReadAsString("../../Day1/input.txt");
    auto elves = StringUtils::Split(data, "\n\n");
    
    int max = 0;
    for (auto& data : elves)
    {
        auto values = StringUtils::Split(data, "\n");
        int sum = 0;
        for (auto& value : values)
        {
            int num = stoi(value);
            sum += num;
        }
        if (sum > max) max = sum;
    }
    
    std::cout << "Max: " << max << std::endl;

    return 0;
}