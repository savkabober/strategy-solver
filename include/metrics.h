#pragma once
#include "field.h"
#include "const.h"
#include "aux.h"
#define ALL_TEAMS 0
#define YELLOW 1
#define BLUE 2
struct Waypoint
{
    public:
    double time;
    double acc_angle;
    Waypoint(double time_,double acc_angle_):time(time_),acc_angle(acc_angle_) {}
};

float point_metrics(Waypoint *wps,int traj_len,Field field,Point tgt_point)
{
    Point acc;
    Point vel;
    Point pos;
    double est;
    for(int i;i<traj_len;i++)
    {
        Waypoint wp = wps[i];
        acc = rotate(Point(MAX_ACCELERATION,0),wp.acc_angle);
        pos = pos + vel*wp.time + acc*wp.time*wp.time/2;
        vel = vel + acc*wp.time;
    }
    est = dist(pos,tgt_point);
    if(est<1)//tolerance
        est = 0;
    return est;
}
float speed_metrics(Waypoint *wps,int traj_len,Field field,Point tgt_speed)
{
    Point acc;
    Point vel;
    Point pos;
    double est;
    for(int i;i<traj_len;i++)
    {
        Waypoint wp = wps[i];
        acc = rotate(Point(MAX_ACCELERATION,0),wp.acc_angle);
        pos = pos + vel*wp.time + acc*wp.time*wp.time/2;
        vel = vel + acc*wp.time;
    }
    est = dist(vel,tgt_speed);
    if(est<5)//tolerance
        est = 0;

    return est;
}
