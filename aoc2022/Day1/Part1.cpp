#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day1/input.txt", { "\n\n", "\n" });
    
    int max = 0;
    for (auto& group : root.Children)
    {
        int sum = 0;
        for (auto& value : group.Children)
            sum += value.IntegerElement;
        if (sum > max) max = sum;
    }
    
    std::cout << "Max: " << max << std::endl;

    return 0;
}