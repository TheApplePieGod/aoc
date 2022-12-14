#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

enum Cell
{
    None = 0,
    Rock = 1,
    Sand = 2
};

int sign(int val)
{
    if (val < 0) return -1;
    if (val == 0) return 0;
    return 1;
}

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day14/input.txt", { "\n", " -> ", "," });
    
    std::vector<std::vector<Cell>> grid;
    for (u32 i = 0; i < 600; i++)
    {
        std::vector<Cell> c;
        for (u32 j = 0; j < 600; j++)
            c.push_back(None);
        grid.push_back(c);
    }

    for (auto& line : root.C)
    {
        vec2i sp = { line.C[0].C[0].I, line.C[0].C[1].I };
        grid[sp.y][sp.x] = Rock;
        for (u32 i = 1; i < line.C.size(); i++)
        {
            vec2i ep = { line.C[i].C[0].I, line.C[i].C[1].I };

            int signx = sign(ep.x - sp.x);
            int signy = sign(ep.y - sp.y);
            while (ep.x != sp.x || ep.y != sp.y)
            {
                sp.x += signx;
                sp.y += signy;
                grid[sp.y][sp.x] = Rock;
            }
        }
    }
    
    vec2i sandPos = { 0, 0 };
    u32 restCount = 0;
    bool complete = false;
    while (!complete)
    {
        vec2i sandPos = { 500, 0 };

        while (true)
        {
            bool moved = false;
            while (grid[sandPos.y + 1][sandPos.x] == None)
            {
                if (sandPos.y > 500)
                {
                    complete = true;
                    break;
                }
                sandPos.y++;        
                moved = true;
            }
            if (complete)
                break;
            if (moved)
                continue;
            
            if (grid[sandPos.y + 1][sandPos.x - 1] == None)
            {
                sandPos.y += 1;
                sandPos.x -= 1;
                continue;
            }

            if (grid[sandPos.y + 1][sandPos.x + 1] == None)
            {
                sandPos.y += 1;
                sandPos.x += 1;
                continue;
            }
            
            grid[sandPos.y][sandPos.x] = Sand;

            break;
        }
        
        if (!complete)
            restCount++;
    }
    
//    std::cout << score << std::endl;

    return 0;
}