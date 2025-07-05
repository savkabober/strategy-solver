#include <iostream>
#include <complex>
#include "include/field.h"
#include "include/metrics.h"
#include "include/quicksort.h"
#include "include/aux.h"
#include <vector>

using namespace std;

int main() {
    // complex<double> out[4];
    // int i, n;
    // n = solve_four(1, -10, 35, -50, 24, out);
    // cout << n << endl;
    // for (i = 0; i < n; i++) {
    //     cout << out[i] << endl;
    // }
    // cout << "end" << endl
    double a[6] = {1.2, 0, 5.3, 3, 5.1, 2};
    quick_sort(a, 0, 5);
    cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << " " << a[4] << " " << a[5] << endl;
}