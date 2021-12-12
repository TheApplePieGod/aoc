#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(char* argv, int argc)
{
    std::vector<std::string> commands = FilesystemUtils::ReadLines("../../../Day2/input.txt");

    vec2 position;
    for (auto& command : commands)
    {
        auto split = StringUtils::Split(command, " ");
        if (split[0] == "forward")
            position.x += stoi(split[1]);
        if (split[0] == "up")
            position.y += stoi(split[1]);
        if (split[0] == "down")
            position.y -= stoi(split[1]);
    }
    
    std::cout << "Final position: (" << position.x << ", " << position.y << ")" << std::endl;

    return 0;
}