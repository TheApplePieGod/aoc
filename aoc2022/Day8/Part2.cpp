#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day8/input.txt", { "\n", "" });

    u32 highest = 0;
    u32 rows = root.C.size();
    for (u32 y = 1; y < rows - 1; y++)
    {
        u32 cols = root.C[y].C.size();
        for (u32 x = 1; x < cols - 1; x++)
        {

            u32 size = root.C[y].C[x].I;            
            u32 vis = 0;
            u32 score = 1;
            for (int tx = x - 1; tx >= 0; tx--)
            {
                vis++;
                if (root.C[y].C[tx].I >= size)
                    break;
            }
            score *= vis;
            vis = 0;
            for (int tx = x + 1; tx < cols; tx++)
            {
                vis++;
                if (root.C[y].C[tx].I >= size)
                    break;
            }
            score *= vis;
            vis = 0;
            for (int ty = y - 1; ty >= 0; ty--)
            {
                vis++;
                if (root.C[ty].C[x].I >= size)
                    break;
            }
            score *= vis;
            vis = 0;
            for (int ty = y + 1; ty < rows; ty++)
            {
                vis++;
                if (root.C[ty].C[x].I >= size)
                    break;
            }
            score *= vis;
            
            if (score > highest) highest = score;
        }
    }
    
    // std::cout << "Value: " << score << std::endl;

    return 0;
}