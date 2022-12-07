#include <iostream>

#include "Base.h"
#include "Utils.h"

int main(int argc, char** argv)
{
    auto data = FilesystemUtils::ReadAsString("../../Day6/input.txt");
    
    std::vector<char> last;
    int index = 0;
    for (char c : data)
    {
        index++;
        last.push_back(c);
        if (last.size() > 14)
            last.erase(last.begin());            
        
        if (last.size() != 14) continue;
        
        bool b = false;
        for (int i = 0; i < last.size(); i++)
        {
            for (int j = 0; j < last.size(); j++)
            {
                if (last[i] == last[j] && i != j)
                {
                    b = true;
                    break;
                }
            }
            if (b) break;
        }
        if (b) continue;
        
        break;
    }

    
     std::cout << "Value: " << index << std::endl;

    return 0;
}