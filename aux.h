#include <math.h>
using namespace std;

class Point {
    public: 
        float x, y;
        Point() : x(0), y(0) {}
        Point(float x_, float y_) : x(x_), y(y_) {}
        Point operator-(const Point& b) const { return Point(x - b.x, y - b.y); }
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
};

sign(float a) {
    if (a > 0) return 1;
    if (a < 0) return -1;
    return 0;
}

Point closest_point_on_line(Point point1, Point point2, Point point, char type = 'S') {
    float line_len = (point1 - point2).mag();
    if (line_len == 0) {
        return point1;
    }
    Point line_dir = (point1 - point2).unity();
    Point point_vec = point - point1;
    float dot_product = point_vec.scalar(line_dir);
    if (dot_product <= 0 && type != 'L') {
        return point1;
    }
    if (dot_product >= line_len && type == 'S') {
        return point2;
    }
    return line_dir * dot_product + point1;
}

float wind_down_angle(float angle) {
    if (fabs(angle) > 2 * M_PI) {
        angle = fmod(angle, 2 * M_PI);
    }
    if (fabs(angle) > M_PI) {
        angle -= 2 * M_PI * sign(angle);
    }
    return angle;
}

float get_angle_between_points(Point a, Point b, Point c) {
    return wind_down_angle((a - b).arg() - (c - b).arg());
}

void circles_inter(Point p0, Point p1, float r0, float r1, Point* out) {
    float d = (p0 - p1).mag();
    float a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    float h = sqrtf(r0 * r0 - a * a);
    float x2 = p0.x + a * (p1.x - p0.x) / d;
    float y2 = p0.y + a * (p1.y - p0.y) / d;
    out[0].x = x2 + h * (p1.y - p0.y) / d;
    out[0].y = y2 - h * (p1.x - p0.x) / d;
    out[1].x = x2 - h * (p1.y - p0.y) / d;
    out[1].y = y2 + h * (p1.x - p0.x) / d;
}

int get_tangent_points(Point point0, Point point1, float r, Point* out) {
    float d = (point1 - point0).mag();
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

Point closest_point_on_line(Point point1, Point point2, Point point, char type = 'S') {
    float line_len = (point1 - point2).mag();
    if (line_len == 0) {
        return point1;
    }
    Point line_dir = (point1 - point2).unity();
    Point point_vec = point - point1;
    float dot_product = point_vec.scalar(line_dir);
    if (dot_product <= 0 && type != 'L') {
        return point1;
    }
    if (dot_product >= line_len && type == 'S') {
        return point2;
    }
    return line_dir * dot_product + point1;
}

Point nearest_point_on_poly(Point p, Point *poly, int ed_n) {
    float min_ = -1, d;
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
    float old_sign = sign((p - points[ed_n - 1]).vector(points[0] - points[ed_n - 1]));
    for (int i = 0; i < ed_n - 1; i++) {
        if (old_sign != sign((p - points[i]).vector(points[i + 1] - points[i]))) {
            return false;
        }  
    }
    return true;
}