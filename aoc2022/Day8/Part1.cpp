#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day8/input.txt", { "\n", "" });

    u32 numVis = 0;
    u32 rows = root.C.size();
    for (u32 y = 0; y < rows; y++)
    {
        u32 cols = root.C[y].C.size();
        for (u32 x = 0; x < cols; x++)
        {
            u32 size = root.C[y].C[x].I;            
            u32 vis = 4;
            for (u32 tx = 0; tx < x; tx++)
            {
                if (root.C[y].C[tx].I >= size)
                {
                    vis -= 1;
                    break;
                }
            }
            for (u32 tx = x + 1; tx < cols; tx++)
            {
                if (root.C[y].C[tx].I >= size)
                {
                    vis -= 1;
                    break;
                }
            }
            for (u32 ty = 0; ty < y; ty++)
            {
                if (root.C[ty].C[x].I >= size)
                {
                    vis -= 1;
                    break;
                }
            }
            for (u32 ty = y + 1; ty < rows; ty++)
            {
                if (root.C[ty].C[x].I >= size)
                {
                    vis -= 1;
                    break;
                }
            }
            
            if (vis > 0) numVis++;
        }
    }
    
    // std::cout << "Value: " << score << std::endl;

    return 0;
}