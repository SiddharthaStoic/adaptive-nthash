/**
 * @file normal_benchmark.cpp
 * @brief Benchmarks the original ntHash spaced seed implementation.
 */

#include <chrono>
#include <iostream>
#include "nthash/adaptive_hash.hpp"

int main() {
    std::string seq(1'000'000, 'A'); // 1M 'A's

    auto start = std::chrono::high_resolution_clock::now();
    adaptive_hash(seq, 21, 2);
    auto end = std::chrono::high_resolution_clock::now();

    double time = std::chrono::duration<double>(end - start).count();
    std::cout << "Time taken for 1M-length sequence: " << time << "s\n";
    return 0;
}