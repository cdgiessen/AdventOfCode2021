#include "common.h"

struct Dot
{
    bool operator==(const Dot &other) const
    {
        return (x == other.x && y == other.y);
    }
    int x{}, y{};
};
namespace std
{

    template <>
    struct hash<Dot>
    {
        std::size_t operator()(const Dot &p) const
        {
            using std::hash;
            using std::size_t;
            using std::string;

            // Compute individual hash values for first,
            // second and third and combine them using XOR
            // and bit shifting:

            return p.y * 10000 + p.x;
        }
    };

}

std::array<Dot, 835> dots = {
#include "inputs/day13.txt"
};
struct Fold
{
    const char *dir;
    int axis;
};
// std::array folds = {
//     Fold{"x", 655},
//     Fold{"y", 447},
//     Fold{"x", 327},
//     Fold{"y", 223},
//     Fold{"x", 163},
//     Fold{"y", 111},
//     Fold{"x", 81},
//     Fold{"y", 55},
//     Fold{"x", 40},
//     Fold{"y", 27},
//     Fold{"y", 13},
//     Fold{"y", 6}};

struct Paper
{
    std::unordered_set<Dot> data;
    Paper(std::array<Dot, 835> const &in)
    {
        for (auto &d : in)
        {
            data.emplace(d);
        }
    }
    void fold_x(int fold_index)
    {
        std::unordered_set<Dot> new_data;
        for (auto &d : data)
        {
            Dot p = d;
            if (p.x > fold_index)
            {
                p.x = fold_index - std::abs(p.x - fold_index);
            }
            new_data.emplace(p);
        }
        data = new_data;
    };
    void fold_y(int fold_index)
    {
        std::unordered_set<Dot> new_data;
        for (auto &d : data)
        {
            Dot p = d;
            if (p.y > fold_index)
            {
                p.y = fold_index - std::abs(p.y - fold_index);
            }
            new_data.emplace(p);
        }
        data = new_data;
    };
};

int main()
{
    Paper p{dots};
    std::cout << p.data.size() << "\n";
    p.fold_x(655);
    std::cout << p.data.size() << "\n";
    p.fold_y(447);
    p.fold_x(327);
    p.fold_y(223);
    p.fold_x(163);
    p.fold_y(111);
    p.fold_x(81);
    p.fold_y(55);
    p.fold_x(40);
    p.fold_y(27);
    p.fold_y(13);
    p.fold_y(6);

    for (int y = 0; y < 7; y++)
    {
        for (int x = 0; x < 41; x++)
        {
            if (p.data.contains(Dot{x, y}))
                std::cout << "X";
            else
                std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
    return 0;
}