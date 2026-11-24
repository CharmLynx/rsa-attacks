#include "crt.hpp"

#include <stdexcept>

using namespace std;

bool pairwise_coprime(const vector<mpz_class>& moduli) {
    for (size_t i = 0; i < moduli.size(); i++) {
        for (size_t j = i + 1; j < moduli.size(); j++) {
            if (gcd(moduli[i], moduli[j]) != 1) {
                return false;
            }
        }
    }
    return true;
}

mpz_class crt(const vector<mpz_class>& residues,
              const vector<mpz_class>& moduli) {
    mpz_class result = 0;

    return result;
}