#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(char* argv, int argc)
{
    std::vector<std::string> commands = FilesystemUtils::ReadLines("../../../Day2/input.txt");

    vec2 position;
    f32 aim = 0.f;
    for (auto& command : commands)
    {
        auto split = StringUtils::Split(command, " ");
        if (split[0] == "forward")
        {
            int val = stoi(split[1]);
            position.x += val;
            position.y -= aim * val; 
        }
        if (split[0] == "up")
            aim -= stoi(split[1]);
        if (split[0] == "down")
            aim += stoi(split[1]);
    }
    
    std::cout << "Final position: (" << position.x << ", " << position.y << ")" << std::endl;

    return 0;
}