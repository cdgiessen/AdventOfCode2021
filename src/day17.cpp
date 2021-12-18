#include "common.h"

// target area: x=156..202, y=-110..-69

struct TargetArea
{
    int x0{}, x1{}, y0{}, y1{};
    bool is_within(int x, int y)
    {
        return x0 <= x && x <= x1 && y0 <= y && y <= y1;
    }
};

int main()
{
    TargetArea ta{156, 202, -110, -69};
    std::unordered_set<Point> vels_in_ta;
    int highest_y_found = 0;
    for (int vel_x_start = -1000; vel_x_start < 1000; vel_x_start++)
    {
        for (int vel_y_start = -1000; vel_y_start < 1000; vel_y_start++)
        {
            int max_y = 0;
            int x = 0, y = 0;
            int vel_x = vel_x_start, vel_y = vel_y_start;
            for (int i = 0; i < 5000; i++)
            {
                if (x > ta.x0 && y < ta.y0)
                    break;
                x += vel_x;
                y += vel_y;
                if (max_y < y)
                    max_y = y;
                vel_y -= 1;
                if (vel_x > 0)
                {
                    vel_x -= 1;
                }
                else if (vel_x < 0)
                {
                    vel_x += 1;
                }
                if (ta.is_within(x, y))
                {
                    if (max_y > highest_y_found)
                    {
                        highest_y_found = max_y;
                        std::cout << "Is within. Start x vel " << vel_x_start << " start y vel " << vel_y_start << "\n";
                    }
                    vels_in_ta.emplace(Point{vel_x_start, vel_y_start});
                    break;
                }
            }
        }
    }
    std::cout << "highest_y_value " << highest_y_found << "\n";
    std::cout << "unique vels " << vels_in_ta.size() << "\n";
    return 0;
}