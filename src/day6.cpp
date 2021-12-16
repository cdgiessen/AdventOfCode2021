#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>

std::array<int, 300> inputs = {
#include "inputs/day6.txt"
};
const bool debug = true;
int64_t naive()
{
    std::vector<char> buckets;
    for (auto &i : inputs)
    {
        buckets.push_back(i);
    }
    for (int gen = 0; gen < 80; gen++)
    {
        size_t s = buckets.size();
        size_t new_count = 0;
        for (size_t i = 0; i < s; i++)
        {
            if (buckets[i] == 0)
            {
                buckets[i] = 6;
                new_count++;
            }
            else
            {
                buckets[i]--;
            }
        }
        buckets.insert(buckets.end(), new_count, 8);
        std::cout << "gen: " << gen << " size of vector " << buckets.size() << "\n";
    }

    return buckets.size();
}

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
        if (debug)
        {
            std::cout << "[";
            for (auto &b : buckets)
            {
                std::cout << b << ", ";
            }
            std::cout << "]\n";
        }
    }
    int64_t count = 0;
    for (auto &c : buckets)
    {
        count += c;
    }
    std::cout << " num fish: " << count << "\n";
    naive();
    return 0;
}
