#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(char* argv, int argc)
{
    std::vector<int> data = FilesystemUtils::ReadInts("../../../Day1/input.txt");

    int count = -1;
    int prev = 0;
    for (int elem : data)
    {
        if (elem > prev) count++;
        prev = elem;
    }

    std::cout << "Count: " << count << std::endl;

    return 0;
}