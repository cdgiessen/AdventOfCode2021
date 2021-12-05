#include <iostream>
#include <vector>
#include <math.h>
#include <string>

struct Line
{
    int x1, y1, x2, y2;
};

#include "inputs/day5.txt"

int get(std::vector<int> const &grid, int x, int y)
{
    return grid[y * 1000 + x];
}
void add(std::vector<int> &grid, int x, int y)
{
    grid[y * 1000 + x]++;
}
int main()
{
    std::vector<int> grid;
    grid.resize(1000 * 1000);

    for (auto &line : inputs)
    {
        int dist = line.x1 == line.x2 ? abs(line.y2 - line.y1) : abs(line.x2 - line.x1);
        int x_up = line.x1 == line.x2 ? 0 : (line.x2 - line.x1 > 0 ? 1 : -1);
        int y_up = line.y1 == line.y2 ? 0 : (line.y2 - line.y1 > 0 ? 1 : -1);
        for (int i = 0; i <= dist; i++)
        {
            add(grid, line.x1 + i * x_up, line.y1 + i * y_up);
        }
    }
    int count = 0;
    for (int x = 0; x < 1000; x++)
    {
        for (int y = 0; y < 1000; y++)
        {
            if (get(grid, x, y) >= 2)
            {
                count++;
            }
        }
    }
    std::cout << count << "\n";
    return 0;
}