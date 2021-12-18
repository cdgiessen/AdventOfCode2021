#include "common.h"

#include "inputs/day16.txt"

enum class Type
{
    len0 = 0,
    len1 = 1,
    literal = 4,
};

using Data = std::variant<int>;

struct Packet
{
    int8_t version;
    Type type;
    std::vector<int> data;
};

int main()
{

    for (auto c : bits)
    {
    }
    return 0;
}