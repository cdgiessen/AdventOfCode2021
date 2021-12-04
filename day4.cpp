#include <iostream>
#include <vector>
#include <math.h>
#include <string>

struct Board
{
    int data[25];

    int get(int x, int y)
    {
        return data[y * 5 + x];
    }

    void mark(int number)
    {
        for (int i = 0; i < 25; i++)
        {
            if (data[i] == number)
            {
                data[i] = -1;
                break;
            }
        }
    }
    bool is_win()
    {
        for (int i = 0; i < 5; i++)
        {
            if (get(0, i) == -1 && get(1, i) == -1 && get(2, i) == -1 && get(3, i) == -1 && get(4, i) == -1)
            {
                return true;
            }
            if (get(i, 0) == -1 && get(i, 1) == -1 && get(i, 2) == -1 && get(i, 3) == -1 && get(i, 4) == -1)
            {
                return true;
            }
        }
        if ((get(0, 0) == -1 && get(1, 1) == -1 && get(2, 2) == -1 && get(3, 3) == -1 && get(4, 4) == -1) ||
            (get(0, 4) == -1 && get(1, 3) == -1 && get(2, 2) == -1 && get(3, 1) == -1 && get(4, 0) == -1))
        {
            return true;
        }
        return false;
    }
    int get_score()
    {
        int count = 0;
        for (auto &d : data)
        {
            if (d > -1)
                count += d;
        }
        return count;
    }
};

#include "inputs/day4.txt"

struct Done
{
    int turn_to_win;
    int score;
};

int main()
{
    std::vector<Done> out_boards;
    for (auto &board : boards)
    {
        for (int i = 0; i < sizeof(inputs) / sizeof(int); i++)
        {
            board.mark(inputs[i]);
            if (board.is_win())
            {
                out_boards.push_back({i, board.get_score() * inputs[i]});
                break;
            }
        }
    }
    int index_of_last = 0;
    int score = 0;
    for (auto &board : out_boards)
    {
        if (board.turn_to_win > index_of_last)
        {

            index_of_last = board.turn_to_win;
            score = board.score;
        }
    }
    std::cout << score << "\n";
    return 0;
}