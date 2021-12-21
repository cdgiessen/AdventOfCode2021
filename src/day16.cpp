#include "common.h"

#include "inputs/day16.txt"

enum class Type
{
    sum = 0,
    product = 1,
    min = 2,
    max = 3,
    literal = 4,
    greater_than = 5,
    less_than = 6,
    equal_to = 7,
};

struct Packet
{
    int64_t version = 0;
    Type type = Type::sum;
    int64_t literal = 0;
    std::vector<Packet> sub_packets;
};

int64_t get(std::string const &bits, int64_t index)
{
    return bits.at(index) == '0' ? 0 : 1;
}

int64_t parse_version(std::string const &bits, int64_t &i)
{
    int64_t num = 4 * get(bits, i) + 2 * get(bits, i + 1) + 1 * get(bits, i + 2);
    i += 3;
    return num;
}

Type parse_type(std::string const &bits, int64_t &i)
{
    int64_t num = 4 * get(bits, i) + 2 * get(bits, i + 1) + 1 * get(bits, i + 2);
    i += 3;
    return static_cast<Type>(num);
}

int64_t parse_literal(std::string const &bits, int64_t &i)
{
    std::vector<int64_t> outs;
    bool keep_parsing = true;
    while (keep_parsing)
    {
        if (bits[i] == '0')
        {
            keep_parsing = false;
        }
        i += 1;
        outs.insert(outs.begin(), 8 * get(bits, i) + 4 * get(bits, i + 1) + 2 * get(bits, i + 2) + 1 * get(bits, i + 3));
        int64_t shift = 1;
        for (auto &val : outs)
        {
            val *= shift;
            shift = 16;
        }
        i += 4;
    }
    int64_t out = 0;
    for (auto const &val : outs)
    {
        out += val;
    }
    return out;
}

Packet parse_packet_header(std::string const &bits, int64_t &i)
{
    Packet p{};
    p.version = parse_version(bits, i);
    p.type = parse_type(bits, i);
    return p;
}

Packet parse_packet(std::string const &bits, int64_t &i)
{
    auto p = parse_packet_header(bits, i);
    switch (p.type)
    {

    case (Type::sum):
    case (Type::product):
    case (Type::min):
    case (Type::max):
    case (Type::greater_than):
    case (Type::less_than):
    case (Type::equal_to):
        // If the length type ID is 0, then the next 15 bits are a number that represents the total length in bits of the sub-packets contained by this packet.
        // If the length type ID is 1, then the next 11 bits are a number that represents the number of sub-packets immediately contained by this packet.
        {
            if (bits[i] == '0')
            {
                i += 1;
                int64_t len = 0;
                int64_t power = 16384;
                for (int64_t index = 0; index < 15; index++)
                {
                    len += get(bits, i + index) * power;
                    power /= 2;
                }
                i += 15;
                int64_t current_i = i;
                while (i < current_i + len)
                {
                    p.sub_packets.push_back(parse_packet(bits, i));
                }
            }
            else if (bits[i] == '1')
            {
                i += 1;
                int64_t len = 0;
                int64_t power = 1024;
                for (int64_t index = 0; index < 11; index++)
                {
                    len += get(bits, i + index) * power;
                    power /= 2;
                }
                i += 11;
                for (int64_t index = 0; index < len; index++)
                {
                    p.sub_packets.push_back(parse_packet(bits, i));
                }
            }
        }
        break;
    case (Type::literal):
        p.literal = parse_literal(bits, i);
        break;
    }
    return p;
}

int64_t count_versions(Packet const &p)
{
    int64_t out = 0;
    out += p.version;
    for (auto const &sp : p.sub_packets)
    {
        out += count_versions(sp);
    }
    return out;
}

int64_t compute(Packet const &p)
{
    switch (p.type)
    {
    default:
    case (Type::sum):
    {
        int64_t out = 0;
        for (auto const &sp : p.sub_packets)
        {
            out += compute(sp);
        }
        return out;
    }
    case (Type::product):
    {
        int64_t out = 1;
        for (auto const &sp : p.sub_packets)
        {
            out *= compute(sp);
        }
        return out;
    }
    case (Type::min):
    {
        int64_t min = compute(p.sub_packets.front());
        for (auto const &sp : p.sub_packets)
        {
            int64_t val = compute(sp);
            if (min > val)
                min = val;
        }
        return min;
    }
    case (Type::max):
    {
        int64_t max = compute(p.sub_packets.front());
        for (auto const &sp : p.sub_packets)
        {
            int64_t val = compute(sp);
            if (max < val)
                max = val;
        }
        return max;
    }
    case (Type::literal):
        return p.literal;
    case (Type::greater_than):
        return compute(p.sub_packets[0]) > compute(p.sub_packets[1]) ? 1 : 0;
    case (Type::less_than):
        return compute(p.sub_packets[0]) < compute(p.sub_packets[1]) ? 1 : 0;
    case (Type::equal_to):
        return compute(p.sub_packets[0]) == compute(p.sub_packets[1]) ? 1 : 0;
    }
}

const char *hex_char_to_bin(char c)
{
    // TODO handle default / error
    switch (toupper(c))
    {
    default:
    case '0':
        return "0000";
    case '1':
        return "0001";
    case '2':
        return "0010";
    case '3':
        return "0011";
    case '4':
        return "0100";
    case '5':
        return "0101";
    case '6':
        return "0110";
    case '7':
        return "0111";
    case '8':
        return "1000";
    case '9':
        return "1001";
    case 'A':
        return "1010";
    case 'B':
        return "1011";
    case 'C':
        return "1100";
    case 'D':
        return "1101";
    case 'E':
        return "1110";
    case 'F':
        return "1111";
    }
}

Packet parse(std::string input)
{
    std::string bin;
    for (unsigned i = 0; i != input.length(); ++i)
        bin += hex_char_to_bin(input[i]);
    int64_t i = 0;
    return parse_packet(bin, i);
}
int main()
{
    std::vector<std::pair<const char *, int64_t>> tests = {
        {"C200B40A82", 3},
        {"04005AC33890", 54},
        {"880086C3E88112", 7},
        {"CE00C43D881120", 9},
        {"D8005AC2A8F0", 1},
        {"F600BC2D8F", 0},
        {"9C005AC2F8F0", 0},
        {"9C0141080250320F1802104A08", 1}};
    // for (auto const &t : tests)
    // {
    //     auto p = parse(std::string(t.first));
    //     std::cout << "expected: " << t.second << " actual: " << compute(p) << "\n";
    // }

    auto final_hex = parse(hex);
    std::cout << "final version count: " << count_versions(final_hex) << "\n";
    std::cout << "final computation: " << compute(final_hex) << "\n";
    return 0;
}