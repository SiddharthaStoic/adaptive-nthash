#pragma once

#include <string>

void adaptive_hash(const std::string& sequence, int k, int h, double entropy_threshold = 1.5);