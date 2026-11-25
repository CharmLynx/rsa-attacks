#pragma once

#include <optional>
#include <gmpxx.h>
#include "io.hpp"

struct MitmResult {
    unsigned long t;
    unsigned long s;
};

std::optional<MitmResult> mitm_attack(const MitmData& data,
                                      unsigned long e,
                                      unsigned int l);

std::optional<mpz_class> brute_force(const MitmData& data,
                                     unsigned long e,
                                     unsigned int l);