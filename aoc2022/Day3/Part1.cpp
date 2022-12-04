#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto lines = FilesystemUtils::ReadLines("../../Day3/input.txt");
    
    int score = 0;
    for (auto& line : lines)
    {
        auto str1 = StringUtils::Substring(line, 0, line.size() / 2);
        auto str2 = StringUtils::Substring(line, line.size() / 2);
        
        char same;
        for (char c : str1)
        {
            if (StringUtils::Contains(str2, c))
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