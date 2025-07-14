#pragma once

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <complex>
#include "const.h"

using namespace std;

#define SQUARE(x) ((x) * (x))

class Complex;

double abs2(const Complex &c);

double abs(const Complex &c);

struct Complex
{
private:
    double conj, r_, i_;

public:
    double r, i;
    Complex() : r(0), i(0) {}
    Complex(double r_) : r(r_), i(0) {}
    Complex(double r_, double i_) : r(r_), i(i_) {}
    inline Complex operator-() const
    {
        return Complex(-r, -i);
    }
    inline Complex operator+(const Complex &other) const
    {
        return Complex(r + other.r, i + other.i);
    }
    inline Complex operator+(double other) const
    {
        return Complex(r + other, i);
    }
    inline Complex operator-(const Complex &other) const
    {
        return Complex(r - other.r, i - other.i);
    }
    inline Complex operator-(double other) const
    {
        return Complex(r - other, i);
    }
    inline Complex operator*(const Complex &other) const
    {
        return Complex(r * other.r - i * other.i, r * other.i + i * other.r);
    }
    inline Complex operator*(double other) const
    {
        return Complex(r * other, i * other);
    }
    inline Complex operator/(const Complex &other)
    {
        conj = SQUARE(other.r) + SQUARE(other.i);
        return Complex((r * other.r + i * other.i) / conj, (-r * other.i + i * other.r) / conj);
    }
    inline Complex operator/(double other) const
    {
        return Complex(r / other, i / other);
    }
    inline Complex &operator+=(const Complex other)
    {
        r += other.r;
        i += other.i;
        return *this;
    }
    inline Complex &operator+=(double other)
    {
        r += other;
        return *this;
    }
    inline Complex &operator-=(const Complex other)
    {
        r -= other.r;
        i -= other.i;
        return *this;
    }
    inline Complex &operator-=(double other)
    {
        r -= other;
        return *this;
    }
    inline Complex &operator*=(const Complex &other)
    {
        r_ = r * other.r - i * other.i;
        i_ = r * other.i + i * other.r;
        r = r_;
        i = i_;
        return *this;
    }
    inline Complex &operator*=(double other)
    {
        r *= other;
        i *= other;
        return *this;
    }
    inline Complex &operator/=(const Complex &other)
    {
        conj = SQUARE(other.r) + SQUARE(other.i);
        r_ = (r * other.r + i * other.i) / conj;
        i_ = (-r * other.i + i * other.r) / conj;
        r = r_;
        i = i_;
        return *this;
    }
    inline Complex &operator/=(double other)
    {
        r /= other;
        i /= other;
        return *this;
    }
    inline bool operator==(const Complex &other) const
    {
        return abs(*this - other) < EPSILON;
    }
    inline bool operator==(double other) const
    {
        return abs(*this - other) < EPSILON;
    }
    inline bool operator!=(const Complex &other) const
    {
        return !(*this == other);
    }
    inline bool operator!=(double other) const
    {
        return !(*this == other);
    }
    inline Complex &operator=(double other)
    {
        r = other;
        i = 0;
        return *this;
    }
};

inline double abs2(const Complex &c)
{
    return SQUARE(c.r) + SQUARE(c.i);
}
inline double abs(const Complex &c)
{
    return sqrt(abs2(c));
}
inline double arg(const Complex &c)
{
    return atan2(c.i, c.r);
}
inline Complex pow(const Complex &c, double exp)
{
    static double ang, mag;
    ang = arg(c);
    mag = abs(c);
    mag = pow(mag, exp);
    ang *= exp;
    return Complex(cos(ang) * mag, sin(ang) * mag);
}
inline Complex sqrt(const Complex &c)
{
    return pow(c, 0.5);
}
inline double real(const Complex &c)
{
    return c.r;
}
inline double imag(const Complex &c)
{
    return c.i;
}
ostream &operator<<(ostream &os, const Complex &c)
{
    os << "r = " << c.r << ", i = " << c.i;
    return os;
}

class Point;

double abs2(const Point &p);

double abs(const Point &p);

struct Point
{
    double x, y;
    bool is_none;
    Point() : x(0), y(0), is_none(false) {}
    Point(double x_, double y_, bool is_none_ = false) : x(x_), y(y_), is_none(is_none_) {}
    Point operator-() const
    {
        return Point(-x, -y);
    }
    Point operator+(const Point &other) const
    {
        return Point(x + other.x, y + other.y);
    }
    Point operator-(const Point &other) const
    {
        return Point(x - other.x, y - other.y);
    }
    Point operator*(double scalar_mult) const
    {
        return Point(x * scalar_mult, y * scalar_mult);
    }
    Point operator/(double scalar_mult) const
    {
        return Point(x / scalar_mult, y / scalar_mult);
    }
    Point &operator+=(const Point &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }
    Point &operator-=(const Point &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Point &operator*=(double other)
    {
        x *= other;
        y *= other;
        return *this;
    }
    Point &operator/=(double other)
    {
        x /= other;
        y /= other;
        return *this;
    }
    bool operator==(const Point &other) const
    {
        return abs(*this - other) < EPSILON;
    }
    bool operator!=(Point other) const
    {
        return !(*this == other);
    }
    Point unity() const
    {
        double len = abs(*this);
        return len > 0.0f ? Point(x / len, y / len) : Point(0.0, 0.0);
    }
};

double abs2(const Point &p)
{
    return SQUARE(p.x) + SQUARE(p.y);
}
double abs(const Point &p)
{
    return sqrt(abs2(p));
}
double arg(const Point &p)
{
    return atan2(p.y, p.x);
}
double scalar_mult(const Point &p1, const Point &p2)
{
    return p1.x * p2.x + p1.y * p2.y;
}
double vector_mult(const Point &p1, const Point &p2)
{
    return p1.x * p2.y - p1.y * p2.x;
}
Point rotate(const Point &p, double ang)
{
    double c = cos(ang), s = sin(ang);
    return Point(p.x * c - p.y * s, p.y * c + p.x * s);
}
ostream &operator<<(ostream &os, const Point &point)
{
    os << "x = " << point.x << ", y = " << point.y;
    return os;
}

const Point GRAVEYARD_POS = Point(GRAVEYARD_POS_X, 0);

class Object
{
public:
    Point c;
    double r;
    Object() : c(Point(0, 0)), r(0) {}
    Object(Point c_, double r_) : c(c_), r(r_) {}
    bool operator==(Object other)
    {
        return c == other.c && r == other.r;
    }
    bool operator!=(Object other)
    {
        return !(*this == other);
    }
};

int sign(double a)
{
    if (a > 0)
        return 1;
    if (a < 0)
        return -1;
    return 0;
}

Point closest_point_on_line(Point point1, Point point2, Point point, char type = 'S')
{
    double line_len = abs(point1 - point2);
    if (line_len == 0)
    {
        return point1;
    }
    Point line_dir = (point1 - point2).unity();
    Point point_vec = point - point1;
    double dot_product = scalar_mult(point_vec, line_dir);
    if (dot_product <= 0 && type != 'L')
    {
        return point1;
    }
    if (dot_product >= line_len && type == 'S')
    {
        return point2;
    }
    return line_dir * dot_product + point1;
}

Point get_line_inretsesction(
    Point line1_start,
    Point line1_end,
    Point line2_start,
    Point line2_end,
    string types = "SS")
{
    double delta_x1 = line1_end.x - line1_start.x;
    double delta_y1 = line1_end.y - line1_start.y;
    double delta_x2 = line2_end.x - line2_start.x;
    double delta_y2 = line2_end.y - line2_start.y;
    double determinant = delta_y1 * delta_x2 - delta_y2 * delta_x1;
    if (determinant == 0)
        return Point(0, 0, true);
    double delta_x_start = line1_start.x - line2_start.x;
    double delta_y_start = line1_start.y - line2_start.y;
    double t1 = (delta_x_start * delta_y2 - delta_x2 * delta_y_start) / determinant;
    double t2 = (delta_x_start * delta_y1 - delta_x1 * delta_y_start) / determinant;
    double intersection_x = line1_start.x + t1 * delta_x1;
    double intersection_y = line1_start.y + t1 * delta_y1;
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

double wind_down_angle(double angle)
{
    if (abs(angle) > 2 * M_PI)
    {
        angle = fmod(angle, 2 * M_PI);
    }
    if (abs(angle) > M_PI)
    {
        angle -= 2 * M_PI * sign(angle);
    }
    return angle;
}

double get_angle_between_points(Point a, Point b, Point c)
{
    return wind_down_angle(arg(a - b) - arg(c - b));
}

void circles_inter(Point p0, Point p1, double r0, double r1, Point *out)
{
    double d = abs(p0 - p1);
    double a = (r0 * r0 - r1 * r1 + d * d) / (2 * d);
    double h = sqrtf(r0 * r0 - a * a);
    double x2 = p0.x + a * (p1.x - p0.x) / d;
    double y2 = p0.y + a * (p1.y - p0.y) / d;
    out[0].x = x2 + h * (p1.y - p0.y) / d;
    out[0].y = y2 - h * (p1.x - p0.x) / d;
    out[1].x = x2 - h * (p1.y - p0.y) / d;
    out[1].y = y2 + h * (p1.x - p0.x) / d;
}

int get_tangent_points(Point point0, Point point1, double r, Point *out)
{
    double d = abs(point1 - point0);
    if (d < r)
    {
        return 0;
    }

    if (d == r)
    {
        out[0] = point1;
        return 1;
    }
    circles_inter(point0, Point((point0.x + point1.x) / 2, (point0.y + point1.y) / 2), r, d / 2, out);
    return 2;
}

Point nearest_point_on_poly(Point p, Point *poly, int ed_n)
{
    double min_ = -1, d;
    Point ans(0, 0), pnt(0, 0);
    for (int i = 0; i < ed_n; i++)
    {
        pnt = closest_point_on_line(poly[i], poly[i > 0 ? i - 1 : ed_n - 1], p);
        d = abs(pnt - p);
        if (d < min_ || min_ < 0)
        {
            min_ = d;
            ans = pnt;
        }
    }
    return ans;
}

bool is_point_inside_poly(Point p, Point *points, int ed_n)
{
    double old_sign = sign(vector_mult(p - points[ed_n - 1], points[0] - points[ed_n - 1]));
    for (int i = 0; i < ed_n - 1; i++)
    {
        if (old_sign != sign(vector_mult(p - points[i], points[i + 1] - points[i])))
        {
            return false;
        }
    }
    return true;
}

inline int solve_one(double a, double b, complex<double> *out)
{
    if (a == 0)
    {
        return 0;
    }
    out[0] = -b / a;
    return 1;
}

inline int solve_one(double a, double b, double *out) {
    if (a == 0)
        return 0;
    out[0] = -b / a;
    return 1;
}

inline int solve_two(double a, double b, double c, complex<double> *out)
{
    if (a == 0)
    {
        return solve_one(b, c, out);
    }
    complex<double> D(b * b - 4 * a * c, 0);
    if (abs(D) < EPSILON) {
        out[0] = -b / (2 * a);
        return 1;
    }
    out[0] = (-b + sqrt(D)) / (2 * a);
    out[1] = (-b - sqrt(D)) / (2 * a);
    return 2;
}

inline int solve_two(double a, double b, double c, double *out) {
    if (a == 0)
        return solve_one(b, c, out);
    double D = b * b - 4 * a * c;
    if (D < -EPSILON) {
        return 0;
    }
    if (D < EPSILON) {
        out[0] = -b / (2 * a);
        return 1;
    }
    out[0] = (-b - sqrt(D)) / (2 * a);
    out[1] = (-b + sqrt(D)) / (2 * a);
    return 2;
}

inline int solve_three(double a, double b, double c, double d, complex<double> *out)
{
    if (a == 0)
    {
        return solve_two(b, c, d, out);
    }
    double D0 = b * b - 3 * a * c, D1 = 2 * b * b * b - 9 * a * b * c + 27 * a * a * d, alpha;
    if (D0 == 0 && D1 == 0)
    {
        out[0] = -b / (3 * a);
        return 1;
    }
    complex<double> m = sqrt(complex<double>(D1 * D1 - 4.0 * D0 * D0 * D0, 0)), high, low, e = complex<double>(-1 / 2.0, sqrt(3.0) / 2.0);
    if (abs(m) < EPSILON)
    {
        high = pow(D1, 1 / 3);
        low = D0 / high;
        out[0] = -(b + high * e + low / e) / (3.0 * a);
        alpha = fmod(arg(low) - arg(high), 2.0 * M_PI);
        if (abs(alpha) > M_PI)
        {
            alpha -= 2.0 * M_PI * sign(alpha);
        }
        if (abs(alpha) < M_PI / 4)
        {
            out[1] = -(b + high + low) / (3.0 * a);
        }
        else
        {
            out[1] = -(b + high * e * e + low / (e * e)) / (3.0 * a);
        }
        return 2;
    }
    if (abs(m - D1) < EPSILON)
    {
        high = pow((D1 + m) / 2.0, 1.0 / 3.0);
    }
    else
    {
        high = pow((D1 - m) / 2.0, 1.0 / 3.0);
    }
    low = D0 / high;
    out[0] = -(b + high + low) / (3.0 * a);
    out[1] = -(b + high * e + low / e) / (3.0 * a);
    out[2] = -(b + high * e * e + low / (e * e)) / (3.0 * a);
    return 3;
}

inline int solve_four(double a, double b, double c, double d, double e, complex<double> *out)
{
    if (a == 0)
    {
        return solve_three(b, c, d, e, out);
    }
    b /= a;
    c /= a;
    d /= a;
    e /= a;
    double p = (8.0 * c - 3.0 * b * b) / 8.0, q = (b * b * b - 4.0 * b * c + 8.0 * d) / 8.0, r = (-3.0 * b * b * b * b + 256.0 * e - 64.0 * b * d + 16.0 * b * b * c) / 256.0;
    int i, n = solve_three(8.0, 8.0 * p, 2.0 * p * p - 8.0 * r, -q * q, out);;
    complex<double> m(0, 0), k, h, l1, l2;
    for (i = 0; i < n; i++)
    {
        if (abs(out[i]) > EPSILON)
        {
            m = out[i];
            break;
        }
    }
    if (abs(m) < EPSILON)
    {
        if (p < EPSILON)
        {
            out[0] = -b / 4.0;
            return 1;
        }
        k = sqrt(-p / 2.0);
        out[0] = -b / 4.0 + k;
        out[1] = -b / 4.0 - k;
        return 2;
    }
    k = sqrt(2.0 * m);
    h = 2.0 * q / k;
    l1 = sqrt(-2.0 * p - 2.0 * m - h);
    l2 = sqrt(-2.0 * p - 2.0 * m + h);
    out[0] = -b / 4.0 + (k + l1) / 2.0;
    out[1] = -b / 4.0 + (k - l1) / 2.0;
    n = 2;
    if (abs(2.0 * k - l1 - l2) > EPSILON && abs(2.0 * k + l1 - l2) > EPSILON)
    {
        out[2] = -b / 4.0 + (-k + l2) / 2.0;
        n++;
    }
    if (abs(2.0 * k + l1 + l2) > EPSILON && abs(2.0 * k + l2 - l1) > EPSILON)
    {
        out[n] = -b / 4.0 + (-k - l2) / 2.0;
        n++;
    }
    return n;
}

Point closest_point_on_parabola(Point x, Point r0, Point v0, Point a, double t_min = -1e10, double t_max = 1e10)
{
    static double ak, bk, ck, dk, real_roots[3], best, answ, value;
    static int n_rls, n_rts, i;
    if (abs2(a) == 0 && abs2(v0) == 0)
    {
        return r0;
    }
    ak = abs2(a) / 2.0;
    bk = 3.0 / 2.0 * scalar_mult(a, v0);
    ck = abs2(v0) + scalar_mult(a, r0 - x);
    dk = scalar_mult(v0, r0 - x);
    complex<double> roots[3];
    n_rts = solve_three(ak, bk, ck, dk, roots);
    n_rls = 0;
    for (i = 0; i < n_rts; i++)
    {
        if (abs(imag(roots[i])) < EPSILON)
        {
            real_roots[n_rls] = real(roots[i]);
            n_rls++;
        }
    }
    best = -1.0;
    for (i = 0; i < n_rls; i++)
    {
        if (real_roots[i] >= t_min && real_roots[i] <= t_max)
        {
            value = abs2(r0 + v0 * real_roots[i] + a * real_roots[i] * real_roots[i] / 2.0 - x);
            if (best < 0 || value < best)
            {
                best = value;
                answ = real_roots[i];
            }
        }
    }
    value = abs2(r0 + v0 * t_min + a * t_min * t_min / 2.0 - x);
    if (best < 0 || value < best)
    {
        best = value;
        answ = t_min;
    }
    value = abs2(r0 + v0 * t_max + a * t_max * t_max / 2.0 - x);
    if (best < 0 || value < best)
    {
        best = value;
        answ = t_max;
    }
    return r0 + v0 * answ + a * answ * answ / 2.0;
}

int gauss_sovle(double *a, double *b, int n, double *x)
{
    static double maxV, val, k;
    static int maxJ, i1, i2, i, j, p;
    // a[0] = -1;
    // a[1] = 1;
    // a[2] = -2;
    // a[3] = 2;
    // b[0] = 1;
    // b[1] = 1;
    maxV = 0;
    maxJ = 0;
    for (i = 0; i < n; i++)
    {
        maxJ = 0;
        maxV = 0;
        for (j = 0; j < n - i; j++)
        {
            val = abs(a[(i + j) * n + i]);
            if (val > maxV)
            {
                maxV = val;
                maxJ = j;
            }
        }
        // cout << "jjjjjjj " << maxJ << endl;
        if (maxV == 0)
        {
            return 0;
        }
        if (maxJ != 0)
        {
            i1 = (maxJ + i) * n + i;
            i2 = i * n + i;
            for (j = 0; j < n - i; j++)
            {
                a[i1 + j] += a[i2 + j];
                a[i2 + j] = a[i1 + j] - a[i2 + j];
                a[i1 + j] -= a[i2 + j];
            }
            b[maxJ + i] += b[i];
            b[i] = b[maxJ + i] - b[i];
            b[maxJ + i] -= b[i];
        }
        // cout << "semen lobanov " << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << ", " << b[0] << ", " << b[1] << endl;
        for (j = 1; j < n - i; j++)
        {
            k = a[(i + j) * n + i] / a[i * n + i];
            for (p = 1; p < n - i; p++)
            {
                a[(i + j) * n + i + p] -= a[i * n + i + p] * k;
            }
            b[i + j] -= b[i] * k;
        }
    }
    // cout << "pupupu " << a[0] << ", " << a[1] << ", " << a[2] << ", " << a[3] << ", " << b[0] << ", " << b[1] << endl;
    for (i = n - 1; i >= 0; i--)
    {
        for (j = n - 1; j > i; j--)
        {
            b[i] -= a[i * n + j] * x[j];
        }
        if (a[i * n + i] == 0)
        {
            // cout << "нашел пидора" << endl;
            x[i] = 0;
        }
        else
        {
            x[i] = b[i] / a[i * n + i];
        }
    }
    // cout << "gauss " << a[0] << ", " << b[0] << ", " << x[0] << endl;
    return 1;
}