#include <iostream>
#include <unordered_map>

#include "Base.h"
#include "Utils.h"

struct DirEntry
{
    u32 Size = 0;
    std::vector<std::string> SubDirs;
};

int main(int argc, char** argv)
{
    auto root = FilesystemUtils::Read("../../Day7/input.txt", { "\n", " " });
    std::unordered_map<std::string, DirEntry> dirs;
    
    std::vector<std::string> curPath;
    for (auto& line : root.C)
    {
        if (line.C[1].E == "cd")                
        {
            if (line.C[2].E == "..") curPath.pop_back();
            else
            {
                curPath.push_back(line.C[2].E);
                auto path = StringUtils::Join(curPath, "|");
                if (dirs.find(path) == dirs.end())
                    dirs[path] = {};
            }
        }
        else if (line.C[0].E == "dir")
        {
            auto path = StringUtils::Join(curPath, "|");
            curPath.push_back(line.C[1].E);
            dirs[path].SubDirs.push_back(StringUtils::Join(curPath, "|"));
            curPath.pop_back();
        }
        else if (line.C[0].I != 0)
        {
            auto path = StringUtils::Join(curPath, "|");
            dirs[path].Size += (u32)line.C[0].I;
        }
    }
    
    std::vector<std::string> keys;
    for (auto it = dirs.begin(); it != dirs.end(); it++)
        keys.push_back(it->first);
    std::sort(keys.begin(), keys.end(), [](const std::string& a, const std::string& b){ return a.size() > b.size(); });
    
    u32 score = 0;
    for (auto& key : keys)
    {
        auto& val = dirs[key];
        for (auto& sub : val.SubDirs)
            val.Size += dirs[sub].Size;
        if (val.Size < 100000) score += val.Size;
    }

    std::cout << "Value: " << score << std::endl;

    return 0;
}