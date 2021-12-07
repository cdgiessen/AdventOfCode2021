#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>

std::array inputs = {
#include "inputs/day7.txt"
};

int main()
{
    int min = INT_MAX;
    int max = INT_MIN;
    int sum = 0;
    for (auto &i : inputs)
    {
        if (max < i)
            max = i;
        if (min > i)
            min = i;
        sum += i;
    }
    std::cout << "avg: " << sum / inputs.size() << "\n";
    int min_cost = INT_MAX;
    for (int i = min; i < max; i++)
    {
        int fuel_cost = 0;
        for (auto &p : inputs)
            fuel_cost += abs(i - p);
        if (min_cost > fuel_cost)
            min_cost = fuel_cost;
    }
    std::cout << "min fuel const cost: " << min_cost << "\n";
    min_cost = INT_MAX;
    for (int i = min; i < max; i++)
    {
        int fuel_cost = 0;
        for (auto &p : inputs)
            fuel_cost += (abs(i - p) + 1) * abs(i - p) / 2;
        if (min_cost > fuel_cost)
            min_cost = fuel_cost;
    }
    std::cout << "min fuel linear cost: " << min_cost << "\n";
    return 0;
}