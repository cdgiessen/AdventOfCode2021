#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>

std::array inputs = {
#include "inputs/day6.txt"
};
int main()
{
    std::array<int64_t, 9> buckets = {0};
    for (auto &i : inputs)
    {
        buckets[i]++;
    }

    for (int gen = 0; gen < 256; gen++)
    {
        auto new_fish = buckets[0];
        std::rotate(buckets.begin(), buckets.begin() + 1, buckets.end());
        buckets[6] += new_fish;
        std::cout << "[";
        for (auto &b : buckets)
        {
            std::cout << b << ", ";
        }
        std::cout << "]\n";
    }
    int64_t count = 0;
    for (auto &c : buckets)
    {
        count += c;
    }
    std::cout << " num fish: " << count << "\n";
    return 0;
}
