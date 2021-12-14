#include "common.h"

const char *p_template = "SHPPPVOFPBFCHHBKBNCV";

struct Rule
{
    char left;
    char right;
    char insert;
    bool operator==(const Rule &other) const
    {
        return (left == other.left && right == other.right && insert == other.insert);
    }
};

namespace std
{

    template <>
    struct hash<Rule>
    {
        std::size_t operator()(const Rule &p) const
        {
            using std::hash;
            using std::size_t;
            using std::string;

            return p.left * 256 + p.right + p.insert * 10000;
        }
    };

}
std::array rules = {
#include "inputs/day14.txt"
};

std::unordered_map<Rule, std::array<size_t, 26>> mem;

std::array<size_t, 26> rec(int i, char left, char right)
{
    if (i == 0)
    {
        return {};
    }
    auto it = mem.find(Rule{left, right, static_cast<char>(i)});
    if (it != mem.end())
    {
        return it->second;
    }
    for (auto const &r : rules)
    {
        if (left == r.left && right == r.right)
        {
            auto out1 = rec(i - 1, left, r.insert);
            auto out2 = rec(i - 1, r.insert, right);
            out1[r.insert - 65]++;
            for (size_t i = 0; i < 26; i++)
            {
                out1[i] += out2[i];
            }
            mem.insert(std::pair{Rule{left, right, static_cast<char>(i)}, out1});
            return out1;
        }
    }
    return {};
}

int main()
{
    // part 1
    if (true)
    {
        std::string polymer = p_template;

        for (int i = 0; i < 10; i++)
        {
            std::string new_polymer;
            for (int c = 0; c < polymer.size() - 1; c++)
            {
                new_polymer += polymer[c];
                for (auto &rule : rules)
                {
                    if (rule.left == polymer[c] && rule.right == polymer[c + 1])
                    {
                        new_polymer += rule.insert;
                    }
                }
            }
            new_polymer += polymer.back();
            polymer = new_polymer;
            // std::cout << "step " << std::to_string(i) << "\n";
            // std::cout << "step " << std::to_string(i) << " polymer: " << new_polymer << "\n";
        }
        std::array<size_t, 26> chars_count{};
        for (char c : polymer)
        {
            chars_count.at(c - 65)++;
        }
        size_t max = 0, min = SIZE_MAX;
        for (auto i : chars_count)
        {
            if (max < i)
                max = i;
            if (min > i && i > 0)
                min = i;
        }
        std::cout << "max " << std::to_string(max) << " min " << std::to_string(min) << " max - min " << std::to_string(max - min) << "\n";
    }
    {
        std::array<size_t, 26> chars_count{};
        std::string polymer = p_template;
        for (int c = 0; c < polymer.size() - 1; c++)
        {
            chars_count[polymer[c] - 65]++;
            auto out = rec(40, polymer[c], polymer[c + 1]);
            for (size_t i = 0; i < 26; i++)
            {
                chars_count[i] += out[i];
            }
            std::cout << "step " << std::to_string(c + 1) << "\n";
        }
        chars_count[polymer.back() - 65]++;

        size_t max = 0, min = SIZE_MAX;
        for (auto i : chars_count)
        {
            if (max < i)
                max = i;
            if (min > i && i > 0)
                min = i;
        }
        std::cout << "max " << std::to_string(max) << " min " << std::to_string(min) << " max - min " << std::to_string(max - min) << "\n";
    }
    return 0;
}