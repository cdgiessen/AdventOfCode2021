#include "common.h"

#include "inputs/day20.txt"

struct Grid
{
    template <size_t dim>
    Grid(std::array<const char *, dim> input, const char *algorithm, size_t num_passes)
        : algorithm(algorithm), num_passes(num_passes)
    {
        num_passes *= 4; // account for both + and - sides of grid
        rows.resize(dim + num_passes);
        intermed_rows.resize(dim + num_passes);
        for (auto &s : rows)
        {
            s.resize(dim + num_passes, '.');
        }
        for (auto &s : intermed_rows)
        {
            s.resize(dim + num_passes, '.');
        }
        for (size_t y = 0; y < dim; y++)
        {
            for (size_t x = 0; x < dim; x++)
            {
                rows[y + num_passes / 2][x + num_passes / 2] = input[y][x];
            }
        }
    }
    void sim(int sim_step)
    {
        uint32_t rim_char = (sim_step + 1) % 2;
        // rim_char = 0;
        for (size_t y = 0; y < rows.size(); y++)
        {
            for (size_t x = 0; x < rows[y].size(); x++)
            {
                uint32_t y0x0 = rim_char;
                uint32_t y0x1 = rim_char;
                uint32_t y0x2 = rim_char;
                uint32_t y1x0 = rim_char;
                uint32_t y1x1 = rim_char;
                uint32_t y1x2 = rim_char;
                uint32_t y2x0 = rim_char;
                uint32_t y2x1 = rim_char;
                uint32_t y2x2 = rim_char;
                if (y > 0)
                {
                    if (x > 0)
                        y0x0 = rows[y - 1][x - 1] == '#' ? 1 : 0;
                    y0x1 = rows[y - 1][x + 0] == '#' ? 1 : 0;
                    if (x < rows.size() - 1)
                        y0x2 = rows[y - 1][x + 1] == '#' ? 1 : 0;
                }
                if (x > 0)
                    y1x0 = rows[y + 0][x - 1] == '#' ? 1 : 0;
                y1x1 = rows[y + 0][x + 0] == '#' ? 1 : 0;
                if (x < rows.size() - 1)
                    y1x2 = rows[y + 0][x + 1] == '#' ? 1 : 0;
                if (y < rows.size() - 1)
                {
                    if (x > 0)
                        y2x0 = rows[y + 1][x - 1] == '#' ? 1 : 0;
                    y2x1 = rows[y + 1][x + 0] == '#' ? 1 : 0;
                    if (x < rows.size() - 1)
                        y2x2 = rows[y + 1][x + 1] == '#' ? 1 : 0;
                }

                uint32_t index =
                    256 * y0x0 + 128 * y0x1 + 64 * y0x2 + 32 * y1x0 + 16 * y1x1 + 8 * y1x2 + 4 * y2x0 + 2 * y2x1 + 1 * y2x2;
                intermed_rows[y][x] = algorithm[index];
            }
        }
        for (size_t y = 0; y < rows.size(); y++)
        {
            intermed_rows[y][0] = rim_char == 0 ? '.' : '#';
            intermed_rows[y][rows.size() - 1] = rim_char == 0 ? '.' : '#';
        }
        for (size_t x = 0; x < rows.size(); x++)
        {
            intermed_rows[0][x] = rim_char == 0 ? '.' : '#';
            intermed_rows[rows.size() - 1][x] = rim_char == 0 ? '.' : '#';
        }
        for (size_t y = 0; y < rows.size(); y++)
        {
            for (size_t x = 0; x < rows.size(); x++)
            {
                rows[y][x] = intermed_rows[y][x];
            }
        }
    }
    size_t count_lit()
    {
        size_t count = 0;
        for (size_t y = 0; y < rows.size(); y++)
        {
            for (size_t x = 0; x < rows.size(); x++)
            {
                if (rows[y][x] == '#')
                    count++;
            }
        }
        return count;
    }

    std::vector<std::string> rows;
    std::vector<std::string> intermed_rows;
    const char *algorithm;
    size_t num_passes = 0;
};

int main()
{
    size_t step_size = 50;
    // Grid test_g{test_grid, test_alg, step_size};
    // for (int i = 0; i < step_size; i++)
    // {
    //     test_g.sim(i);
    // }
    // std::cout << "Num lit: " << test_g.count_lit() << "\n";
    Grid g{grid, alg, step_size};
    for (int i = 0; i < step_size; i++)
    {
        g.sim(i);
    }
    std::cout << "Num lit: " << g.count_lit() << "\n";
    return 0;
}
