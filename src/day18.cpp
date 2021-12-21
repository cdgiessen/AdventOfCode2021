#include "common.h"

std::array inputs = {
#include "inputs/day18.txt"
};

struct snail_number
{
    std::variant<int, std::unique_ptr<snail_number>> first = 0;
    std::variant<int, std::unique_ptr<snail_number>> second = 0;
};

snail_number parse(std::string const &s, int &index)
{
    snail_number ret{};
    if (index >= s.size())
        return ret;
    assert(s[index] == '[');
    index++;
    if (s[index] == '[')
    {
        ret.first = std::make_unique<snail_number>(parse(s, index));
    }
    else
    {
        ret.first = s[index++] - 48;
    }
    assert(s[index] == ',');
    index++;

    if (s[index] == '[')
    {
        ret.second = std::make_unique<snail_number>(parse(s, index));
    }
    else
    {
        ret.second = s[index++] - 48;
    }
    assert(s[index] == ']');
    index++;

    return ret;
}

int main()
{
    std::vector<snail_number> snail_numbers;
    for (auto &s : inputs)
    {
        int index = 0;
        snail_numbers.push_back(parse(s, index));
    }

    return 0;
}