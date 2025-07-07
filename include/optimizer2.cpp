#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include "math.h"
#include "drawing.h"
#include <thread>

using namespace std;
struct Waypoint
{
public:
    double time;
    double acc_angle;
    Waypoint(double time_, double acc_angle_) : time(time_), acc_angle(acc_angle_) {}
};
long long int time()
{
    auto start = std::chrono::high_resolution_clock::now();
    auto duration = start.time_since_epoch();
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    return millis;
}
typedef vector<Waypoint> Trajectory;
mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
double random_double(double min, double max)
{
    return uniform_real_distribution<double>(min, max)(rng);
}

int random_int(int min, int max)
{
    return uniform_int_distribution<int>(min, max)(rng);
}

void mutate_change_angle(Trajectory &t)
{
    if (t.empty())
        return;
    int idx = random_int(0, t.size() - 1);
    t[idx].acc_angle += random_double(-M_PI / 8.0, M_PI / 8.0);
    t[idx].acc_angle = wind_down_angle(t[idx].acc_angle);
}

void mutate_change_time(Trajectory &t)
{
    if (t.empty())
        return;
    int idx = random_int(0, t.size() - 1);
    t[idx].time *= random_double(0.7, 1.3); //+-30%
    if (t[idx].time < 0.1)
        t[idx].time = 0.1; // min time
}

void mutate_add_segment(Trajectory &t)
{
    if (t.empty())
    {
        t.push_back({random_double(-M_PI, M_PI), random_double(1.0, 5.0)});
        return;
    }
    int idx = random_int(0, t.size() - 1);
    Waypoint original_seg = t[idx];

    double split_time = random_double(0.1, original_seg.time - 0.1);
    if (split_time > 0 && original_seg.time - split_time > 0)
    {
        t[idx].time = split_time;
        Waypoint new_seg = {random_double(-M_PI, M_PI), original_seg.time - split_time};
        t.insert(t.begin() + idx + 1, new_seg);
    }
}

void mutate_remove_segment(Trajectory &t)
{
    if (t.size() <= 1)
        return;
    int idx = random_int(0, t.size() - 1);
    t.erase(t.begin() + idx);
}

void mutate(Trajectory &trajectory)
{
    double choice = random_double(0, 1);
    if (choice < 0.4)
    { // 40%
        mutate_change_angle(trajectory);
    }
    else if (choice < 0.8)
    { // 40%
        mutate_change_time(trajectory);
    }
    else if (choice < 0.95)
    { // 15%
        mutate_add_segment(trajectory);
    }
    else
    { // 5%
        mutate_remove_segment(trajectory);
    }
}
int main()
{

    Drawer drawer = Drawer(950, 650);
    // 1 stage: 0.4261636310795653 3.373608626246523
    // 2 stage: -2.7154290225102278 1.4336855804409427
    Trajectory traj = {Waypoint(3.373608626246523, 0.4261636310795653), Waypoint(1.4336855804409427, 2.7154290225102278)};
    // long long int start = time();
    while (drawer.window.isOpen())
    {
        double total_time;
        for (Waypoint wp : traj)
            total_time += wp.time;
        Point pos = Point(-4500, -3000);
        Point vel = Point(500, 0);
        for (double t = 0; t < total_time; t += 0.01)
        {
            Waypoint cur_wp = Waypoint(0, 0);
            double total_wp_time = 0;
            for (Waypoint wp : traj)
            {
                total_wp_time += wp.time;
                if (t < total_wp_time)
                {
                    cur_wp = wp;
                    break;
                }
            }
            Point acc = Point(MAX_ACCELERATION, 0).rotate(cur_wp.acc_angle);
            if ((vel + acc * 0.01).mag() < MAX_SPEED)
                vel += acc * 0.01;
            pos += vel * 0.01;
            drawer.drawCircle(pos, 10, Color(200, 200, 200));
        }

        drawer.update();
    }

    // cout << random_double(0,10) << endl;
    return 0;
}