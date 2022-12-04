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
            score += 1;
            if (left == 'C') score += 6;
            if (left == 'A') score += 3;
        }
        if (right == 'Y')
        {
            score += 2;
            if (left == 'A') score += 6;
            if (left == 'B') score += 3;
        }
        if (right == 'Z')
        {
            score += 3;
            if (left == 'B') score += 6;
            if (left == 'C') score += 3;
        }
    }

    std::cout << "Count: " << score << std::endl;

    return 0;
}