#include <iostream>
#include <cmath>

#include "Base.h"
#include "Utils.h"

struct Pos
{
    int X;
    int Y;
};

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day9/input.txt", { "\n", " " });

    std::unordered_set<std::string> positions;
    
    std::vector<Pos> knots;
    for (u32 i = 0; i < 10; i++)
        knots.push_back({ 0, 0 });
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
            knots[0].X += dx;
            knots[0].Y += dy;
            
            for (u32 k = 1; k < knots.size(); k++)
            {
                auto& k0 = knots[k];
                auto& k1 = knots[k - 1];
                int diffx = k1.X - k0.X;
                int diffy = k1.Y - k0.Y;
                int adiffx = (int)abs((float)diffx);
                int adiffy = (int)abs((float)diffy);
                if (adiffx > 1 && k1.Y == k0.Y)
                    k0.X += (diffx > 1 ? 1 : -1);
                else if (adiffy > 1 && k1.X == k0.X)
                    k0.Y += (diffy > 1 ? 1 : -1);
                else if (adiffx > 1.f || adiffy > 1.f)
                {
                    if (diffx % 2 == diffy % 2)
                    {
                        k0.X += diffx + (diffx > 0 ? -1 : 1);
                        k0.Y += diffy + (diffy > 0 ? -1 : 1);
                    }
                    else
                    {
                        if (adiffx > adiffy)
                            k0.Y = k1.Y;
                        else
                            k0.X = k1.X;
                        
                        k--;
                    }
                }

                if (k == knots.size() - 1)
                    positions.insert(std::to_string(k0.X) + "|" + std::to_string(k0.Y));
            }
        }
    }
    
    u32 unique = positions.size();
    std::cout << "Value: " << unique << std::endl;

    return 0;
}