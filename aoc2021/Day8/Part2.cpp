#include <iostream>
#include <array>
#include <unordered_map>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

std::array<int, 10> segmasks = { 119, 36, 93, 109, 46, 107, 123, 37, 127, 111 }; // 0-9

struct Entry
{
    std::vector<std::string> SignalPatterns;
    std::vector<std::string> OutputValues;

    const std::string& FindPatternWithLength(int length)
    {
        for (auto& str : SignalPatterns)
            if (str.size() == length) return str;
        return SignalPatterns[0];
    }
};

int GetSegFromChar(char c)
{
    return 1 << (c - 97);
}

void NarrowDown(std::vector<int>& possibleSegments, const Entry& entry, int segMask)
{
    // find pattern with the matching number of segments
    int segCount = 0;
    for (int i = 0; i < 7; i++)
        if (segMask & (1 << i))
            segCount++;
    const std::string* pattern;
    for (auto& p : entry.SignalPatterns)
        if (p.size() == segCount)
            pattern = &p;

    // remove used segments from all unused possible segments
    for (int i = 0; i < 7; i++)
        if (!(segMask & (1 << i)))
            for (char c : *pattern)
                possibleSegments[i] &= ~GetSegFromChar(c);
}

std::vector<int> Solve(const std::vector<int>& possibleSegments, const Entry& entry)
{
    int segCount = 0;
    for (int i = 0; i < 7; i++)
    {
        if (possibleSegments[i] == 0) return {}; // if any are zeros then this branch is done
        for (int j = 0; j < 7; j++)
            if (possibleSegments[i] & (1 << j))
                segCount++;
    }

    // if segcount is 7 then we can check the solution
    if (segCount == 7)
    {
        // flip the segments so [] will return the corrected index
        std::unordered_map<int, int> segments;
        for (int i = 0; i < 7; i++)
            segments[possibleSegments[i]] = i;

        // check each segmask to make sure this solution can create all 10 numbers
        int valid = 0;
        for (int segmask : segmasks)
        {
            for (auto& pattern : entry.SignalPatterns)
            {
                int mask = 0;
                for (char c : pattern)
                    mask |= (1 << segments[GetSegFromChar(c)]);
                if (mask == segmask)
                {
                    valid++;
                    break;
                }
            }
        }

        if (valid == segmasks.size())
            return possibleSegments;
        else
            return {};
    }

    // find most constrained segment that has more than one possibility
    int constrainedIndex = -1;
    int constrainedCount = 99999;
    for (int i = 0; i < 7; i++)
    {
        int segCount = 0;
        for (int j = 0; j < 7; j++)
            if (possibleSegments[i] & (1 << j))
                segCount++;
        if (segCount > 1 && segCount < constrainedCount)
        {
            constrainedCount = segCount;
            constrainedIndex = i;
        }
    }

    // test each combination
    for (int i = 0; i < 7; i++)
    {
        if (possibleSegments[constrainedIndex] & (1 << i))
        {
            auto newSegments = possibleSegments;
            for (int j = 0; j < 7; j++)
            {
                if (j == constrainedIndex)
                    newSegments[j] = 1 << i; // this is the combo we are testing so set this segment to the testing segment
                else
                    newSegments[j] &= ~(1 << i); // otherwise remove the testing segment as a possiblity from the rest of the segments
            }
            newSegments = Solve(newSegments, entry);
            if (newSegments.size() > 0)
                return newSegments;
        }
    }

    return {};
}

int main()
{
    Timer timer("Day8Part2");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day8/input.txt");
    
    // parse
    std::vector<Entry> entries;
    for (auto& line : lines)
    {
        auto split = StringUtils::Split(line, " | ");
        entries.push_back({
            StringUtils::Split(split[0], " "),
            StringUtils::Split(split[1], " ")
        });
    }

    int sum = 0;
    std::vector<int> possibleSegments;
    for (auto& entry : entries)
    {
        possibleSegments.clear();
        possibleSegments.resize(7, 127);

        // narrow down possiblities using the unique segcounts of 1,4,7,8
        NarrowDown(possibleSegments, entry, segmasks[1]);
        NarrowDown(possibleSegments, entry, segmasks[4]);
        NarrowDown(possibleSegments, entry, segmasks[7]);
        NarrowDown(possibleSegments, entry, segmasks[8]);

        auto sol = Solve(possibleSegments, entry);

        // flip the segments so [] will return the corrected index
        std::unordered_map<int, int> segments;
        for (int i = 0; i < 7; i++)
            segments[sol[i]] = i;

        std::string outputBuffer;
        for (auto& output : entry.OutputValues)
        {
            int d = 0;
            for (int i = 0; i < segmasks.size(); i++)
            {
                int mask = 0;
                for (char c : output)
                    mask |= (1 << segments[GetSegFromChar(c)]);
                if (mask == segmasks[i])
                {
                    outputBuffer += std::to_string(i);
                    break;
                }
            }
        }

        sum += atoi(outputBuffer.c_str());
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}