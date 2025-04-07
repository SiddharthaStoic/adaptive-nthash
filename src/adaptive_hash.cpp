#include "nthash/nthash.hpp"
#include "nthash/entropy.hpp"

#include <iostream>
#include <chrono>

// Global seeds — constructed once
static const std::vector<std::string> DENSE_SEED  = {"111111111111111111111"};
static const std::vector<std::string> SPARSE_SEED = {"100100100100100100100"};

void adaptive_hash(const std::string& seq, int k, int h, double entropy_threshold = 1.5) {
    const size_t len = seq.size();
    if (len < static_cast<size_t>(k)) {
        std::cerr << "Sequence too short.\n";
        return;
    }

    const std::string init_kmer = seq.substr(0, k);
    const char* p = seq.data();

    nthash::RollingEntropy entropy_calc(k);
    entropy_calc.init(init_kmer);

    // Stack-allocated hashers (faster than unique_ptr)
    nthash::SeedNtHash dense_hasher(init_kmer, DENSE_SEED, h, k);
    nthash::SeedNtHash sparse_hasher(init_kmer, SPARSE_SEED, h, k);

    dense_hasher.roll();
    sparse_hasher.roll();

    bool use_dense = false;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = k; i < static_cast<int>(len); ++i) {
        entropy_calc.roll(p[i - k], p[i]);
        double entropy = entropy_calc.compute();

        use_dense = (entropy > entropy_threshold);

        if (use_dense) {
            dense_hasher.roll();
            // const uint64_t* hashes = dense_hasher.hashes(); // optional
        } else {
            sparse_hasher.roll();
            // const uint64_t* hashes = sparse_hasher.hashes(); // optional
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    double elapsed_sec = std::chrono::duration<double>(end - start).count();
    std::cout << "Adaptive hashing completed in " << elapsed_sec << " seconds.\n";
}