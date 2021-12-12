#include <iostream>
#include <array>

#include "Base.h"
#include "Utils.h"
#include "Timer.h"

#define WIDTH 5
#define HEIGHT 5
#define MARK_MASK (1 << 31)

typedef std::array<int, WIDTH * HEIGHT> Board;

bool CheckWin(const Board& board)
{
    std::array<int, HEIGHT> colCounts{};
    int rowCount = 0;

    for (int i = 0; i < WIDTH * HEIGHT; i++)
    {
        int col = i % WIDTH;

        if (col == 0) rowCount = 0;

        rowCount += (bool)(board[i] & MARK_MASK);
        colCounts[col] += (bool)(board[i] & MARK_MASK);

        if (rowCount == WIDTH) return true;
        if (colCounts[col] == HEIGHT) return true;
    }
    
    return false;
}

void MarkNumber(Board& board, int mark)
{
    for (auto& num : board)
    {
        if (num == mark)
        {
            num |= MARK_MASK;
            return;
        }
    }
}

int CalcBoardSum(Board& board)
{
    int sum = 0;
    for (int num : board)
        if (!(num & MARK_MASK))
            sum += num;
    return sum;
}

int main()
{
    Timer timer("Day4Part2");
    std::vector<std::string> lines = FilesystemUtils::ReadLines("../../../Day4/input.txt");

    // parse
    std::vector<int> numbers = StringUtils::SplitToInt(lines[0], ",");
    std::vector<Board> boards = {};
    for (size_t i = 2; i < lines.size(); i += HEIGHT + 1) // for each board
    {
        size_t boardIndex = boards.size();
        boards.emplace_back();

        for (size_t y = 0; y < HEIGHT; y++) // for each row
        {
            auto nums = StringUtils::SplitToInt(lines[i + y], " ");
            for (size_t x = 0; x < nums.size(); x++)
                boards[boardIndex][x + y * WIDTH] = nums[x];
        }
    }
    
    // draw numbers
    int drawCount = 0;
    int lastScore = 0;
    for (int draw : numbers)
    {
        for (int i = 0; i < boards.size(); i++)
        {
            MarkNumber(boards[i], draw);
            if (drawCount >= 4 && CheckWin(boards[i]))
            {
                int sum = CalcBoardSum(boards[i]);
                lastScore = sum * draw;

                boards[i--] = boards.back();
                boards.pop_back();
            }
        }

        drawCount++;
    }

    std::cout << "Losing score: " << lastScore << std::endl;

    return 0;
}