#include <iostream>

#include "Base.h"
#include "FilesystemUtils.h"

//#define BIT_COUNT 5
#define BIT_COUNT 12

int GetGammaRate(const std::vector<int>& data)
{
    int finalNum = 0;
    int mask = 1;
    for (int i = 0; i < BIT_COUNT; i++)
    {
        int oneCount = 0;
        for (int num : data)
            oneCount += (bool)(num & mask);
        if (oneCount * 2 > data.size())
            finalNum |= mask;
        mask <<= 1;
    }

    return finalNum;
}

int GetEpsilonRate(int gammaRate)
{
    int mask = (1 << BIT_COUNT) - 1;
    return ~gammaRate & mask;
}

int main(char* argv, int argc)
{
    std::vector<int> data = FilesystemUtils::ReadBinary("../../../Day3/input.txt");

    int gammaRate = GetGammaRate(data);
    int epsilonRate = GetEpsilonRate(gammaRate);

    std::cout << "Power consumption: " << (gammaRate * epsilonRate) << std::endl;

    return 0;
}