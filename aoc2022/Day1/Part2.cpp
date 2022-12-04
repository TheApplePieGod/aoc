#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day1/input.txt", { "\n\n", "\n" });
    
    std::vector<int> totals;
    for (auto& group : root.Children)
    {
        int sum = 0;
        for (auto& value : group.Children)
            sum += value.IntegerElement;
        totals.push_back(sum);
    }

    std::sort(totals.begin(), totals.end());
    
    int top = totals.back();
    top += totals[totals.size() - 2];
    top += totals[totals.size() - 3];
    
    std::cout << "Top: " << top << std::endl;

    return 0;
}