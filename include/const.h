#pragma once

//robot movement
#define MAX_SPEED 1500
#define MAX_ACCELERATION 1500
//hz
#define MAX_ROBOT_COUNT 16
#define MAX_SOLVER_DEGREE 10
#define TIME_TO_BORN 0.5
#define TIME_TO_DIE 1.5
//geometry
#define ROBOT_R 100.0
#define BALL_R 40.0
#define GRAVEYARD_POS_X 10000
#define FIELD_DX 4500
#define FIELD_DY 3000
#define PEN_DX 1000
#define PEN_DY 2000
#define POLARITY 1
#define FIELD_COLOR Color(52, 92, 10)
#define FIELD_MARGIN 200
//colors
#define ALL_TEAMS 0
#define YELLOW 1
#define BLUE 2
//metrics
#define DIST_K 1000
#define VEL_K 100
#define OBSTACLE_K 10