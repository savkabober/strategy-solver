#include <time.h>
#include <stdio.h>
#include <math.h>
class Complex {
    public: 
        float r, i;
        Complex() : r(0), i(0) {}
        Complex(float r_, float i_) : r(r_), i(i_) {}
        Complex operator+(Complex b) {
            return Complex(r + b.r, i + b.i);
        }
        Complex operator-(Complex b) {
            return Complex(r - b.r, i - b.i);
        }
        bool operator==(Complex other) {
            return r == other.r && i == other.i;
        }
        bool operator!=(Complex other) {
            return !(*this == other);
        }
        void print(void)
        {
            printf("(%f,%f)\n",r,i);
        }
};
void check_same(double *roots,int roots_len,double delta=1e-10)
{
    int unique_roots;
    for(int i;i<roots_len;i++)
    {
        for(int j;j<roots_len-i-1;i++)
        {
            if(fabs(roots[i]-roots[j])
        }
    }
}
/*
def check_same(roots, delta=1e-10):
    new_roots = []
    for i, a in enumerate(roots):
        flag = True
        
        for b in roots[i + 1:]:
            if abs(a - b) < delta:
                flag = False
                break
        if flag:
            new_roots.append(to_zero(a))
    return new_roots

def to_zero(a, delta=1e-10):
    root = 0
    if(abs(a.real) > delta):
        root += a.real
    if(abs(a.imag) > delta):
        root += a.imag * 1j
    return root

def solve_zero(a):
 if a == 0:
  return [True]
 return [False]

def solve_one(a, b):
 if a == 0:
  return solve_zero(b)
 return [-b / a]

def solve_two(a, b, c):
 if a == 0:
  return solve_one(b, c)
 D = b ** 2 - 4 * a * c
 if D == 0:
  return [-b / (2 * a)]
 return [(-b + pow(D, 1 / 2)) / (2 * a), (-b - pow(D, 1 / 2)) / (2 * a)]

def solve_three(a, b, c, d):
 if a == 0:
  return solve_two(b, c, d)
 D0 = b ** 2 - 3 * a * c
 D1 = 2 * b ** 3 - 9 * a * b * c + 27 * a ** 2 * d
 if D0 == 0 and D1 == 0:
  return [-b / (3 * a)]
 m = pow(D1 ** 2 - 4 * D0 ** 3, 1 / 2)
 if m == D1:
  C = pow((D1 + m) / 2, 1 / 3)
 else:
  C = pow((D1 - m) / 2, 1 / 3)
 e = (-1 + pow(-3, 1 / 2)) / 2
 x1 = -(b + C + D0 / C) / (3 * a)
 x2 = -(b + C * e + D0 / (C * e)) / (3 * a)
 x3 = -(b + C * e ** 2 + D0 / (C * e ** 2)) / (3 * a)
 return check_same([x1, x2, x3])

def solve_four(a:float, b:float, c:float, d:float, e:float):
    if a == 0:
        return solve_three(b, c, d, e)#saveliy glupi vibecoder
    b /= a
    c /= a
    d /= a
    e /= a
    p = (8 * c - 3 * b ** 2) / 8
    q = (b ** 3 - 4 * b * c + 8 * d) / 8
    r = (-3 * b ** 4 + 256 * e - 64 * b * d + 16 * b ** 2 * c) / 256
    ms = solve_three(8, 8 * p, 2 * p ** 2 - 8 * r, -q ** 2)
    m = 0
    for i in ms:
        if i != 0:
            m = i
            break
    if m == 0:
        if p == 0:
            return check_same([-b / 4])
        k = pow(-2 * p, 1 / 2)
        return check_same([-b / 4 + k / 2, -b / 4 - k / 2])
    h = pow(2 / m, 1 / 2) * q
    k = pow(2 * m, 1 / 2)
    l1 = pow(-2 * p - 2 * m - h, 1 / 2)
    l2 = pow(-2 * p - 2 * m + h, 1 / 2)
    x1 = -b / 4 + (k + l1) / 2
    x2 = -b / 4 + (k - l1) / 2
    x3 = -b / 4 + (-k + l2) / 2
    x4 = -b / 4 + (-k - l2) / 2
    return check_same([x1, x2, x3, x4])
    */