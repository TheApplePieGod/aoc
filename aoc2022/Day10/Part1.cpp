#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day10/input.txt", { "\n", " " });

    std::vector<u32> cycles = { 20, 60, 100, 140, 180, 220 };
    u32 cycle = 0;
    u32 score = 0;
    u32 x = 1;
    auto updateScore = [&](bool uc = true)
    {
        for (u32 c : cycles)
            if (c == cycle)
                score += c * x;
        if (uc)
            cycle++;
    };

    for (auto& line : root.C)
    {
        updateScore(false);
        auto& ins = line.C[0].E;
        if (ins == "noop")
        {
            cycle++;
            continue;
        }
        
        int val = line.C[1].I;
        cycle++;
        updateScore();
        x += val;
    }
    
    // std::cout << "Value: " << score << std::end;

    return 0;
}