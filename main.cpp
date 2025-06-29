#include "aux.h"
#include <iostream>
#include <complex>

int main() {
    complex<double> out[2];
    int i, n;
    n = solve_two(1, 1, 1, out);
    cout << n << endl;
    for(i = 0; i < n; i++) {
        cout << out[i] << endl;
    }
    return 0;
}