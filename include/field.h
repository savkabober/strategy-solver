#pragma once
#include "const.h"
#include "aux.h"
#include <math.h>
class Entity
{
    public:
    Point pos;
    Point vel;
    Point acc;
    float angle;
    float angle_vel;
    float angle_acc;
    float R;
    float _last_update;
    Entity(Point pos_, float angle_,float R_): pos(pos_.x,pos_.y), angle(angle_),R(R_) {}
    Entity(): pos(0,0), angle(0), R(ROBOT_R) {}
    void update(Point new_pos,float new_angle,float t)
    {
        float dt = t-_last_update;
        acc = (vel-(pos-new_pos)/dt)/dt;
        vel = (pos-new_pos)/dt;
        pos = new_pos; 
        angle_acc = (angle_vel-(angle-new_angle)/dt)/dt;
        angle_vel = (angle-new_angle)/dt;
        angle = new_angle;
        _last_update = t;
    }
};

class Goal
{
    public:
    Point center;
    Point up;
    Point down;
    Point frw_up;
    Point frw_down;
    Point frw_center;
    Point hull[4];
    Goal(float goal_dx,float pen_dx,float pen_dy,int polarity): 
    center(goal_dx*polarity,0),
    up(goal_dx*polarity,pen_dy/2),
    down(goal_dx*polarity,-pen_dy/2),
    frw_up(goal_dx*polarity-pen_dx*polarity,pen_dy),
    frw_down(goal_dx*polarity-pen_dx*polarity,-pen_dy),
    frw_center(goal_dx*polarity-pen_dx*polarity,0)
    {
        hull[0] = this->up;
        hull[1] = this->down;
        hull[2] = this->frw_down;
        hull[3] = this->frw_up;
    }
};
class Robot:public Entity
{
    public:
    int color;
    int r_id;
    bool is_used;
    void update(Point new_pos,float new_angle,float t)
    {
        float dt = t-_last_update;
        acc = (vel-(pos-new_pos)/dt)/dt;
        vel = (pos-new_pos)/dt;
        pos = new_pos; 
        angle_acc = (angle_vel-(angle-new_angle)/dt)/dt;
        angle_vel = (angle-new_angle)/dt;
        angle = new_angle;
        if(new_pos!=GRAVEYARD_POS)
            is_used = true;
        else
            is_used = false;
        _last_update = t;
        
    }
    
};
class Field
{
    public:

    Goal ally_goal;
    Goal enemy_goal;
    Point hull[4];//EBANIE KITAYCI
    Robot allies[MAX_ROBOT_COUNT];
    Robot enemies[MAX_ROBOT_COUNT];
    Entity ball;
    Field (float field_dx,float field_dy,float pen_dx,float pen_dy,int polarity):
    ally_goal(field_dx,pen_dx,pen_dy,polarity),
    enemy_goal(field_dx,pen_dx,pen_dy,-polarity)
    {
        hull[0] = Point(field_dx,field_dy);
        hull[1] = Point(field_dx,-field_dy);
        hull[2] = Point(-field_dx,-field_dy);
        hull[3] = Point(-field_dx,field_dy);
    }
    void update_all(Point *ally_robots_poses,float *ally_robot_angles,Point *enemy_robots_poses,float *enemy_robots_angles,Point ball_pos,float t)
    {
        for(int i;i<MAX_ROBOT_COUNT;i++)
        {
            allies[i].update(ally_robots_poses[i],ally_robot_angles[i],t);
            enemies[i].update(enemy_robots_poses[i],enemy_robots_angles[i],t);
        }
        ball.update(ball_pos,0,t);
    }
    int active_allies_num()
    {
        int cnt;
        for(int i;i<MAX_ROBOT_COUNT;i++)
            if(allies[i].is_used)
                cnt++;
        return cnt;
    }
    void active_allies(Robot *list)
    {
        int cnt;
        for(int i;i<MAX_ROBOT_COUNT;i++)
            if(allies[i].is_used)
                cnt++;
        int j;
        for(int i; i<MAX_ROBOT_COUNT;i++)
            if(allies[i].is_used)
            {
                list[j] = allies[i];
                j++;
            }

    }
    
};