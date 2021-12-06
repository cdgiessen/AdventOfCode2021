#include <iostream>
#include <vector>
#include <array>

std::array input = {
#include "inputs/day1.txt"
};

int main()
{
    int count1 = 0;
    for (int i = 0; i < input.size() - 1; i++)
    {
        if ((input[i]) < (input[i + 1]))
        {
            count1++;
        }
    }
    int count2 = 0;
    for (int i = 0; i < input.size() - 3; i++)
    {
        if ((input[i] + input[i + 1] + input[i + 2]) < (input[i + 1] + input[i + 2] + input[i + 3]))
        {
            count2++;
        }
    }
    std::cout << "part 1: " << count1 << " part 2: " << count2 << "\n";
    return 0;
}