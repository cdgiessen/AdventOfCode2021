#include <iostream>
#include <vector>
#include <math.h>
#include <string>
#include <array>
#include <algorithm>
#include <set>

struct Input
{
    std::string entries[10];
    std::string outputs[4];
};

std::array inputs = {
#include "inputs/day8.txt"
};

int basic_guess_char(size_t len)
{
    if (len == 2)
        return 1;
    else if (len == 3)
        return 7;
    else if (len == 4)
        return 4;
    else if (len == 7)
        return 8;
    else
        return -1;
}

std::vector<char> to_vec_char(std::string s)
{
    std::vector<char> out;
    for (auto &c : s)
        out.push_back(c);
    return out;
}

void intersect(std::vector<char> &in_out, std::string values)
{
    std::sort(in_out.begin(), in_out.end());
    std::sort(values.begin(), values.end());
    std::vector<char> x = in_out;
    in_out.clear();
    std::set_intersection(x.begin(), x.end(), values.begin(), values.end(), std::back_inserter(in_out));
}
std::vector<char> pure_intersect(std::vector<char> left, std::vector<char> right)
{
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    std::vector<char> out;
    std::set_intersection(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(out));
    return out;
}
void union_it_up(std::vector<char> &in_out, std::vector<char> right)
{
    std::vector<char> left = in_out;
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    in_out.clear();
    std::set_union(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(in_out));
}
std::vector<char> pure_union(std::vector<char> left, std::vector<char> right)
{
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    std::vector<char> out;
    std::set_union(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(out));
    return out;
}
void set_difference(std::vector<char> &in_out, std::vector<char> remove)
{
    std::vector<char> x = in_out;
    in_out.clear();
    std::sort(x.begin(), x.end());
    std::sort(remove.begin(), remove.end());
    std::set_difference(x.begin(), x.end(), remove.begin(), remove.end(), std::back_inserter(in_out));
}
std::vector<char> pure_difference(std::vector<char> left, std::vector<char> right)
{
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    std::vector<char> out;
    std::set_difference(left.begin(), left.end(), right.begin(), right.end(), std::back_inserter(out));
    return out;
}
int main()
{
    {
        //part 1 answer
        size_t count = 0;
        for (auto &i : inputs)
        {
            for (auto &output : i.outputs)
            {
                if (basic_guess_char(output.size()) > 0)
                    count++;
            }
        }
        std::cout << "count of unique output characters: " << count << "\n";
    }

    size_t count = 0;
    for (auto &i : inputs)
    {
        std::vector<char> entries;
        std::vector<char> outputs;
        for (auto &entry : i.entries)
        {
            entries.push_back(basic_guess_char(entry.size()));
        }
        for (auto &output : i.outputs)
        {
            outputs.push_back(basic_guess_char(output.size()));
        }

        std::vector<char> alphabet = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
        std::vector<char> guess_a = alphabet;
        std::vector<char> guess_b = alphabet;
        std::vector<char> guess_c = alphabet;
        std::vector<char> guess_d = alphabet;
        std::vector<char> guess_e = alphabet;
        std::vector<char> guess_f = alphabet;
        std::vector<char> guess_g = alphabet;
        for (auto &entry : i.entries)
        {
            if (entry.size() == 2)
            {
                intersect(guess_c, entry);
                intersect(guess_f, entry);
            }
            if (entry.size() == 3)
            {
                intersect(guess_a, entry);
                intersect(guess_c, entry);
                intersect(guess_f, entry);
            }
            if (entry.size() == 4)
            {
                intersect(guess_b, entry);
                intersect(guess_c, entry);
                intersect(guess_d, entry);
                intersect(guess_f, entry);
            }
        }
        //assert guess_c == guess_f at this point
        auto c_f = pure_union(guess_c, guess_f);
        //assert guess_a.size() == 1 - have found a
        guess_a = pure_difference(guess_a, c_f);
        auto a_c_f = pure_union(guess_a, c_f);

        guess_b = pure_difference(guess_b, c_f);
        guess_d = pure_difference(guess_d, c_f);
        //assert guess_b == guess_d
        auto b_d = pure_union(guess_b, guess_d);

        auto a_b_c_d_f = pure_union(a_c_f, b_d);

        guess_e = pure_difference(guess_e, a_b_c_d_f);
        guess_g = pure_difference(guess_g, a_b_c_d_f);
        //assert guess_e == guess_g
        auto e_g = pure_union(guess_e, guess_g);

        for (auto &entry : i.entries)
        {
            auto vec = to_vec_char(entry);
            if (entry.size() == 5)
            {
                // '2'
                if (pure_intersect(vec, e_g).size() == 2)
                {
                    guess_f = pure_difference(guess_f, vec);
                    guess_c = pure_difference(guess_c, guess_f);
                    guess_b = pure_difference(guess_b, vec);
                    guess_d = pure_difference(guess_d, guess_b);
                }
                // '3'
                if (pure_intersect(vec, c_f).size() == 2)
                {
                    guess_e = pure_difference(guess_e, vec);
                    guess_g = pure_difference(guess_g, guess_e);
                    guess_b = pure_difference(guess_b, vec);
                    guess_d = pure_difference(guess_d, guess_b);
                }
                // '5'
                if (pure_intersect(vec, b_d).size() == 2)
                {
                    guess_c = pure_difference(guess_c, vec);
                    guess_f = pure_difference(guess_f, guess_c);
                    guess_e = pure_difference(guess_e, vec);
                    guess_g = pure_difference(guess_g, guess_e);
                }
            }
            if (entry.size() == 6)
            {
                // '0'
                if (pure_intersect(vec, b_d).size() == 1)
                {
                    guess_d = pure_difference(guess_d, vec);
                    guess_b = pure_difference(guess_b, guess_d);
                }
                // '6'
                if (pure_intersect(vec, c_f).size() == 1)
                {
                    guess_c = pure_difference(guess_c, vec);
                    guess_f = pure_difference(guess_f, guess_c);
                }
                // '9'
                if (pure_intersect(vec, e_g).size() == 1)
                {
                    guess_e = pure_difference(guess_e, vec);
                    guess_g = pure_difference(guess_g, guess_e);
                }
            }
        }

        char a = guess_a[0];
        char b = guess_b[0];
        char c = guess_c[0];
        char d = guess_d[0];
        char e = guess_e[0];
        char f = guess_f[0];
        char g = guess_g[0];

        std::vector<char> l_0 = {a, b, c, e, f, g};    //0: abc efg = 6
        std::vector<char> l_1 = {c, f};                //1:   c  f  = 2 -
        std::vector<char> l_2 = {a, c, d, e, g};       //2: a cde g = 5
        std::vector<char> l_3 = {a, c, d, f, g};       //3: a cd fg = 5
        std::vector<char> l_4 = {b, c, d, f};          //4:  bcd f  = 4 -
        std::vector<char> l_5 = {a, b, d, f, g};       //5: ab d fg = 5
        std::vector<char> l_6 = {a, b, d, e, f, g};    //6: ab defg = 6
        std::vector<char> l_7 = {a, c, f};             //7: a c  f  = 3 -
        std::vector<char> l_8 = {a, b, c, d, e, f, g}; //8: abcdefg = 7 -
        std::vector<char> l_9 = {a, b, c, d, f, g};    //9: abcd fg = 6

        std::string num = "";
        for (auto &o : i.outputs)
        {
            if (o.size() == 2)
                num += '1';
            if (o.size() == 3)
                num += '7';
            if (o.size() == 4)
                num += '4';
            if (o.size() == 7)
                num += '8';
            if (o.size() == 5 && pure_intersect(to_vec_char(o), l_2).size() == 5)
                num += '2';
            if (o.size() == 5 && pure_intersect(to_vec_char(o), l_3).size() == 5)
                num += '3';
            if (o.size() == 5 && pure_intersect(to_vec_char(o), l_5).size() == 5)
                num += '5';
            if (o.size() == 6 && pure_intersect(to_vec_char(o), l_0).size() == 6)
                num += '0';
            if (o.size() == 6 && pure_intersect(to_vec_char(o), l_6).size() == 6)
                num += '6';
            if (o.size() == 6 && pure_intersect(to_vec_char(o), l_9).size() == 6)
                num += '9';
        }
        count += atoi(num.c_str());
        std::cout << "atoi " << atoi(num.c_str()) << "\n";
    }
    std::cout << "final count: " << count << "\n";

    return 0;
}