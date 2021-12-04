#include <iostream>
#include <vector>

int input[] = {
#include "inputs/day1.txt"
};

int main()
{
    int count = 0;
    for (int i = 0; i < sizeof(input) / 4 - 3; i++)
    {
        if ((input[i] + input[i + 1] + input[i + 2]) < (input[i + 1] + input[i + 2] + input[i + 3]))
        {
            count++;
        }
    }
    std::cout << count << "\n";
    return 0;
}