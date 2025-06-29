#pragma once
#include <math.h>
#include <stdio.h>
using namespace std;

class Point {
    public: 
        float x, y;
        Point() : x(0), y(0) {}
        Point(float x_, float y_) : x(x_), y(y_) {}
        float mag() const { return sqrtf(x * x + y * y); }
        Point operator+(Point b) {
            return Point(x + b.x, y + b.y);
        }
        Point operator-(Point b) {
            return Point(x - b.x, y - b.y);
        }
        Point operator*(float scalar) {
            return Point(x * scalar, y * scalar);
        }
        Point operator/(float scalar) {
            return Point(x / scalar, y / scalar);
        }
        Point& operator+=(const Point& other) {
            x += other.x;
            y += other.y;
            return *this;
        }
        Point& operator-=(const Point& other) {
            x -= other.x;
            y -= other.y;
            return *this;
        }
        Point& operator*=(const float other) {
            x *= other;
            y *= other;
            return *this;
        }
        bool operator==(Point other) {
            return x == other.x && y == other.y;
        }
        bool operator!=(Point other) {
            return !(*this == other);
        }
        float scalar(Point b) {
            return x * b.x + y * b.y;
        }

        float vector(Point b) {
            return x * b.y - y * b.x;
        }

        float mag() {
            return sqrtf(x * x + y * y);
        }

        Point unity() {
            float len = mag();
            return len > 0.0f ? Point(x / len, y / len) : Point(0.0f, 0.0f);
        }

        float arg() {
            return atan2f(y, x);
        }
        void print(void)
        {
            printf("(%f,%f)\n",x,y);
        }
};
Point rotate(Point p, double angle);
int sign(float a);
double dist(Point a,Point b);
float wind_down_angle(float angle);
float get_angle_between_points(Point a, Point b, Point c);
void circles_inter(Point p0, Point p1, float r0, float r1, Point* out);
int get_tangent_points(Point point0, Point point1, float r, Point* out);
Point closest_point_on_line(Point point1, Point point2, Point point, char type = 'S');
Point nearest_point_on_poly(Point p, Point *poly, int ed_n);
bool is_point_inside_poly(Point p, Point *points, int ed_n);