#pragma once

#include "const.h"
#include "math.h"
#include <cmath>

using namespace std;

class Ball
{
public:
    Point pos;
    Point vel;
    Point acc;
    double R = BALL_R;
    double _last_update;
    Ball(Point pos_) : pos(pos_.x, pos_.y) {}
    Ball() : pos(0.0, 0.0) {}
    void update(Point new_pos, double t)
    {
        static double dt;
        dt = t - _last_update;
        acc = ((new_pos - pos) / dt - vel) / dt;
        vel = (new_pos - pos) / dt;
        pos = new_pos;
    }
};

class Robot : public Ball
{
public:
    int color;
    int r_id;
    bool is_used;
    double angle;
    double angle_vel;
    double angle_acc;
    double R = ROBOT_R;
    double _lifetime;
    Robot(Point pos_, double angle_) : Ball(pos_), angle(angle_) {}
    Robot() : Ball(Point(GRAVEYARD_POS_X, 0)), angle(0.0) {}
    void update(Point new_pos, double new_angle, double t)
    {
        static double dt;
        dt = t - _last_update;
        acc = ((new_pos - pos) / dt - vel) / dt;
        vel = (new_pos - pos) / dt;
        pos = new_pos;
        angle_acc = ((new_angle - angle) / dt - angle_vel) / dt;
        angle_vel = (new_angle - angle) / dt;
        angle = new_angle;
        if (!((new_pos == Point(GRAVEYARD_POS_X, 0)) ^ is_used)) {
            _lifetime = t;
        }
        if (_lifetime > TIME_TO_BORN) {
            is_used = true;
        }
        else if (_lifetime > TIME_TO_DIE) {
            is_used = false;
        }
        _last_update = t;
    }
};

struct Goal
{
    Point center, up, down, frw_up, frw_down, frw_center, center_up, center_down;
    Point hull[5], big_hull[5]; 
    Goal(int polarity) : center(FIELD_DX / 2.0 * polarity, 0),
                                                                    up(FIELD_DX / 2.0 * polarity, ZONE_DY / 2.0),
                                                                    down(FIELD_DX / 2.0 * polarity, -ZONE_DY / 2.0),
                                                                    frw_up(FIELD_DX / 2.0 * polarity - ZONE_DX * polarity, ZONE_DY / 2.0),
                                                                    frw_down(FIELD_DX / 2.0 * polarity - ZONE_DX * polarity, -ZONE_DY / 2.0),
                                                                    frw_center(FIELD_DX / 2.0 * polarity - ZONE_DX * polarity, 0),
                                                                    center_up(FIELD_DX / 2.0 * polarity, GOAL_DY * polarity / 2.0),
                                                                    center_down(FIELD_DX / 2.0 * polarity, -GOAL_DY * polarity / 2.0)
    {
        hull[0] = this->center_up;
        hull[1] = this->frw_up;
        hull[2] = this->frw_down;
        hull[3] = this->center_down;
        hull[4] = Point(INF * polarity, 0);
        big_hull[0] = hull[0] + Point(0, ROBOT_R * polarity);
        big_hull[1] = hull[1] + Point(-ROBOT_R * polarity, ROBOT_R * polarity);
        big_hull[2] = hull[2] + Point(-ROBOT_R * polarity, -ROBOT_R * polarity);
        big_hull[3] = hull[3] + Point(0, -ROBOT_R * polarity);
        big_hull[4] = hull[4];
    }
};

class Field
{
public:
    Goal ally_goal, enemy_goal;
    Point hull[4];
    Robot allies[MAX_ROBOT_COUNT], enemies[MAX_ROBOT_COUNT];
    Robot active_allies[MAX_ROBOT_COUNT], active_enemies[MAX_ROBOT_COUNT];
    int n_active_allies, n_active_enemies;
    Ball ball;
    Field(int polarity) : ally_goal(polarity),
                                                                                      enemy_goal(-polarity)
    {
        hull[0] = Point(FIELD_DX, FIELD_DY);
        hull[1] = Point(FIELD_DX, -FIELD_DY);
        hull[2] = Point(-FIELD_DX, -FIELD_DY);
        hull[3] = Point(-FIELD_DX, FIELD_DY);
    }

    void update_all(Point *ally_robots_poses, double *ally_robot_angles, Point *enemy_robots_poses, double *enemy_robots_angles, Point ball_pos, double t)
    {
        static int i;
        for (i = 0; i < MAX_ROBOT_COUNT; i++)
        {
            allies[i].update(ally_robots_poses[i], ally_robot_angles[i], t);
            enemies[i].update(enemy_robots_poses[i], enemy_robots_angles[i], t);
        }
        ball.update(ball_pos, t);
    }

    void get_active_robots()
    {
        static int cnt, i;
        cnt = 0;
        for (i = 0; i < MAX_ROBOT_COUNT; i++)
            if (allies[i].is_used)
            {
                active_allies[cnt] = allies[i];
                cnt++;
            }
        n_active_allies = cnt;
        cnt = 0;
        for (i = 0; i < MAX_ROBOT_COUNT; i++)
            if (enemies[i].is_used)
            {
                active_enemies[cnt] = enemies[i];
                cnt++;
            }

        n_active_enemies = cnt;
    }
};
