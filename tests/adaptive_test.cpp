#include <iostream>
#include "nthash/adaptive_hash.hpp"

int main() {
    std::cout << "\nTest 1: Mixed high entropy\n";
    adaptive_hash("ACGTACGTGCGTATATAGCGCGCGCGCGCGCGCG", 21, 2);

    std::cout << "\nTest 2: Repetitive low entropy\n";
    adaptive_hash("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 21, 2);

    std::cout << "\nTest 3: Ambiguous bases\n";
    adaptive_hash("ACGNTGNNTGCAANGTNNNNACGTAGCTN", 21, 2);

    return 0;
}