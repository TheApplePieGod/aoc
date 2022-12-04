#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day2/input.txt", { "\n", " " });

    int score = 0;
    for (auto& line : root.Children)
    {
        char left = line.Children[0].Element[0];
        char right = line.Children[1].Element[0];
        
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