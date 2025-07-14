#pragma once

#include <chrono>

long double time() {
    static chrono::time_point<chrono::high_resolution_clock> start_clock_time = chrono::high_resolution_clock::now();
    static chrono::time_point<chrono::high_resolution_clock> now_time;
    now_time = chrono::high_resolution_clock::now();
    chrono::duration<long double> delta = now_time - start_clock_time;
    return delta.count();
}