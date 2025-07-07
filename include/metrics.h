#pragma once

#include "field.h"
#include "const.h"
#include "math.h"
#include <complex>
#include <vector>
#include "quicksort.h"

using namespace std;

struct RbtMove
{
    Object objects[2 * MAX_ROBOT_COUNT + 1];
    Point r_move[2 * MAX_SOLVER_DEGREE + 1], v_move[2 * MAX_SOLVER_DEGREE + 1], a_move[2 * MAX_SOLVER_DEGREE], target_pos, target_vel, m_center[2 * MAX_ROBOT_COUNT + 1];
    double t_move[2 * MAX_SOLVER_DEGREE + 1];
    vector<double> roots[2 * MAX_ROBOT_COUNT + 1], grp_rts[2 * MAX_ROBOT_COUNT + 1];
    int n_move, r_id, n_objects, n_groups, i, j, k, group[2 * MAX_ROBOT_COUNT + 1];
    void set_config(int r_id_)
    {
        r_id = r_id_;
    }

    void reset(Field field, Point target_pos_, Point target_vel_, bool ball_collision = true)
    {
        static Robot rbt;
        static int n_group;
        target_pos = target_pos_;
        target_vel = target_vel_;
        n_move = 0;
        r_move[0] = field.allies[r_id].pos;
        v_move[0] = field.allies[r_id].vel;
        t_move[0] = 0;
        n_objects = 0;
        for (i = 0; i < field.n_active_allies; i++)
        {
            rbt = field.active_allies[i];
            if (rbt.r_id != r_id && (r_move[0] - rbt.pos).mag() >= 2.0 * ROBOT_R && (target_pos - rbt.pos).mag() >= 2.0 * ROBOT_R)
            {
                objects[n_objects] = Object(rbt.pos, rbt.R);
                n_objects++;
            }
        }
        for (i = 0; i < field.n_active_enemies; i++)
        {
            rbt = field.active_enemies[i];
            if ((r_move[0] - rbt.pos).mag() >= 2.0 * ROBOT_R && (target_pos - rbt.pos).mag() >= 2.0 * ROBOT_R)
            {
                objects[n_objects] = Object(rbt.pos, rbt.R);
                n_objects++;
            }
        }
        if (ball_collision && (r_move[0] - field.ball.pos).mag() >= ROBOT_R + BALL_R && (target_pos - field.ball.pos).mag() >= ROBOT_R + BALL_R)
        {
            objects[n_objects] = Object(field.ball.pos, field.ball.R);
            n_objects++;
        }
        n_groups = 0;
        for (i = 0; i < n_objects; i++)
        {
            group[i] = -1;
            for (j = i - 1; j >= 0; j--)
            {
                if ((objects[i].c - objects[j].c).mag() < objects[i].r + objects[j].r + 2 * ROBOT_R)
                {
                    group[i] = group[j];
                }
            }
            if (group[i] == -1)
            {
                group[i] = n_groups;
                n_groups++;
            }
        }
        for (i = 0; i < n_group; i++)
        {
            n_group = 0;
            for (j = 0; j < n_objects; j++)
            {
                if (group[j] == i)
                {
                    m_center[i] += objects[j].c;
                    n_group++;
                }
            }
            m_center[i] /= n_group;
        }
        for (i = 0; i < 2 * MAX_ROBOT_COUNT + 1; i++)
        {
            roots[i] = vector<double>();
            roots[i].push_back(0.0);
            grp_rts[i] = vector<double>();
        }
    }

    void append_segment(double angle, double t)
    {
        static double acc_time, min_t, ak, bk, ck, dk, ek, real_rt;
        static Point r, v, a, rp;
        static complex<double> complex_roots[4];
        static int n_st, n_rts;
        if (t == 0)
        {
            return;
        }
        acc_time = 2.0 * a_move[n_move].unity().scalar(-v_move[n_move]) / MAX_ACCELERATION;
        acc_time = fmax(acc_time, 0.0);
        n_st = n_move;
        if (acc_time != 0.0)
        {
            min_t = fmin(acc_time, t);
            a_move[n_move] = Point(MAX_ACCELERATION, 0).rotate(angle);
            t_move[n_move + 1] = t_move[n_move] + min_t;
            v_move[n_move + 1] = v_move[n_move] + a_move[n_move] * min_t;
            r_move[n_move + 1] = r_move[n_move] + (v_move[n_move] + v_move[n_move + 1]) * min_t / 2.0;
            n_move++;
        }
        if (t > acc_time)
        {
            a_move[n_move] = Point(0, 0);
            t_move[n_move + 1] = t_move[n_move] + t - acc_time;
            v_move[n_move + 1] = v_move[n_move];
            r_move[n_move + 1] = r_move[n_move] + v_move[n_move + 1] * (t - acc_time);
            n_move++;
        }
        for (i = n_st; i < n_move; i++)
        {
            r = r_move[i];
            v = v_move[i];
            a = a_move[i];
            for (j = 0; j < n_objects; j++)
            {
                rp = objects[j].c;
                ak = (r.x * r.x - 2.0 * r.x * rp.x + rp.x * rp.x) + (r.y * r.y - 2.0 * r.y * rp.y + rp.y * rp.y) - (ROBOT_R + objects[j].r) * (ROBOT_R + objects[j].r);
                bk = 2.0 * ((r.x * v.x - v.x * rp.x) + (r.y * v.y - v.y * rp.y));
                ck = (r.x * a.x + v.x * v.x - a.x * rp.x) + (r.y * a.y + v.y * v.y - a.y * rp.y);
                dk = (v.x * a.x) + (v.y * a.y);
                ek = (a.x * a.x / 4.0) + (a.y * a.y / 4.0);
                n_rts = solve_four(ak, bk, ck, dk, ek, complex_roots);
                for (k = 0; k < n_rts; k++)
                {
                    if (abs(imag(complex_roots[k])) < EPSILON)
                    {
                        real_rt = real(complex_roots[k]);
                        if (real_rt >= 0 && real_rt < t_move[i + 1] - t_move[i])
                        {
                            roots[j].push_back(real_rt + t_move[i]);
                        }
                    }
                }
            }
        }
    }

    int get_t_idx(double t)
    {
        if (t < 0 || t > t_move[n_move])
        {
            return -1;
        }
        if (t == 0)
        {
            return 0;
        }
        static int idx;
        for (idx = 1; t_move[idx] < t; idx++)
            ;
        return idx - 1;
    }

    Point get_current_pos(double t, int idx_ = -1)
    {
        static double dt;
        static int idx;
        if (idx_ >= 0 && idx_ < n_move)
        {
            idx = idx_;
        }
        else
        {
            idx = get_t_idx(t);
        }
        if (idx == -1)
        {
            return Point(0, 0, true);
        }
        dt = t - t_move[idx];
        return r_move[idx] + v_move[idx] * dt + a_move[idx] * dt * dt / 2.0;
    }

    Point get_current_vel(double t, int idx_ = -1)
    {
        static int idx;
        if (idx_ >= 0 && idx_ < n_move)
        {
            idx = idx_;
        }
        else
        {
            idx = get_t_idx(t);
        }
        if (idx == -1)
        {
            return Point(0, 0, true);
        }
        return v_move[idx] + a_move[idx] * (t - t_move[idx]);
    }

    Point get_current_acc(double t, int idx_ = -1)
    {
        static int idx;
        if (idx_ >= 0 && idx_ < n_move)
        {
            idx = idx_;
        }
        else
        {
            idx = get_t_idx(t);
        }
        if (idx == -1)
        {
            return Point(0, 0, true);
        }
        return a_move[idx];
    }

    void filter_roots()
    {
        static int poses[3], size;
        static double average_dist;
        static bool gone_in;
        for (i = 0; i < n_objects; i++)
        {
            size = roots[i].size() + 1;
            if (size > 2)
            {
                abs_sort(roots[i], 1, size - 2);
                roots[i].push_back(t_move[n_move - 1]);
                k = -1;
                for (j = 0; j < 3; j++)
                {
                    for (k++; k < size - 1 && roots[i][k + 1] - roots[i][k] < EPSILON; k++)
                        ;
                    poses[j] = k;
                }
                if (poses[1] == size)
                {
                    continue;
                }
                if (poses[0] != 0 && (get_current_pos((roots[i][poses[0]] + roots[i][poses[1]]) / 2.0) - objects[i].c).mag() < ROBOT_R + objects[i].r)
                {
                    grp_rts[group[i]].push_back(roots[i][poses[0]]);
                    gone_in = true;
                }
                else
                {
                    gone_in = false;
                }
                if (poses[2] < size)
                {
                    average_dist = (get_current_pos((roots[i][poses[0]] + roots[i][poses[1]]) / 2.0) - objects[i].c).mag() - ROBOT_R - objects[i].r;
                    if (average_dist * ((get_current_pos((roots[i][poses[1]] + roots[i][poses[2]]) / 2.0) - objects[i].c).mag() - ROBOT_R - objects[i].r) < 0)
                    {
                        if (average_dist < 0)
                        {
                            if (!gone_in)
                            {
                                grp_rts[group[i]].push_back(0);
                            }
                            grp_rts[group[i]].push_back(-roots[i][poses[1]]);
                        }
                        else
                        {
                            grp_rts[group[i]].push_back(roots[i][poses[1]]);
                        }
                    }
                    gone_in = true;
                }
                for (j = poses[2]; j < size - 1;)
                {
                    for (j++; j < size - 1 && roots[i][j + 1] - roots[i][j] < EPSILON; j++)
                        ;
                    poses[0] = poses[1];
                    poses[1] = poses[2];
                    poses[2] = j;
                    average_dist = (get_current_pos((roots[i][poses[0]] + roots[i][poses[1]]) / 2.0) - objects[i].c).mag() - ROBOT_R - objects[i].r;
                    if (average_dist * ((get_current_pos((roots[i][poses[1]] + roots[i][poses[2]]) / 2.0) - objects[i].c).mag() - ROBOT_R - objects[i].r) < 0)
                    {
                        if (average_dist < 0)
                        {
                            grp_rts[group[i]].push_back(-roots[i][poses[1]]);
                        }
                        else
                        {
                            grp_rts[group[i]].push_back(roots[i][poses[1]]);
                        }
                    }
                }
                size = grp_rts[group[i]].size() - 1;
                if (gone_in && grp_rts[group[i]][size] >= 0)
                {
                    grp_rts[group[i]].push_back(-t_move[n_move - 1]);
                }
            }
        }
        for (i = 0; i < n_groups; i++)
        {
            abs_sort(grp_rts[i], 0, grp_rts[i].size() - 1);
        }
    }

    double solve_metrics()
    {
        static int enter_idx, group_score, mv_idx[3], grp_size;
        static Point closest, start_vals[3];
        static double minVal, val, metrics[4];
        metrics[0] = (r_move[n_move] - target_pos).mag() / MAX_SPEED;
        if (metrics[0] < 0.05)
        {
            metrics[0] = 0;
        }
        metrics[1] = (v_move[n_move] - target_vel).mag() / MAX_ACCELERATION;
        if (metrics[1] < 0.05)
        {
            metrics[1] = 0;
        }
        metrics[2] = 0;
        for (i = 0; i < n_groups; i++)
        {
            enter_idx = 0;
            group_score = 1;
            grp_size = grp_rts[i].size();
            for (j = 1; j < grp_size; j++)
            {
                if (-grp_rts[i][j] >= 0)
                {
                    group_score++;
                }
                else
                {
                    group_score--;
                }
                if (group_score == 0)
                {
                    mv_idx[0] = get_t_idx(grp_rts[i][enter_idx]) + 1;
                    mv_idx[1] = get_t_idx(-grp_rts[i][j]);
                    start_vals[0] = get_current_pos(grp_rts[i][enter_idx], mv_idx[0] - 1);
                    start_vals[1] = get_current_vel(grp_rts[i][enter_idx], mv_idx[0] - 1);
                    start_vals[2] = get_current_acc(grp_rts[i][enter_idx], mv_idx[0] - 1);
                    if (mv_idx[1] < mv_idx[0])
                    {
                        closest = closest_point_on_parabola(m_center[i], start_vals[0], start_vals[1], start_vals[2], 0, -grp_rts[i][j] - grp_rts[i][enter_idx]);
                        minVal = (closest - m_center[i]).mag();
                    }
                    else
                    {
                        k = mv_idx[0];
                        closest = closest_point_on_parabola(m_center[i], start_vals[0], start_vals[1], start_vals[2], 0, t_move[mv_idx[0]] - grp_rts[i][enter_idx]);
                        minVal = (closest - m_center[i]).mag();
                        for (; k < mv_idx[1]; k++)
                        {
                            closest = closest_point_on_parabola(m_center[i], r_move[k], v_move[k], a_move[k], 0, t_move[k + 1] - t_move[k]);
                            val = (closest - m_center[i]).mag();
                            if (val < minVal)
                            {
                                minVal = val;
                            }
                        }
                        closest = closest_point_on_parabola(m_center[i], r_move[k], v_move[k], a_move[k], 0, -grp_rts[i][j] - t_move[k]);
                        val = (closest - m_center[i]).mag();
                        if (val < minVal)
                        {
                            minVal = val;
                        }
                    }
                    enter_idx = j + 1;
                    metrics[2] += 1.0 / minVal;
                }
            }
        }
        metrics[3] = t_move[n_move];
        return metrics[0] * DIST_K + metrics[1] * VEL_K + metrics[2] * OBSTACLE_K + metrics[3];
    }
};