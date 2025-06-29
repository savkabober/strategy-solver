#pragma once
#include <stdio.h>
#include <cmath>

class Point {
    public: 
        double x, y, isNone;
        Point() : x(0), y(0), isNone(false) {}
        Point(double x_, double y_, bool isNone_ = false) : x(x_), y(y_), isNone(isNone_) {}
        Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
        double mag() const { return sqrtf(x * x + y * y); }
        Point operator+(Point b) {
            return Point(x + b.x, y + b.y);
        }
        Point operator-(Point b) {
            return Point(x - b.x, y - b.y);
        }
        Point operator*(double scalar) {
            return Point(x * scalar, y * scalar);
        }
        Point operator/(double scalar) {
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
        double scalar(Point b) {
            return x * b.x + y * b.y;
        }

        double vector(Point b) {
            return x * b.y - y * b.x;
        }

        double mag() {
            return sqrtf(x * x + y * y);
        }

        Point unity() {
            double len = mag();
            return len > 0.0f ? Point(x / len, y / len) : Point(0.0f, 0.0f);
        }

        double arg() {
            return atan2f(y, x);
        }
};

int sign(double a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

Point closest_point_on_line(Point point1, Point point2, Point point, char type = 'S') {
    double line_len = (point1 - point2).mag();
    if (line_len == 0) {
        return point1;
    }
    Point line_dir = (point1 - point2).unity();
    Point point_vec = point - point1;
    double dot_product = point_vec.scalar(line_dir);
    if (dot_product <= 0 && type != 'L') {
        return point1;
    }
    if (dot_product >= line_len && type == 'S') {
        return point2;
    }
    return line_dir * dot_product + point1;
}
Point get_line_inretsesction(
    Point line1_start,
    Point line1_end,
    Point line2_start,
    Point line2_end,
    char* types = "SS"
    )
    {
        float delta_x1 = line1_end.x - line1_start.x;
        float delta_y1 = line1_end.y - line1_start.y;
        float delta_x2 = line2_end.x - line2_start.x;
        float delta_y2 = line2_end.y - line2_start.y;
        float determinant = delta_y1 * delta_x2 - delta_y2 * delta_x1;
        if(determinant == 0)
            return Point(0, 0, true);
        float delta_x_start = line1_start.x - line2_start.x;
        float delta_y_start = line1_start.y - line2_start.y;
        float t1 = (delta_x_start * delta_y2 - delta_x2 * delta_y_start) / determinant;
        float t2 = (delta_x_start * delta_y1 - delta_x1 * delta_y_start) / determinant;
        float intersection_x = line1_start.x + t1 * delta_x1;
        float intersection_y = line1_start.y + t1 * delta_y1;
        Point p = Point(intersection_x, intersection_y);
        bool first_valid = false;
        bool second_valid = false;
        if ((types[0] == 'S' && 0 <= t1 && t1 <= 1) || (types[0] == 'R' && t1 >= 0) || types[0] == 'L')
            first_valid = true;
        if ((types[1] == 'S' && 0 <= t2 && t2 <= 1) || (types[1] == 'R' && t2 >= 0) || types[1] == 'L')
            second_valid = true;

        if (first_valid && second_valid)
            return p;
        return Point(0, 0, true);
    }

double wind_down_angle(double angle) {
    if (fabs(angle) > 2 * M_PI) {
        angle = fmod(angle, 2 * M_PI);
    }
    if (fabs(angle) > M_PI) {
        angle -= 2 * M_PI * sign(angle);
    }
    return angle;
}

double get_angle_between_points(Point a, Point b, Point c) {
    return wind_down_angle((a - b).arg() - (c - b).arg());
}

void circles_inter(Point p0, Point p1, double r0, double r1, Point* out) {
    double d = (p0 - p1).mag();
    double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    double h = sqrtf(r0 * r0 - a * a);
    double x2 = p0.x + a * (p1.x - p0.x) / d;
    double y2 = p0.y + a * (p1.y - p0.y) / d;
    out[0].x = x2 + h * (p1.y - p0.y) / d;
    out[0].y = y2 - h * (p1.x - p0.x) / d;
    out[1].x = x2 - h * (p1.y - p0.y) / d;
    out[1].y = y2 + h * (p1.x - p0.x) / d;
}

int get_tangent_points(Point point0, Point point1, double r, Point* out) {
    double d = (point1 - point0).mag();
    if (d < r) {
        return 0;
    }   

    if (d == r) {
        out[0] = point1;
        return 1;
    }
    circles_inter(point0, Point((point0.x + point1.x) / 2, (point0.y + point1.y) / 2), r, d / 2, out);
    return 2;
}

Point nearest_point_on_poly(Point p, Point *poly, int ed_n) {
    double min_ = -1, d;
    Point ans(0, 0), pnt(0, 0);
    for (int i = 0; i < ed_n; i++) {
        pnt = closest_point_on_line(poly[i], poly[i > 0 ? i - 1 : ed_n - 1], p);
        d = (pnt - p).mag();
        if (d < min_ || min_ < 0) {
            min_ = d;
            ans = pnt;
        }
    }
    return ans;
}

bool is_point_inside_poly(Point p, Point *points, int ed_n) {
    double old_sign = sign((p - points[ed_n - 1]).vector(points[0] - points[ed_n - 1]));
    for (int i = 0; i < ed_n - 1; i++) {
        if (old_sign != sign((p - points[i]).vector(points[i + 1] - points[i]))) {
            return false;
        }  
    }
    return true;
}
