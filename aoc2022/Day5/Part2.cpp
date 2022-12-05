#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day5/input.txt", { "\n\n", "\n", " " });
    
    std::vector<std::vector<char>> stacks;
    for (int i = root.C[0].C.size() - 2; i >= 0; i--)
    {
        // Remove extra spaces from parse
        for (int j = 1; j < root.C[0].C[i].C.size(); j++)
            if (root.C[0].C[i].C[j].E.empty() && root.C[0].C[i].C[j - 1].E.empty())
                root.C[0].C[i].C.erase(root.C[0].C[i].C.begin() + j);

        for (int j = 0; j < root.C[0].C[i].C.size(); j++)
        {
            // Populate stacks
            if (i == root.C[0].C.size() - 2)
                stacks.push_back({});
            
            // Push stack if elem is not empty
            if (root.C[0].C[i].C[j].E[0])
                stacks[j].push_back(root.C[0].C[i].C[j].E[1]);
        }
    }
    
    for (auto& line : root.C[1].C)
    {
        int count = line.C[1].I;
        int from = line.C[3].I - 1;
        int to = line.C[5].I - 1;
        
        for (int i = 0; i < count; i++)
        {
            char pop = stacks[from][stacks[from].size() - count + i];
            stacks[to].push_back(pop);
        }

        for (int i = 0; i < count; i++)
            stacks[from].pop_back();
    }

    std::string result;
    for (auto& stack : stacks)
        result.push_back(stack.back());
    
     std::cout << "Value: " << result << std::endl;

    return 0;
}