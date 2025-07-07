#pragma once

//robot movement
#define MAX_SPEED 1500
#define MAX_ACCELERATION 1500
//idk
#define MAX_ROBOT_COUNT 16
#define MAX_SOLVER_DEGREE 10
#define TIME_TO_BORN 0.0
#define TIME_TO_DIE 1.5
//geometry
#define ROBOT_R 100.0
#define BALL_R 40.0
#define GRAVEYARD_POS_X 10000
#define FIELD_DX 9000
#define FIELD_DY 6000
#define ZONE_DX 1000
#define ZONE_DY 2000
#define GOAL_DY 1000
#define POLARITY 1
#define FIELD_COLOR Color(52, 92, 10)
#define FIELD_MARGIN 200
//field info
#define ALL_TEAMS 0
#define YELLOW 1
#define BLUE 2
#define POLARITY 1 //sign of x coordinate of our goal
//metrics
#define DIST_K 1e6
#define VEL_K 1e4
#define OBSTACLE_K 1e2
//some math constants
#define EPSILON 1e-10
#define INF 1e10