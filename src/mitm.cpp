#include "mitm.hpp"

#include <map>
#include <stdexcept>

using namespace std;

optional<MitmResult> mitm_attack(const MitmData& data,
                                 unsigned long e,
                                 unsigned int l) {
    return nullopt;
}

optional<mpz_class> brute_force(const MitmData& data,
                                unsigned long e,
                                unsigned int l) {
    mpz_class limit = mpz_class(1) << l;
    mpz_class x;

    for (mpz_class m = 1; m < limit; m++) {
        mpz_powm_ui(x.get_mpz_t(), m.get_mpz_t(), e, data.n.get_mpz_t());
        if (x == data.c) {
            return m;
        }
    }

    return nullopt;
}