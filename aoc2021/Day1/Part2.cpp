#include <iostream>

#include "Base.h"
#include "FilesystemUtils.h"

int main(char* argv, int argc)
{
    std::vector<int> data = FilesystemUtils::ReadInts("../../../Day1/input.txt");

    int count = 0;
    for (int i = 3; i < data.size(); i++)
        if (data[i] > data[i - 3]) count++;

    std::cout << "Count: " << count << std::endl;

    return 0;
}