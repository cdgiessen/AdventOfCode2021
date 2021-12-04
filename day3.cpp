#include <iostream>
#include <vector>
#include <math.h>
#include <string>

const char *input[] = {
#include "inputs/day3.txt"
};

std::string find_common_bitstring(char want_most_common)
{
    std::string out = "";
    for (int place = 0; place < 12; place++)
    {
        uint32_t one_count = 0;
        uint32_t zero_count = 0;
        uint32_t last_index = 0;
        for (int i = 0; i < sizeof(input) / sizeof(const char *); i++)
        {
            bool has_it = true;
            for (int j = 0; j < out.size(); j++)
            {
                if (input[i][j] != out[j])
                {
                    has_it = false;
                    break;
                }
            }
            if (has_it)
            {
                if (input[i][place] == '1')
                {
                    one_count++;
                }
                else
                {
                    zero_count++;
                }
                last_index = i;
            }
        }
        if (one_count + zero_count == 1)
        {
            return input[last_index];
        }
        if (one_count == zero_count)
        {
            out += want_most_common ? '1' : '0';
        }
        else if (one_count > zero_count)
        {
            out += want_most_common ? '1' : '0';
        }
        else if (zero_count > one_count)
        {
            out += want_most_common ? '0' : '1';
        }
    }
    return out;
}
void main()
{
    int counts[12] = {};

    for (int i = 0; i < sizeof(input) / sizeof(const char *); i++)
    {
        for (int place = 0; place < 12; place++)
        {
            if (input[i][place] == '1')
            {
                counts[place]++;
            }
            else
            {
                counts[place]--;
            }
        }
    }
    std::string gamma = "";
    std::string epsilon = "";
    for (int place = 0; place < 12; place++)
    {
        if (counts[place] > 0)
        {
            gamma += '0';
            epsilon += '1';
        }
        else
        {
            gamma += '1';
            epsilon += '0';
        }
        std::cout << counts[place] << ", ";
    }

    std::cout << "gamma: " << gamma << " epsilon: " << epsilon << "\n";
    {
        //copy paste values from command line in here and let the compiler do the binary->decimal conversion for me.
        int gamma = 0b010000110001;
        int epsilon = 0b101111001110;
        std::cout << "gamma: " << std::to_string(gamma) << " epsilon: " << std::to_string(epsilon) << "\n";
        std::cout << "final gamma * epsilon: " << std::to_string(gamma * epsilon) << "\n";
    }
    // realized that this could be done in regex easier than with code, since it would tell me the count of each digit
    // X[01], alternate x from 0 to 1 and take either the higher or lower value depending on which thing I was looking for.
    // Lazy? yes. but also effective.
    int oxy = 0b101110111101;
    int co2 = 0b011001010000;
    std::cout << "final co2 * oxy: " << std::to_string(oxy * co2) << "\n";

    std::cout << "co2 binary: " << find_common_bitstring(true) << " oxy binary: " << find_common_bitstring(false);

    // std::cout << "final: " < <  < < "\n";
}