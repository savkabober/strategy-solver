#pragma once
class Point {
    public: 
        float x, y;
        Point() : x(0), y(0) {}
        Point(float x_, float y_) : x(x_), y(y_) {}
        Point operator+(Point b);
        Point operator-(Point b);
        Point operator*(float scalar);
        Point operator/(float scalar);
        bool operator==(Point other);
        bool operator!=(Point other);
        float scalar(Point b);
        float vector(Point b);
        float mag();
        Point unity();
        float arg();
        void print();
        
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