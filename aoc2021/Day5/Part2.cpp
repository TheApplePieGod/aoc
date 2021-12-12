#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

struct LineSegment
{
    vec2i From;
    vec2i To;
};

void PrintBoard(const std::vector<int>& board, int width)
{
    std::cout << "-----------------" << std::endl;

    std::string buffer;
    for (int num : board)
    {
        if (num == 0)
            buffer += '.';
        else
            buffer += std::to_string(num);
        buffer += ' ';
        if (buffer.size() == width * 2)
        {
            std::cout << buffer << std::endl;
            buffer.clear();
        }
    }

    std::cout << "-----------------" << std::endl;
}

int GetSlope(int from, int to)
{
    int diff = to - from;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int main()
{
    Timer timer("Day5Part1");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day5/input.txt");

    // parse segments
    std::vector<LineSegment> segments;
    segments.reserve(lines.size());
    int xMax = 0;
    int yMax = 0;
    for (auto& line : lines)
    {
        LineSegment segment{};
        auto fromToSplit = StringUtils::Split(line, " -> ");
        auto fromSplit = StringUtils::SplitToInt(fromToSplit[0], ",");
        auto toSplit = StringUtils::SplitToInt(fromToSplit[1], ",");
        segment.From = { fromSplit[0], fromSplit[1] };
        segment.To = { toSplit[0], toSplit[1] };
        segments.emplace_back(segment);

        if (fromSplit[0] > xMax) xMax = fromSplit[0];
        if (toSplit[0] > xMax) xMax = toSplit[0];
        if (fromSplit[1] > yMax) yMax = fromSplit[1];
        if (toSplit[1] > yMax) yMax = toSplit[1];
    }

    int width = xMax + 1;
    int height = yMax + 1;

    // create board based on segment bounds
    std::vector<int> board(width * height);

    for (auto& segment : segments)
    {
        // start at smallest values
        int currentX = segment.From.x;
        int currentY = segment.From.y;
        int slopeX = GetSlope(segment.From.x, segment.To.x);
        int slopeY = GetSlope(segment.From.y, segment.To.y);

        while (true)
        {
            board[currentX + currentY * width]++;

            if (currentX == segment.To.x && currentY == segment.To.y)
                break;

            currentX += slopeX;
            currentY += slopeY;
        }
    }

    int numPoints = 0;
    for (int num : board)
        if (num >= 2) numPoints++;

    std::cout << "Overlaps >2: " << numPoints << std::endl;

    //PrintBoard(board, width);

    return 0;
}