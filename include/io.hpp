#pragma once

#include <map>
#include <string>
#include <vector>
#include <gmpxx.h>

struct BroadcastData {
    std::vector<mpz_class> c;
    std::vector<mpz_class> n;
};

struct MitmData {
    mpz_class c;
    mpz_class n;
};

std::map<std::string, mpz_class> read_values(const std::string& path);
BroadcastData read_broadcast(const std::string& path);
MitmData read_mitm(const std::string& path);