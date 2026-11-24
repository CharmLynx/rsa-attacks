#include "hastad.hpp"
#include "crt.hpp"
#include "nth_root.hpp"

#include <stdexcept>
#include <string>

using namespace std;

mpz_class hastad_attack(const BroadcastData& data, unsigned long e) {
    if (data.c.size() < e) {
        throw runtime_error("hastad: need at least e = " + to_string(e) +
                            " ciphertexts, got " + to_string(data.c.size()));
    }
    if (!pairwise_coprime(data.n)) {
        throw runtime_error("hastad: moduli are not pairwise coprime");
    }

    mpz_class c = crt(data.c, data.n);
    mpz_class m = nth_root(c, e);

    mpz_class check;
    mpz_pow_ui(check.get_mpz_t(), m.get_mpz_t(), e);
    if (check != c) {
        throw runtime_error("hastad: root is not exact, attack failed");
    }

    return m;
}