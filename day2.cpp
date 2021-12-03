#include <iostream>
#include <vector>

enum Direction
{
    forward,
    up,
    down
};
struct Input
{
    Direction direction;
    int amount;
};

Input input[] = {
#include "day2_input.txt"
};

void main()
{
    int aim = 0;
    int depth = 0; //down is up eg higher x == deeper
    int position_horiz = 0;
    for (int i = 0; i < sizeof(input) / sizeof(Input); i++)
    {
        switch (input[i].direction)
        {
        case (Direction::forward):
            position_horiz += input[i].amount;
            depth += aim * input[i].amount;
            break;
        case (Direction::up):
            aim -= input[i].amount;
            break;
        case (Direction::down):
            aim += input[i].amount;
            break;
        }
    }
    std::cout << "aim: " << aim << " depth: " << depth << " position_horiz: " << position_horiz << "\n";
    std::cout << "final: " << depth * position_horiz << "\n";
}