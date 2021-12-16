#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <compare>

struct Point
{
    bool operator==(const Point &other) const
    {
        return (x == other.x && y == other.y);
    }
    int x{}, y{};
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

            return p.y * 10000 + p.x;
        }
    };

}
