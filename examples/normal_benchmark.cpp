#include <iostream>
#include <chrono>
#include <string>
#include "nthash/nthash.hpp"  // ✅ Required public interface

using namespace std;
using namespace nthash;

int main() {
    string seq(1000000, 'A'); // 1M A's
    int k = 21;

    auto start = chrono::high_resolution_clock::now();

    NtHash nth(seq, 1, k); // 1 hash per k-mer
    while (nth.roll()) {
        const uint64_t* h = nth.hashes();
        (void)h; // ignore value
    }

    auto end = chrono::high_resolution_clock::now();
    double time = chrono::duration<double>(end - start).count();

    cout << "Time taken by standard ntHash: " << time << "s\n";
    return 0;
}