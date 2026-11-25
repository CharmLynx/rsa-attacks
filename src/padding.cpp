#include "padding.hpp"

#include <stdexcept>

using namespace std;

vector<uint8_t> to_bytes(const mpz_class& x, size_t len) {
    if (x < 0) {
        throw invalid_argument("to_bytes: negative number");
    }

    size_t need = (mpz_sizeinbase(x.get_mpz_t(), 2) + 7) / 8;
    if (need > len) {
        throw invalid_argument("to_bytes: number does not fit in " +
                               to_string(len) + " bytes");
    }

    vector<uint8_t> bytes(len, 0);
    size_t written = 0;
    mpz_export(bytes.data() + (len - need), &written,
               1, 1, 1, 0, x.get_mpz_t());

    return bytes;
}

vector<uint8_t> strip_pkcs1_v15(const vector<uint8_t>& em) {
    vector<uint8_t> data;

    return data;
}

string to_hex(const vector<uint8_t>& bytes) {
    string hex;

    return hex;
}