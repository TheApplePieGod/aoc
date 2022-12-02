#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto data = FilesystemUtils::ReadAsString("../../Day1/input.txt");
    auto elves = StringUtils::Split(data, "\n\n");
    
    std::vector<int> totals;
    for (auto& data : elves)
    {
        auto values = StringUtils::Split(data, "\n");
        int sum = 0;
        for (auto& value : values)
        {
            int num = stoi(value);
            sum += num;
        }
        totals.push_back(sum);
    }
    
    std::sort(totals.begin(), totals.end());
    
    int top = totals.back();
    top += totals[totals.size() - 2];
    top += totals[totals.size() - 3];
    
    std::cout << "Top: " << top << std::endl;

    return 0;
}