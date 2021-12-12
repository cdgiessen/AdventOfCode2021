#include "common.h"

enum CN
{
    start,
    kc,
    pd,
    NV,
    zw,
    UI,
    HK,
    end,
    ih,
    ks,
    MF,
    mq,
    LF,
};

struct Cave
{
    CN name;
    std::vector<CN> paths;
};

std::unordered_map<CN, Cave> caves{
    std::pair{start, Cave{start, {kc, UI, zw}}},
    std::pair{kc, Cave{kc, {start, zw, pd, UI, HK, MF}}},
    std::pair{pd, Cave{pd, {NV, ih, UI, kc, ks, MF}}},
    std::pair{NV, Cave{NV, {pd, ih, zw, ks}}},
    std::pair{zw, Cave{zw, {start, UI, HK, kc, NV}}},
    std::pair{UI, Cave{UI, {start, pd, kc, zw}}},
    std::pair{HK, Cave{HK, {end, zw, kc, ih, ks}}},
    std::pair{end, Cave{end, {ks, ih, HK}}},
    std::pair{ih, Cave{ih, {pd, end, HK, NV}}},
    std::pair{ks, Cave{ks, {LF, pd, HK, NV, end}}},
    std::pair{MF, Cave{MF, {mq, kc, pd}}},
    std::pair{mq, Cave{mq, {MF}}},
    std::pair{LF, Cave{LF, {ks}}},
};

bool is_big(CN cn)
{
    if (cn == start)
        return false;
    if (cn == kc)
        return false;
    if (cn == pd)
        return false;
    if (cn == NV)
        return true;
    if (cn == zw)
        return false;
    if (cn == UI)
        return true;
    if (cn == HK)
        return true;
    if (cn == end)
        return false;
    if (cn == ih)
        return false;
    if (cn == ks)
        return false;
    if (cn == MF)
        return true;
    if (cn == mq)
        return false;
    if (cn == LF)
        return true;
}

const char *str(CN cn)
{
    if (cn == start)
        return "start";
    if (cn == kc)
        return "kc";
    if (cn == pd)
        return "pd";
    if (cn == NV)
        return "NV";
    if (cn == zw)
        return "zw";
    if (cn == UI)
        return "UI";
    if (cn == HK)
        return "HK";
    if (cn == end)
        return "end";
    if (cn == ih)
        return "ih";
    if (cn == ks)
        return "ks";
    if (cn == MF)
        return "MF";
    if (cn == mq)
        return "mq";
    if (cn == LF)
        return "LF";
}

bool can_traverse_p1(std::vector<CN> const &route, CN p)
{
    if (is_big(p))
        return true;
    for (auto &cn : route)
    {
        if (p == cn)
        {
            return false;
        }
    }
    return true;
}
bool can_traverse_p2(std::vector<CN> const &route, CN p)
{
    if (is_big(p))
        return true;
    if (p == start)
        return false;
    std::vector<CN> new_route = route;

    return true;
}

std::vector<std::vector<CN>> get_routes(std::vector<CN> const &route)
{
    std::vector<std::vector<CN>> out_routes;
    CN top = route.back();

    for (auto &p : caves[top].paths)
    {
        if (p == start)
            continue;
        if (p == end)
        {
            std::vector<CN> new_route = route;
            // for (auto &c : new_route)
            // {
            //     std::cout << str(c) << "-";
            // }
            // std::cout << "end\n";
            new_route.push_back(end);
            out_routes.push_back({new_route});
            continue;
        }
        std::vector<CN> new_route = route;
        new_route.push_back(p);
        int count_dupes = 0;
        if (!is_big(p))
        {
            for (int i = 1; i < new_route.size(); i++)
            {
                if (!is_big(new_route[i]))
                {
                    for (int j = i + 1; j < new_route.size(); j++)
                    {
                        if (new_route[i] == new_route[j])
                        {
                            count_dupes++;
                        }
                    }
                }
            }
        }
        if (count_dupes <= 1)
        {
            auto new_routes = get_routes(new_route);
            for (auto &r : new_routes)
            {
                out_routes.push_back(r);
            }
        }
    }
    return out_routes;
}
int main()
{
    std::vector<CN> start_route = {start};
    auto routes = get_routes(start_route);
    std::cout << "num routes: " << routes.size() << "\n";
    return 0;
}