#include "common.h"

enum class Axis
{
    x,
    y,
    z,
};
enum class Direction
{
    up,
    down
};
using Combo = std::pair<Axis, Direction>;
using Triple = std::array<Combo, 3>;
std::array<Triple, 24> orientations = {
    Triple{Combo{Axis::x, Direction::up}, Combo{Axis::y, Direction::up}, Combo{Axis::z, Direction::up}},
    Triple{Combo{Axis::x, Direction::up}, Combo{Axis::y, Direction::down}, Combo{Axis::z, Direction::down}},
    Triple{Combo{Axis::x, Direction::up}, Combo{Axis::z, Direction::up}, Combo{Axis::y, Direction::down}},
    Triple{Combo{Axis::x, Direction::up}, Combo{Axis::z, Direction::down}, Combo{Axis::y, Direction::up}},
    Triple{Combo{Axis::x, Direction::down}, Combo{Axis::y, Direction::up}, Combo{Axis::z, Direction::up}},
    Triple{Combo{Axis::x, Direction::down}, Combo{Axis::y, Direction::down}, Combo{Axis::z, Direction::down}},
    Triple{Combo{Axis::x, Direction::down}, Combo{Axis::z, Direction::up}, Combo{Axis::y, Direction::down}},
    Triple{Combo{Axis::x, Direction::down}, Combo{Axis::z, Direction::down}, Combo{Axis::y, Direction::up}},

    Triple{Combo{Axis::y, Direction::up}, Combo{Axis::x, Direction::up}, Combo{Axis::z, Direction::up}},
    Triple{Combo{Axis::y, Direction::up}, Combo{Axis::x, Direction::down}, Combo{Axis::z, Direction::down}},
    Triple{Combo{Axis::y, Direction::up}, Combo{Axis::z, Direction::up}, Combo{Axis::x, Direction::down}},
    Triple{Combo{Axis::y, Direction::up}, Combo{Axis::z, Direction::down}, Combo{Axis::x, Direction::up}},
    Triple{Combo{Axis::y, Direction::down}, Combo{Axis::x, Direction::up}, Combo{Axis::z, Direction::up}},
    Triple{Combo{Axis::y, Direction::down}, Combo{Axis::x, Direction::down}, Combo{Axis::z, Direction::down}},
    Triple{Combo{Axis::y, Direction::down}, Combo{Axis::z, Direction::up}, Combo{Axis::x, Direction::down}},
    Triple{Combo{Axis::y, Direction::down}, Combo{Axis::z, Direction::down}, Combo{Axis::x, Direction::up}},

    Triple{Combo{Axis::z, Direction::up}, Combo{Axis::y, Direction::up}, Combo{Axis::x, Direction::up}},
    Triple{Combo{Axis::z, Direction::up}, Combo{Axis::y, Direction::down}, Combo{Axis::x, Direction::down}},
    Triple{Combo{Axis::z, Direction::up}, Combo{Axis::x, Direction::up}, Combo{Axis::y, Direction::down}},
    Triple{Combo{Axis::z, Direction::up}, Combo{Axis::x, Direction::down}, Combo{Axis::y, Direction::up}},
    Triple{Combo{Axis::z, Direction::down}, Combo{Axis::y, Direction::up}, Combo{Axis::x, Direction::up}},
    Triple{Combo{Axis::z, Direction::down}, Combo{Axis::y, Direction::down}, Combo{Axis::x, Direction::down}},
    Triple{Combo{Axis::z, Direction::down}, Combo{Axis::x, Direction::up}, Combo{Axis::y, Direction::down}},
    Triple{Combo{Axis::z, Direction::down}, Combo{Axis::x, Direction::down}, Combo{Axis::y, Direction::up}},
};

struct Point3D
{
    int x{}, y{}, z{};
};
struct Dir3D
{
    int x{}, y{}, z{};
    Dir3D get_xyz(Triple triple)
    {
        Dir3D ret{};
        ret.x = ((triple[0].first == Axis::x) * x + (triple[0].first == Axis::y) * y + (triple[0].first == Axis::z) * z) * (triple[0].second == Direction::up ? 1 : -1);
        ret.y = ((triple[1].first == Axis::x) * x + (triple[1].first == Axis::y) * y + (triple[1].first == Axis::z) * z) * (triple[1].second == Direction::up ? 1 : -1);
        ret.z = ((triple[2].first == Axis::x) * x + (triple[2].first == Axis::y) * y + (triple[2].first == Axis::z) * z) * (triple[2].second == Direction::up ? 1 : -1);
        return ret;
    }
    bool operator==(Dir3D const &other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

std::array<std::vector<Point3D>, 5> test_inputs = {
    std::vector<Point3D>{
        {404, -588, -901},
        {528, -643, 409},
        {-838, 591, 734},
        {390, -675, -793},
        {-537, -823, -458},
        {-485, -357, 347},
        {-345, -311, 381},
        {-661, -816, -575},
        {-876, 649, 763},
        {-618, -824, -621},
        {553, 345, -567},
        {474, 580, 667},
        {-447, -329, 318},
        {-584, 868, -557},
        {544, -627, -890},
        {564, 392, -477},
        {455, 729, 728},
        {-892, 524, 684},
        {-689, 845, -530},
        {423, -701, 434},
        {7, -33, -71},
        {630, 319, -379},
        {443, 580, 662},
        {-789, 900, -551},
        {459, -707, 401}},
    std::vector<Point3D>{
        {686, 422, 578},
        {605, 423, 415},
        {515, 917, -361},
        {-336, 658, 858},
        {95, 138, 22},
        {-476, 619, 847},
        {-340, -569, -846},
        {567, -361, 727},
        {-460, 603, -452},
        {669, -402, 600},
        {729, 430, 532},
        {-500, -761, 534},
        {-322, 571, 750},
        {-466, -666, -811},
        {-429, -592, 574},
        {-355, 545, -477},
        {703, -491, -529},
        {-328, -685, 520},
        {413, 935, -424},
        {-391, 539, -444},
        {586, -435, 557},
        {-364, -763, -893},
        {807, -499, -711},
        {755, -354, -619},
        {553, 889, -390}},
    std::vector<Point3D>{
        {649, 640, 665},
        {682, -795, 504},
        {-784, 533, -524},
        {-644, 584, -595},
        {-588, -843, 648},
        {-30, 6, 44},
        {-674, 560, 763},
        {500, 723, -460},
        {609, 671, -379},
        {-555, -800, 653},
        {-675, -892, -343},
        {697, -426, -610},
        {578, 704, 681},
        {493, 664, -388},
        {-671, -858, 530},
        {-667, 343, 800},
        {571, -461, -707},
        {-138, -166, 112},
        {-889, 563, -600},
        {646, -828, 498},
        {640, 759, 510},
        {-630, 509, 768},
        {-681, -892, -333},
        {673, -379, -804},
        {-742, -814, -386},
        {577, -820, 562}},
    std::vector<Point3D>{
        {-589, 542, 597},
        {605, -692, 669},
        {-500, 565, -823},
        {-660, 373, 557},
        {-458, -679, -417},
        {-488, 449, 543},
        {-626, 468, -788},
        {338, -750, -386},
        {528, -832, -391},
        {562, -778, 733},
        {-938, -730, 414},
        {543, 643, -506},
        {-524, 371, -870},
        {407, 773, 750},
        {-104, 29, 83},
        {378, -903, -323},
        {-778, -728, 485},
        {426, 699, 580},
        {-438, -605, -362},
        {-469, -447, -387},
        {509, 732, 623},
        {647, 635, -688},
        {-868, -804, 481},
        {614, -800, 639},
        {595, 780, -596}},
    std::vector<Point3D>{
        {727, 592, 562},
        {-293, -554, 779},
        {441, 611, -461},
        {-714, 465, -776},
        {-743, 427, -804},
        {-660, -479, -426},
        {832, -632, 460},
        {927, -485, -438},
        {408, 393, -506},
        {466, 436, -512},
        {110, 16, 151},
        {-258, -428, 682},
        {-393, 719, 612},
        {-211, -452, 876},
        {808, -476, -593},
        {-575, 615, 604},
        {-485, 667, 467},
        {-680, 325, -822},
        {-627, -443, -432},
        {872, -547, -609},
        {833, 512, 582},
        {807, 604, 487},
        {839, -516, 451},
        {891, -625, 532},
        {-652, -548, -490},
        {30, -46, -14}}};
// test_inputs answer = 79
std::array<std::vector<Point3D>, 30> inputs = {
#include "inputs/day19.txt"
};

struct Scanner
{
    std::vector<Point3D> points;
    std::vector<Dir3D> directions;
    Triple orientation;
};

int main()
{
    std::vector<Scanner> scanners;
    for (auto &i : test_inputs)
    {
        Scanner s{};
        s.points = i;
        for (size_t i = 0; i < s.points.size() - 1; i++)
        {
            for (size_t j = i + 1; j < s.points.size(); j++)
            {
                s.directions.push_back({s.points[i].x - s.points[j].x,
                                        s.points[i].y - s.points[j].y,
                                        s.points[i].z - s.points[j].z});
            }
        }
        scanners.push_back(s);
    }
    std::vector<Scanner> set_scanners;
    set_scanners.push_back(set_scanners.back());
    scanners.pop_back();

    return 0;
}