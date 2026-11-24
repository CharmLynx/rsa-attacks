#pragma once

#include <vector>
#include <gmpxx.h>

bool pairwise_coprime(const std::vector<mpz_class>& moduli);

mpz_class crt(const std::vector<mpz_class>& residues,
              const std::vector<mpz_class>& moduli);