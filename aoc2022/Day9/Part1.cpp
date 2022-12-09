#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day9/input.txt", { "\n", " " });

    std::unordered_set<std::string> positions;
    
    int hx = 0;
    int hy = 0;
    int tx = 0;
    int ty = 0;
    for (auto& in : root.C)
    {
        auto& dir = in.C[0].E;
        int num = in.C[1].I;
        
        int dx = 0;
        if (dir == "L") dx = -1;
        if (dir == "R") dx = 1;
        int dy = 0;
        if (dir == "U") dy = 1;
        if (dir == "D") dy = -1;
        for (int step = 0; step < num; step++)
        {
            hx += dx;
            hy += dy;
            
            if (abs((float)hx - tx) > 1.f || abs((float)hy - ty) > 1.f)
            {
                tx = hx - dx;
                ty = hy - dy;
            }

            positions.insert(std::to_string(tx) + "|" + std::to_string(ty));
        }
    }
    
    u32 unique = positions.size();
    // std::cout << "Value: " << score << std::end;

    return 0;
}