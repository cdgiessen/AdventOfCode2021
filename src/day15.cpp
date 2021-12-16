#include "common.h"

std::array<int, 100 * 100> inputs = {
#include "inputs/day15.txt"
};

struct Cell
{
    int x{}, y{};
    int cost;
    bool operator==(Cell const &rhs) const { return x == rhs.x && y == rhs.y; }
    bool operator!=(Cell const &rhs) const { return !(*this == rhs); }
    bool operator<(Cell const &rhs) const { return cost < rhs.cost; }
    bool operator<=(Cell const &rhs) const { return cost <= rhs.cost; }
    bool operator>(Cell const &rhs) const { return cost > rhs.cost; }
    bool operator>=(Cell const &rhs) const { return cost >= rhs.cost; }
};

namespace std
{

    template <>
    struct hash<Cell>
    {
        std::size_t operator()(const Cell &p) const
        {
            using std::hash;
            using std::size_t;
            using std::string;

            return p.y * 10000 + p.x;
        }
    };

}

struct Grid
{
    Grid(int x_size, int y_size)
        : x_size(x_size),
          y_size(y_size)
    {
        data.resize(x_size * y_size);
    }
    int get(int x, int y) const
    {
        return data[y * y_size + x];
    }
    void set(int x, int y, int value)
    {
        data[y * y_size + x] = value;
    }
    std::vector<int> data;
    int x_size = 0;
    int y_size = 0;
};

struct Search
{
    std::priority_queue<Cell, std::deque<Cell>, std::greater<Cell>> frontier;
    std::unordered_map<Cell, Cell> came_from;
    Search(Grid const &grid)
    {
        frontier.push({0, 0, 0});
        came_from[{0, 0, 0}] = {0, 0, 0};
        while (frontier.size() > 0)
        {
            Cell c = frontier.top();
            frontier.pop();

            auto explore = [&](int x, int y, Cell origin)
            {
                std::cout << "exploring:  " << x << ", " << y << "\n";

                if (x < 0 || x >= grid.x_size || y < 0 || y >= grid.y_size)
                    return;
                int new_cost = origin.cost + grid.get(x, y);
                Cell new_cell = {x, y, new_cost};
                if (!came_from.contains(new_cell))
                {
                    came_from[new_cell] = origin;
                    frontier.push(new_cell);
                }
                else if (new_cost < came_from.at(new_cell).cost)
                {
                    came_from[new_cell] = origin;
                }
            };
            explore(c.x + 1, c.y + 0, c);
            explore(c.x - 1, c.y + 0, c);
            explore(c.x + 0, c.y + 1, c);
            explore(c.x + 0, c.y - 1, c);
            // std::cout << "size of frontier " << frontier.size() << " size of explored " << came_from.size() << "\n";
        }
        // backtrack
        int cost = 0;
        Cell current = {grid.x_size - 1, grid.y_size - 1, grid.get(grid.x_size - 1, grid.y_size - 1)};
        std::vector<Cell> path;
        while (current.x != 0 || current.y != 0)
        {
            path.push_back(current);
            cost += grid.get(current.x, current.y);
            current = came_from.at(current);
        }
        std::cout << "path cost " << cost << "\n";
        std::cout << "came_from cost " << came_from.at({grid.x_size - 1, grid.y_size - 1, 0}).cost + grid.get(grid.x_size - 1, grid.y_size - 1) << "\n";
    }
};

int main()
{
    Grid grid{100, 100};
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            grid.set(x, y, inputs[y * 100 + x]);
        }
    }
    std::ofstream out("grid.txt");

    Grid new_grid{500, 500};
    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            for (int y_start = 0; y_start < 100; y_start++)
            {
                for (int x_start = 0; x_start < 100; x_start++)
                {
                    int c = grid.get(x_start, y_start);
                    c += x + y;
                    if (c > 9)
                        c -= 9;
                    new_grid.set(x * 100 + x_start, y * 100 + y_start, c);
                }
            }
        }
    }
    for (int y = 0; y < 500; y++)
    {
        for (int x = 0; x < 500; x++)
        {
            int c = new_grid.get(x, y);
            while (c > 9)
                c -= 9;
            new_grid.set(x, y, c);
            out << new_grid.get(x, y) << ' ';
        }
        out << '\n';
    }
    out << '\n';
    Search s{new_grid};

    // for (int y = 0; y < 100; y++)
    // {
    //     for (int x = 0; x < 100; x++)
    //     {
    //         auto it = std::find(path.begin(), path.end(), Cell{x, y, 0});
    //         if (it != path.end())
    //         {
    //             out << inputs[100 * y + x];
    //         }
    //         else
    //         {
    //             out << ".";
    //         }
    //     }
    //     out << "\n";
    // }
    // out << "\n";
    // for (int y = 0; y < 100; y++)
    // {
    //     for (int x = 0; x < 100; x++)
    //     {
    //         out << std::setw(5) << came_from.at({x, y, 0}).cost + inputs[y * 100 + x];
    //     }
    //     out << "\n";
    // }
    // out << "\n\n";

    // for (int y = 0; y < 99; y++)
    // {
    //     for (int x = 0; x < 99; x++)
    //     {
    //         out << std::setw(4) << came_from.at({x, y, 0}).cost + inputs[y * 100 + x];
    //         if (came_from.at({x, y, 0}).cost + inputs[y * 100 + x] < came_from.at({x + 1, y, 0}).cost + inputs[y * 100 + x + 1])
    //             out << '<';
    //         else
    //             out << '>';
    //     }
    //     out << came_from.at({99, y, 0}).cost + inputs[y * 100 + 99];
    //     out << "\n";
    //     for (int x = 0; x < 100; x++)
    //     {
    //         if (came_from.at({x, y, 0}).cost + inputs[y * 100 + x] < came_from.at({x, y + 1, 0}).cost + inputs[(y + 1) * 100 + x])
    //             out << std::setw(5) << "^  ";
    //         else
    //             out << std::setw(5) << ".  ";
    //     }
    //     out << "\n";
    // }
    // for (int x = 0; x < 99; x++)
    // {
    //     out << std::setw(4) << came_from.at({x, 99, 0}).cost + inputs[99 * 100 + x];
    //     if (came_from.at({x, 99, 0}).cost + inputs[99 * 100 + x] < came_from.at({x + 1, 99, 0}).cost + inputs[99 * 100 + x + 1])
    //         out << '<';
    //     else
    //         out << '>';
    // }
    // out << std::setw(4) << came_from.at({99, 99, 0}).cost + inputs[99 * 100 + 99];
    // out << "\n";
    return 0;
}