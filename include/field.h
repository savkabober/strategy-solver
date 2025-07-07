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
    double _lifetime, _cur_time;
    Robot(Point pos_, double angle_) : Ball(pos_), angle(angle_) {}
    Robot() : Ball(Point(GRAVEYARD_POS_X, 0)), angle(0.0) {}
    void update(Point new_pos, double new_angle)
    {
        static double dt;
        dt = _cur_time - _last_update;
        acc = ((new_pos - pos) / dt - vel) / dt;
        vel = (new_pos - pos) / dt;
        pos = new_pos;
        angle_acc = ((new_angle - angle) / dt - angle_vel) / dt;
        angle_vel = (new_angle - angle) / dt;
        angle = new_angle;
        _last_update = _cur_time;
    }

    void process(double t) {
        if (!(_last_update == _cur_time ^ is_used)) {
            _lifetime = _cur_time;
        }
        if (_lifetime >= TIME_TO_BORN && !is_used) {
            is_used = true;
        }
        else if (_lifetime >= TIME_TO_DIE && is_used) {
            is_used = false;
        }
        _cur_time = t;
    }
};

struct Goal
{
    Point center, up, down, frw_up, frw_down, frw_center;
    Point hull[4];
    Goal(double goal_dx, double pen_dx, double pen_dy, int polarity) : center(goal_dx * polarity, 0),
                                                                    up(goal_dx * polarity, pen_dy / 2),
                                                                    down(goal_dx * polarity, -pen_dy / 2),
                                                                    frw_up(goal_dx * polarity - pen_dx * polarity, pen_dy),
                                                                    frw_down(goal_dx * polarity - pen_dx * polarity, -pen_dy),
                                                                    frw_center(goal_dx * polarity - pen_dx * polarity, 0)
    {
        hull[0] = this->up;
        hull[1] = this->down;
        hull[2] = this->frw_down;
        hull[3] = this->frw_up;
    }
};

class Field
{
public:
    Goal ally_goal, enemy_goal;
    Point hull[4]; // EBANIE KITAYCI (a chto ne tak to? i stav probeli pozhaluysta)
    Robot allies[MAX_ROBOT_COUNT], enemies[MAX_ROBOT_COUNT];
    Robot active_allies[MAX_ROBOT_COUNT], active_enemies[MAX_ROBOT_COUNT];
    int n_active_allies, n_active_enemies;
    Ball ball;
    Field(double field_dx, double field_dy, double pen_dx, double pen_dy, int polarity) : ally_goal(field_dx, pen_dx, pen_dy, polarity),
                                                                                      enemy_goal(field_dx, pen_dx, pen_dy, -polarity)
    {
        hull[0] = Point(field_dx, field_dy);
        hull[1] = Point(field_dx, -field_dy);
        hull[2] = Point(-field_dx, -field_dy);
        hull[3] = Point(-field_dx, field_dy);
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
