#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto lines = FilesystemUtils::ReadLines("../../Day3/input.txt");
    
    int score = 0;
    for (int i = 0; i < lines.size(); i += 3)
    {
        char same;
        for (auto c : lines[i])
        {
            if (StringUtils::Contains(lines[i + 1], c) && StringUtils::Contains(lines[i + 2], c))
            {
                same = c;
                break;
            }
        }
        
        if (same >= 'a' && same <= 'z')
            score += same - 'a' + 1;
        else
            score += same - 'A' + 27;
    }

    std::cout << "Value: " << score << std::endl;

    return 0;
}