#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

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

    vec2i startPos;
    vec2i endPos;
    std::vector<std::vector<Cell>> grid;
    for (u32 y = 0; y < root.C.size(); y++)
    {
        std::vector<Cell> v;
        for (u32 x = 0; x < root.C[y].C.size(); x++)
        {
            char c = root.C[y].C[x].E[0];
            if (c == 'S')
            {
                v.push_back({ false, 0 });
                startPos.x = x;
                startPos.y = y;
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
    
    std::vector<StackEntry> stack;
    stack.push_back({ startPos, 0 });
    
    u32 min = 0;
    while (!stack.empty())
    {
        auto pos = stack.front();
        stack.erase(stack.begin(), stack.begin() + 1);
        
        if (pos.Pos.y >= grid.size() || pos.Pos.y < 0) continue;
        if (pos.Pos.x >= grid[0].size() || pos.Pos.x < 0) continue;
        
        auto& cell = grid[pos.Pos.y][pos.Pos.x];
        if (cell.Visited) continue;
        if (cell.Elevation > pos.PrevEl + 1) continue;

        if (pos.Pos.x == endPos.x && pos.Pos.y == endPos.y)
        {
            min = pos.Distance;
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

    std::cout << "Value: " << min << std::endl;

    return 0;
}