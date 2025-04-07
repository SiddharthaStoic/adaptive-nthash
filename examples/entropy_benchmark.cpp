#include <iostream>
#include <chrono>
#include <string>
#include "nthash/entropy.hpp"

int main() {
    std::string seq(1000000, 'A');
    for (int i = 100000; i < 200000; ++i)
        seq[i] = "CGT"[i % 3];  // insert some entropy

    nthash::RollingEntropy re(21);

    re.init(seq.substr(0, 21));

    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 21; i < seq.size(); ++i) {
        re.roll(seq[i - 21], seq[i]);
        double e = re.compute();
        (void)e;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Entropy rolling benchmark took "
              << std::chrono::duration<double>(end - start).count()
              << "s\n";
}