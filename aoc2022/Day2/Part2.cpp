#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../Day2/input.txt");

    int score = 0;
    for (auto& line : lines)
    {
        auto data = StringUtils::Split(line, " ");
        char left = data[0][0];
        char right = data[1][0];
        
        if (right == 'X')
        {
            if (left == 'A') score += 3;
            if (left == 'B') score += 1;
            if (left == 'C') score += 2;
        }
        if (right == 'Y')
        {
            score += 3;
            if (left == 'A') score += 1;
            if (left == 'B') score += 2;
            if (left == 'C') score += 3;
        }
        if (right == 'Z')
        {
            score += 6;
            if (left == 'A') score += 2;
            if (left == 'B') score += 3;
            if (left == 'C') score += 1;
        }
    }

    std::cout << "Count: " << score << std::endl;

    return 0;
}