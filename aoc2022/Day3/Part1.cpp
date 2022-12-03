#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto lines = FilesystemUtils::ReadLines("../../Day3/input.txt");
    
    int score = 0;
    for (auto& line : lines)
    {
        int start0 = 0;
        int start1 = line.size() / 2;

        while (line[start0] != line[start1])
        {
            start1++;
            if (start1 >= line.size())
            {
                start1 = line.size() / 2;
                start0++;
            }
        }
        
        char same = line[start0];
        if (same >= 'a' && same <= 'z')
            score += same - 'a' + 1;
        else
            score += same - 'A' + 27;
    }

    std::cout << "Value: " << score << std::endl;

    return 0;
}