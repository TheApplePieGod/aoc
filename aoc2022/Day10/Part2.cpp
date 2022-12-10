#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day10/input.txt", { "\n", " " });
    
    std::vector<std::vector<char>> pixels;
    for (int i = 0; i < 6; i++)
    {
        std::vector<char> v;
        for (int j = 0; j < 40; j++)
            v.push_back(' ');
        pixels.push_back(v);
    }

    int x = 1;
    u32 cycle = 0;
    u32 score = 0;
    u32 row = 0;
    auto updatePixel = [&]()
    {
        if ((int)abs((float)x - (cycle % 40)) < 2)
            pixels[row][cycle % 40] = '#';
        cycle++;
        if (cycle % 40 == 0)
            row++;
    };

    for (auto& line : root.C)
    {
        auto& ins = line.C[0].E;
        if (ins == "noop")
        {
            updatePixel();
            continue;
        }
        
        int val = line.C[1].I;
        updatePixel();
        updatePixel();
        x += val;
    }
    
    for (auto& row : pixels)
    {
        for (char c : row)
            std::cout << c << " ";
        std::cout << std::endl;
    }
    // std::cout << "Value: " << score << std::end;

    return 0;
}