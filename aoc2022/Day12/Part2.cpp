#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

struct Cell
{
    bool Visited = false;
    u32 Elevation;
};

struct StackEntry
{
    vec2i Pos;
    u32 PrevEl;
    u32 Distance = 0;
};

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day12/input.txt", { "\n", "" });

    std::vector<vec2i> startPosi;
    vec2i endPos;
    std::vector<std::vector<Cell>> grid;
    for (u32 y = 0; y < root.C.size(); y++)
    {
        std::vector<Cell> v;
        for (u32 x = 0; x < root.C[y].C.size(); x++)
        {
            char c = root.C[y].C[x].E[0];
            if (c == 'S' || c == 'a')
            {
                v.push_back({ false, 0 });
                startPosi.push_back({ (int)x, (int)y });
            }
            else if (c == 'E')
            {
                v.push_back({ false, 25 });
                endPos.x = x;
                endPos.y = y;
            }
            else
                v.push_back({ false, (u32)(c - 97) });
        }
        grid.push_back(v);
    }
    
    Timer timer("program");
    
    u32 min = 99999;
    for (auto startPos : startPosi)
    {
        std::vector<StackEntry> stack;
        stack.push_back({ startPos, 0 });
        
        u32 lmin = 0;
        auto lgrid = grid;
        while (!stack.empty())
        {
            auto pos = stack.front();
            stack.erase(stack.begin(), stack.begin() + 1);
            
            if (pos.Pos.y >= lgrid.size() || pos.Pos.y < 0) continue;
            if (pos.Pos.x >= lgrid[0].size() || pos.Pos.x < 0) continue;
            
            auto& cell = lgrid[pos.Pos.y][pos.Pos.x];
            if (cell.Visited) continue;
            if (cell.Elevation > pos.PrevEl + 1) continue;

            if (pos.Pos.x == endPos.x && pos.Pos.y == endPos.y)
            {
                lmin = pos.Distance;
                break;            
            }
            
            cell.Visited = true;
            
            vec2i newPos = pos.Pos;
            newPos.x += 1;
            stack.push_back({ newPos, cell.Elevation, pos.Distance + 1 });
            newPos.x -= 2;
            stack.push_back({ newPos, cell.Elevation, pos.Distance + 1 });
            newPos.x += 1;
            newPos.y += 1;
            stack.push_back({ newPos, cell.Elevation, pos.Distance + 1 });
            newPos.y -= 2;
            stack.push_back({ newPos, cell.Elevation, pos.Distance + 1 });
        }
    
        if (lmin < min && lmin != 0) min = lmin;
    }

    std::cout << "Value: " << min << std::endl;

    return 0;
}