#include "nth_root.hpp"

#include <stdexcept>

using namespace std;

mpz_class nth_root(const mpz_class& a, unsigned long m) {
    if (m == 0) {
        throw invalid_argument("nth_root: m must be positive");
    }
    if (a < 0) {
        throw invalid_argument("nth_root: a must be non-negative");
    }
    if (a == 0 || m == 1) {
        return a;
    }

    size_t bits = mpz_sizeinbase(a.get_mpz_t(), 2);
    mpz_class x = 1;
    x <<= (bits + m - 1) / m;

    while (true) {
        mpz_class p;
        mpz_pow_ui(p.get_mpz_t(), x.get_mpz_t(), m - 1);

        mpz_class y = ((m - 1) * x + a / p) / m;
        if (y >= x) {
            break;
        }
        x = y;
    }

    return x;
}