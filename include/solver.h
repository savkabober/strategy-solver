#pragma once
#include <cmath>
#include <complex>
#include <iostream>
using namespace std;

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