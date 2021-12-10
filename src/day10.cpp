#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

enum class Type
{
    round,
    square,
    curly,
    angle
};

std::array inputs = {
#include "inputs/day10.txt"
};

int main()
{
    size_t points = 0;
    size_t score = 0;
    std::vector<size_t> scores;
    std::vector<std::string> good_chunks;
    for (auto &chunks : inputs)
    {
        std::string s = chunks;
        std::vector<Type> stack;
        size_t cur_points = 0;
        for (auto &c : s)
        {
            if (c == '(')
            {
                stack.push_back(Type::round);
            }
            if (c == '[')
            {
                stack.push_back(Type::square);
            }
            if (c == '{')
            {
                stack.push_back(Type::curly);
            }
            if (c == '<')
            {
                stack.push_back(Type::angle);
            }
            if (c == ')')
            {
                if (stack.back() == Type::round)
                {
                    stack.pop_back();
                }
                else
                {
                    cur_points = 3;
                    break;
                }
            }
            if (c == ']')
            {
                if (stack.back() == Type::square)
                {
                    stack.pop_back();
                }
                else
                {
                    cur_points = 57;
                    break;
                }
            }
            if (c == '}')
            {
                if (stack.back() == Type::curly)
                {
                    stack.pop_back();
                }
                else
                {
                    cur_points = 1197;
                    break;
                }
            }
            if (c == '>')
            {
                if (stack.back() == Type::angle)
                {
                    stack.pop_back();
                }
                else
                {
                    cur_points = 25137;
                    break;
                }
            }
        }
        if (cur_points > 0)
        {
            points += cur_points;
            std::cout << "current corrupt points " << cur_points << "\n";
        }
        else
        {
            size_t cur_score = 0;
            if (!stack.empty())
            {
                while (!stack.empty())
                {
                    switch (stack.back())
                    {
                    case (Type::round):
                        cur_score = 5 * cur_score + 1;
                        break;
                    case (Type::square):
                        cur_score = 5 * cur_score + 2;
                        break;
                    case (Type::curly):
                        cur_score = 5 * cur_score + 3;
                        break;
                    case (Type::angle):
                        cur_score = 5 * cur_score + 4;
                        break;
                    }
                    stack.pop_back();
                }
                scores.push_back(cur_score);
                score += cur_score;
                std::cout << "current score " << cur_score << "\n";
            }
        }
    }
    std::sort(scores.begin(), scores.end());
    std::cout << "final corrupt points " << points << "\n";
    std::cout << "final score " << score << "\n";
    std::cout << "final median score " << scores.at(scores.size() / 2) << "\n";

    return 0;
}