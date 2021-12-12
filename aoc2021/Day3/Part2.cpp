#include <iostream>

#include "Base.h"
#include "Utils.h"

//#define BIT_COUNT 5
#define BIT_COUNT 12

int GetRating(const std::vector<int>& data, bool isCO2)
{
    std::vector<int> filtered = data;

    int mask = 1 << (BIT_COUNT - 1);
    for (int i = BIT_COUNT - 1; i >= 0; i--) // start at 'first' bit
    {
        bool filterOnes = false;
        int oneCount = 0;
        for (int num : filtered)
            oneCount += (bool)(num & mask);

        filterOnes = oneCount * 2 >= filtered.size() != isCO2;

        for (int j = 0; j < filtered.size(); j++)
        {
            if ((bool)(filtered[j] & mask) != filterOnes)
            {
                filtered[j--] = filtered.back();
                filtered.pop_back();
            }
        }
            
        if (filtered.size() == 1)
            return filtered[0];

        mask >>= 1;
    }

    return -1;
}

int main()
{
    std::vector<int> data = FilesystemUtils::ReadBinary("../../../Day3/input.txt");

    int oxygenRating = GetRating(data, false);
    int co2Rating = GetRating(data, true);

    std::cout << "Support rating: " << (oxygenRating * co2Rating) << std::endl;

    return 0;
}