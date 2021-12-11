#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

std::array<int, 100> inputs{
#include "inputs/day11.txt"
};
std::array<bool, 100> has_flashed_grid{};
bool inc(int x, int y)
{
    if (x < 0 || x > 9 || y < 0 || y > 9)
        return false;
    inputs[y * 10 + x]++;
    return inputs[y * 10 + x] > 9;
}

struct P
{
    int x{}, y{};
};

void calc_flash(int x, int y, std::vector<P> &flashed)
{
    if (x < 0 || x > 9 || y < 0 || y > 9)
        return;
    inputs[y * 10 + x]++;
    if (inputs[y * 10 + x] > 9 && !has_flashed_grid[y * 10 + x])
    {
        has_flashed_grid[y * 10 + x] = true;
        flashed.push_back({x, y});
    }
}

int main()
{

    std::vector<P> flashed;
    flashed.reserve(100);
    size_t count_flashed = 0;
    for (int i = 0; i < 1000; i++)
    {
        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                if (inc(x, y))
                {
                    flashed.push_back({x, y});
                    has_flashed_grid[y * 10 + x] = true;
                }
            }
        }

        while (!flashed.empty())
        {
            P f = flashed.back();
            flashed.pop_back();
            calc_flash(f.x - 1, f.y - 1, flashed);
            calc_flash(f.x + 1, f.y - 1, flashed);
            calc_flash(f.x - 1, f.y + 1, flashed);
            calc_flash(f.x + 1, f.y + 1, flashed);
            calc_flash(f.x + 0, f.y - 1, flashed);
            calc_flash(f.x + 0, f.y + 1, flashed);
            calc_flash(f.x - 1, f.y + 0, flashed);
            calc_flash(f.x + 1, f.y + 0, flashed);
        }
        std::cout << "Generation " << std::to_string(i) << "\n";
        int local_count_flash = 0;
        for (auto &i : inputs)
        {
            if (i > 9)
            {
                count_flashed++;
                i = 0;
                local_count_flash++;
            }
        }
        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                std::cout << inputs[y * 10 + x];
                // if (inputs[y * 10 + x] > 9)
                // std::cout << "X";
                // else
            }
            std::cout << "\n";
        }
        if (local_count_flash == 100)
        {
            std::cout << "Synced in step " << i << "\n";
            i = 10000;
        }
        flashed.clear();
        for (auto &f : has_flashed_grid)
        {
            f = false;
        }
    }
    std::cout << "Total flashed " << count_flashed << "\n";
}