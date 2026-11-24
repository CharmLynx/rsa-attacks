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
    if (residues.size() != moduli.size()) {
        throw runtime_error("crt: residues and moduli sizes differ");
    }
    if (moduli.empty()) {
        throw runtime_error("crt: empty input");
    }

    mpz_class N = 1;
    for (const mpz_class& m : moduli) {
        N *= m;
    }

    mpz_class result = 0;
    for (size_t i = 0; i < moduli.size(); i++) {
        mpz_class Ni = N / moduli[i];

        mpz_class yi;
        if (mpz_invert(yi.get_mpz_t(), Ni.get_mpz_t(), moduli[i].get_mpz_t()) == 0) {
            throw runtime_error("crt: moduli are not pairwise coprime");
        }

        result += residues[i] * Ni * yi;
    }

    return result % N;
}