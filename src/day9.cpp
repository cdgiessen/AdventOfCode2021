#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

std::array<int, 10000> inputs = {
#include "inputs/day9.txt"
};
bool is_valid_point(int x, int y)
{
    return (x >= 0 && x < 100 && y >= 0 && y < 100);
}
int index(int x, int y)
{
    if (is_valid_point(x, y))
    {
        return inputs[y * 100 + x];
    }
    else
    {
        return 9;
    }
}

struct Point
{
    int x{}, y{};

    bool is_valid_point()
    {
        return (x >= 0 && x < 100 && y >= 0 && y < 100);
    }
    bool operator==(const Point &other) const
    {
        return (x == other.x && y == other.y);
    }
};
namespace std
{

    template <>
    struct hash<Point>
    {
        std::size_t operator()(const Point &p) const
        {
            using std::hash;
            using std::size_t;
            using std::string;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return p.y * 100 + p.x;
        }
    };

}

int main()
{
    int count_low_points = 0;
    int sum = 0;
    std::vector<Point> lowest_points;
    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            int val = index(i, j);

            int valU = index(i + 1, j);
            int valD = index(i - 1, j);
            int valL = index(i, j + 1);
            int valR = index(i, j - 1);

            if (val < valU && val < valD && val < valL && val < valR)
            {
                count_low_points++;
                sum += val + 1;
                lowest_points.push_back({i, j});
            }
        }
    }
    std::cout << "lowest point count " << count_low_points << "\n";
    std::cout << "risk level " << sum << "\n";

    std::vector<size_t> basins;
    size_t count_of_not_nines = 0;
    for (auto &p : lowest_points)
    {
        std::unordered_set<Point> points_in_basin;

        points_in_basin.emplace(p);
        bool searching = true;
        while (searching)
        {
            bool found_new_places = false;
            std::unordered_set<Point> new_points;
            for (auto &i : points_in_basin)
            {
                if (is_valid_point(i.x - 1, i.y) && index(i.x - 1, i.y) < 9)
                {
                    new_points.emplace(Point{i.x - 1, i.y});
                }
                if (is_valid_point(i.x + 1, i.y) && index(i.x + 1, i.y) < 9)
                {
                    new_points.emplace(Point{i.x + 1, i.y});
                }
                if (is_valid_point(i.x, i.y - 1) && index(i.x, i.y - 1) < 9)
                {
                    new_points.emplace(Point{i.x, i.y - 1});
                }
                if (is_valid_point(i.x, i.y + 1) && index(i.x, i.y + 1) < 9)
                {
                    new_points.emplace(Point{i.x, i.y + 1});
                }
            }
            for (auto &i : new_points)
            {
                if (!points_in_basin.contains(i))
                {
                    points_in_basin.emplace(i);
                    found_new_places = true;
                }
            }
            if (!found_new_places)
            {
                searching = false;
                break;
            }
        }
        count_of_not_nines += points_in_basin.size();
        std::cout << "size " << points_in_basin.size() << "\n";
        basins.push_back(points_in_basin.size());
    }
    std::sort(basins.begin(), basins.end());
    std::cout << "count_of_not_nines  " << count_of_not_nines << "\n";
    size_t x1 = basins[basins.size() - 1];
    size_t x2 = basins[basins.size() - 2];
    size_t x3 = basins[basins.size() - 3];
    std::cout << x1 * x2 * x3 << "\n";

    return 0;
}