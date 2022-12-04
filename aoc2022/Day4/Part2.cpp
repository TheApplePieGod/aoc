#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day4/input.txt", { "\n", ",", "-" });
    
    int total = 0;
    for (auto& pair : root.C)
    {
        if (pair.C[0].C[1].I >= pair.C[1].C[0].I && pair.C[0].C[0].I <= pair.C[1].C[1].I)
            total++;
    }
    
    std::cout << "Value: " << total << std::endl;

    return 0;
}