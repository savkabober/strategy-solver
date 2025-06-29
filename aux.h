#pragma once
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;

class Point {
    public: 
        double x, y;
        Point() : x(0), y(0) {}
        Point(double x_, double y_) : x(x_), y(y_) {}
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

int solve_one(double a, double b, complex<double> *out) {
    if (a == 0) {
        return 0;
    }
    out[0] = -b / a;
    return 1;
}

int solve_two(double a, double b, double c, complex<double> *out) {
    if (a == 0) {
        return solve_one(b, c, out);;
    }
    static complex<double> D;
    D = complex<double>(b * b - 4 * a * c, 0.0);
    if (real(D) == 0) {
        out[0] = -b / (2 * a);
        return 1;
    }
    out[0] = (-b + sqrt(D)) / (2 * a);
    out[1] = (-b - sqrt(D)) / (2 * a);
    return 2;
}

int solve_three(double a, double b, double c, double d, complex<double> *out) {
    if (a == 0) {
        return solve_two(b, c, d, out);
    }
    static double D0, D1, alpha;
    D0 = b * b - 3 * a * c;
    D1 = 2 * b * b * b - 9 * a * b * c + 27 * a * a * d;
    if (D0 == 0 && D1 == 0) {
        out[0] = -b / (3 * a);
        return 1;
    }
    static complex <double> m, high, low, e = complex<double>(-1 / 2, sqrt(3) / 2);
    m = sqrt((D1 * D1 - 4 * D0 * D0 * D0) / 2);
    if (abs(m) == 0) {
        high = pow(D1, 1 / 3);
        low = D0 / high;
        out[0] = -(b + high * e + low / e) / (3 * a);
        alpha = fmod(arg(low) - arg(high), 2 * M_PI);
        if (abs(alpha) < M_PI / 4) {
            out[1] = -(b + high + low) / (3 * a);
        }
        else {
            out[1] = -(b + high * e * e + low / (e * e)) / (3 * a);
        }
        return 2;
    }
    if (m == D1) {
        high = pow((D1 + m) / 2.0, 1 / 3);
    }
    else {
        high = pow((D1 - m) / 2.0, 1 / 3);
    }
    low = D0 / high;
    out[0] = -(b + high + low) / (3 * a);
    out[1] = -(b + high * e + low / e) / (3 * a);
    out[2] = -(b + high * e * e + low / (e * e)) / (3 * a);
    return 3;
}

int solve_four(double a, double b, double c, double d, double e, complex<double> *out) {
    if (a == 0) {
        return solve_three(b, c, d, e, out);
    }
    b /= a;
    c /= a;
    d /= a;
    e /= a;
    static double p, q, r;
    p = (8 * c - 3 * b * b) / 8;
    q = (b * b * b - 4 * b * c + 8 * d) / 8;
    r = (-3 * b * b * b * b + 256 * e - 64 * b * d + 16 * b * b * c) / 256;
    static int i, n;
    n = solve_three(8, 8 * p, 2 * p * p - 8 * r, -q * q, out);
    static complex<double> m, k, h, l1, l2;
    m = complex<double> (0, 0);
    for(i = 0; i < n; i++) {
        if(abs(out[n]) != 0) {
            m = out[n];
            break;
        }
    }
    if (abs(m) == 0) {
        if (p == 0) {
            out[0] = -b / 4.0;
            return 1;
        }
        k = sqrt(-p / 2);
        out[0] = -b / 4 + k;
        out[1] = -b / 4 - k;
        return 2;
    }
    h = sqrt(2.0 / m) * q;
    k = sqrt(2.0 * m);
    l1 = sqrt(-2.0 * p - 2.0 * m - h);
    l2 = sqrt(-2.0 * p - 2.0 * m + h);
    out[0] = -b / 4.0 + (k + l1) / 2.0;
    out[1] = -b / 4.0 + (k - l1) / 2.0;
    n = 2;
    if (2.0 * k != l1 + l2 && 2.0 * k != l2 - l1) {
        out[2] = -b / 4.0 + (-k + l2) / 2.0;
        n++;
    }
    if (2.0 * k != -l1 - l2 && 2.0 * k != l1 - l2) {
        out[n] = -b / 4.0 + (-k - l2) / 2.0;
        n++;
    }
    return n;
}